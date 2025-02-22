#include <stddef.h> /*size_t*/
#include <assert.h> /*assert*/
#include <string.h> /*memset*/
#include <stdlib.h> /*calloc*/
#include "circ_buf.h"

#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT)) /*later*/
#define MINN(a, b) ((a < b) ? (a) : (b))
#define NEQUAL(a, b, c) ((a == b) ? -1 : (c))
#define IF_EMPTY_SET_0(a)  (((a)== -1) ? 0 : (a))

/*typedef struct circ_buf circ_buf_t;*/
struct circ_buf
{
	size_t capacity;
	ssize_t head_idx;  /*first*/
	ssize_t tail_idx; /*last*/
	char arr[1];
};

/*Allocates memory to Circular BUffer*/
circ_buf_t* BufCreate(size_t capacity)
{
	circ_buf_t* cir_buf = (circ_buf_t*)calloc(1, OFFSETOF(circ_buf_t, arr) + capacity);
	
	if (NULL == cir_buf)
	{
		return (NULL);
	}
	
	cir_buf->capacity = capacity;
	cir_buf->head_idx = -1;
	cir_buf->tail_idx = -1; /*check*/
	
	return (cir_buf);
}

void BufDestroy(circ_buf_t* buf)
{
	assert(NULL != buf);
	memset(buf, 0, sizeof(circ_buf_t));/*later*/
	free(buf);
}


size_t BufSize(const circ_buf_t* buf)
{
	size_t size = 0;
	
	assert(NULL != buf);
	
	/*if idx_tail not (-1) the buffer not empty*/

	size = (buf->tail_idx + buf->capacity - buf->head_idx) % buf->capacity;
	
	if ((0 == size) && (buf->tail_idx != -1))
	{
		size = buf->capacity;
	}
	
	return (size);
}

size_t BufFreeSpace(const circ_buf_t* buf)
{
	assert(NULL != buf);
	return (buf->capacity - BufSize(buf));
	
}

int BufIsEmpty(const circ_buf_t* buf)
{
	assert(NULL != buf);
	return (-1 == buf->tail_idx);
}

/*head*/
/*read from buffer to dst */
ssize_t BufRead(circ_buf_t* buf, char* dst, size_t n_bytes)
{
	size_t first_read = 0;
	size_t second_read = 0;
	
	assert(NULL != buf && NULL != dst);
	
	n_bytes = MINN(n_bytes, BufSize(buf));
	


	first_read = MINN(buf->capacity - buf->head_idx, n_bytes);
	memcpy(dst, buf->arr + buf->head_idx, first_read);
	
	
	
	buf->head_idx = (buf->head_idx + first_read) % (buf->capacity);	
	dst += first_read;
	
	second_read = n_bytes - first_read;
	memcpy(dst, buf->arr + buf->head_idx, second_read);
	buf->head_idx = (buf->head_idx + second_read) % (buf->capacity);	
	
	buf->tail_idx = NEQUAL(n_bytes, BufSize(buf), buf->tail_idx);
	buf->head_idx = NEQUAL(buf->tail_idx, -1, buf->head_idx);
	
	return n_bytes;
}

/*tail*/
/* write from src to buffer */
ssize_t BufWrite(circ_buf_t* buf, const char* src, size_t n_bytes)
{
	size_t first_write = 0;
	size_t second_write = 0;
	
	assert(NULL != buf && NULL != src );
	
	/*if n bigger than free space in buffer*/
	/*n_bytes will be the minimum of given n_bytes and the free space in buffer*/
	n_bytes = MINN(n_bytes, BufFreeSpace(buf));

	/*if buffer is empty set indices to 0*/		
	buf->head_idx = IF_EMPTY_SET_0(buf->head_idx);
	buf->tail_idx = IF_EMPTY_SET_0(buf->tail_idx);
	
	/*first part is the minimum of given n_bytes and the space till the end*/
	first_write = MINN(buf->capacity - buf->tail_idx, n_bytes);
	memcpy(buf->arr + buf->tail_idx, src, first_write);
	
	buf->tail_idx = (buf->tail_idx + first_write) % (buf->capacity); 
	src += first_write;
	
	/*if first part was n_bytes than second part will be 0*/
	second_write = n_bytes - first_write;
	memcpy(buf->arr + buf->tail_idx, src, second_write);
	buf->tail_idx = (buf->tail_idx + second_write) % (buf->capacity); 

	return ((ssize_t)n_bytes);
}




