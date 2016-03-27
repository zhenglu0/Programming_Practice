//
//    Simplex.cpp
//    
//    AUTHOR: GPL(C) moshahmed@gmail.com.
//    Modified by 罗铮 on 03/14/14.
//    http://stackoverflow.com/questions/3956950/
//    c-c-implementation-of-simplex-method

/*

What: Solves LP Problem with Simplex:
    { maximize cx : Ax <= b, x >= 0 }.

Input: { m, n, Mat[m x n] }, where:
    b = mat[1..m,0] .. column 0 is b >= 0, so x=0 is a basic feasible solution.
    c = mat[0,1..n] .. row 0 is z to maximize, note c is negated in input.
    A = mat[1..m,1..n] .. constraints.
    x = [x1..xm] are the named variables in the problem.
    Slack variables are in columns [m+1..m+n]

USAGE:
    1. Problem can be specified before main function in source code:
        c:\> vim mosplex.c    
        Tableau tab    = { m, n, {     // tableau size, row x columns.
                {    0 , -c1, -c2,    },    // Max: z = c1 x1 + c2 x2,
                { b1 , a11, a12,    },    //    b1 >= a11 x1 + a12 x2
                { b2 , a21, a22,    },    //    b2 >= a21 x1 + a22 x2
            }
        };
        c:\> cl /W4 mosplex.c    ... compile this file.
        c:\> mosplex.exe problem.txt > solution.txt

    2. OR Read the problem data from a file:
        $ cat problem.txt
                    m n
                    0    -c1 -c2
                    b1 a11 a12
                    b2 a21 a11 
        $ gcc -Wall -g mosplex.c    -o mosplex
        $ mosplex problem.txt > solution.txt
*/

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>

#define M 20
#define N 20

static const double epsilon     = 1.0e-8;

int equal(double a, double b) 
{ 
    return fabs(a-b) < epsilon; 
}

typedef struct {
    int m, n; // m=rows, n=columns, mat[m x n]
    double mat[M][N];
} Tableau;

void nl(int k)
{
    for(int j = 0; j < k; j++) 
        putchar('-'); 

    putchar('\n'); 
}

void print_tableau(Tableau *tab, const char* mes)
{
    static int counter=0;
    printf("\n%d. Tableau %s:\n", ++counter, mes);
    nl(70);

    printf("%-6s%5s", "col:", "b[i]");

    for(int j = 1; j < tab->n; j++)
        printf("%6s%d", "x",j); 
    printf("\n");

    for(int i = 0; i<tab->m; i++) {
        if (i == 0) 
            printf("max:"); 
        else
            printf("b%d: ", i);
        
        for(int j = 0; j < tab->n; j++) {
            if (equal((int)tab->mat[i][j], tab->mat[i][j]))
                printf("%7d", (int)tab->mat[i][j]);
            else
                printf("%7.2lf", tab->mat[i][j]);
        }
        printf("\n");
    }
    nl(70);
}

/* Example input file for read_tableau:
     4 5
      0   -0.5  -3 -1  -4 
     40    1     1  1   1 
     10   -2    -1  1   1 
     10    0     1  0  -1   
*/

void read_tableau(Tableau *tab, const char * filename)
{
    int err;
    FILE * fp;

    fp    = fopen(filename, "r" );
    if( !fp ) {
        printf("Cannot read %s\n", filename); 
        exit(1);
    }

    memset(tab, 0, sizeof(*tab));
    err = fscanf(fp, "%d %d", &tab->m, &tab->n);
    
    if (err == 0 || err == EOF)
        printf("Cannot read m or n\n"); exit(1);
    
    for(int i = 0; i < tab->m; i++) {
        for(int j = 0; j < tab->n; j++) {
            err = fscanf(fp, "%lf", &tab->mat[i][j]);
            if (err == 0 || err == EOF) {
                printf("Cannot read A[%d][%d]\n", i, j); exit(1);
            }
        }
    }

    printf("Read tableau [%d rows x %d columns] from file '%s'.\n",
            tab->m, tab->n, filename);
    
    fclose(fp);
}

void pivot_on(Tableau *tab, int row, int col)
{
    double pivot;

    pivot = tab->mat[row][col];
    assert(pivot > 0);

    for(int j = 0; j < tab->n; j++)
        tab->mat[row][j] /= pivot;

    assert( equal(tab->mat[row][col], 1. ));

    for(int i = 0; i < tab->m; i++) { 
        // foreach remaining row i do
        double multiplier = tab->mat[i][col];
        if(i == row)
            continue;
        // r[i] = r[i] - z * r[row];
        for(int j = 0; j < tab->n; j++)
            tab->mat[i][j] -= multiplier * tab->mat[row][j];
    }
}

// Find pivot_col = most negative column in mat[0][1..n]
int find_pivot_column(Tableau *tab) 
{
    int pivot_col = 1;
    double lowest = tab->mat[0][pivot_col];
    
    for(int j = 1; j < tab->n; j++) {
        if (tab->mat[0][j] < lowest) {
            lowest = tab->mat[0][j];
            pivot_col = j;
        }
    }

    printf("Most negative column in row[0] is col %d = %g.\n", pivot_col, lowest);
    // All positive columns in row[0], this is optimal.
    if( lowest >= 0 )
        return -1; 

    return pivot_col;
}

// Find the pivot_row, with smallest positive ratio = col[0] / col[pivot]
int find_pivot_row(Tableau *tab, int pivot_col) 
{
    int pivot_row = 0;
    double min_ratio = -1;
    printf("Ratios A[row_i,0]/A[row_i,%d] = [",pivot_col);

    for(int i = 1;i < tab->m; i++) {
        double ratio = tab->mat[i][0] / tab->mat[i][pivot_col];
        printf("%3.2lf, ", ratio);
        if ( (ratio > 0  && ratio < min_ratio ) || 
              min_ratio < 0 ) {
            min_ratio = ratio;
            pivot_row = i;
        }
    }
    printf("].\n");

    if (min_ratio == -1)
        return -1; // Unbounded.

    printf("Found pivot A[%d,%d], min positive ratio=%g in row=%d.\n",
            pivot_row, pivot_col, min_ratio, pivot_row);
    
    return pivot_row;
}

void add_slack_variables(Tableau *tab) 
{
    for(int i = 1; i < tab->m; i++)
        for(int j = 1; j < tab->m; j++)
            tab->mat[i][j + tab->n -1] = (i==j);

    tab->n += tab->m -1;
}

void check_b_positive(Tableau *tab) {
    for(int i = 1; i < tab->m; i++)
        assert(tab->mat[i][0] >= 0);
}

// Given a column of identity matrix, find the row containing 1.
// return -1, if the column as not from an identity matrix.
int find_basis_variable(Tableau *tab, int col) {
    int xi = -1;
    
    for(int i = 1; i < tab->m; i++) {
        if (equal( tab->mat[i][col],1) ) {
            if (xi == -1)
                xi = i;     // found first '1', save this row number.
            else
                return -1; // found second '1', not an identity matrix.

        } else if (!equal( tab->mat[i][col],0) )
            return -1; // not an identity matrix column.
    }

    return xi;
}

void print_optimal_vector(Tableau *tab, const char *message) 
{
    int xi;
    printf("%s at ", message);
    
    // for each column.
    for(int j = 1; j < tab->n; j++) {
        xi = find_basis_variable(tab, j);
        if (xi != -1)
            printf("x%d=%3.2lf, ", j, tab->mat[xi][0] );
        else
            printf("x%d=0, ", j);
    }
    printf("\n");
} 

void simplex(Tableau *tab)
{
    int loop = 0;

    add_slack_variables(tab);
    check_b_positive(tab);
    print_tableau(tab,"Padded with slack variables");

    while( ++loop ) {
        int pivot_col, pivot_row;

        pivot_col = find_pivot_column(tab);
        if( pivot_col < 0 ) {
            printf("Found optimal value=A[0,0]=%3.2lf (no negatives in row 0).\n",
                tab->mat[0][0]);
            print_optimal_vector(tab, "Optimal vector");
            break;
        }
        printf("Entering variable x%d to be made basic, so pivot_col=%d.\n",
            pivot_col, pivot_col);

        pivot_row = find_pivot_row(tab, pivot_col);
        if (pivot_row < 0) {
            printf("unbounded (no pivot_row).\n");
            break;
        }
        printf("Leaving variable x%d, so pivot_row=%d\n", pivot_row, pivot_row);

        pivot_on(tab, pivot_row, pivot_col);
        print_tableau(tab,"After pivoting");
        print_optimal_vector(tab, "Basic feasible solution");

        // Just an example here
        if(loop > 20) {
            printf("Too many iterations > %d.\n", loop);
            break;
        }
    }
}

Tableau tab  = { 4, 5, {              // Size of tableau [4 rows x 5 columns ]
    {  0.0 , -0.5 , -3.0 ,-1.0 , -4.0,   },  // Max: z = 0.5*x + 3*y + z + 4*w,
    { 40.0 ,  1.0 ,  1.0 , 1.0 ,  1.0,   },  //    x + y + z + w <= 40 .. b1
    { 10.0 , -2.0 , -1.0 , 1.0 ,  1.0,   },  //  -2x - y + z + w <= 10 .. b2
    { 10.0 ,  0.0 ,  1.0 , 0.0 , -1.0,   },  //        y     - w <= 10 .. b3
    }
};

int main(int argc, char *argv[])
{
    // usage: cmd datafile
    if (argc > 1) 
        read_tableau(&tab, argv[1]);

    print_tableau(&tab,"Initial");
    simplex(&tab);

    return 0;
} 