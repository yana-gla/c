#include <stddef.h> /*NULL*/
#include <stdio.h> /*printf*/
#include <stdlib.h> /*malloc*/
/*#include <assert.h> */

#define GREEN "\x1b[1;32m"
#define RED "\x1b[1;31m"
#define BLUE "\x1b[1;34m"
#define PINK "\x1b[1;35m"
#define UNFORMAT "\x1b[0m"


static int TestFlip();
static int TestFlipSingleElement();
static int TestFlipTwoElements();
static int TestFlipSixElements();

static int TestHasLoop();
static int TestHasLoopSixElementsWithLoop();
static int TestHasLoopSixElementsWithoutLoop();
static int TestHasLoopTwoElementsWithLoop();
static int TestHasLoopTwoElementsWithLoop2();
static int TestHasLoopTwoElementsWithoutLoop();
static int TestHasLoopSingleElementWithLoop();
static int TestHasLoopSingleElementWithoutLoop();

static int TestFindIntersection();
static int TestFindIntersectionSixAndThreeWithIntersection();
static int TestFindIntersectionSixAndThreeWithoutIntersection();
static int TestFindIntersectionTwoAndTwoWithIntersection();
static int TestFindIntersectionTwoAndTwoWithoutIntersection();
static int TestFindIntersectionSingleElementWithIntersection();
static int TestFindIntersectionSingleElementWithoutIntersection();

 
typedef struct node
{
	void *data;
	struct node *next;
}node_t;

/******************************************************************************/
/*Revers the order of a given slist*/
node_t *Flip(node_t *head)
{
	
	node_t *prev = NULL;
	node_t *curr = head;
	node_t *next = head->next;
	
	head->next = prev;
	
	while (NULL != next)
	{
		prev = curr;
		curr = next;
		next = curr->next;
		curr->next = prev;
	}
	
	return curr;
}


/******************************************************************************/
/*Tells whether a given slist has a loop
 slow pointer- advance one position, fast pointer- advance two position
 starting position- slow=head, fast= head->next
 if linked list has a loop, they will meet (equal)
 x + (1-2) in every loop the gap closing by -1.
 if fast pointer reaches NULL there isn't a loop                              */
int HasLoop(const node_t *head)
{
	const node_t *slow = head, *fast = head->next;
	
	while ((slow != fast) && (NULL != fast) && (NULL != fast->next))
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	
	return (slow == fast);
}


/******************************************************************************/
/*Returns a pointer to a first node mutual to both slists, if any. 
 Travers 2 lists simultaneously.
 When one pointer reaches the end of its list, it is reassigned to the head of
 the other list. if they have intersection point they will meet, if not they
 will meet at null*/
 
node_t *FindIntersection(node_t *head_1, node_t *head_2)
{
	node_t *ptr1 = head_1;
	node_t *ptr2 = head_2;
	/*
	if(NULL == head_1 || NULL == head_2)
	{
		return NULL;
	}
	*/
	
	
	while (ptr1 != ptr2)
	{
		ptr1 = (ptr1 == NULL) ? head_2:  ptr1->next;
		ptr2 = (ptr2 == NULL) ? head_1 : ptr2->next;
	}
	
	/*return intersection point or null*/
	return ptr1;
}
/******************************************************************************/



int main (void)
{
	 if(TestFlip())
    {
    	return (1);
    }
	
	 if(TestHasLoop())
    {
    	return (1);
    }
     if(TestFindIntersection())
    {
    	return (1);
    }
    printf(GREEN"\n\n\t\tALL TESTS PASSED!\n\n"UNFORMAT);
	
	return 0;

}



/*------------------------------TestFlip--------------------------------------*/
static int TestFlip()
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

static int TestFlipSingleElement()
{
    int a = 1;
    node_t* head = malloc(sizeof(node_t));
    node_t* flipped = NULL;
    printf(BLUE"\tSTART SINGLE ELEMENT TEST FLIP:\n"UNFORMAT);
    if(!head)
    {
    	printf(RED"\t\tAllocation memory fail!!\n"UNFORMAT);
    	return (1);
    }
    head->data = &a;
    head->next = NULL;
    
    
    flipped = Flip(head);
    
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
    node_t* n1 = malloc(sizeof(node_t));
    node_t* n2 = malloc(sizeof(node_t));
    node_t* flipped = NULL;
    
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
    
    flipped = Flip(n1);
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
    node_t* n1 = malloc(sizeof(node_t));
    node_t* n2 = malloc(sizeof(node_t));
    node_t* n3 = malloc(sizeof(node_t));
    node_t* n4 = malloc(sizeof(node_t));
    node_t* n5 = malloc(sizeof(node_t));
    node_t* n6 = malloc(sizeof(node_t));
    node_t* flipped = NULL;
    
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
    
    flipped = Flip(n1);
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



/*------------------------------TestHasLoop-----------------------------------*/

static int TestHasLoop()
{
	printf(BLUE"START TEST HAS LOOP:\n"UNFORMAT);
    if(TestHasLoopSixElementsWithLoop())
    {
    	return (1);
    }
    if(TestHasLoopSixElementsWithoutLoop())
    {
    	return (1);
    }
    if(TestHasLoopTwoElementsWithLoop())
    {
    	return (1);
    }
    if(TestHasLoopTwoElementsWithLoop2())
    {
    	return (1);
    }
    if(TestHasLoopTwoElementsWithoutLoop())
    {
    	return (1);
    }
    if(TestHasLoopSingleElementWithLoop())
    {
    	return (1);
    }
    if(TestHasLoopSingleElementWithoutLoop())
    {
    	return (1);
    }
    printf(GREEN"\n\n\t\tALL TESTS LOOP PASSED!\n\n"UNFORMAT);
    
    return (0);
}

static int TestHasLoopSixElementsWithLoop()
{
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
    node_t* n1 = malloc(sizeof(node_t));
    node_t* n2 = malloc(sizeof(node_t));
    node_t* n3 = malloc(sizeof(node_t));
    node_t* n4 = malloc(sizeof(node_t));
    node_t* n5 = malloc(sizeof(node_t));
    node_t* n6 = malloc(sizeof(node_t));
    
    printf(BLUE"\tSTART SIX ELEMENT TEST WITH LOOP:\n"UNFORMAT);

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
    n6->next = n3;

    
    if (!HasLoop(n1))
    {
        printf(RED"\t\tTestHasLoopSixElementsWithLoop failed: expected 1, got 0\n"UNFORMAT);
        return (1);
    }

    n6->next = NULL;
    free(n1);
    free(n2);
    free(n3);
    free(n4);
    free(n5);
    free(n6);

    return (0);
}

static int TestHasLoopSixElementsWithoutLoop()
{
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
    node_t* n1 = malloc(sizeof(node_t));
    node_t* n2 = malloc(sizeof(node_t));
    node_t* n3 = malloc(sizeof(node_t));
    node_t* n4 = malloc(sizeof(node_t));
    node_t* n5 = malloc(sizeof(node_t));
    node_t* n6 = malloc(sizeof(node_t));
    
    printf(BLUE"\tSTART SIX ELEMENT TEST WITHOUT LOOP:\n"UNFORMAT);
    
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
    
    if (HasLoop(n1))
    {
        printf(RED"\t\tTestHasLoopSixElementsWithoutLoop failed: expected 0, got 1\n"UNFORMAT);
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

static int TestHasLoopTwoElementsWithLoop()
{
    int a = 1, b = 2;
    node_t* n1 = malloc(sizeof(node_t));
    node_t* n2 = malloc(sizeof(node_t));

    printf(BLUE"\tSTART TWO ELEMENT TEST WITH LOOP:\n"UNFORMAT);
    
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
    n2->next = n1;

    
    if (!HasLoop(n1))
    {
        printf(RED"\t\tTestHasLoopTwoElementsWithLoop failed: expected 1, got 0\n"UNFORMAT);
        return (1);
    }

    n2->next = NULL;
    free(n1);
    free(n2);

    return (0);
}


static int TestHasLoopTwoElementsWithLoop2()
{
	int a = 1, b = 2;
	node_t n1 = {0};
	node_t n2 = {0};
	
	n1.data = &a;
	n1.next = &n1;
	n2.data = &b;
	n2.next = NULL;
	
	printf(BLUE"\tSTART TWO ELEMENT TEST WITH LOOP 2:\n"UNFORMAT);
	if (1 != HasLoop(&n1))
	{
        printf(RED"\t\tTestHasLoopTwoElementsWithLoop 2 failed: expected 1, got 0\n"UNFORMAT);
        return (1);
	}
	
	return 0;
}


static int TestHasLoopTwoElementsWithoutLoop()
{
    int a = 1, b = 2;
    node_t* n1 = malloc(sizeof(node_t));
    node_t* n2 = malloc(sizeof(node_t));
    
    printf(BLUE"\tSTART TWO ELEMENT TEST WITHOUT LOOP:\n"UNFORMAT);
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

    if (HasLoop(n1))
    {
        printf(RED"\t\tTestHasLoopTwoElementsWithoutLoop failed: expected 0, got 1\n"UNFORMAT);
        return (1);
    }

    free(n1);
    free(n2);

    return (0);
}

static int TestHasLoopSingleElementWithLoop()
{
    int a = 1;
    node_t* n1 = malloc(sizeof(node_t));
    
    printf(BLUE"\tSTART SINGLE ELEMENT TEST WITH LOOP:\n"UNFORMAT);
    if(!n1)
    {
    	printf(RED"\t\tAllocation memory fail!!\n"UNFORMAT);
    	free(n1);
    	return (1);
    }

    n1->data = &a;
    n1->next = n1;
    
    if (!HasLoop(n1))
    {
        printf(RED"\t\tTestHasLoopSingleElementWithLoop failed: expected 1, got 0\n"UNFORMAT);
        return (1);
    }

    n1->next = NULL;
    free(n1);

    return (0);
}

static int TestHasLoopSingleElementWithoutLoop()
{
    int a = 1;
    node_t* n1 = malloc(sizeof(node_t));

    printf(BLUE"\tSTART SINGLE ELEMENT TEST WITHOUT LOOP:\n"UNFORMAT);
	if(!n1)
    {
    	printf(RED"\t\tAllocation memory fail!!\n"UNFORMAT);
    	free(n1);
    	return (1);
    }

    n1->data = &a;
    n1->next = NULL;
    
    if (HasLoop(n1))
    {
        printf(RED"\t\tTestHasLoopSingleElementWithoutLoop failed: expected 0, got 1\n"UNFORMAT);
        return (1);
    }

    free(n1);

    return (0);
}


/*------------------------------TestFindIntersection--------------------------*/

static int TestFindIntersection()
{
    printf(BLUE"START TEST FIND INTERSECTION:\n"UNFORMAT);
    
    if (TestFindIntersectionSixAndThreeWithIntersection())
    {
        return (1);
    }
    if (TestFindIntersectionSixAndThreeWithoutIntersection())
    {
        return (1);
    }
    if (TestFindIntersectionTwoAndTwoWithIntersection())
    {
        return (1);
    }
    if (TestFindIntersectionTwoAndTwoWithoutIntersection())
    {
        return (1);
    }
    if (TestFindIntersectionSingleElementWithIntersection())
    {
        return (1);
    }
    if (TestFindIntersectionSingleElementWithoutIntersection())
    {
        return (1);
    }

    return (0);
}

static int TestFindIntersectionSixAndThreeWithIntersection()
{
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
    node_t* n1 = malloc(sizeof(node_t));
    node_t* n2 = malloc(sizeof(node_t));
    node_t* n3 = malloc(sizeof(node_t));
    node_t* n4 = malloc(sizeof(node_t));
    node_t* n5 = malloc(sizeof(node_t));
    node_t* n6 = malloc(sizeof(node_t));
    node_t* head2;
    
    printf(BLUE"\tSTART SIX AND THREE ELEMENTS TEST WITH INTERSECTION:\n"UNFORMAT);
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

    head2 = n4;
    
    if (FindIntersection(n1, head2) != n4)
    {
        printf(RED"\t\tTestFindIntersectionSixAndThreeWithIntersection failed\n"UNFORMAT);
        return (1);
    }
    
    if (FindIntersection(head2, n1) != n4)
    {
        printf(RED"\t\tTestFindIntersectionSixAndThreeWithIntersection failed\n"UNFORMAT);
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

static int TestFindIntersectionSixAndThreeWithoutIntersection()
{
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7, h = 8, i = 9;
    node_t* n1 = malloc(sizeof(node_t));
    node_t* n2 = malloc(sizeof(node_t));
    node_t* n3 = malloc(sizeof(node_t));
    node_t* n4 = malloc(sizeof(node_t));
    node_t* n5 = malloc(sizeof(node_t));
    node_t* n6 = malloc(sizeof(node_t));
    
    node_t* m1 = malloc(sizeof(node_t));
    node_t* m2 = malloc(sizeof(node_t));
    node_t* m3 = malloc(sizeof(node_t));
    
    printf(BLUE"\tSTART SIX AND THREE ELEMENTS TEST WITHOUT INTERSECTION:\n"UNFORMAT);
    if(!n1 || !n2 || !n3 || !n4 || !n5 || !n6 || !m1 || !m2 || !m3)
    {
    	printf(RED"\t\tAllocation memory fail!!\n"UNFORMAT);
    	free(n1);
    	free(n2);
    	free(n3);
    	free(n4);
    	free(n5);
    	free(n6);
    	free(m1);
    	free(m2);
    	free(m3);
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

    m1->data = &g;
    m1->next = m2;
    m2->data = &h;
    m2->next = m3;
    m3->data = &i;
    m3->next = NULL;
    
    if (FindIntersection(n1, m1) != NULL)
    {
        printf(RED"\t\tTestFindIntersectionSixAndThreeWithoutIntersection failed\n"UNFORMAT);
        return (1);
    }
    
    if (FindIntersection(m1, n1) != NULL)
    {
        printf(RED"\t\tTestFindIntersectionSixAndThreeWithoutIntersection failed\n"UNFORMAT);
        return (1);
    }

    free(n1);
    free(n2);
    free(n3);
    free(n4);
    free(n5);
    free(n6);
    free(m1);
    free(m2);
    free(m3);

    return (0);
}

static int TestFindIntersectionTwoAndTwoWithIntersection()
{
    int a = 1, b = 2, c = 3;
    node_t* n1 = malloc(sizeof(node_t));
    node_t* n2 = malloc(sizeof(node_t));
    node_t* n3 = malloc(sizeof(node_t));
    node_t* head2;
    
    printf(BLUE"\tSTART TWO AND TWO ELEMENTS TEST WITH INTERSECTION:\n"UNFORMAT);
    if(!n1 || !n2 || !n3)
    {
    	printf(RED"\t\tAllocation memory fail!!\n"UNFORMAT);
    	free(n1);
    	free(n2);
    	free(n3);
    	return (1);
    }

    n1->data = &a;
    n1->next = n2;
    n2->data = &b;
    n2->next = n3;
    n3->data = &c;
    n3->next = NULL;

    head2 = n2;
    
    if (FindIntersection(n1, head2) != n2)
    {
        printf(RED"\t\tTestFindIntersectionTwoAndTwoWithIntersection failed\n"UNFORMAT);
        return (1);
    }

    free(n1);
    free(n2);
    free(n3);

    return (0);
}

static int TestFindIntersectionTwoAndTwoWithoutIntersection()
{
    int a = 1, b = 2, c = 3, d = 4;
    node_t* n1 = malloc(sizeof(node_t));
    node_t* n2 = malloc(sizeof(node_t));
    node_t* m1 = malloc(sizeof(node_t));
    node_t* m2 = malloc(sizeof(node_t));
    
    printf(BLUE"\tSTART TWO AND TWO ELEMENTS TEST WITHOUT INTERSECTION:\n"UNFORMAT);
    if(!n1 || !n2 || !m1 || !m2)
    {
    	printf(RED"\t\tAllocation memory fail!!\n"UNFORMAT);
    	free(n1);
    	free(n2);
    	free(m1);
    	free(m2);
    	return (1);
    }

    n1->data = &a; 
    n1->next = n2;
    n2->data = &b;
    n2->next = NULL;

    m1->data = &c;
    m1->next = m2;
    m2->data = &d;
    m2->next = NULL;
    
    if (FindIntersection(n1, m1) != NULL)
    {
        printf(RED"\t\tTestFindIntersectionTwoAndTwoWithoutIntersection failed\n"UNFORMAT);
        return (1);
    }

    free(n1);
    free(n2);
    free(m1);
    free(m2);

    return (0);
}

static int TestFindIntersectionSingleElementWithIntersection()
{
    int a = 1;
    node_t* n1 = malloc(sizeof(node_t));
    node_t* head2;
    
    printf(BLUE"\tSTART SINGLE ELEMENT TEST WITH INTERSECTION:\n"UNFORMAT);
    if(!n1)
    {
    	printf(RED"\t\tAllocation memory fail!!\n"UNFORMAT);
    	free(n1);
       	return (1);
    }

    n1->data = &a;
    n1->next = NULL;

    head2 = n1;
    
    if (FindIntersection(n1, head2) != n1)
    {
        printf(RED"\t\tTestFindIntersectionSingleElementWithIntersection failed\n"UNFORMAT);
        return (1);
    }

    free(n1);

    return (0);
}

static int TestFindIntersectionSingleElementWithoutIntersection()
{
    int a = 1, b = 2;
    node_t* n1 = malloc(sizeof(node_t));
    node_t* n2 = malloc(sizeof(node_t));


    printf(BLUE"\tSTART SINGLE ELEMENT TEST WITHOUT INTERSECTION:\n"UNFORMAT);
	if(!n1 || !n2)
    {
    	printf(RED"\t\tAllocation memory fail!!\n"UNFORMAT);
    	free(n1);
    	free(n2);
       	return (1);
    }
    n1->data = &a;
    n1->next = NULL;

    n2->data = &b;
    n2->next = NULL;

    if (FindIntersection(n1, n2) != NULL)
    {
        printf(RED"\t\tTestFindIntersectionSingleElementWithoutIntersection failed\n"UNFORMAT);
        return (1);
    }

    free(n1);
    free(n2);

    return (0);
}








