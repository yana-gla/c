/*******************************************************************************
* File: avl.h
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
#ifndef __AVL_H__
#define __AVL_H__

#include <stddef.h>  /*size_t*/

typedef enum
{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER,
    ORDER_SIZE
} avl_traversal_t;

typedef struct avl avl_t;

/* avl_cmp_func - Comparator Function
 * This user-defined function performs comparison between two
 * items passed by reference, and is used to determine ordering
 * scheme/ranking of keys in AVL.
 *
 * Parameters:
 *      first - reference to first item
 *      second - reference to second item
 * 
 * Returns:
 *      -1 - first item comes before second item
 *        0 - first item has same value as second item
 *      +1 - first item comes after second item
 */
typedef int (*avl_cmp_t)(const void* first, const void* second);



/* avl_action_func - Action Function
 * User defined function that execute operation on a given element of the AVL.
 * Used in ForEach to perform the defined operation on each element, in-order.
 * 
 * Parameters:
 *      data_ref - reference to data/item
 *      params - reference to user-defined parameters
 * 
 * Returns:
 *      0 on successful operation
 *		non-zero values failed operation (and exit ForEach)
 */
typedef int(*avl_action_t)(void* data_ref, void* params);



/*******************************************************************************
* AVLCreate
* creates new AVL
* 
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
/* create new tree, Time Complexity: O(1) */
avl_t* AVLCreate(avl_cmp_t cmp_func);

/*******************************************************************************
* AVLDestroy
* Destroy AVL tree (post-order) 
* 
* Params:
* 	avl_tree
*
* Returns:
* 	void
*
* Time Complexity: O(n)
* Space Complexity: O(1)
*******************************************************************************/
void AVLDestroy(avl_t* avl_tree);

/*******************************************************************************
* AVLCreate
* creates new BST 
* 
*
* Params:
* 	cmp_func - compare function to determine ordering
*
* Returns:
* 	
*
* Time Complexity: 
* Space Complexity:
*******************************************************************************/
/* get data to remove, Time Complexity: O(log(n)) */
void AVLRemove(avl_t* avl_tree, void* data);

/*******************************************************************************
* AVLCreate
* creates new BST 
* 
*
* Params:
* 	cmp_func - compare function to determine ordering
*
* Returns:
* 	
*
* Time Complexity: 
* Space Complexity:
*******************************************************************************/
/* insert data to right place in tree, return status (0 for success), Time Complexity: O(log(n)) */
int AVLInsert(avl_t* avl_tree, void* data); 

/*******************************************************************************
* AVLCreate
* creates new BST 
* 
*
* Params:
* 	cmp_func - compare function to determine ordering
*
* Returns:
* 	
*
* Time Complexity: 
* Space Complexity:
*******************************************************************************/
/* return hight of tree, Time Complexity: O(1) */
size_t AVLHeight(const avl_t* avl_tree);

/*******************************************************************************
* AVLCreate
* creates new BST 
* 
*
* Params:
* 	cmp_func - compare function to determine ordering
*
* Returns:
* 	
*
* Time Complexity: 
* Space Complexity:
*******************************************************************************/
/* count items in the tree, (pre-order) Time Complexity: O(n) */
size_t AVLCount(const avl_t* avl_tree);

/*******************************************************************************
* AVLCreate
* creates new BST 
* 
*
* Params:
* 	cmp_func - compare function to determine ordering
*
* Returns:
* 	
*
* Time Complexity: 
* Space Complexity:
*******************************************************************************/
/* return 1 if tree is empty, Time Complexity: O(1) */
int AVLIsEmpty(const avl_t* avl_tree);

/*******************************************************************************
* AVLCreate
* creates new BST 
* 
*
* Params:
* 	cmp_func - compare function to determine ordering
*
* Returns:
* 	
*
* Time Complexity: 
* Space Complexity:
*******************************************************************************/
/* find data in tree, return data if found, NULL if not ,Time Complexity: O(log(n)) */
void* AVLContains(const avl_t* avl_tree, void* data); 

/*******************************************************************************
* AVLCreate
* creates new BST 
* 
*
* Params:
* 	cmp_func - compare function to determine ordering
*
* Returns:
* 	
*
* Time Complexity: 
* Space Complexity:
*******************************************************************************/
/* do action function on each node in tree with specified traversal, Time Complexity: O(n) 
 cant change the order in the action function */
int AVLForEach(avl_t* avl_tree,
			   avl_action_t action,
			   void* params,
			   avl_traversal_t traversal);

#endif /* AVL */



/*לא ללכתוב קוד כפול*/
/*פסאודו קוד עמוק*/
/*לבדוק ביצועים עם 100,000 צמתים*/
/*שלבים במימוש*/
/*א. עץ חיפוש בינארי רקורסיבי*/
/*ב.1. הכנסה עם בלאנס*/
/*ב.2. הוצאה עם בלאנס*/
/*3. stress test*/

/* Other notes: no code duplication */
