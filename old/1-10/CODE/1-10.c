#include "stdio.h"
#define n 4
int t[3*n];
void	Store(int x, int i, int j)
{
	if ( i < 0 || j <0 ||i >=n || j >=n)
	{
		printf("������磡");
		exit(1);
	}
	switch (i - j) {
		case 1: /* �ͶԽ���*/ 
			t[i - 1] = x; break;
		case 0: /* ���Խ���*/ 
			t[n + i - 1] = x; break;
		case -1: /*  �߶Խ���*/ 
			t[2 *n + i - 1] = x; break;
		default:
			if(x != 0)
			{
				printf("�ǶԽ�����Ԫ��ֵ����Ϊ��");
				exit(1);
			}
	}
}
void main()
{
	int i,j;
	int D[n][n]={{2,1,0,0},{3,1,3,0},{0,5,2,7},{0,0,9,0}};
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			Store(D[i][j],i,j);
	for(i=0;i<3*n-2;i++)
	   printf("%d  ",t[i]);
    printf("\n");
}

