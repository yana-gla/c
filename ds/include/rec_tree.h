enum traversal

btr_t *create(cmp);
void destroy (btr_t *btr); post order
void remove(btr_itr_t itr);
btr_itr_t insert(btr_t *btr, void *data);
size_t height(btr_t *btr);
size_t size(btr_t *btr);
int is_empty(btr_t *btr);
btr_itr_t find(btr_t *btr, void *param);
int foreach(btr_itr_t from, btr_itr_t to, func_ptr, void *param, travers_order); /*pre/ in post order*/ ?
