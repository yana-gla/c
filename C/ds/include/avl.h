/*******************************************************************************
* File: avl.h
*
* Purpose:
*   Implement Balanced Binary Search Tree recursively  (AVL)
*	Balance: Height difference no more than one 
*	O(log(n))- Insertion, Deletion, Search
*	
*
* Author:
*   Yana Glazer
* Code reviewd by:
*   __________
*
*Date: 18/03/2025
*Last Update: --/--/----
*******************************************************************************/
#ifndef __AVL_H__
#define __AVL_H__

#include <stddef.h>  /*size_t*/



/* avl_cmp_func - Comparator Function
 * This user-defined function performs comparison between two items and used
 * to determine ordering.
 *
 * Parameters:
 *      first - reference to first item
 *      second - reference to second item
 * 
 * Returns:
 *      -1 - first item comes before second item
 *       0 - first item has same value as second item
 *      +1 - first item comes after second item
 */
typedef int (*avl_cmp_t)(const void* first, const void* second);

/* AVL Action Function
* User defined function which executes operation on a given element of the AVL.
* Used in ForEach to perform defined operation on each element.
* 
* Params:
* data_ref - reference to data of current node
* params - reference to user-defined parameters
*
*
* Returns:
*		status:  0 - operation success
*			   	non-zero - operation failed, and exit ForEach
*
* Time Complexity: O(1)
* Space Complexity: O(1)
 */
typedef int(*avl_action_t)(void* data_ref, void* params);

/******************************************************************************/
/*enum for traversal order*/
typedef enum
{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER,
    ORDER_SIZE
} avl_traversal_t;

typedef struct avl avl_t;

/****************************** API FUNCTION ***********************************
* AVLCreate
* creates new AVL
* 
* Params:
* 	cmp_func - compare function to determine ordering
*
* Returns:
* 	On success- pointer to new AVL
*	On failure- NULL
*
* Time Complexity: O(1)
* Space Complexity: O(1)
*******************************************************************************/
avl_t* AVLCreate(avl_cmp_t cmp_func);

/*******************************************************************************
* AVLDestroy
* Destroy AVL tree (post-order) and free allocated memory
* 
* Params:
* 	avl_tree- pointer to an AVL tree
*
* Returns:
* 	void
*
* Time Complexity: O(n)
* Space Complexity: O(1)
*******************************************************************************/
void AVLDestroy(avl_t* avl_tree);

/*******************************************************************************
* AVLRemov
* Removes node pointed by data and frees memory
* 
* Params:
* 	avl_tree- pointer to an AVL tree
*   data - A pointer to the data node to be removed
*
* Returns:
* 	void
*
* Time Complexity: O(log(n))
* Space Complexity: O(1)
*
*Note:
	If data doesn't exist in the tree, the function does nothing
*******************************************************************************/
void AVLRemove(avl_t* avl_tree, void* data);

/*******************************************************************************
* AVLInsert
* Insert new data to the tree
* 
* Params:
* 	avl_tree- pointer to an AVL tree
*   data - A pointer to the data node to be removed
*
* Returns:
*		status:  0 -  success
*		non-zero - failed (alocation failure)
*
* Time Complexity: O(log(n))
* Space Complexity: O(1)
*
*Note:
*	If data exist in the tree, the function doesnt nothing
*	The tree Balanced after insertion	
*******************************************************************************/
int AVLInsert(avl_t* avl_tree, void* data); 

/*******************************************************************************
* AVLHeight
* Returns the height of the tree
* 
* Params:
* 	avl_tree- pointer to an AVL tree
*
* Returns:
*		height of the tree
*
* Time Complexity:  O(1)
* Space Complexity: O(1)
*
*Note:
* Height of empty tree- 0, height of leaf is 1
*******************************************************************************/
size_t AVLHeight(const avl_t* avl_tree);

/*******************************************************************************
* AVLCount
* counts number of node in the tree
* 
* Params:
* 	avl_tree- pointer to an AVL tree
*
* Returns:
* number of node in the tree
*
* Time Complexity: O(n)
* Space Complexity: O(1)
*
*Note:
* pre-order traversal
*******************************************************************************/
size_t AVLCount(const avl_t* avl_tree);

/*******************************************************************************
* AVLIsEmpty
* checks if the tree is empty
* 
*
* Params:
* 	avl_tree- pointer to an AVL tree
*
* Returns:
* 	1- empty
*	0- not empty
*
* Time Complexity: O(1)
* Space Complexity: O(1)
*******************************************************************************/
int AVLIsEmpty(const avl_t* avl_tree);

/*******************************************************************************
* AVLContains
* checks if given data is in the tree
* 
* Params:
* 	avl_tree- pointer to an AVL tree
*   data - A pointer to the data node to be removed
*
* Returns:
* 	pointer to data
*	NULL- data is not found
*
* Time Complexity: O(log(n))
* Space Complexity: O(1)
*******************************************************************************/
void* AVLContains(const avl_t* avl_tree, void* data); 

/*******************************************************************************
* AVLForEach
* execute action on each data in the tree
* 
* Params:
*      avl_tree - pointer to an AVL tree
*      action - user-defined function to apply to each data
*      params - additional parameter to be passed to the action function
*      order - traversal order (PRE_ORDER, IN_ORDER, POST_ORDER)
*
* Returns:
*		status: 0 - all operation done successfly
*		non-zero - operation failed, and exit ForEach 
* Time Complexity: O(n)
* Space Complexity: O(1)
*
*Note: 
*	action function should'nt change ordering 
*******************************************************************************/

int AVLForEach(avl_t* avl_tree,
			   avl_action_t action,
			   void* params,
			   avl_traversal_t traversal);

#endif /* AVL */

