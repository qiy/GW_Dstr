#include "stdio.h"
#define  MAX_TERMS 100    /* size of terms array */
typedef  struct {
	float  coef;
	int expon;
}  polynomial;
polynomial  terms[ MAX_TERMS];
int avail = 0;
int COMPARE(int coef1,int coef2)
{
	if(coef1<coef2)
		return -1;
	else if(coef1==coef2)
		return 0;
	else
		return 1;
}
void attach (float coefficient, int exponent)
{  /* ��һ���������ʽ�� */
     if (avail > MAX_TERMS)  {
        printf("Too many terms in the polynomial \n");
        exit(1);
     }
    terms[avail].coef = coefficient;
    terms[avail++].expon = exponent;
}
void padd( int starta, int  finisha, int startb, int finishb, 
		  int *startd,int *finishd)
{ /* A(x)��B(x)��D (x) */
    float coefficient;
    *startd = avail;
    while ( starta <= finisha && startb <=finishb)
        switch (COMPARE(terms[starta].expon, terms[startb].expon))  {
           case -1:  /* a ָ��С�� bָ��*/
              attach(terms[startb].coef, terms[startb].expon);
                  startb ++;
                  break;
           case 0:  /*��ָ�����*/
                  coefficient = terms[starta].coef + terms[startb].coef;
                  if (coefficient)
                          attach(coefficient, terms[starta].expon);
                   starta++;
                   startb ++;
                   break;
          case 1:  /* aָ������bָ��*/
                    attach(terms[starta].coef,terms[starta].expon);
                    starta++;
	}
	/* �������A(x)��� */
    for (; starta <= finisha;  starta++)
            attach(terms[starta].coef,terms[starta].expon);
	/* �������B(x)��� */
    for (; startb <= finishb;  startb++)
           attach(terms[startb].coef,terms[startb].expon);
    *finishd = avail -1;
}
void main()
{
	int startd,finishd;
	padd(4,1,3,2,&startd,&finishd);
}
