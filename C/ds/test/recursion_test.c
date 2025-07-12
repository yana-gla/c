#include <stdio.h> /*print*/
#include <stdlib.h> /*malloc*/
#include <assert.h> 
#include <string.h>
#include "recursion.h"

#define GREEN "\x1b[1;32m"
#define RED "\x1b[1;31m"
#define BLUE "\x1b[1;34m"
#define PINK "\x1b[1;35m"
#define UNFORMAT "\x1b[0m"

#define UNDERLINE(text) "\033[4m" text "\033[0m"



typedef size_t (*FibFunc)(int);


void run_test(FibFunc FibonacciIterative,int element_index, size_t expected, int *failed)
{
	size_t result = FibonacciIterative(element_index);
	
	if (result == expected)
	{
		printf("✅ %lu == fibonacci(%d)\n", expected, element_index);
    } else 
    {
        printf("❌ Test failed: fibonacci(%d) → Expected: %lu, Got: %lu\n",
        								 element_index, expected, result);
        ++(*failed);
	}
}

void FibonacciTest(FibFunc FibonacciFunc)
{
	int failed = 0;
	
	run_test(FibonacciFunc,-2, 0, &failed);
	run_test(FibonacciFunc, 0, 0, &failed);
	run_test(FibonacciFunc, 1, 1, &failed);
	run_test(FibonacciFunc, 2, 1, &failed);
	run_test(FibonacciFunc, 5, 5, &failed);
	run_test(FibonacciFunc, 50, 12586269025, &failed);
	
	if (failed == 0) 
	{
		printf("\n🎉 All tests passed successfully!\n");
	}
    else 
    {
    	printf("\n⚠️ %d test(s) failed.\n", failed);
    }
}



/******************************************************************************/


static int TestFlipSingleElement()
{
    int a = 1;
    Node* head = malloc(sizeof(Node));
    Node* flipped = NULL;
    printf(BLUE"\tSTART SINGLE ELEMENT TEST FLIP:\n"UNFORMAT);
    if(!head)
    {
    	printf(RED"\t\tAllocation memory fail!!\n"UNFORMAT);
    	return (1);
    }
    head->data = &a;
    head->next = NULL;
    
    
    flipped = FlipList(head);
    
    if (flipped != head)
    {
        printf(RED"\t\tTestFlipSingleElement failed: expected %p, got %p\n"UNFORMAT, (void*)head, (void*)flipped);
        return (1);
    }
    if (flipped->data != &a)
    {
        printf(RED"\t\tTestFlipSingleElement failed: expected data %d, got %d\n"UNFORMAT, a, *(int*)flipped->data);
        return (1);
    }
    if (flipped->next != NULL)
    {
        printf(RED"\t\tTestFlipSingleElement failed: expected next NULL, got non-NULL\n"UNFORMAT);
        return (1);
    }
    free(head);
    
    return (0);
}

static int TestFlipTwoElements()
{
    int a = 1, b = 2;
    Node* n1 = malloc(sizeof(Node));
    Node* n2 = malloc(sizeof(Node));
    Node* flipped = NULL;
    
    printf(BLUE"\tSTART TWO ELEMENT TEST FLIP:\n"UNFORMAT);
    
    if(!n1 || !n2)
    {
    	printf(RED"\t\tAllocation memory fail!!\n"UNFORMAT);
    	free(n1);
    	free(n2);
    	return (1);
    }
    
    n1->data = &a;
    n1->next = n2;
    n2->data = &b;
    n2->next = NULL;
    
    flipped = FlipList(n1);
    if (flipped != n2)
    {
        printf(RED"\t\tTestFlipTwoElements failed: expected head %p, got %p\n"UNFORMAT, (void*)n2, (void*)flipped);
        return (1);
    }
    if (flipped->data != &b)
    {
        printf(RED"\t\tTestFlipTwoElements failed: expected data %d, got %d\n"UNFORMAT, b, *(int*)flipped->data);
        return (1);
    }
    if (flipped->next != n1)
    {
        printf(RED"\t\tTestFlipTwoElements failed: expected next %p, got %p\n"UNFORMAT, (void*)n1, (void*)flipped->next);
        return (1);
    }
    if (n1->data != &a)
    {
        printf(RED"\t\tTestFlipTwoElements failed: expected data %d, got %d\n"UNFORMAT, a, *(int*)n1->data);
        return (1);
    }
    if (n1->next != NULL)
    {
        printf(RED"\t\tTestFlipTwoElements failed: expected next NULL, got non-NULL\n"UNFORMAT);
        return (1);
    }
    
    free(n1);
    free(n2);
    
    return (0);
}

static int TestFlipSixElements()
{
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
    Node* n1 = malloc(sizeof(Node));
    Node* n2 = malloc(sizeof(Node));
    Node* n3 = malloc(sizeof(Node));
    Node* n4 = malloc(sizeof(Node));
    Node* n5 = malloc(sizeof(Node));
    Node* n6 = malloc(sizeof(Node));
    Node* flipped = NULL;
    
    printf(BLUE"\tSTART SIX ELEMENT TEST FLIP:\n"UNFORMAT);

    if(!n1 || !n2 || !n3 || !n4 || !n5 || !n6)
    {
    	printf(RED"\t\tAllocation memory fail!!\n"UNFORMAT);
    	free(n1);
    	free(n2);
    	free(n3);
    	free(n4);
    	free(n5);
    	free(n6);
    	return (1);
    }
    
    n1->data = &a;
    n1->next = n2;
    n2->data = &b;
    n2->next = n3;
    n3->data = &c;
    n3->next = n4;
    n4->data = &d;
    n4->next = n5;
    n5->data = &e;
    n5->next = n6;
    n6->data = &f;
    n6->next = NULL;
    
    flipped = FlipList(n1);
    if (flipped != n6)
    {
        printf(RED"\t\tTestFlipSixElements failed: expected head %p, got %p\n"UNFORMAT, (void*)n6, (void*)flipped);
        return (1);
    }
    if (flipped->data != &f)
    {
        printf(RED"\t\tTestFlipSixElements failed: expected data %d, got %d\n"UNFORMAT, f, *(int*)flipped->data);
        return (1);
    }
    if (flipped->next != n5)
    {
        printf(RED"\t\tTestFlipSixElements failed: expected next %p, got %p\n"UNFORMAT, (void*)n5, (void*)flipped->next);
        return (1);
    }
    if (n5->next != n4)
    {
        printf(RED"\t\tTestFlipSixElements failed: expected next %p, got %p\n"UNFORMAT, (void*)n4, (void*)n5->next);
        return (1);
    }
    if (n4->next != n3)
    {
        printf(RED"\t\tTestFlipSixElements failed: expected next %p, got %p\n"UNFORMAT, (void*)n3, (void*)n4->next);
        return (1);
    }
    if (n3->next != n2)
    {
        printf(RED"\t\tTestFlipSixElements failed: expected next %p, got %p\n"UNFORMAT, (void*)n2, (void*)n3->next);
        return (1);
    }
    if (n2->next != n1)
    {
        printf(RED"\t\tTestFlipSixElements failed: expected next %p, got %p\n"UNFORMAT, (void*)n1, (void*)n2->next);
        return (1);
    }
    if (n1->next != NULL)
    {
        printf(RED"\t\tTestFlipSixElements failed: expected next NULL, got non-NULL\n"UNFORMAT);
        return (1);
    }
    
    free(n1);
    free(n2);
    free(n3);
    free(n4);
    free(n5);
    free(n6);
    
    return (0);
}

static int TestFlipList()
{
	printf(BLUE"START TEST FLIP:\n"UNFORMAT);
	
    if(TestFlipSingleElement())
    {
    	return (1);
    }
    if(TestFlipTwoElements())
    {
    	return (1);
    }
    if(TestFlipSixElements())
    {
    	return (1);
    }
    
    printf(GREEN"\n\n\t\tALL TESTS FLIP PASSED!\n\n"UNFORMAT);


    return (0);
}


void TestStack()
{
	stack_t *stack = NULL;
	int arr[] = {30, -5, 18, 14, -3};
	int size_of_stack = sizeof(arr)/sizeof(int);
	int expected[] = {30, 18, 14, -3, -5};
	int i = 0;
	
	printf ("Test Stack\n");
	stack = Create(size_of_stack, sizeof(int));
	assert (NULL != stack && "Stack creation failed");
	
	for (i= 0; i < size_of_stack ; ++i)
	{
		Push(stack, &arr[i]);	
	}
	SortStack(stack);
	
	for (i= 0; i < size_of_stack ; ++i)
	{
		if (expected[i] == *(int*)Peek(stack) )
		{
			printf("✅ %d\n", *(int*)Peek(stack));
		}
		else
		{
			printf("❌ %d\n",*(int*)Peek(stack) );
		}
		
		Pop(stack);	
	}
	Destroy(stack);
}

void TestStrLen(void)
{
	char *str1 = "";
	char *str2 = "abc";
	
	if (Strlen(str1) == 0)
	{
		printf("Empty string ✅ \n");
	}
	else
	{
		printf("Empty string ❌\n");
	}
	
	if (Strlen(str2) == 3)
	{
		printf("String abc ✅ \n");
	}
	else
	{
		printf("Srtring abc ❌\n");
	}
	
	
}



void TestStrcmp()
{
	char *str10 = "", *str11 = "";
	char *str20 = "a";
	char *str30 = "ab", *str31 = "abc";
	
	if (0 == Strcmp(str10, str11))
	{
		printf("Strcmp 1 is  ✅ \n");
	}
	else
	{
		printf("Strcmp 1 is ❌\n");
	}
	/*******************************/
	if (0 == Strcmp(str20, str20))
	{
		printf("Strcmp 2 is  ✅ \n");
	}
	else
	{
		printf("Strcmp 2 is ❌\n");
	}
	/*******************************/
	if (0 > Strcmp(str30, str31))
	{
		printf("Strcmp 3 is  ✅ \n");
	}
	else
	{
		printf("Strcmp 3 is ❌\n");
	}
	/*******************************/
	if (0 < Strcmp(str31, str30))
	{
		printf("Strcmp 4 is  ✅ \n");
	}
	else
	{
		printf("Strcmp 4 is ❌\n");
	}
	/*******************************/
	if (0 > Strcmp(str20, str30))
	{
		printf("Strcmp 5 is ✅ \n");
	}
	else
	{
		printf("Strcmp 5 is ❌\n");
	}
	/*******************************/
	if (0 < Strcmp(str30, str20))
	{
		printf("Strcmp 6 is  ✅ \n");
	}
	else
	{
		printf("Strcmp 6 is ❌\n");
	}
}

void TestStrcpy()
{
	char dest1[2] = "1", dest2[3]= "";
	char *src1 = "", *src2 = "ab";
	printf("Should be . : %s.\n", Strcpy(dest1, src1));
	printf("Should be ab : %s\n", Strcpy(dest2, src2));
}

void TestStrcat()
{
	char dest1[6] = "ab", *src1 = "cde", *src2 = "ab";
	char dest2[3] = "", dest3[3] = "";
	
	printf("Should be abcde: %s\n", Strcat(dest1, src1));
	printf("Should be cde: %s\n", Strcat(dest2, src1));
	printf("Should be ab: %s\n", Strcat(dest3, src2));
	
	
/*	printf("Should be ab: %s\n", strcat(dest3, src2));*/
	
}

void TestStrstr()
{
	char *hay1 = "abcd", *need1 = "bc";
	char *hay2 = "abcd", *need2 = "";
	char *hay3 = "abcd", *need3 = "f";
	
	
	printf ("Should be bcd: %s\n", Strstr(hay1, need1));
	printf ("Shold be abcd %s\n", Strstr(hay2, need2));
	printf ("should be 1: %d\n",  (NULL == Strstr(hay3, need3)));
}


int main(void)
{
	printf("start test fibonaci iterative\n");
	FibonacciTest(FibonacciIterative);
	printf("\n");
	
	printf("start test fibonaci recursive\n");
	FibonacciTest(FibonacciRecrusive);
	printf("\n");
	
	TestFlipList();
	printf("\n");
	
	TestStack();
	printf("\n");
	
	printf("Start test Strings-------------------------\n");
    printf(UNDERLINE("Strlen:\n"));

	TestStrLen();
	printf("\n");
	
    printf(UNDERLINE("Strcmp:\n"));
	TestStrcmp();
	printf("\n");
	
	printf(UNDERLINE("Strcpy:\n"));
	TestStrcpy();
	printf("\n");
	
	printf(UNDERLINE("Strcat:\n"));
	TestStrcat();
	printf("\n");

	printf(UNDERLINE("Strstr:\n"));
	TestStrstr();
	printf("\n");

	printf("\n🎉End of test!\n");
	
	return 0;
}







