typedef int (*compare)(void*, void*); /*most of the function use*/

/*O(1)*/
bst* BSTCreate(compare cmp_func); 
/*O(1)*/
void BSTDestroy(bst_t *bst);
/*O(n)*/
size_t BSTSize(bst_t *bst);
/*O(1)*/
int BSTIsEmpty(bst_t *bst);

itr_bst BSTInsert(bst_t* bst, void *data); /*closed*/

/*A.C: O(log(n))  W.C: O(n)*/
void BSTRemove(itr_t *itr); /*can return void*/ מקבל בהכרח משהו שקיים בעץ, למצוא מחליף

/*minimum value*/
itr_bst BSTBegin(bst_t *bst);
/*O(1) validi*/ 
itr_bst BSTEnd(bst_t *bst);
/*O(?)*/ /*not o(1)*/
itr_bst BSTPrev(itr_bst itr);
/*O(?)*/ /*not o(1)*/
itr_bst BSTNext(itr_bst itr);
int BSTIsSameIter(itr_bst itr1, itr_bst itr2);
void *GetData(itr_bst itr);

/*A.C: O(log(n))  W.C: O(n)*//*closed*/
itr_bst BSTFind(bst_t *bst, void *data);/*match is compare?*//*key*///*invalid itr end, tail no valid*/

/*פונ' מסוכנת אפשר להרוס את הסדר'*/
int BSTForEach(itr_bst from, itr_bst to, action act_fnc, void* params);
