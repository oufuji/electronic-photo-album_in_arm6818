#include "kernel_list.h"
#include <stdio.h>
#include <stdlib.h>

//0,设计链表节点
typedef struct Kernel_List_Node{
	char* data;	//数据域
	struct list_head ptr;	//地址结构体
}My_Node;


//1,初始化链表
My_Node * List_Init(void)
{
	//1,为头结点申请一片堆内存
	My_Node *head = (My_Node *)malloc(sizeof(My_Node));
	if(head == NULL)
	{
		perror("malloc failed");
		return NULL;
	}
	
	//2,链表初始化	INIT_LIST_HEAD(ptr)
	INIT_LIST_HEAD( &(head->ptr) );
	//3,返回头结点地址指针
	return  head;
}

//2,新建链表节点
My_Node * New_Node(int size, char* DiZhi)
{
	//1,为新结点申请一片堆内存
	My_Node *new_node = (My_Node *)malloc(sizeof(My_Node));
	if(new_node == NULL)
	{
		perror("malloc new_node failed");
		return NULL;
	}
	//2,节点内容分配内存
	new_node->data = (char *)malloc(size);
	//3.把数据放入内存中
	memcpy(new_node->data,DiZhi,size);
	//4,返回结点地址指针
	return new_node;
}

//3,添加新的链表节点到链表 //头插法
void Add_Node(My_Node *list, My_Node *newnode)
{
	list_add(&(newnode->ptr), &(list->ptr));
}

/*
 *功能：	递归寻找文件夹里面的内容，并存放到链表中
 *参数：	char *name ：文件夹名字
			char *name_for_tupian：后缀名
			My_Node *d_list：链表头
 *返回值：  无
 */

void ReadDir(char *name,char *name_for_tupian,My_Node *d_list){
	int i=0;
	char s[320]={0};
	My_Node *new_node = NULL;
	/*判断最后一个是不是/符号，如果是，则去掉*/
	char *pr=(name+strlen(name)-1);
		
	if(*pr=='/')
	{
		*pr='\0';
	}
	DIR *dp = opendir(name); //打开文件夹
	if(dp==NULL){
		perror("open dir failed");
		exit(1);
	}
	struct dirent *fp =NULL;
	
	
	while(1){
		fp=readdir(dp); //阅读文件夹
		if(fp==NULL)
			break ;
		if(strcmp(name_for_tupian,(fp->d_name+strlen(fp->d_name))-4)==0) //名字对比
		
		{	sprintf(s,"%s/%s",name,fp->d_name); //路径和文件名进行拼接
			printf("%s\n",s);
		    new_node=New_Node(strlen(s)+1,s); //建立新节点
			Add_Node(d_list, new_node);		//添加到链表中
		}
		if(fp->d_type==DT_DIR&&*(fp->d_name)!='.'){ //如果是文件是目录文件
			sprintf(s,"%s/%s",name,fp->d_name); //路径拼接
			ReadDir(s,name_for_tupian,d_list);//递归进入下一子目录
		}
		
	}
}





