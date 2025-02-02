#include <stddef.h>		/* for size_t */

typedef struct node_t node_t;
typedef struct slist_t slist_t;
typedef struct node_t* slist_itr_t;

typedef int(*match_func_t) (void*, void*);
typedef int(*action_func_t) (void*, void*); 

slist_t* ListCreate();/**/
void ListDestroy(slist_t* list);

slist_itr_t ListItrBegin(const slist_t* list);/**/
slist_itr_t ListItrNext(slist_itr_t itr);/**/
slist_itr_t ListItrEnd(slist_t* list);/**/
int ListItrIsEqual(slist_itr_t itr1, slist_itr_t itr2);/**/

void* ListGetData(slist_itr_t itr);/**/
void ListSetData(slist_itr_t itr, const void* data);/**/

slist_itr_t ListInsertBefore(slist_itr_t itr, const void* data);
slist_itr_t ListRemove(slist_itr_t itr);

size_t ListCount(const slist_t* list);
int ListIsEmpty(slist_t* list);

slist_itr_t ListFind(slist_itr_t from, slist_itr_t to, match_func_t is_match, const void* data);
int ListForEach(slist_itr_t from, slist_itr_t to, action_func_t action_func, const void* param);
