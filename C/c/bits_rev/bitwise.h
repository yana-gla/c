/*************************************************************************
Author: Yana Glazer

BitWise WorkSheet

Reviwed by: Sharona Amran

17/01/2025
*************************************************************************/
#ifndef __BITWISE_H__
#define __BITWISE_H__

typedef unsigned char uchar_t;

long Pow2(unsigned int x, unsigned int y);
int IsPow2Lp(unsigned int n);
int IsPow2WLp(unsigned int n);
int Ads1(int num);
void Prnt3Bits(const unsigned int arr[], size_t n);
uchar_t ByteMirror1(uchar_t byte);
uchar_t ByteMirror2(uchar_t b);
int Chk2_26Bit(uchar_t num);
int Chk1_26Bit(uchar_t num);
uchar_t Swap_35Bit1(uchar_t num);
uchar_t Swap_35Bit2(uchar_t num);
unsigned int Clsst16(const unsigned int num);
void Swap(int *x, int *y);
uchar_t Cnt1BitsLp(unsigned int num);
uchar_t Cnt1BitsWLp(unsigned int i);
void PrntFltBts1(float num);
void PrntFltBts2(float fp);

#endif
