/*
*	Writer : Ofir Hasson
*	Implementation of Hash Table
*	data structure that stores elements by key - value pairs.
*	every value has unique key.
*	every bucket is doubly linked list for chaining.
*
*	Reviewed by: 
*	Reviewed date:
*/


#include <stdio.h> /* For printf */
#include <assert.h> /* For assert */
#include <string.h> /* strcmp */
#include <stdlib.h> /* malloc */

#include "hash_table.h"

#define GREEN "\x1b[1;32m"
#define RED "\x1b[1;31m"
#define BLUE "\x1b[1;34m"
#define UNFORMAT "\x1b[1;0m"

#define DICT_PATH "/usr/share/dict/words"
#define MAX_WORD_LEN 128
#define SIZE 10

static int result = 0;

/*static void TestSpellChecker();*/
/*static void SpellChecker(char* str);*/
/*static int SpellCheckerInsert(ht_table_t* tbl);*/
/*static void SpellCheckerFind(ht_table_t* tbl, char* str);*/
/*static int FreeWords(void* value, void* params);*/
/*static size_t DictHashFunc(const void* key);*/
/*static int DictMatchFunc(const void* key1, const void* key2);*/

static void TestCreateAndDestroy();
static void TestInsertAndCount();
static void TestRemoveAndIsEmpty();
static void TestFind();
static void TestForEach();

static int MatchFunc(const void* key1, const void* key2);
static size_t HashFunc(const void* key);
static int Add(void* value, void* param);

int main(void)
{
	printf("Beginning hash_table.c tests...\n\n");
	
	TestCreateAndDestroy();
	TestInsertAndCount();
	TestRemoveAndIsEmpty();
	TestFind();
	TestForEach();
	
	printf("\nAll tests completed successfully");
	
	if(0 == result)
	{
		printf(GREEN "\tPASSED!\n" UNFORMAT);
	}
	else
	{
		printf(RED "\tFAILED!\n" UNFORMAT);
	}
	
/*	TestSpellChecker();*/
	return (0);
}

static void TestCreateAndDestroy()
{
    ht_table_t* tbl = HTCreate(MatchFunc, HashFunc, 5);
    
	printf(BLUE "\n Create and destroy test:\n" UNFORMAT);
	
	if(NULL == tbl)
	{
		++result;
		printf(RED "\t Create Failed ! \n" UNFORMAT);
	}
   	
   	HTDestroy(tbl);
   	printf(BLUE "\t Check valgrind for destroy!\n" UNFORMAT);
   	
}

static void TestInsertAndCount()
{
    size_t i = 0;
    int values[] = {1,2,3,4,5,15,14,26,34,7};
    
    ht_table_t* tbl = HTCreate(MatchFunc, HashFunc, 5);
	if(NULL == tbl)
	{
		++result;
		printf(RED "\t Create Failed ! \n" UNFORMAT);
	}
	
    printf(BLUE "\n Insert and Count test:\n" UNFORMAT);

    for (i = 0; i < SIZE; ++i)
    {
        if (0 != HTInsert(tbl, &values[i], &values[i]))
        {
        	++result;
            printf(RED "\tInsert Failed : expected return 0 but got non-zero\n"UNFORMAT);
        }
    }
	
	if(SIZE != HTCount(tbl))
	{
		++result;
		printf(RED "\tInsert Failed : Expected count %d, but got %lu! \n" UNFORMAT, SIZE, HTCount(tbl));
	}
   	
   	HTDestroy(tbl);
}

static void TestRemoveAndIsEmpty()
{
    size_t i = 0;
    int values[] = {1,2,3,4,5,15,14,26,34,7};
    
    ht_table_t* tbl = HTCreate(MatchFunc, HashFunc, 5);
	if(NULL == tbl)
	{
		++result;
		printf(RED "\t Create Failed ! \n" UNFORMAT);
	}
	
    printf(BLUE "\n Remove and IsEmpty test:\n" UNFORMAT);
    
    if(1 != HTIsEmpty(tbl))
    {
    	++result;
    	printf(RED "\tIsEmpty Failed : expected return 1 but got %d\n"UNFORMAT, HTIsEmpty(tbl));
    }

    for (i = 0; i < SIZE; ++i)
    {
        if (0 != HTInsert(tbl, &values[i], &values[i]))
        {
        	++result;
            printf(RED "\tInsert Failed : expected return 0 but got non-zero\n"UNFORMAT);
        }
    }
    
    if(0 != HTIsEmpty(tbl))
    {
    	++result;
    	printf(RED "\tIsEmpty Failed : expected return 0 but got %d\n"UNFORMAT, HTIsEmpty(tbl));
    }
    
    for (i = 0; i < SIZE; ++i)
    {
       HTRemove(tbl, &values[i]);
    }
    
    /* remove from empty hash table */
    HTRemove(tbl, &values[0]);
    
    if(1 != HTIsEmpty(tbl))
    {
    	++result;
    	printf(RED "\tIsEmpty Failed : expected return 1 but got %d\n"UNFORMAT, HTIsEmpty(tbl));
    }
   	
   	HTDestroy(tbl);
}

static void TestFind()
{
    size_t i = 0;
    int values[] = {1,2,3,4,5,15,14,26,34,7};
    int tmp = 80;
    
    ht_table_t* tbl = HTCreate(MatchFunc, HashFunc, 5);
	if(NULL == tbl)
	{
		++result;
		printf(RED "\t Create Failed ! \n" UNFORMAT);
	}
	
    printf(BLUE "\n Find test:\n" UNFORMAT);

    for (i = 0; i < SIZE; ++i)
    {
        if (0 != HTInsert(tbl, &values[i], &values[i]))
        {
        	++result;
            printf(RED "\tInsert Failed : expected return 0 but got non-zero\n"UNFORMAT);
        }
    }
    
    if(values[0] != *(int*)HTFind(tbl, &values[0]))
    {
    	++result;
       	printf(RED "\tFind Failed : expected return %d but got %d\n"UNFORMAT, values[0], *(int*)HTFind(tbl, &values[0]));
    }
    
    if(values[5] != *(int*)HTFind(tbl, &values[5]))
    {
    	++result;
       	printf(RED "\tFind Failed : expected return %d but got %d\n"UNFORMAT, values[5], *(int*)HTFind(tbl, &values[5]));
    }
    
    if(values[SIZE-1] != *(int*)HTFind(tbl, &values[SIZE-1]))
    {
    	++result;
       	printf(RED "\tFind Failed : expected return %d but got %d\n"UNFORMAT, values[SIZE-1], *(int*)HTFind(tbl, &values[SIZE-1]));
    }
    
    if(NULL != HTFind(tbl, &tmp))
    {
    	++result;
       	printf(RED "\tFind Failed : expected return NULL but got %d\n"UNFORMAT, *(int*)HTFind(tbl, &tmp));
    }
   	
   	HTDestroy(tbl);
}

static void TestForEach()
{
    size_t i = 0;
    int values[] = {1,2,3,4,5,15,14,26,34,7};
    int add = 10;
    
    ht_table_t* tbl = HTCreate(MatchFunc, HashFunc, 5);
	if(NULL == tbl)
	{
		++result;
		printf(RED "\t Create Failed ! \n" UNFORMAT);
	}
	
    printf(BLUE "\n ForEach test:\n" UNFORMAT);

    for (i = 0; i < SIZE; ++i)
    {
        if (0 != HTInsert(tbl, &values[i], &values[i]))
        {
        	++result;
            printf(RED "\tInsert Failed : expected return 0 but got non-zero\n"UNFORMAT);
        }
    }
    
   	HTForEach(tbl, Add, &add);
   	
   	if(values[0] != 11)
    {
    	++result;
       	printf(RED "\tFind Failed : expected return 11 but got %d\n"UNFORMAT,values[0]);
    }
    
    if(values[5] != 25)
    {
    	++result;
       	printf(RED "\tFind Failed : expected return 25 but got %d\n"UNFORMAT,values[5]);
    }
    
    if(values[SIZE-1] != 17)
    {
    	++result;
       	printf(RED "\tFind Failed : expected return 17 but got %d\n"UNFORMAT,values[SIZE-1]);
    }
   	
   	HTDestroy(tbl);
}

static int MatchFunc(const void* key1, const void* key2)
{
    return (*(int*) key1 == *(int*) key2);
}

static size_t HashFunc(const void* key)
{
    return (*(int*) key);
}

static int Add(void* value, void* param)
{
    *(int*)value += *(int*)param;
    return (0);
}

/*------------Spell Checker---------------------------------*/
/*
static void TestSpellChecker()
{
	char str[MAX_WORD_LEN];
	
	printf("Enter String:\n");
	scanf("%s",str);
	
	SpellChecker(str);
}

static void SpellChecker(char* str)
{
    ht_table_t* tbl = NULL;
    
    tbl = HTCreate(DictMatchFunc, DictHashFunc, 256);
    if (NULL == tbl)
    {
        printf("Error memory allocation\n");
        return;
    }
    
    if(1 != SpellCheckerInsert(tbl))
    {
    	SpellCheckerFind(tbl,str);
    }
	
	HTForEach(tbl, FreeWords, NULL);
	HTDestroy(tbl);
 
    return;
}

static int SpellCheckerInsert(ht_table_t* tbl)
{
	char word[MAX_WORD_LEN];

	FILE *file = fopen(DICT_PATH, "r");
    if (NULL == file)
    {
        printf("Error opening file\n");
        return (1);
    }
    
    while (NULL != fgets(word, MAX_WORD_LEN, file))
    {
    	size_t len = strlen(word);
    	
    	char* word_copy = (char*)malloc(len + 1);
    	if(NULL == word_copy)
    	{
    		printf("Error memory allocation\n");
    		fclose(file);
    		return (1);
    	}
    	
    	if (len > 0 && word[len-1] == '\n') 
    	{
        	word[len-1] = '\0';
    	}
    	
    	strcpy(word_copy,word);

	    if(0 != HTInsert(tbl, word_copy, word_copy))
	    {
	    	printf("Insertion Failed\n");
    		fclose(file);
    		return (1);
	    }
    }
    
    fclose(file);
    
    return (0);
}

static void SpellCheckerFind(ht_table_t* tbl, char* str)
{
	char* found_str = (char*)HTFind(tbl, str);
    
    if(NULL != found_str)
    {
    	printf("%s - In the dictionary!\n", str);
    }
    else
    {
    	printf("%s - Not In the dictionary!\n", str);
    }
}

static int FreeWords(void* value, void* params)
{
	free (value);
	(void) params;
	return (0);
}

static size_t DictHashFunc(const void* key)
{
	return ((size_t)*(char*)key);
}

static int DictMatchFunc(const void* key1, const void* key2)
{
	return (0 == strcmp((char*)key1, (char*)key2));
}


*/










