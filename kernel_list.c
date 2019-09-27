#include "kernel_list.h"
#include <stdio.h>
#include <stdlib.h>

//0,�������ڵ�
typedef struct Kernel_List_Node{
	char* data;	//������
	struct list_head ptr;	//��ַ�ṹ��
}My_Node;


//1,��ʼ������
My_Node * List_Init(void)
{
	//1,Ϊͷ�������һƬ���ڴ�
	My_Node *head = (My_Node *)malloc(sizeof(My_Node));
	if(head == NULL)
	{
		perror("malloc failed");
		return NULL;
	}
	
	//2,�����ʼ��	INIT_LIST_HEAD(ptr)
	INIT_LIST_HEAD( &(head->ptr) );
	//3,����ͷ����ַָ��
	return  head;
}

//2,�½�����ڵ�
My_Node * New_Node(int size, char* DiZhi)
{
	//1,Ϊ�½������һƬ���ڴ�
	My_Node *new_node = (My_Node *)malloc(sizeof(My_Node));
	if(new_node == NULL)
	{
		perror("malloc new_node failed");
		return NULL;
	}
	//2,�ڵ����ݷ����ڴ�
	new_node->data = (char *)malloc(size);
	//3.�����ݷ����ڴ���
	memcpy(new_node->data,DiZhi,size);
	//4,���ؽ���ַָ��
	return new_node;
}

//3,����µ�����ڵ㵽���� //ͷ�巨
void Add_Node(My_Node *list, My_Node *newnode)
{
	list_add(&(newnode->ptr), &(list->ptr));
}

/*
 *���ܣ�	�ݹ�Ѱ���ļ�����������ݣ�����ŵ�������
 *������	char *name ���ļ�������
			char *name_for_tupian����׺��
			My_Node *d_list������ͷ
 *����ֵ��  ��
 */

void ReadDir(char *name,char *name_for_tupian,My_Node *d_list){
	int i=0;
	char s[320]={0};
	My_Node *new_node = NULL;
	/*�ж����һ���ǲ���/���ţ�����ǣ���ȥ��*/
	char *pr=(name+strlen(name)-1);
		
	if(*pr=='/')
	{
		*pr='\0';
	}
	DIR *dp = opendir(name); //���ļ���
	if(dp==NULL){
		perror("open dir failed");
		exit(1);
	}
	struct dirent *fp =NULL;
	
	
	while(1){
		fp=readdir(dp); //�Ķ��ļ���
		if(fp==NULL)
			break ;
		if(strcmp(name_for_tupian,(fp->d_name+strlen(fp->d_name))-4)==0) //���ֶԱ�
		
		{	sprintf(s,"%s/%s",name,fp->d_name); //·�����ļ�������ƴ��
			printf("%s\n",s);
		    new_node=New_Node(strlen(s)+1,s); //�����½ڵ�
			Add_Node(d_list, new_node);		//��ӵ�������
		}
		if(fp->d_type==DT_DIR&&*(fp->d_name)!='.'){ //������ļ���Ŀ¼�ļ�
			sprintf(s,"%s/%s",name,fp->d_name); //·��ƴ��
			ReadDir(s,name_for_tupian,d_list);//�ݹ������һ��Ŀ¼
		}
		
	}
}





