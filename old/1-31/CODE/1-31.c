#include "stdio.h"
#define MAX_DANCERS 100//�����������
#define QueueSize 100 //�ٶ�Ԥ����Ķ��пռ����Ϊ100��Ԫ��  	
typedef struct{
	char name[20];
	char sex;  //�Ա�'F'��ʾŮ�ԣ�'M'��ʾ����
}Person;
typedef Person DataType;  //��������Ԫ�ص��������͸�ΪPerson
typedef struct{
	DataType data[QueueSize];
	int front;//ͷָ��
	int rear;//βָ��
	int count; //����������¼����Ԫ������
}CirQueue;
// �ö��п�
void Initial(CirQueue *Q)
{//��˳������ÿ�
	Q->front=Q->rear=0;
	Q->count=0;     //��������0
}
//�ж��п�
int IsEmpty(CirQueue *Q)
{
	return Q->front==Q->rear;
}
//�ж�����
int IsFull(CirQueue *Q)
{
	return Q->rear==QueueSize-1+Q->front;
}
//������
void EnQueue(CirQueue *Q,DataType x)
{
	if (IsFull(Q))
	{
		printf("��������"); //����,�˳�����
		exit(1);
	}
	Q->count ++;                        //����Ԫ�ظ�����1
	Q->data[Q->rear]=x;                 //��Ԫ�ز����β
	Q->rear=(Q->rear+1)%QueueSize;      //ѭ�������½�βָ���1
}
//������
DataType DeQueue(CirQueue *Q)
{
	DataType temp;
	if(IsEmpty(Q))
	{
		printf("����Ϊ��"); //����,�˳�����
		exit(1);
	}
	temp=Q->data[Q->front];
	Q->count--;                        //����Ԫ�ظ�����1
	Q->front=(Q->front+1)&QueueSize;   //ѭ�������µ�ͷָ���1
	return temp;
	
}
// ȡ���ж�Ԫ��
DataType Front(CirQueue *Q)
{
	if(IsEmpty(Q))
	{
		printf("����Ϊ��"); //����,�˳�����
		exit(1);
	}
	return Q->data[Q->front];
}
void DancePartner(Person dancer[],int num)
{//�ṹ����dancer�д���������Ů��num�������������
	int i;
	Person p;
	CirQueue Mdancers,Fdancers;
	Initial(&Mdancers);//��ʿ���г�ʼ��
	Initial(&Fdancers);//Ůʿ���г�ʼ��
	for(i=0;i<num;i++){//���ν������������Ա����
		p=dancer[i];
		if(p.sex=='F')
			EnQueue(&Fdancers,p);   //����Ů��
		else
			EnQueue(&Mdancers,p);   //�����ж�
	}
	printf("�����:\n");
	while(!IsEmpty(&Fdancers)&&!IsEmpty(&Mdancers)){
		//����������Ů�����
		p=DeQueue(&Fdancers);     //Ůʿ����
		printf("%s        ",p.name);//��ӡ����Ůʿ��
		p=DeQueue(&Mdancers);     //��ʿ����
		printf("%s\n",p.name);    //��ӡ������ʿ��
	}
	if(!IsEmpty(&Fdancers)){ //���Ůʿʣ����������ͷŮʿ������
		printf("���� %d ��Ůʿ����һ��.\n",Fdancers.count);
		p=Front(&Fdancers);  //ȡ��ͷ
		printf("%s will be the first to get a partner. \n",p.name);
	}
	else if(!IsEmpty(&Mdancers)){//����ж�ʣ����������ͷ������
		printf("����%d ����ʿ����һ��.\n",Mdancers.count);
		p=Front(&Mdancers);
		printf("%s will be the first to get a partner.\n",p.name);
	}
}
void InitialDancer(Person dancer[])
{
	//���豨��
}
void main()
{
	Person dancer[MAX_DANCERS];
	int n=93;
	InitialDancer(dancer);
	DancePartner(dancer,93);
}

