//
//  BalancedParentheses.cpp
//
//  Modified by 罗铮 on 03/26/14.
//  http://www.geeksforgeeks.org/
//  check-for-balanced-parentheses-in-an-expression/

#include <cstdio>
#include <cstdlib>
 
/* structure of a stack node */
struct sNode
{
    char data;
    struct sNode *next;
};
 
/* Function to push an item to stack*/
void push(struct sNode** top_ref, int new_data);
 
/* Function to pop an item from stack*/
int pop(struct sNode** top_ref);
 
/* Returns 1 if character1 and character2 are matching left
   and right Parenthesis */
bool isMatchingPair(char character1, char character2)
{
    if(character1 == '(' &&
       character2 == ')')
        return true;
    else if(character1 == '{' &&
            character2 == '}')
        return true;
    else if(character1 == '[' &&
            character2 == ']')
        return true;
    else
        return false;
}
 
/*Return 1 if expression has balanced Parenthesis */
bool DifferentParenthesBalanced(char exp[])
{
    int i = 0;
    /* Declare an empty character stack */
    struct sNode *stack = NULL;

    /* Traverse the given expression to check matching parenthesis */
    while(exp[i])
    {
        /*If the exp[i] is a starting parenthesis then push it*/
        if(exp[i] == '{' ||
           exp[i] == '(' || 
           exp[i] == '[')
            push(&stack, exp[i]);

        /* If exp[i] is a ending parenthesis then pop from stack and 
            check if the popped parenthesis is a matching pair*/
        if(exp[i] == '}' ||
           exp[i] == ')' ||
           exp[i] == ']')
        {
            /*If we see an ending parenthesis without a pair then 
              return false*/
            if(stack == NULL)
                return false; 

            /* Pop the top element from stack, if it is not a pair 
            parenthesis of character then there is a mismatch.
            This happens for expressions like {(}) */
            else if ( !isMatchingPair(pop(&stack), exp[i]) )
                return false;
        }
        i++;
    }

    /* If there is something left in expression then there is a starting
       parenthesis without a closing parenthesis */
    if(stack == NULL)
        return true;  /*balanced*/
    else
        return false; /*not balanced*/
} 
 
/* UTILITY FUNCTIONS */ 
/* Function to push an item to stack*/
void push(struct sNode** top_ref, int new_data)
{
    /* allocate node */
    struct sNode* new_node =
              (struct sNode*) malloc(sizeof(struct sNode));

    if(new_node == NULL)
    {
        printf("Stack overflow \n");
        getchar();
        exit(0);
    }           

    /* put in the data  */
    new_node->data  = new_data;

    /* link the old list off the new node */
    new_node->next = (*top_ref);  

    /* move the head to point to the new node */
    (*top_ref)    = new_node;
}
 
/* Function to pop an item from stack*/
int pop(struct sNode** top_ref)
{
    char res;
    struct sNode *top;

    /*If stack is empty then error */
    if(*top_ref == NULL)
    {
        printf("Stack overflow \n");
        getchar();
        exit(0);
    }
    else
    {
        top = *top_ref;
        res = top->data;
        *top_ref = top->next;
        free(top);
        return res;
    }
}

// A simplified version
bool SameParenthesBalanced(const char *exp)
{
    int left = 0, right = 0, i = 0;
    while (exp[i] != '\0') 
    {
        if (exp[i] == '(')
            left++;
        if (exp[i] == ')')
            right++;
        
        if (right > left)
            return false;
        i++;
    }
    return (left == right) ? true : false;
}

/*driver program to test above functions*/
int main()
{
    char exp[100] = "{(y)y}[luozheng]";
    const char* exp2 = "{()()()((009)())";

    if(DifferentParenthesBalanced(exp))
        printf("Balanced \n");
    else
        printf("Not Balanced \n");

    if(SameParenthesBalanced(exp2))
        printf("Balanced \n");
    else
        printf("Not Balanced \n");

    return 0;
}   