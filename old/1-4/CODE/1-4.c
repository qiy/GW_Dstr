#include<stdio.h>
void main()
{
    int i,j,n=13;
    printf("N=");
    while(n>12)
    scanf("%d",&n); /*����������ȷ��ֵ�Ա�֤��Ļ��ʾ��ͼ����ȷ*/
    for(i=0;i<=n;i++) /*�������N��*/
    {
        for(j=0;j<24-2*i;j++)
            printf(" "); /*���������i��ǰ��Ŀո�*/
        for(j=1;j<i+2;j++)
            printf("%4d",c(i,j)); /*�����i�еĵ�j��ֵ*/
        printf("\n");
    }
}
int c(int x,int y) /*������������е�x�е�y�е�ֵ*/
{
    int z;
    if((y==1)||(y==x+1))
    return 1; /*��Ϊx�еĵ�1���x+1�У������1*/
    z=c(x-1,y-1)+c(x-1,y); /*������ֵΪǰһ���е�y-1�����y��ֵ֮��*/
    return z;
}
