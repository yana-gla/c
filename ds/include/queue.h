typedef struct Queue queue_t;

queue_t* QueueCreate(); 
void QueueDestroy(queue_t* queue);
int QueueEnqueue(queue_t* queue, void* data);
void QueueDequeue(queue_t* queue);
void* QueuePeek(const queue_t* queue);

size_t QueueSize(const queue_t* queue);
int QueueIsEmpty(const queue_t* queue);
queue_t* QueueAppend(queue_t* queue_dst, queue_t* queue_src);



