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

#define DICTIONARY "/usr/share/dict/words"
#define LONGEST_WORD 50 /*45 = pneumonoultramicroscopicsilicovolcanoconiosis*/
#define SIZE 10
#define DICT_HT_SIZE 1000

static int result = 0;

static size_t HashDict(const void *string);
static int MatchDict(const void *key1, const void *key2);
static int LoadDict(ht_table_t *ht_dict);
static int FreeWord(void *word, void * params);
static void SpellCheckerWrpr(char *word);
static void SpellChecker(ht_table_t* ht_dict, char *word);
static void TestSpellChecker();

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
	
	TestSpellChecker();
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

/******************************** Spell Checker *******************************/
static size_t HashDict(const void *string) /*djb2 algo from http://www.cse.yorku.ca/~oz/hash.html*/
{
    size_t hash = 5381;
    char *runner = (char*)string;
	char asci_num = 0;
	
    while ('\0' != *runner)
    {
    	asci_num = *runner;
    	hash = ((hash << 5) + hash) + asci_num; /* hash * 33 + c */
    	++runner;
    } 
    return hash;   
}
/*the magic of number 33 (why it works better than many other constants,
     prime or not) has never been adequately explained */


static int MatchDict(const void *key1, const void *key2)
{
	return (0 == strcmp((char*)key1, (char*)key2));
}

static int LoadDict(ht_table_t *ht_dict)
{
	FILE *dictionary = NULL;
	char buff_word[LONGEST_WORD] = "";
	char *hash_word = NULL;
	int status = 0;
	
	dictionary = fopen(DICTIONARY, "r");
	if (NULL == dictionary)
	{
		printf("Error opening file\n");
		return 1;
	}
	
	while (NULL != fgets(buff_word, LONGEST_WORD, dictionary))
	{
		size_t len = strlen(buff_word);
	
    	/*replace ending new line with null terminator*/
    	if (len > 0 && '\n' == buff_word[len-1])
    	{
    		buff_word[len-1] = '\0';
    	}
    	len = strlen(buff_word);
    	
    	hash_word = (char*)malloc(len + 1);
		if(NULL == hash_word)
    	{
    		printf("Error malloc\n");
    		fclose(dictionary);
    		return 1;
    	}
    	
    	/*copy to hash_word*/
    	strcpy(hash_word, buff_word);
		status =  HTInsert(ht_dict, hash_word, hash_word);
		
		if (0 != status)
		{
			printf("Failed Hash Insertion\n");
			fclose(dictionary);
			free(hash_word);
			
			return 1;
		}
	}
	
	fclose(dictionary);
	
	return 0;
}

static int FreeWord(void *word, void * params)
{
	free(word);
	
	(void)params;
	
	return 0;
}

static void SpellCheckerWrpr(char *word)
{
	/*create hash dict*/
	ht_table_t *ht_dict = HTCreate(MatchDict, HashDict, DICT_HT_SIZE);
	if (NULL == ht_dict)
    {
        printf("Error HTCreate\n");
        return;
    }
    
    /*init hash dict*/
    if(1 != LoadDict(ht_dict))
    {
    	SpellChecker(ht_dict, word);
    }
    
    /*free words*/
    HTForEach(ht_dict, FreeWord, NULL);
	HTDestroy(ht_dict);
}


static void SpellChecker(ht_table_t* ht_dict, char *word)
{
	void *result = NULL;
	
	result = HTFind(ht_dict, word);
	
	if (NULL == result)
	{
		printf("Word is *not* in the dictionary.\n");
	}
	else 
	{
		printf("Word is in the dictionary.\n");
	}
}

static void TestSpellChecker()
{
	char str[LONGEST_WORD];
	
	printf("Enter String:\n");
	scanf("%s",str);
	
	SpellCheckerWrpr(str);
}










