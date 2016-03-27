//
//  Trie.cpp
//  
//  Modified by 罗铮 on 03/24/14.
//
//  http://www.geeksforgeeks.org/trie-insert-and-search/

#include <cstdio>
#include <cstdlib>
#include <cstring>
 
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
 
// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)
// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
 
// trie node
struct trie_node
{
    int value;
    trie_node *children[ALPHABET_SIZE];
};
 
// trie ADT
struct trie
{
    trie_node *root;
    int count;
};
 
// Returns new trie node (initialized to NULLs)
trie_node *newNode(void)
{
    trie_node *pNode = NULL;
 
    pNode = (trie_node *)malloc(sizeof(trie_node));
 
    if( pNode )
    {
        pNode->value = 0;
 
        for(int i = 0; i < ALPHABET_SIZE; i++)
            pNode->children[i] = NULL;
    }
 
    return pNode;
}
 
// Initializes trie (root is dummy node)
void initialize(trie *pTrie)
{
    pTrie->root = newNode();
    pTrie->count = 0;
}
 
// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(trie *pTrie, const char key[])
{
    int length = strlen(key);
    int index;
    trie_node *pCrawl;
 
    pTrie->count++;
    pCrawl = pTrie->root;
 
    for(int level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if(!pCrawl->children[index])
            pCrawl->children[index] = newNode();
 
        pCrawl = pCrawl->children[index];
    }
 
    // mark last node as leaf
    pCrawl->value = pTrie->count;
}
 
// Returns non zero, if key presents in trie
int search(trie *pTrie, const char key[])
{
    int length = strlen(key);
    int index;
    trie_node *pCrawl;
 
    pCrawl = pTrie->root;
 
    for(int level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
 
        if(!pCrawl->children[index])
            return 0;

        pCrawl = pCrawl->children[index];
    }
 
    return (pCrawl != NULL && pCrawl->value);
}
 
// Driver program to test above funtion
int main()
{

    // Input keys (use only 'a' through 'z' and lower case)
    const char keys[][8] = {"the", "a", "there", "answer", "any",
    					    "by", "bye", "their"};

    const char output[][32] = {"Not present in trie", "Present in trie"};
    
    trie trie;
    initialize(&trie);
 
    // Construct trie
    for(size_t i = 0; i < ARRAY_SIZE(keys); i++)
        insert(&trie, keys[i]);
 
    // Search for different keys
    printf("%s --- %s\n", "the", output[search(&trie, "the")] );
    printf("%s --- %s\n", "these", output[search(&trie, "these")] );
    printf("%s --- %s\n", "their", output[search(&trie, "their")] );
    printf("%s --- %s\n", "thaw", output[search(&trie, "thaw")] );
 
    return 0;
}