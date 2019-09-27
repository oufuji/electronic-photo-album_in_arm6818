#ifndef _Lcd_h
#define _Lcd_h

#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "kernel_list.h"

int CaiDan;
unsigned int* buff_480_800;
unsigned int* buff_yuan;
unsigned int* buff_480_800_Hecheng;
extern int p_all;
extern int Flag_SongShou;
unsigned int *mmp;
int Yuan_NeiCun[7210];
typedef struct Kernel_List_Node{
	char* data;	
	struct list_head ptr;	
}My_Node;


void ChuLi_High_Weigh(char *p_name);
void HeCheng(int dx,int dy,int R);
void YingShe(unsigned int* p);
int Lcd_Init(char *pname);

extern void ReadDir(char *,char*,My_Node*);
extern My_Node* List_Init(void);


#endif