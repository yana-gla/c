/******************************************************************************
* File: hash_table.h
*
* Purpose:
*  Implement Hash DS
*
* Author:
*   Yana Glazer
* 
*Date:
*	24/03/2025
*
* Code Reviewd by:
*
******************************************************************************/
#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stddef.h> /*size_t*/

/* Hash Table: A data structure with average O(1) operations
 * Space complexity: average case O(n), worst case O(m + n) */
typedef struct ht_table ht_table_t;


/* Hash Function
 * User-defined function that converts a key into a unique number
 *
 * Params:
 *      key - pointer to key data
 *
 * Returns:
 *      unique hash value corresponding to the key
 */
typedef size_t (*ht_hash_func_t)(const void* key);

/* Match function
 * User-defined function that compares two keys for equality
 *
 * Params:
 *      key1, key2 - pointers to keys being compared
 *
 * Returns:
 *      1 if keys match, 0 otherwise
 */
typedef int (*ht_match_func_t)(const void* key1, const void* key2);

/* Action function
 * User-defined function to perform an action on key-value pairs
 *
 * Params:
 *      key - pointer to key
 *      value - pointer to value
 *      params - additional parameters for the action
 *
 * Returns:
 *      0 to continue iteration, non-zero to stop
 */
typedef int (*ht_action_func_t)(void* data, void* params);



/* Create a new hash table - O(n) */
/* Create all d lists in create */
ht_table_t* HTCreate(ht_match_func_t match_func, ht_hash_func_t hash_func, size_t capacity);

/* Destroy given hash table, O(n) */
void HTDestroy(ht_table_t* table);

/* Remove an entry from the hash table - average O(1), worst O(n) */
void HTRemove(ht_table_t* table, void* key);

/* Insert a key-value pair into the hash table - average O(1), worst O(n)
 * Returns 0 on success, non-zero on failure */
int HTInsert(ht_table_t* table, void* key, void* value);

/* Get the number of entries in the hash table - O(n) */
size_t HTCount(const ht_table_t* table);

/* Check if the hash table is empty - O(m), m = number of buckets
 * Returns 1 if empty, 0 otherwise */
int HTIsEmpty(const ht_table_t* table);

/* Find a value by key in the hash table - average O(1), worst O(n)
 * Returns pointer to value if found, NULL otherwise */
void* HTFind(const ht_table_t* table, void* key);

/* Apply a function to each value in the hash table - O(n)
 * Returns result from action_func if it returns non-zero, 0 otherwise */
int HTForEach(ht_table_t* table, ht_action_func_t action_func, void* params);


#endif /* HASH_TABLE */
