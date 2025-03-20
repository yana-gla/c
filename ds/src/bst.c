#include <stddef.h> /*size_t*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include <string.h> /*memset*/
#include <stdio.h> 


#include "bst.h"

#define CMP_TO_CHILD(comp_result) ((comp_result == (-1)) ? 0 : 1) 

struct node
{
    void* data;
    bst_node_t* parent;
    bst_node_t* children[2]; /*index 0 left child, index 1 right child*/
};

struct bst
{
    bst_node_t dummy_max;
    bst_comparator_t cmp_func;
};

typedef enum
{
	LEFT,  
	RIGHT
}child_t;


/******************************  static function   ****************************/
static bst_node_t* Extremum(bst_node_t *root, child_t child);
static bst_node_t *NextValue(bst_node_t *node, child_t direct);
static bst_node_t *BSTSearch(bst_t *bst, void *data, child_t *side);
static int CountOneNode(void* data_ref, void* num_nodes);
static bst_node_t *BSTItrToNode(bst_itr_t itr);
static bst_itr_t BSTNodeToItr(bst_node_t *node);
static void BSTDestroyNode(bst_node_t *node);
static bst_node_t *CreateNode(bst_node_t *parent, void *data);
/******************************************************************************/
/*Return new created bst pointer on success, O.W NULL*/
bst_t* BSTCreate(bst_comparator_t comparator)
{
	bst_t *bst = NULL;
	
	assert(NULL != comparator);
	
	bst = (bst_t*)calloc(1, sizeof(bst_t)); /*calloc to initialize dummy to 0*/
	if (NULL == bst)
	{
		return NULL;
	}
	
	bst->cmp_func = comparator;
	
	return bst;
}

/******************************************************************************/
/*destroy all the tree*/
/*O()n)*/
void BSTDestroy(bst_t* bst)
{
	bst_node_t *node = bst->dummy_max.children[LEFT];
	child_t child_side = LEFT;
	
	assert(NULL != bst);
	
	while (!BSTIsEmpty(bst))
	{
		/*while not leaf, go down*/
		while (!(NULL == node->children[LEFT] && NULL == node->children[RIGHT]))
		{
			child_side = node->children[LEFT] != NULL ? LEFT : RIGHT;
			node = node->children[child_side];
		}
		/*else*/ /*leaf*/
		{
			child_side = node->parent->children[LEFT] == node ? LEFT : RIGHT;
			/*gowing one up*/
			node = node->parent;
			BSTDestroyNode(node->children[child_side]);
			node->children[child_side] = NULL;
		}
	}
	memset(bst, 0, sizeof(bst_t));
	free(bst);
	bst = NULL;
}

/******************************************************************************/
/*insert- return parent node to attach to, find- return node of matched data*/
/*find perspective- search may not find data if the data isn't exist, will return 
	leaf*/
bst_itr_t BSTInsert(bst_t* bst, void* data)
{	
	bst_node_t *parent = NULL, *new_node = NULL;
	child_t side = LEFT;
	
	assert(NULL != bst);

	parent = BSTSearch(bst, data, &side);
	
	/*Multiple instances*/
	if ((parent != &bst->dummy_max) && (0 == bst->cmp_func(data, parent->data)))
	{
		return BSTNodeToItr(parent);
	}
	
	new_node = CreateNode(parent, data);
	if (NULL == new_node)
	{
		return BSTItrEnd(bst);
	}
	
	parent->children[side] = new_node;
	
	return BSTNodeToItr(new_node);
}

/******************************************************************************/
void BSTRemove(bst_itr_t itr)
{
	bst_node_t *node = BSTItrToNode(itr), *successor = NULL;
	child_t parent_side = 0, child_side = 0;
	
	/*if node have 2 children*/
	if (NULL != node->children[LEFT] && NULL != node->children[RIGHT])
	{
		/*find next*/
		successor = BSTItrToNode(BSTItrNext(itr));
		node->data = successor->data;
		node = successor;
	}

	parent_side = (node == node->parent->children[LEFT] ? LEFT : RIGHT);
	
	if (NULL != node->children[LEFT] || NULL != node->children[RIGHT])
	{
		child_side = node->children[LEFT] != NULL ? LEFT : RIGHT;
		/*update child at parent*/
		node->parent->children[parent_side] = node->children[child_side];
		/*update parent at child*/
		node->children[child_side]->parent= node->parent;
	}
	else /*leaf*/
	{
		node->parent->children[parent_side] = NULL;

	}
		BSTDestroyNode(node);
}

/******************************************************************************/
/*Cases- empty, found, not found*/
bst_itr_t BSTFind(const bst_t* bst, void* data)
{
	bst_itr_t itr_search = {0};
	int comp_result = 0;
	child_t dummy_child = LEFT;
	
	assert(NULL != bst);
	
	if (BSTIsEmpty(bst))
	{
		return BSTItrEnd(bst);
	}
	
	itr_search = BSTNodeToItr(BSTSearch((bst_t*)bst, data, &dummy_child));
	comp_result = bst->cmp_func(data, BSTGetData(itr_search));
	
	return ((0 == comp_result) ? itr_search : BSTItrEnd(bst));
}

/******************************************************************************/
int BSTForEach(bst_itr_t from, bst_itr_t to, bst_action_t action, void* params)
{
	bst_itr_t itr = from;
	int status = 0;
	
	assert (NULL != action);
	
	while (!BSTIsSameItr(itr, to) && 0 == status)
	{
		status = action(BSTGetData(itr), params);
		itr = BSTItrNext(itr);
	}
	
	return status;
}

/******************************************************************************/
size_t BSTCount(const bst_t* bst)
{
	bst_itr_t itr = BSTItrBegin(bst), end = BSTItrEnd(bst);/*start from smallest node*/
	size_t num_nodes = 0;
	
	assert(NULL != bst);
	
	BSTForEach(itr, end, CountOneNode, &num_nodes);

	return num_nodes;
}

/****************************   itr function  *********************************/
/*returns iterator of minimum value of the tree*/
bst_itr_t BSTItrBegin(const bst_t* bst)
{
	assert (NULL != bst);
	return BSTNodeToItr(Extremum((bst_node_t*)&bst->dummy_max, LEFT));
}

/*next on max will return duumy_max (30), prev on min will return null*/
bst_itr_t BSTItrPrev(bst_itr_t itr)
{
	bst_node_t *node = BSTItrToNode(itr);
	return BSTNodeToItr(NextValue(node, LEFT));
}

bst_itr_t BSTItrNext(bst_itr_t itr)
{
	bst_node_t *node = BSTItrToNode(itr);
	return BSTNodeToItr(NextValue(node, RIGHT));
}

/*returns dummy_max of the tree*/
bst_itr_t BSTItrEnd(const bst_t* bst)
{
	assert (NULL != bst);
	return BSTNodeToItr((bst_node_t*)&bst->dummy_max);
}

int BSTIsSameItr(bst_itr_t itr1, bst_itr_t itr2)
{
	bst_node_t *node1 = BSTItrToNode(itr1);
	bst_node_t *node2 = BSTItrToNode(itr2);
	
	return (node1 == node2);
}

/******************************************************************************/
void* BSTGetData(bst_itr_t itr)
{
	bst_node_t *node = BSTItrToNode(itr);
	return (node->data);
}

/******************************************************************************/
int BSTIsEmpty(const bst_t* bst)
{
	assert(NULL != bst);
	return (NULL == bst->dummy_max.children[LEFT]);
}

/***************************    Static function  ******************************/
/*finds max/min in a tree, from given root*/
static bst_node_t* Extremum(bst_node_t *root, child_t direct)
{
	bst_node_t* runner = root;
	
	assert(NULL != root);
	
	while (NULL != runner->children[direct])
	{
		runner = runner->children[direct];
	}
	
	return runner;
}

/******************************************************************************/
/*function to find prev/next according to direction*/
/*left indicates minimum, right maximum*/	
 /*if max it will return duumy*/
 /*next on max will return duumy_max (30), prev on min will return null*/
static bst_node_t *NextValue(bst_node_t *node, child_t direct)
{
	bst_node_t *result = NULL, *parent = NULL;
	
	/*if there is a child in same direct, Search down*/
	if (NULL != node->children[direct])
	{
		/* pass the max/ min subtree and find min/max */
		result = Extremum(node->children[direct], !direct); 
	}
	/* if there isn't a child, Search up and return parent*/
	else 
	{
		parent = node->parent;
		
		while (NULL != parent && node != parent->children[!direct])
		{
			node = parent;
			parent = node->parent;
		}
			
		result = parent;
	}
			
	return result;
}

/******************************************************************************/
static bst_node_t *BSTSearch(bst_t *bst, void *data, child_t *side)
{
	bst_node_t *parent = &bst->dummy_max; /*start Search from dummy max*/
	int comp_result = -1; /*-1 is left child, 1 is right child*/
	*side = LEFT;
	
	/*0 exit value- when equal*/
	while (0 != comp_result && NULL != parent->children[*side])
	{
		parent = parent->children[*side];
		comp_result = bst->cmp_func(data, parent->data);
		*side = CMP_TO_CHILD(comp_result);
	}
	return parent;
}

/******************************************************************************/
static int CountOneNode(void* data_ref, void* num_nodes)
{
	assert(NULL != data_ref);
	assert(NULL != num_nodes);
	
	++*(size_t*)num_nodes;
	
	return 0;
}	

/******************************************************************************/
static bst_node_t *BSTItrToNode(bst_itr_t itr)
{
	return itr.node;
}

static bst_itr_t BSTNodeToItr(bst_node_t *node)
{
	bst_itr_t itr = {0};
	itr.node = node;
	return itr;
}
	
/******************************************************************************/
static bst_node_t *CreateNode(bst_node_t *parent, void *data)
{
	bst_node_t *node = (bst_node_t*)calloc(1, sizeof(bst_node_t));
	if (NULL == node)
	{
		return NULL;
	}
	
	node->data = data;
	node->parent = parent;
	
	return node;
}
	
static void BSTDestroyNode(bst_node_t *node)
{
	assert(NULL != node);
	
	memset(node, 0, sizeof(bst_node_t));
	free(node);
	node = NULL;
}
/******************************************************************************/


