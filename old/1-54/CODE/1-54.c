#include "stdio.h"
#define MAX_SIZE  50   /* ����ϡ����� */
typedef enum  {head, entry} tagfield;
struct entry_node  {
      int  row;
      int  col;
      int  value;
};
typedef struct Matrix  {
struct Matrix	*  down;
      struct Matrix  *	right;
      tagfield  tag;
      union   {
      	 struct Matrix  *  next;
		 struct entry_node  entry;
      } u;
}matrix_node;
typedef matrix_node * matrix_pointer;
matrix_pointer  hdnode [ MAX_SIZE ];
matrix_pointer new_node(void)
{      
		matrix_pointer temp;
		temp = (matrix_pointer)malloc(sizeof(matrix_node));
		if (temp==NULL) {
			printf("The memory is full\n");
			exit(1);
		}
		return temp;
}             
matrix_pointer Create(void)
{   
    int num_rows, num_cols, num_terms, num_heads, i,current_row;
    int col,  value,row;
	matrix_pointer	node,temp,last;
    printf("Enter the number of rows, columns and number of nonzero terms: ");
    scanf("%d%d%d",&num_rows,&num_cols,&num_terms);
    num_heads = (num_cols > num_rows) ? num_cols :num_rows;
		/* �����½�� */
    node = new_node(); 
	node->tag = entry;
    node->u.entry.row = num_rows;
    node->u.entry.col = num_cols;
	if ( !num_heads )
		node->right = node;
    else {	/*��ʼ��ͷ�����ͼ5-5-4*/
        for ( i = 0; i<num_heads; i++ ) {
            temp = new_node();
            hdnode[i] = temp;
			hdnode[i]->tag = head;				
            hdnode[i]->right = temp; 
            hdnode[i]->u.next = temp;
		}
   		current_row = 0;	
		last = hdnode[0];	
		for ( i = 0; i < num_terms; i++ ) {
            printf("Enter row, column and value: ");
            scanf("%d%d%d",&row,&col,&value);
            if ( row > current_row ) {
                /* ת��row������ȥ*/
                last->right = hdnode[current_row];
                current_row = row; 
				last = hdnode[row];
			}
            temp = new_node();
            temp->tag = entry; 
			temp->u.entry.row = row;
            temp->u.entry.col = col;
            temp->u.entry.value = value;
			/* ���ӵ��н������ͼ5-5-5��ʾ */
            last->right = temp;	
            last = temp;
			/*���ӵ��н���� */
            hdnode[col]->u.next->down = temp;  
            hdnode[col]->u.next = temp;  
        }
			/* ������һ�н�� */
        last->right = hdnode[current_row]; 
			/*���������н��*/
        for ( i=0; i<num_cols; i++ )
			hdnode[i]->u.next->down= hdnode[i];  
			/*�������е�ͷ��� */
        for ( i=0; i<num_heads-1; i++ )
             hdnode[i]->u.next = hdnode[i+1];
        hdnode[num_heads-1]->u.next = node;
        node->right = hdnode[0];
    }
    return node;
}											     
void erase(matrix_pointer *node)
{
		matrix_pointer x,y,head = (*node)->right;
		int i;
		/* ����ÿ�У�ɾ��Ԫ�ؽ���ͷ��� */
		for ( i = 0; i< (*node)->u.entry.row; i++ ) {
			y = head->right;
			while ( y != head ) {
				x = y; y = y->right; 
				free(x);
			}
			x = head; head = head->u.next; free(x);
		}
		/* ɾ��ʣ���ͷ���*/
		y = head;
		while ( y != *node ) {
			x = y; 
			y = y->u.next; 
			free(x);
		}
		free(*node); 
		*node = NULL;
}
void main()
{
	matrix_pointer matric=Create();
	erase(&matric);
}
