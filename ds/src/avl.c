#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include "avl.h" /*own header*/

#define CHILD_SIDE(cmp_result) ((cmp == L) ? L : R)

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

typedef enum {
	NEGATIVE = -1,
	EQUAL = 0,
	POSITIVE = 1
}cmp_result_t;

typedef int (*FuncTraverse_t)(node_t *root, avl_action_t action, void* params);

/*typedef enum*/
/*{*/
/*	SUCCESS,*/
/*	FAILURE*/
/*}*/



static void *AVLContainsHelper(node_t *root, void *data, avl_cmp_t cmp_func);
static int AVLForEachPreOr(node_t *root, avl_action_t action, void* params);
static int AVLForEachInOr(node_t *root, avl_action_t action, void* params);
static int AVLForEachPostOr(node_t *root, avl_action_t action, void* params);
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

static void AVLDestroyHelper(node_t *node)
{
	if (NULL == node)
	{
		return NULL;
	}
	node->children[L] = AVLDestroyHelper(node->childre[L]);
	node->children[R] = AVLDestroyHelper(node->childre[R]);
	
	AvlDestroy(node);
	
	return NULL;
}

/******************************************************************************/
/*need to update height*/
int AVLInsert(avl_t* avl_tree, void* data)
{
	int status = 0;
	node_t *new_node = NULL;
	
	assert(NULL != avl_tree);
	assert(NULL != data);
	
	new_node = AVLInsertHelper(avl_tree->root, data, avl_tree->cmp_func);
	status = (node == NULL ? -1 : 0); /*new_node, same date- returns 0
										failed to create node- returns -1*/
	
	if (AVLIsEmpty && 0 == status) /*update root in tree*/
	{
		avl_tree->root = new_node;
	}
	return status;
}

/*NULL- failed to create node*/
static node_t *AVLInsertHelper(node_t *root, void* data, avl_cmp_t cmp_func)
{
	if (NULL == root)
	{
		return CreateNode(data);
	}
	
	cmp = cmp_func(data, root->data); /*check which side*/
	if (EQUAL == cmp)
	{
		return root;
	}
	side = CHILD_SIDE(cmp);
	
	root->children[side] = AVLInsertHelper(root->children[side], data, cmp_func);
	return root;
}



static node_t *CreateNode(void *data)
{
	node_t *new_node = (node_t*)calloc(sizeof(node_t)); /*all fields except data 
														are NULL*/
	if (NULL == new_node)
	{
		return NULL;
	}
	new_node->data = data;
	
	return new_node;
}

static void DestroyNode(node_t *node)
{
	memset(node, 0, sizeof(node_t));
	free(node);
	node = NULL;
}

static void *AVLContainsHelper(node_t *root, void *data, avl_cmp_t cmp_func)
{
	 cmp_result_t cmp = NEGATIVE;
	 avl_child_t side = L;
	
	if (NULL == root)
	{
		return NULL;
	}
	cmp = cmp_func(data, root->data);
	
	if (EQUAL == cmp )
	{
		return root->data;
	}
	
	/*cmp to child*/
	side = CHILD_SIDE(cmp); 
	return AVLContainsHelper(root->children[side], data, cmp_func);
}


/******************************************************************************/
void AVLRemove(avl_t* avl_tree, void *data)
{
	assert(NULL != avl_tree);
	
	AVLRemoveHelper(avl_tree->root, data);
	
}


void AVLRemoveHelper(avl_t* avl_tree, node_t *node, void *data)
{
	 cmp_result_t cmp = NEGATIVE;
	 avl_child_t side = L;
	 node_t *child = NULL;
	 
	 /* if data isn't the tree */
	if (NULL == node) 
	{
		return;
	}
	
	cmp = avl_tree->cmp_func(data, node->data);
	
	if (cmp == EQUAL) /*data match*/
	{
		  /*Cases when root has 0 or 1 children*/
		  if (NULL == node->children[L] || NULL == node->children[R])
		  {
		  		/*remember child*/
		  		child = (NULL != node->children[L] ? node->children[L] : node->children[R]);
		  		DestroyNode(node);
		  		return child;
		  }
		  else /*case when has 2 children*/
		  {
		  		
		  }

	}
	
	
	else 
	{
		side = CHILD_SIDE(cmp_result);
		AVLRemoveHelper(avl_tree, node->children[side], data);
	}

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

size_t AVLCount(const avl_t* avl_tree);
/******************************************************************************/

int AVLIsEmpty(const avl_t* avl_tree)
{
	assert(NULL != avl_tree);
	
	return (avl_tree->root == NULL);
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
	FuncTraverse_t for_each_func_order[ORDER_SIZE] = 
								{AVLForEachPreOr, AVLForEachInOr, AVLForEachPostOr};
	
	assert(NULL != avl_tree);
	assert(NULL != action);
	assert(traversal >= PRE_ORDER && traversal <= POST_ORDER);
	
	status = for_each_func_order[traversal](avl_tree->root, action, params);
	return status;
}


/*****************************  Static function  ******************************/
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
	
	return 0;
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
	
	return 0;
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
	return 0;
}


static void *AVLContainsHelper(node_t *root, void *data, avl_cmp_t cmp_func)
{
	 cmp_result_t cmp = NEGATIVE;
	 avl_child_t side = L;
	
	if (NULL == root)
	{
		return NULL;
	}
	cmp = cmp_func(data, root->data);
	
	if (EQUAL == cmp )
	{
		return root->data;
	}
	
	/*cmp to child*/
	side = CHILD_SIDE(cmp); 
	return AVLContainsHelper(root->children[side], data, cmp_func);
}

