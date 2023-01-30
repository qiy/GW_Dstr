#include "stdio.h"
#define MAX_PARENT 100
int 	parent[MAX_PARENT];
void Initialize(int n)
{/* ��ʼ����ÿ����/����һ��Ԫ��*/
	int e ;
	for (e=1; e <= n&&n<MAX_PARENT; e++)
		parent[e] = 0;
}
int Find(int e)
{ /*���ذ���e�����ĸ��ڵ�*/
	while (parent[e]&&e<MAX_PARENT)
		e = parent[e]; /* ����һ��*/
	return e;
}
void Union(int i, int j)
{/* ����Ϊi ��j�����������кϲ�*/
	if(j<MAX_PARENT)
		parent[j]=i;
}
void Combine(int a,int b)
{
	int i = Find(a); 
	int j = Find(b);
	if(i!= j) 
		Union(i, j);
}
void main()
{
	Combine(1,2);
}
