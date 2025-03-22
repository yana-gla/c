/*******************************************************************************
* File: avl.c
*
* Purpose:
*   Implement Binary Search Tree recursively
	
*
* Author:
*   Yana Glazer
* Code reviewd by:
*   __________
*
*Date: 18/03/2025
*Last Update: --/--/----
*******************************************************************************/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include <string.h> /*memset*/
#include <stdio.h> /*printf*/
#include "avl.h" /*own header*/

#define CHILD_SIDE(cmp_result) ((cmp == -1) ? 0 : 1)
#define OTHER_SIDE(side) (!side)
#define HEIGHT(node) ((NULL == node) ? 0 : (node->height))
#define MAX(hight1, hight2) ((hight1 >= hight2) ? hight1 : hight2)
#define NEGATIVE -1
#define	EQUAL 0
#define	POSITIVE 1
#define TAB_WIDTH 2
/******************************************************************************/
typedef struct node node_t;
struct node
{
    node_t* children[2];
    void* data;
    size_t height;
};

struct avl
{
    node_t* root;
    avl_cmp_t cmp_func;
};

typedef enum
{
	L, /*Left*/
	R  /*Right*/
}avl_child_t;

typedef int (*FuncTraverse_t)(node_t *root, avl_action_t action, void* params);
/******************************************************************************/
static void *AVLContainsHelper(node_t *root, void *data, avl_cmp_t cmp_func);
static int AVLForEachPreOr(node_t *root, avl_action_t action, void* params);
static int AVLForEachInOr(node_t *root, avl_action_t action, void* params);
static int AVLForEachPostOr(node_t *root, avl_action_t action, void* params);
static void *AVLDestroyHelper(node_t *node);
static node_t *CreateNode(void *data);
static node_t *AVLDestroyNode(node_t *node);
static node_t *AVLInsertHelper(node_t *root,
								 void* data,
								 avl_cmp_t cmp_func,
								 int *insertion_status);
static node_t *AVLRemoveHelper(avl_cmp_t cmp_func, node_t *node, void *data);
static int ActionCount(void *node_data, void *nodes_num);
static size_t UpdateHeight(node_t *node);
static int BalanceFactor(node_t *node);
static node_t *Balance(node_t *node);
static node_t *Rotate(node_t *node, avl_child_t side);
/*Debug Helper function*/
static void PrintTree(node_t *root, int level);
/******************************************************************************/
avl_t* AVLCreate(avl_cmp_t cmp_func)
{
	avl_t *avl = NULL;	
	
	assert(NULL != cmp_func);
	
	avl = (avl_t*)malloc(sizeof(avl_t));
	if (NULL == avl)
	{
		return NULL;
	}
	
	avl->root = NULL;
	avl->cmp_func = cmp_func;
	
	return avl;
}

/******************************************************************************/
void AVLDestroy(avl_t* avl_tree)
{
	assert(NULL != avl_tree);
	
	AVLDestroyHelper(avl_tree->root);
	avl_tree->root = NULL;
	avl_tree->cmp_func = NULL;
	
	free(avl_tree);
	avl_tree = NULL;
}

/******************************************************************************/
int AVLInsert(avl_t* avl_tree, void* data)
{
	int insertion_status = 0 ; /*0 success, 1 failed*/
	
	assert(NULL != avl_tree);
	assert(NULL != data);
	
	avl_tree->root = AVLInsertHelper(avl_tree->root, data, avl_tree->cmp_func, &insertion_status);

	return insertion_status;
}

/******************************************************************************/
void AVLRemove(avl_t* avl_tree, void *data)
{
	assert(NULL != avl_tree);
	
	avl_tree->root = AVLRemoveHelper(avl_tree->cmp_func, avl_tree->root, data);
}

/******************************************************************************/
size_t AVLHeight(const avl_t* avl_tree)
{
	node_t* root = NULL;
	
	assert(NULL != avl_tree);

	root = avl_tree->root;
	
	return (root != NULL ? root->height : 0);
}

/******************************************************************************/
size_t AVLCount(const avl_t* avl_tree)
{
	size_t nodes_num = 0;
	
	assert (NULL != avl_tree);
	
	AVLForEach((avl_t*)avl_tree, ActionCount, &nodes_num, PRE_ORDER);
	return nodes_num;
}

/******************************************************************************/
int AVLIsEmpty(const avl_t* avl_tree)
{
	assert(NULL != avl_tree);
	
	return (NULL == avl_tree->root);
}

/******************************************************************************/
void* AVLContains(const avl_t* avl_tree, void* data)
{
	assert(NULL != avl_tree);
	
	return AVLContainsHelper(avl_tree->root, data, avl_tree->cmp_func);
}

/******************************************************************************/
int AVLForEach(avl_t* avl_tree,
			   avl_action_t action,
			   void* params,
			   avl_traversal_t traversal)		   
{
	int status = 0;

	/*array of function pointer*/
	FuncTraverse_t for_each_func_travers[ORDER_SIZE] = 
								{AVLForEachPreOr, AVLForEachInOr, AVLForEachPostOr};
	
	assert(NULL != avl_tree);
	assert(NULL != action);
	assert(traversal >= PRE_ORDER && traversal <= POST_ORDER);
	
	status = for_each_func_travers[traversal](avl_tree->root, action, params);
	return status;
}


/******************************************************************************/
/*****************************  Static function  ******************************/
static node_t *AVLInsertHelper(node_t *root, void* data, avl_cmp_t cmp_func, int *insertion_status)
{
	int cmp = NEGATIVE;
	node_t *new_node = NULL, *child = NULL;
	avl_child_t side = L;
	
	
	if (NULL == root)
	{
		new_node = CreateNode(data); /*new node or NULL if failed*/
		if (NULL == new_node)
		{
			*insertion_status = 1;
		}
		return new_node;
	}
	
	cmp = cmp_func(data, root->data); /*check which side*/
	if (EQUAL == cmp)
	{
		return root;
	}
	
	side = CHILD_SIDE(cmp);
	child = AVLInsertHelper(root->children[side], data, cmp_func, insertion_status);
	if (NULL == child) /*if insertion failed*/
	{
		return root;
	}
	root->children[side] = child;
	
	root->height = UpdateHeight(root);
	return Balance(root);
}

/******************************************************************************/
/*post order- left- right- root */
static void *AVLDestroyHelper(node_t *node)
{
	if (NULL == node)
	{
		return NULL;
	}
	node->children[L] = AVLDestroyHelper(node->children[L]);
	node->children[R] = AVLDestroyHelper(node->children[R]);
	
	return AVLDestroyNode(node);
}

/******************************************************************************/
static node_t *CreateNode(void *data)
{
	node_t *new_node = (node_t*)calloc(1, sizeof(node_t)); /*all fields except
	 													data & height are NULL*/
	if (NULL == new_node)
	{
		return NULL;
	}
	new_node->data = data;
	new_node->height = 1;
	
	return new_node;
}

static node_t *AVLDestroyNode(node_t *node)
{
	memset(node, 0, sizeof(node_t));
	free(node);
	node = NULL;
	return NULL;
}
/******************************************************************************/
static size_t UpdateHeight(node_t *node)
{
	size_t height = 0, height_left = 0, height_right = 0;
	
	height_left = HEIGHT(node->children[L]);
	height_right = HEIGHT(node->children[R]);

	height = 1 + MAX(height_left, height_right);
	
	return height;
}

static node_t *Rotate(node_t *node, avl_child_t side)
{
	node_t *pivot = node->children[OTHER_SIDE(side)];
	node->children[OTHER_SIDE(side)] = pivot->children[side]; /*why not null?*/
	pivot->children[side] = node;
	
	node->height = UpdateHeight(node);
	pivot->height = UpdateHeight(pivot);
	
	return pivot;
}

static int BalanceFactor(node_t *node)
{
	int balance_factor = 0;
	size_t height_left = 0, height_right = 0;
	
	if (NULL == node)
	{
		return 0;
	}
	
	height_left = HEIGHT(node->children[L]);
	height_right = HEIGHT(node->children[R]);
	
	balance_factor = height_left - height_right;
	
	return balance_factor;
}

node_t *Balance(node_t *node)
{
	if (NULL == node)
	{
		return NULL;
	}
	
	if (BalanceFactor(node) > 1) /*Left heavy*/
	{
		if (BalanceFactor(node->children[L]) < 0) /*left right rotation*/
		{
			node->children[L] = Rotate(node->children[L], L); /*rotate left*/
		}
		return Rotate(node, R); /*rotate right*/
	}
	
	if (BalanceFactor(node) < -1) /*Right heavy*/
	{
		if (BalanceFactor(node->children[R]) > 0) /*right left rotation*/
		{
			node->children[R] = Rotate(node->children[R], R); /*rotate left*/
		}
		return Rotate(node, L);/*rotate left*/
	}
	
	return node; /*if node is balanced*/
}

/******************************************************************************/
static node_t *Sequential(node_t *node, avl_child_t side)
{
	if (NULL == node->children[side])
	{
		return node;
	}
	return Sequential(node->children[side], side);
}

static node_t *AVLRemoveHelper(avl_cmp_t cmp_func, node_t *node, void *data)
{
	 int cmp = NEGATIVE;
	 avl_child_t side = L;
	 node_t *child = NULL;
	 node_t *next = NULL;
	 
	/* if data isn't in the tree */
	if (NULL == node) 
	{
		return NULL;
	}
	
	cmp = cmp_func(data, node->data);
	
	if (cmp == EQUAL) /*data match*/
	{
		  /*Cases: 0 / 1 children*/
		  if (NULL == node->children[L] || NULL == node->children[R])
		  {
		  		/*remember child*/
		  		child = (NULL != node->children[L] ? node->children[L] : node->children[R]);
		  		AVLDestroyNode(node);
		  		node = NULL;
		  		return child;
		  }
		  else /*case: 2 children*/
		  {
		  		next = Sequential(node->children[R], L);/*find successive- 
		  											minimum in right sub tree*/
		  		node->data = next->data;
		  		node->children[R] = AVLRemoveHelper(cmp_func, node->children[R], next->data); /*Delete the successive*/
		  }
	}
	else 
	{
		side = CHILD_SIDE(cmp);
		node->children[side] = AVLRemoveHelper(cmp_func, node->children[side], data);
	}
	node->height = UpdateHeight(node);
	return Balance(node);
}

/******************************************************************************/
/*PreOrder- root - left - right*/
static int AVLForEachPreOr(node_t *root, avl_action_t action, void* params)
{
	int status = 0;
	
	if (NULL == root)
	{
		return 0;
	}
	
	status = action(root->data ,params);
	if (0 != status) /*if fails*/
	{
		return status;
	}
	
	status = AVLForEachPreOr(root->children[L], action, params);
	if (0 != status) /*if fails*/
	{
		return status;
	}
	
	status = AVLForEachPreOr(root->children[R],action, params);
	if (0 != status) /*if fails*/
	{
		return status;
	}
	
	return status; /*0*/
}

/*PostOrder- left - right- root*/
static int AVLForEachPostOr(node_t *root, avl_action_t action, void* params)
{
	int status = 0;
	
	if (NULL == root)
	{
		return 0;
	}
	
	status = AVLForEachPostOr(root->children[L], action, params);
	if (0 != status) /*if fails*/
	{
		return status;
	}
	
	status = AVLForEachPostOr(root->children[R],action, params);
	if (0 != status) /*if fails*/
	{
		return status;
	}
	
	status = action(root->data ,params);
	if (0 != status) /*if fails*/
	{
		return status;
	}
	
	return status /*0*/;
}

/*InOrder- left - root- right*/
static int AVLForEachInOr(node_t *root, avl_action_t action, void* params)
{
	int status = 0;
	
	if (NULL == root)
	{
		return 0;
	}
	
	status =  AVLForEachInOr(root->children[L], action, params);
	if (0 != status) /*if fails*/
	{
		return status;
	}
	
	status = action(root->data ,params);
	if (0 != status) /*if fails*/
	{
		return status;
	}
	
	status =  AVLForEachInOr(root->children[R],action, params);
	if (0 != status) /*if fails*/
	{
		return status;
	}
	return status /*0*/;
}

/******************************************************************************/
static int ActionCount(void *node_data, void *nodes_num)
{
	(void)node_data;
	++*(size_t*)nodes_num;
	
	return 0;
}

/******************************************************************************/
static void *AVLContainsHelper(node_t *root, void *data, avl_cmp_t cmp_func)
{
	 int cmp = NEGATIVE;
	 avl_child_t side = L;
	
	if (NULL == root)
	{
		return NULL;
	}
	
	cmp = cmp_func(data, root->data);
	
	if (EQUAL == cmp)
	{
		return root->data;
	}
	
	/*cmp to child*/
	side = CHILD_SIDE(cmp); 
	return AVLContainsHelper(root->children[side], data, cmp_func);
}

/******************************************************************************/
static void PrintTree(node_t *root, int level)
{
	int i = 0;
	
	if (root == NULL)
    {
        return;
    }

    PrintTree(root->children[R], level + 1);

    for ( i = 0; i < level * TAB_WIDTH; ++i)
    {
        putchar(' ');
    }

    printf("%d\n", *(int *)root->data);

    PrintTree(root->children[L], level + 1);
}
/******************************************************************************/
