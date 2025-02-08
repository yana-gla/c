 #include <sys/types.h>
 #include <stdio.h>


typedef struct circ_buf circ_buf_t;


circ_buf_t* BufCreate(size_t capacity);

void BufDestroy(circ_buf_t* buf);

/* number of free bytes in the buffer */
size_t BufFreeSpace(const circ_buf_t* buf);

/* number of elements in the buffer */
size_t BufSize(const circ_buf_t* buf);

/* check if buffer is empty */
int BufIsEmpty(const circ_buf_t* buf);

/* read from buffer to dst */
ssize_t BufRead(circ_buf_t* buf, char* dst, size_t n_bytes);

/* write from src to buffer */
ssize_t BufWrite(circ_buf_t* buf, const char* src, size_t n_bytes);


/********************************** NOTES **********************************/
/*
*the flexible array MUST BE the last element in the struct.

*allocate memory only once (calloc for the struct, according to offset)
	
*malloc + memset VS calloc:
	- calloc set element to 0 when memory accessed
	- memset sets initializes memory on the spot
	< we use calloc because it's easier for now >
	
	*/
	
