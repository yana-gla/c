#include <assert.h> /*assert*/
#include <stdio.h> /*print*/
#include "avl.h" /*own header*/

static int CompareInts(const void* num1, const void* num2)
{
	assert(NULL != num1);
	assert(NULL != num2);

	return ((*(int*)num1 == *(int*)num2) ? (0) :
					((*(int*)num1 < *(int*)num2) ? (-1) : (1)));
}

int main(void)
{
	
	/**************************************************************************/
	 avl_t *avl = AVLCreate(CompareInts);
	 if (NULL == avl)
	{
		printf ("avl failed\n");
	}
	else
	{
		printf ("avl succeed\n");
	}
	/**************************************************************************/
	
	printf ("AVL is empty? %d\n",AVLIsEmpty(avl));
	printf ("Height of AVL? %lu\n",AVLHeight(avl));
	
	
	return 0;
}
