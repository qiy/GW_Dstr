#include "stdio.h"
#define n 4
int t[n*n/2];
void Store(int x, int i, int j)
{/* ��x ��ΪL ( i , j ) */ 
	if (i<0||j<0||i>=n||j>=n)
	{
		printf("������磡");
		exit(1);
	}
	/* ���ҽ���i �� j ʱ(i,j) λ��������*/ 
	if (i >= j)
		t[i*(i+1)/2+j] = x;
	else if (x != 0)
	{
		printf("�ǶԽ�����Ԫ��ֵ����Ϊ��");
		exit(1);
	}
}
void main()
{
	int i,j;
	int D[n][n]={2,0,0,0,5,1,0,0,0,3,1,0,4,2,7,0};
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			Store(D[i][j],i,j);
	for(i=0;i<=n*n/2+1;i++)
	   printf("%d  ",t[i]);
    printf("\n");
}

