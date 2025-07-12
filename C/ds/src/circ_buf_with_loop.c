#include <stddef.h> /*size_t*/
#include <assert.h> /*assert*/
#include <string.h> /*memset*/
#include <stdlib.h> /*calloc*/
#include "circ_buf.h"

#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT)) /*later*/

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
ssize_t BufRead(circ_buf_t* buf, char* dst, size_t n_bytes)
{
	size_t bytes_read = n_bytes;
	assert(NULL != buf && NULL != dst);
	
	/*if n bigger than buffer size*/
	if (n_bytes > BufSize(buf))
	{
		n_bytes = BufSize(buf);
		bytes_read = n_bytes;
	}
	
	while (0 < n_bytes--)
	{
		*dst++ = buf->arr[buf->head_idx];
		buf->head_idx = (buf->head_idx + 1) % (buf->capacity);
		/*--n;*/
	}
	
	/*Will empty the buffer, insertion to tail will start from begining*/
	if (bytes_read == BufSize(buf))
	{	
		buf->tail_idx = -1;
		buf->head_idx = -1;
	}
	
	return (bytes_read);
}

/*tail*/
ssize_t BufWrite(circ_buf_t* buf, const char* src, size_t n_bytes)
{
	size_t bytes_write = n_bytes;
	
	assert(NULL != buf && NULL != src );
	
	/*if n bigger than free space in buffer*/
	if (n_bytes > BufFreeSpace(buf))
	{
		n_bytes = BufFreeSpace(buf);
		bytes_write = n_bytes; /*check*/
	}
	
	/*if buffer is empty*/
	if (buf->tail_idx < 0)
	{
		buf->head_idx = 0;
		buf->tail_idx = 0;
	}
	
	while (0 < n_bytes--)
	{
		buf->arr[buf->tail_idx] = *src++;
		buf->tail_idx = (buf->tail_idx + 1) % (buf->capacity);

	}
	
	return ((ssize_t)bytes_write);
}




