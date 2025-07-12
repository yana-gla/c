/*************************************************************************
Author: Yana Glazer

Struct WorkSheet

Reviwed by: Ofir Hasson, Ben Nadav

22/01/2025
*************************************************************************/
#ifndef __STRUCTARRAYTYPES_H__
#define __STRUCTARRAYTYPES_H__

typedef struct element_struct element_t;
typedef enum {SUCCESS, FAIL} state_t; 
struct element_struct {
	void *ptr_data;                 /* like- int*,  ptr to data */
	void (*p_prnt)(element_t* element); /*pointer to print function*/
	state_t (*p_add)(element_t* element, int a); /*pointer to add function*/ 
	void (*p_cln)(element_t* element); /*pointer to clen function*/
};               /*general member*/


state_t InitInt(element_t *ptr_strct, int x);
state_t InitFlt(element_t *ptr_strct, float flt);
state_t InitStr(element_t *ptr_strct, char *str);

void PrntInt(element_t *ptr_strct);
void PrntFlt(element_t *ptr_strct);
void PrntStr(element_t *ptr_strct);

state_t AddInt(element_t *ptr_strct, int num);
state_t AddFlt(element_t *ptr_strct, int num);
state_t AddStr(element_t *ptr_strct, int num);

void ClnStr(element_t *ptr_strct);
void EmptyFnct(element_t *ptr_strct);

#endif
