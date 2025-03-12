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
static bst_node_t *BSTSearch(bst_t *bst, void *data);
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
	
	bst = (bst_t*)calloc(1, sizeof(bst_t)); /*calloc to null dummy*/
	if (NULL == bst)
	{
		return NULL;
	}
	
	bst->cmp_func = comparator;
	
	return bst;
}

/*next prev O(1)*/
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
		/*if not leaf, go down*/
		if (!(NULL == node->children[LEFT] && NULL == node->children[RIGHT]))
		{
			child_side = node->children[LEFT] != NULL ? LEFT : RIGHT;
			node = node->children[child_side];
		}
		else /*leaf*/
		{
			child_side = node->parent->children[LEFT] == node ? LEFT : RIGHT;
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

/*returns iterator of minimum value of the tree*/
bst_itr_t BSTItrBegin(const bst_t* bst)
{
	assert (NULL != bst);
	return BSTNodeToItr(Extremum((bst_node_t*)&bst->dummy_max, LEFT));
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

void* BSTGetData(bst_itr_t itr)
{
	bst_node_t *node = BSTItrToNode(itr);
	return (node->data);
}

int BSTIsEmpty(const bst_t* bst)
{
	assert(NULL != bst);
	return (NULL == bst->dummy_max.children[LEFT]);
}


size_t BSTCount(const bst_t* bst)
{
	bst_itr_t itr = BSTItrBegin(bst);/*start from smallest node*/
	size_t num_nodes = 0;
	
	assert(NULL != bst);
	
	while (!BSTIsSameItr(itr ,BSTItrEnd(bst)))
	{
		++num_nodes;
		itr = BSTItrNext(itr);
	}
	
	return num_nodes;
}




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
		BSTDestroyNode(node);
	}
	else /*leaf*/
	{
		node->parent->children[parent_side] = NULL;
		BSTDestroyNode(node);
	}
}


/*Cases- empty, found, not found*/
bst_itr_t BSTFind(const bst_t* bst, void* data)
{
	bst_itr_t itr_search = {0};
	int comp_result = 0;
	
	assert(NULL != bst);
	
	if (BSTIsEmpty(bst))
	{
		return BSTItrEnd(bst);
	}
	
	itr_search = BSTNodeToItr(BSTSearch((bst_t*)bst, data));
	comp_result = bst->cmp_func(data, BSTGetData(itr_search));
	
	return ((0 == comp_result) ? itr_search : BSTItrEnd(bst));
}

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

/*insert- return parent node to attach to, find- return node of matchind data*/
/*find perspective- search may not find data if the data isn't exist, will return 
	leaf*/
bst_itr_t BSTInsert(bst_t* bst, void* data)
{	
	bst_node_t *parent = NULL, *new_node = NULL;
	int comp_result = 0;
	child_t side = 0;
	
	assert(NULL != bst);

	parent = BSTSearch(bst, data);
	
	new_node = CreateNode(parent, data);
	if (NULL == new_node)
	{
		return BSTItrEnd(bst);
	}
	
	/*Update child in parent- which side?*/

	if (&bst->dummy_max == parent) /*root, dummy_max data it's not actual data*/
	{
		side = LEFT;
	}
	else
	{
		comp_result = bst->cmp_func(data, parent->data);
		side = CMP_TO_CHILD(comp_result);
		
	}
	
	parent->children[side] = new_node;
	
	return BSTNodeToItr(new_node);
}

static bst_node_t *BSTSearch(bst_t *bst, void *data)
{
	bst_node_t *parent = &bst->dummy_max; /*start Search from dummy max*/
	int comp_result = -1;
	child_t side = LEFT;
	
	/*0 exit value- when equal*/
	while (0 != comp_result && NULL != parent->children[side])
	{
		parent = parent->children[side];
		comp_result = bst->cmp_func(data, parent->data);
		side = CMP_TO_CHILD(comp_result);
	}
	return parent;
}
	
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
	


