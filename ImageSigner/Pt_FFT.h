#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define __PI 3.1415926535f
#define _IN
#define _OUT

typedef struct __complex
{
	float re;// really 
	float im;// imaginary
}complex,*pcomplex;

void FFT(_IN complex x[],_OUT complex X[],int N);
void IFFT(_IN complex X[],_OUT complex x[],int N);
void FFT_2(_IN complex x[],_OUT complex X[],int N_N);
void IFFT_2(_IN complex X[],_OUT complex x[],int N_N);
void FFT_2_Shift(_IN complex _in[],_OUT complex _out[],int N_N);