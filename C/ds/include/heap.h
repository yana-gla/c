#ifndef __HEAP_H__
#define __HEAP_H__


#include <stddef.h> /*size_t*/

typedef struct heap heap_t;

/* heap_cmp_func - Comparator Function
 * This user-defined function performs comparison between two
 * items passed by reference, and is used to determine ordering
 * priority in heap.
 *
 * Parameters:
 *      first - reference to first item
 *      second - reference to second item
 * 
 * Returns:
 *      <0 - first item has higher priority
 *       0 - items  have same priority
 *      >0 - second item has higher priority
 */

/* heap_match_func - Match Function
 * This user-defined function determins
 */

typedef int (*heap_cmp_func_t)(const void* first, const void* second);

/* Space Complexity for all operations is O(1) */

/* default capacity. O(1) */
heap_t* HeapCreate(int (*heap_cmp_func)(const void* first, const void* second));

/* O(1) */
void HeapDestroy(heap_t* heap);

/* O(log(n))? return success 0 failure 1 */
/* Check time complexity for average and worst */
int HeapPush(heap_t* heap, void* data);

/* O(log(n))? */
/* Check time complexity for average and worst */
void HeapPop(heap_t* heap);

/* O(1) */
void* HeapPeek(const heap_t* heap);

/* if found return data. if not found return NULL,  
    O(n) */
void* HeapRemove(heap_t* heap, 
                int (*heap_match_func)(const void* data, void* params),
                void* params);
                
int HeapIsEmpty(const heap_t* heap);

/* O(1) */
size_t HeapSize(const heap_t* heap);

/* O(1) */


 
#endif /*HEAP*/


