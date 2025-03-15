/*Data Structer Exam
Yana Glazer
07/03/25 */
 
#include <stdlib.h> /*NULL*/
#include <stdio.h>
#include <assert.h>
#include <string.h> /*memset*/


/* Macros for test formatting */
#define BOLD_FORMAT "\x1b[1;38m"
#define PASS_FORMAT	"\x1b[1;36m"
#define FAIL_FORMAT	"\x1b[1;31m"
#define UNFORMAT	"\x1b[1;0m"

#define TEST_CHECK(condition, message) \
	Check((condition), (message), __FILE__, __LINE__)


#define TEST_RESULT(status) \
	do { \
		if (0 == (status)) \
		{ \
			printf(PASS_FORMAT "\tPASSED\n" UNFORMAT); \
		} \
	} while (0)





/*********************************** Q1 FSA ***********************************/
/*FSA*/
typedef struct fsa 
{
	size_t off_free_block; /*holds offset from begining to free block, 
							not necessarily the first*/
}fsa_t;

void *Malloc(fsa_t *fsa)
{
	void *free_block = NULL;
	
	/*check if there is avilable blocks*/
	if (NULL != fsa  &&  fsa->off_free_block != 0)
	{	
		/*update address of free block*/
		free_block = (char*)fsa + fsa->off_free_block;
		/*update new next free block*/
		fsa->off_free_block = *(size_t*)free_block;
	}
	return free_block;
}

void Free(fsa_t *fsa, void *block)
{
	if (NULL == fsa || NULL == block)
	{
		return;
	}
	
	*(size_t*)block = fsa->off_free_block;
	fsa->off_free_block =(size_t)((char*)block - (char*)fsa);
}


/*********************************** Q1 VSA ***********************************/
#define WORD_SIZE sizeof(size_t)
#define METADATA_SIZE sizeof(vsa_t)
#define ROUND_UP_TWS(size)  (size + (WORD_SIZE - 1)) & ~(WORD_SIZE - 1)
#define ABS(x) ((x > 0) ? x : (-x))
#define NEXT_META(adr) ((long*)((char*)adr + WORD_SIZE + (ABS(*adr))))
#define END ((long)-1) /*end value in memory*/
/*VSA*/
void* VSAAllocate(vsa_t* vsa, size_t memory_size)
{
	long *runner = (long*)vsa, *free_block = NULL;
	long next_free_space = 0;
	int not_found = 1;
	memory_size = ROUND_UP_TWS(memory_size);

	assert(NULL != vsa);
	assert(0 < memory_size);/*check if neccasery*/
	
	while (not_found && (END != *runner))
	{
		if (*runner >= 0)
		{
			VSADefrag(runner); /*combine free consecutive blocks (until first negative)*/
		}

		next_free_space = *runner - memory_size;
		if (next_free_space >= 0)
		{
			/*pointer to free block*/
			free_block = (long*)((char*)runner + METADATA_SIZE); 
			/*update occupancy current block*/
			*runner = -memory_size;
			not_found = 0;
		}
		if(next_free_space > 0)
		{
			/*update after the block, amount of free space*/
			*(long*)((char*)free_block + memory_size) = next_free_space - METADATA_SIZE;
		}
		/*jump to next metadata*/
		runner = NEXT_META(runner); 
	}
	return free_block;
}


void VSAFree(void* block)
{
	long *meta_block = (long*)((char*)block - METADATA_SIZE);
	
	assert(NULL != block);
	
	if (0 <= block)
	{
		return;
	}
	
	*meta_block *= -1;
}
/*********************************** Q2 ***************************************/
/*Reverse list*/
typedef struct nodes
{
	void *data;
	struct nodes *next;
}snode_t;

static void PrintList(snode_t *rnr);

snode_t *Flip(snode_t *head)
{
	snode_t *prev = NULL, *curr = head, *next = NULL;
	
	assert(NULL != head);
	
	next = head->next;
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
/*********************************** Q4 ***************************************/
int IsSllLoop(snode_t *head)
{
	snode_t *slow = head, *fast = NULL;
	
	assert(NULL != head);
	
	fast = head->next;
	
	while (slow != fast && NULL != fast && NULL != fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	return (slow==fast); /*if there is a loop, the pointers will meet at some	
						 node in the loop.
						 if there isn't a loop, fast pointer will reach NULL*/
}

/*returns head pointer, not necessarily of the starting node of the loop*/
snode_t *OpenSllLoop(snode_t *head)
{
	snode_t *slow = head, *fast = NULL;
	
	assert(NULL != head);
	
	fast = head->next;
	
	if (!IsSllLoop(head))
	{
		return head;
	}
	
	/*if there is a loop, find pointer inside a loop*/
	while (slow != fast)
	{
		slow = slow->next;
		fast = fast->next->next;
	} /*now, slow and fast point to same node in the loop*/
	
	head = slow->next;
	slow->next = NULL;
	
	return head;
}
/*********************************** Q5 ***************************************/
/*Given head pointers of two singly linked-lists headA and headB,
 return the node at which the two lists intersect.
 If the two linked lists have no intersection at all, return null.*/
snode_t *IntersectionNode(snode_t *head1, snode_t *head2)
{
	snode_t *ptr1 = head1, *ptr2 = head2;
	
	assert(NULL != head1);
	assert(NULL != head2);
	
	while (ptr1 != ptr2)
	{
		ptr1 = (ptr1 != NULL ? ptr1->next : head2);
		ptr2 = (ptr2 != NULL ? ptr2->next : head1);
	}
	/*return intersection point or null*/
	return ptr1;
}

void SeparateIntersectSll(snode_t *head1, snode_t *head2)
{
	snode_t *ptr1 = head1, *ptr2 = head2;
	
	assert(NULL != head1);
	assert(NULL != head2);
	
	if (NULL == IntersectionNode(head1, head2))
	{
		return;
	}
	
	/*if there is an intersection, run until one node before it*/
	while (ptr1->next != ptr2->next)
	{
		ptr1 = (ptr1 != NULL ? ptr1->next : head2);
		ptr2 = (ptr2 != NULL ? ptr2->next : head1);
	}
	
	ptr2->next = NULL;
}
/*********************************** Q6 ***************************************/
void RemoveSll(snode_t *node)
{
	snode_t *snode_to_free = NULL;
	
	assert(NULL != node); 
	assert(NULL != node->next); /*check it isn't dummy, 
								will cause dereference beyond NULL / removing tail*/
	snode_to_free = node->next;
	
	/*copying next node to current mode*/
	node->data = node->next->data;
	node->next = node->next->next;
/*	free(snode_to_free);*/
}
/*********************************** Q7 ***************************************/
typedef struct noded
{
	void *data;
	struct noded *next;
	struct noded *prev;
}dnode_t;

static int TestDLLOperations(void);

/*can assume node exist before and after*/
void RemoveDll(dnode_t *node)
{
	assert(NULL != node);
	
	node->prev->next = node->next;
	node->next->prev = node->prev;
	memset(node, 0, sizeof(dnode_t));
	free(node);
}

int InsertBeforeDll(dnode_t *node_where, void* data)
{
	dnode_t *new_node = NULL;
	
	assert(NULL != node_where);
	
	new_node = (dnode_t*)calloc(1, sizeof(dnode_t));
	if (NULL == new_node)
	{
		return 1;
	}
	
	/*initialize new node*/
	new_node->data = data;
	new_node->next = node_where;
	new_node->prev = node_where->prev;
	 
	/*update the adjacent nodes*/ 
	node_where->prev->next = new_node;
	node_where->prev = new_node;
	 
	return 0;
}

/*********************************** Q8 ***************************************/
int FindMissingNum(int arr[], int max_value)
{
	int arr_sum = 0, real_sum = 0;
	int i = 0;
	
	/*find real sum*/
	for (i = 1; i <= max_value; ++i)
	{
		real_sum +=i;
	}
	
	/*find arr sum*/
	for(i=0; i< max_value -1 ; ++i)
	{
		arr_sum += arr[i];
	}
	return (real_sum - arr_sum);
}

/*********************************** Q10 ***************************************/
#define Q_SIZE 24
typedef struct queue{
	char m_queue[Q_SIZE];
	size_t m_elements_in_q;
	size_t m_first_element_index;
}queue;

static int TestQueueOperations(void);

int QueuePushChar(queue *q, char c)
{
	int status = 1;
	size_t end_index = 0;
	
	assert(NULL != q);
	
	if (q->m_elements_in_q < Q_SIZE)
	{
		status = 0;
		
		end_index = (q->m_first_element_index + q->m_elements_in_q) % Q_SIZE;
		
		q->m_queue[end_index] = c;
		++(q->m_elements_in_q);
	}
	return status;
}

int QueuePopChar(queue *q)
{
	int status = 1;
	assert(NULL != q);
	
	if (q->m_elements_in_q > 0)
	{
		q->m_elements_in_q -= 1;

		q->m_first_element_index = (q->m_first_element_index + 1) % Q_SIZE;
		status = 0;
	}
	return status;
}


/*********************************** main *************************************/
static int g_total_checks = 0;
static int g_failed_checks = 0;

static int Check(
	int condition,			/* Test condition to evaluate */
	const char* message,	/* Error message if test fails */
	const char* file,		/* Source file where check occurred */
	int line				/* Line number where check occurred */
);

/* Core check function implementation */
static int Check(int condition, const char* message, const char* file, int line)
{
	++g_total_checks;

	if (!condition)
	{
		printf(FAIL_FORMAT "\n   FAILED: %s\n   └────File: %s; \tLine: %d\n" UNFORMAT,
						message, file, line);
		++g_failed_checks;
		return (1);
	}

	return (0);
}


static void PrintTestSummary(int status)
{
	printf("\n%s ======= Test Summary =======%s\n", BOLD_FORMAT, UNFORMAT);
	printf("┌──────────────────┬─────────┐\n");
	printf("│ Total checks     │ %7d │\n", g_total_checks);
	printf("│ Failed checks    │ %7d │\n", g_failed_checks);
	printf("└──────────────────┴─────────┘\n");
	if (0 != status)
	{
		printf(FAIL_FORMAT "\nSome tests failed\n" UNFORMAT);
	}
	else
	{
		printf(PASS_FORMAT "\nAll tests completed successfully\n" UNFORMAT);
	}
}



int main(void)
{
	int status = 0;
	

	
	snode_t *head = NULL, *rnr = NULL;
	int counter = 0;

    snode_t n0= {0}, n1= {0}, n2= {0}, n3={0};
    snode_t m0= {0}, m1= {0}, m2= {0}, m3={0}, m10= {0}, m11= {0};
    snode_t *inter_node = NULL;
    int data0 = 0, data1 = 1, data2 = 2, data3 = 3, data10 = 10, data11 = 11;
    
    int arr[4] = {2 ,4 , 5, 3};
    
    g_total_checks = 0; g_failed_checks = 0;
    
    n0.next = &n1, n1.next = &n2, n2.next = &n3, n3.next = &n1;
    m0.data = &data0, m1.data = &data1, m2.data = &data2, m3.data = &data3;
    m10.data = &data10, m11.data = &data11;
    m0.next = &m1, m1.next = &m2, m2.next = &m3, m3.next = NULL;
    m10.next = &m11, m11.next = &m2;
    
    printf ("%p %p %p %p\n", (void*)&n0, (void*)&n1, (void*)&n2, (void*)&n3);
    
    printf("%d result of isloop\n", IsSllLoop(&n0));
    
    head = OpenSllLoop(&n0);
    
    rnr = head;
    
    while (rnr != NULL)
    {
    	++counter;
    	printf ("pointer %p\n", (void*)rnr);
    	rnr = rnr->next;
    }
	
	printf ("counter is %d\n", counter);    
	
	inter_node = IntersectionNode(&m0, &m10);
	printf ("add of m2 is %p , inter node is %p\n", (void*)&m2, (void*)inter_node);
	
	SeparateIntersectSll(&m0, &m10);
	
	PrintList(&m0);

	printf ("end of 1 list\n");

	PrintList(&m10);
	
    /*************************Test Q6 Remove Sll Node**************************/
	
	RemoveSll(&m2);
	PrintList(&m0);
	
	/*Remove(&m3); Assertion `NULL != node->next' failed. as expacted */
	
	/************************ Test Q8 FindMissingNum **************************/
	
	printf("Missing number is %d\n", FindMissingNum(arr, 5));
	
	
	
	/************************ Test Q7                **************************/
	status |= TestDLLOperations();
	
	/************************ Test 10                **************************/
	status |= TestQueueOperations();


	PrintTestSummary(status);
    return 0;
    
}


static void PrintList(snode_t *head)
{
	while (head != NULL)
    {
    	printf ("%d\n", *(int*)head->data);
    	head = head->next;
    }
}



static int TestDLLOperations(void)
{
	int status = 0;
	dnode_t* head = NULL;
	dnode_t* tail = NULL;
	int data1 = 1, data2 = 2, new_data = 42;

	printf("Testing DLL Operations...");

	/* Allocate and initialize head node */
	head = (dnode_t*)malloc(sizeof(dnode_t));
	head->data = &data1;
	head->prev = NULL;

	/* Allocate and initialize tail node */
	tail = (dnode_t*)malloc(sizeof(dnode_t));
	tail->data = &data2;

	/* Connect head and tail */
	head->next = tail;
	tail->prev = head;
	tail->next = NULL;

	/* Test InsertBeforeDll - insert before tail */
	status |= TEST_CHECK(0 == InsertBeforeDll(tail, &new_data),
			"InsertBeforeDll should return 0 on success");

	/* Verify the new node was inserted correctly */
	status |= TEST_CHECK(head->next->data == &new_data,
			"New node's data not set correctly");

	status |= TEST_CHECK(head->next->prev == head,
			"New node's prev pointer not set correctly");

	status |= TEST_CHECK(head->next->next == tail,
			"New node's next pointer not set correctly");

	status |= TEST_CHECK(tail->prev == head->next,
			"Tail's prev pointer not updated correctly");

	/* Test DLLRemove - remove the middle node */
	RemoveDll(head->next);

	/* Verify the node was removed correctly */
	status |= TEST_CHECK(head->next == tail,
			"Head's next pointer not updated after removal");

	status |= TEST_CHECK(tail->prev == head,
			"Tail's prev pointer not updated after removal");

	/* Clean up */
	free(head);
	free(tail);

	TEST_RESULT(status);
	return status;
}

static int TestQueueOperations(void)
{
	int status = 0;
	queue queue;
	int i;

	printf("Testing Queue Operations...");

	/* Initialize the queue */
	memset(&queue, 0, sizeof(queue));

	/* Test push operation */
	for (i = 0; i < Q_SIZE; ++i)
	{
		char ch = 'A' + i;
		status |= TEST_CHECK(0 == QueuePushChar(&queue, ch),
				"QueuePushChar should return 0 on success");
	}

	/* Test that queue is full */
	status |= TEST_CHECK(1 == QueuePushChar(&queue, 'Z'),
			"QueuePushChar should return 1 when queue is full");

	/* Test queue elements count */
	status |= TEST_CHECK(Q_SIZE == queue.m_elements_in_q,
			"Queue element count incorrect after pushes");

	/* Test pop operation */
	for (i = 0; i < Q_SIZE; ++i)
	{
		status |= TEST_CHECK(0 == QueuePopChar(&queue),
				"QueuePopChar should return 0 on success");
	}

	/* Test that queue is empty */
	status |= TEST_CHECK(1 == QueuePopChar(&queue),
			"QueuePopChar should return 1 when queue is empty");

	/* Test queue elements count */
	status |= TEST_CHECK(0 == queue.m_elements_in_q,
			"Queue element count incorrect after pops");

	/* Test wrapping behavior by filling, partially emptying, then refilling */
	for (i = 0; i < Q_SIZE / 2; ++i)
	{
		QueuePushChar(&queue, 'A' + i);
	}

	for (i = 0; i < Q_SIZE / 4; ++i)
	{
		QueuePopChar(&queue);
	}

	for (i = 0; i < Q_SIZE / 2; ++i)
	{
		QueuePushChar(&queue, 'a' + i);
	}

	status |= TEST_CHECK(queue.m_elements_in_q == Q_SIZE * 3 / 4,
			"Queue element count incorrect after wrap-around operations");

	TEST_RESULT(status);
	return status;
}


 
