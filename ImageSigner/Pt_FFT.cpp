#include "Pt_FFT.h"



complex complexBuild(float re,float im)
{
	complex cx;
	cx.re=re;
	cx.im=im;
	return cx;
}

complex complexAdd(complex a,complex b)
{
	complex ret;
	ret.re=a.re+b.re;
	ret.im=a.im+b.im;
	return ret;
}

complex complexMult(complex a,complex b)
{
	complex ret;
	ret.re=a.re*b.re-a.im*b.im;
	ret.im=a.im*b.re+a.re*b.im;
	return ret;
}

void DFT(_IN complex x[],_OUT complex X[],int N)
{
	int k,n;
	complex Wnk;
	for (k=0;k<N;k++)
	{
		X[k].re=0;
		X[k].im=0;
		for (n=0;n<N;n++)
		{
			Wnk.re=(float)cos(2*__PI*k*n/N);
			Wnk.im=(float)-sin(2*__PI*k*n/N);
			X[k]=complexAdd(X[k],complexMult(x[n],Wnk));
		}
	}
}

void IDFT(_IN complex X[],_OUT complex x[],int N)
{
	int k,n;
	float im=0;
	complex ejw;
	for (k=0;k<N;k++)
	{
		x[k].re=0;
		x[k].im=0;
		for (n=0;n<N;n++)
		{
			ejw.re=(float)cos(2*__PI*k*n/N);
			ejw.im=(float)sin(2*__PI*k*n/N);
			x[k]=complexAdd(x[k],complexMult(X[n],ejw));
		}

		x[k].re/=N;x[k].im/=N;
	}
}   

void FFT_Base2(_IN _OUT complex x[],int N)
{
	int exbase,exrang,i,j,k;
	complex excomplex,Wnk,cx0,cx1;
	if (N>>2)
	{
		// x[] 4 base odd/even Sort
		exbase=1;
		exrang=0;
		while (exrang<N)
		{
			exrang=exbase<<2;

			for (i=0;i<N/exrang;i++)//for each token
			{
				for (j=0;j<exbase;j++)//for each atom in token
				{
					excomplex=x[exrang*i+exbase+j];
					x[exrang*i+exbase+j]=x[exrang*i+exbase*2+j];
					x[exrang*i+exbase*2+j]=excomplex;
				}
			}
			exbase<<=1;
		}
		FFT_Base2(x,N>>1);
		FFT_Base2(x+(N>>1),N>>1);

		for(k=0;k<N>>1;k++)
		{
			Wnk.re=(float)cos(-2*__PI*k/N);
			Wnk.im=(float)sin(-2*__PI*k/N);
			cx0=x[k];
			cx1=x[k+(N>>1)];
			x[k]=complexAdd(cx0,complexMult(Wnk,cx1));
			Wnk.re=-Wnk.re;
			Wnk.im=-Wnk.im;
			x[k+(N>>1)]=complexAdd(cx0,complexMult(Wnk,cx1));
		}
	}
	else
	{
		//2 dot DFT
		cx0=x[0];
		cx1=x[1];
		x[0]=complexAdd(cx0,cx1);
		cx1.im=-cx1.im;
		cx1.re=-cx1.re;
		x[1]=complexAdd(cx0,cx1);
	}


}
void FFT(_IN complex x[],_OUT complex X[],int N)
{
	int size=1;
	complex *i_px;

	while((size<<=1)<N);

	i_px=(complex *)malloc(sizeof(complex)*size);

	memset(i_px,0,sizeof(complex)*N);
	memcpy(i_px,x,sizeof(complex)*N);

	FFT_Base2(i_px,size);
	memcpy(X,i_px,sizeof(complex)*N);

	free(i_px);
}

void IFFT_Base2(_IN _OUT complex X[],int N)
{
	int exbase,exrang,i,j,n;
	complex excomplex,Wnnk,cx0,cx1;
	if (N>>2)
	{
		// x[] 4 base odd/even Sort
		exbase=1;
		exrang=0;
		while (exrang<N)
		{
			exrang=exbase<<2;

			for (i=0;i<N/exrang;i++)//for each token
			{
				for (j=0;j<exbase;j++)//for each atom in token
				{
					excomplex=X[exrang*i+exbase+j];
					X[exrang*i+exbase+j]=X[exrang*i+exbase*2+j];
					X[exrang*i+exbase*2+j]=excomplex;
				}
			}
			exbase<<=1;
		}
		IFFT_Base2(X,N>>1);
		IFFT_Base2(X+(N>>1),N>>1);

		for(n=0;n<N>>1;n++)
		{
			Wnnk.re=(float)cos(2*__PI*n/N);
			Wnnk.im=(float)sin(2*__PI*n/N);
			cx0=X[n];
			cx1=X[n+(N>>1)];
			X[n]=complexAdd(cx0,complexMult(Wnnk,cx1));

			Wnnk.re=-Wnnk.re;
			Wnnk.im=-Wnnk.im;
			X[n+(N>>1)]=complexAdd(cx0,complexMult(Wnnk,cx1));

		}
	}
	else
	{
		//2 dot IDFT
		cx0=X[0];
		cx1=X[1];
		X[0]=complexAdd(cx0,cx1);

		cx1.im=-cx1.im;
		cx1.re=-cx1.re;
		X[1]=complexAdd(cx0,cx1);

	}
}
void IFFT(_IN complex X[],_OUT complex x[],int N)
{
	int size=1,i;
	complex *i_px;

	while((size<<=1)<N);

	i_px=(complex *)malloc(sizeof(complex)*size);

	memset(i_px,0,sizeof(complex)*N);
	memcpy(i_px,X,sizeof(complex)*N);

	IFFT_Base2(i_px,size);

	// 1/N operate
	for (i=0;i<N;i++)
	{
		i_px[i].re/=N;
		i_px[i].im/=N;
	}

	memcpy(x,i_px,sizeof(complex)*N);

	free(i_px);
}


void FFT_2(_IN complex x[],_OUT complex X[],int N)
{

	for (int i=0;i<N;i++)
	{
		FFT(&x[i*N],&X[i*N],N);
	}
	//Matrix transpose
	for (int cy=0;cy<N;cy++)
	{
		for (int cx=cy+1;cx<N;cx++)
		{
			complex _t=X[cy*N+cx];
			X[cy*N+cx]=X[cx*N+cy];
			X[cx*N+cy]=_t;
		}
	}

	for(int i=0;i<N;i++)
	{
		FFT(&X[i*N],&X[i*N],N);
	}

	//Matrix transpose again

	for (int cy=0;cy<N;cy++)
	{
		for (int cx=cy+1;cx<N;cx++)
		{
			complex _t=X[cy*N+cx];
			X[cy*N+cx]=X[cx*N+cy];
			X[cx*N+cy]=_t;
		}
	}
}

void IFFT_2(_IN complex X[],_OUT complex x[],int N)
{
	//Matrix transpose
	for (int cy=0;cy<N;cy++)
	{
		for (int cx=cy+1;cx<N;cx++)
		{
			complex _t=X[cy*N+cx];
			X[cy*N+cx]=X[cx*N+cy];
			X[cx*N+cy]=_t;
		}
	}

	for(int i=0;i<N;i++)
	{
		IFFT(&x[i*N],&X[i*N],N);
	}

	//Matrix transpose again
	for (int cy=0;cy<N;cy++)
	{
		for (int cx=cy+1;cx<N;cx++)
		{
			complex _t=X[cy*N+cx];
			X[cy*N+cx]=X[cx*N+cy];
			X[cx*N+cy]=_t;
		}
	}

	for (int i=0;i<N;i++)
	{
		IFFT(&X[i*N],&X[i*N],N);
	}
}

void FFT_2_Shift(_IN complex _in[],_OUT complex _out[],int N)
{
	complex *_t=(complex *)malloc(sizeof(complex)*N*N);
	complex _ext;
	memcpy(_t,_in,sizeof(complex)*N*N);

	for (int y=0;y<N/2;y++)
	{
		for (int x=0;x<N/2;x++)
		{
			_ext=_t[y*N+x];
			_t[y*N+x]=_t[y*N+N*N/2+x+N/2];
			_t[y*N+N*N/2+x+N/2]=_ext;
		}
	}

	for (int y=0;y<N/2;y++)
	{
		for (int x=N/2;x<N;x++)
		{
			_ext=_t[y*N+x];
			_t[y*N+x]=_t[y*N+N*N/2+x-N/2];
			_t[y*N+N*N/2+x-N/2]=_ext;
		}
	}
	memcpy(_out,_t,sizeof(complex)*N*N);
	free(_t);
}
