/****************************** bst.h *********************************/

/*
* Comparator function : receives and compares 2 data references
* Output:
*   (int)-1 if first item comes before second item
*   (int) 0 if the items have the same "value"
*   (int) 1 if the first item comes after the second item
*/
typedef int (*bst_comparator_t)(const void* first, const void* second);

/*
* Action function : receives a reference to data and reference to
*               any desired functions parameters, respectively.
*               will be iteratively performed on each item of tree,
*               unless stopped by non-zero output signal
* Output:
*   (int) 0       - success/continue (on this output, foreach will proceed
*                   to perform action on next item)
*   (int) >0, <0  - failure/stop (on this output, foreach will exit and
*                   return this signal value)
*/
typedef int (*bst_action_t)(void* data_ref, void* params);


typedef struct bst bst_t;
typedef struct node bst_node_t;

typedef struct bst_itr
{
    bst_node_t* node;
} bst_itr_t;

/* 
Create new tree 
Time Complexity: O(1)
*/
bst_t* BSTCreate(bst_comparator_t comparator);

/* 
Destroy tree 
Time Complexity: O(n)
*/
void BSTDestroy(bst_t* bst);

/* 
Return how many nodes are in the tree
Time Complexity: O(n)
*/
size_t BSTCount(const bst_t* bst);

/* 
Return 1 if tree has no nodes, 0 otherwise
Time Complexity: O(1)
*/
int BSTIsEmpty(const bst_t* bst);

/* 
Insert new node to the tree, return pointer (iterator) to that node
If failed to insert -> return BSTEnd
Time Complexity: A.C -> O(log(n)) W.C -> O(n)
*/
bst_itr_t BSTInsert(bst_t* bst, void* data);

/* 
Remove a node pointed to by itr from the tree
Time Complexity: A.C -> O(log(n)) W.C -> O(n)
*/
void BSTRemove(bst_itr_t itr);

/* 
Return pointer (iterator) to the smallest value in the tree
Time Complexity: A.C -> O(log(n)) W.C -> O(n)
*/
bst_itr_t BSTItrBegin(const bst_t* bst);

/*
Returns ending iterator
Time Complexity: O(1)
*/
bst_itr_t BSTItrEnd(const bst_t* bst);

/* 
Return pointer (iterator) to the next (smaller) node
Time Complexity: /worng!!! A.C -> O(log(n)), W.C -> O(n)
*/
bst_itr_t BSTItrPrev(bst_itr_t itr);

/* 
Return pointer (iterator) to the next (larger) node
Time Complexity: worng!!! A.C -> O(log(n)), W.C -> O(n)
*/
bst_itr_t BSTItrNext(bst_itr_t itr);

/* 
Return 1 if iterators point to same node
Time Complexity: O(1)
*/
int BSTIsSameItr(bst_itr_t itr1, bst_itr_t itr2);

/* 
Return data od node pointed to by itr
Time Complexity: O(1)
*/
void* BSTGetData(bst_itr_t itr);

/*
Compare (via cmp_func_t) nodes with data, if found return the itr
Time Complexity:A.C -> O(log(n)), W.C -> O(n)
*/
bst_itr_t BSTFind(const bst_t* bst, void* data);

/* 
For each node in tree do action (with param if needed), 
return 1 for failure 0 for success
Time if action function destroys order, can result in undefined behavior
Time Complexity: O(n)
*/
int BSTForEach(bst_itr_t from,
			   bst_itr_t to,
			   bst_action_t action,
			   void* params);


/****************************** bst.c *********************************/

