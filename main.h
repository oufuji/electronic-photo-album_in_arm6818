#ifndef _MAIN_H
#define _MAIN_H

#include <sys/types.h>
#include <sys/stat.h>
#include "kernel_list.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <string.h>
typedef struct Kernel_List_Node{
	char* data;	
	struct list_head ptr;	
}My_Node;

const char *(opt[20])={  //全局变量，视频操作命令数组指针
	"pause\n",\
	"seek -10\n",\
	"seek 10\n",\
	"volume 200\n",\
	"volume -200\n",\
	"mute 1\n",\
	"mute 0\n",\
	"quit\n",\
	"quit\n" \
};				 
int fp_write;    //视频操作管道文件描述符，全局变量
int ll;       	 //拿来关掉传输锁，让两端不停的传输（视频传输有用）
char *(a[20]);	//图片名指针数组，全局变量
int p_all;		//这个是LCD文件的描述符的全局变量
My_Node *d_avi; //avi视频文件链表的全局变量


extern int Lcd_Init(char *pname);//LCD初始化，链表初始化
extern My_Node * List_Init(void);

extern void show(char *p_name); //显示图片的函数 

								//图片模式命令函数
extern struct list_head* cmd_bmp(struct list_head *p,int cmd);


extern void* server(void *argv);  //线程函数1
extern void* sendbuf(void *argv);//线程函数2

extern void ReadDir(char *,char*,My_Node*);//搜索函数并放在链表中

extern int buf; //全局变量，拿来接收发送端（客户端）4个字节的指令
extern int suo; //全局变量，拿来同步、锁定显示和发送图片的时序
	
extern void YingShe(unsigned int* p);
extern unsigned int *mmp;
extern unsigned int* buff_480_800_Hecheng;
extern void ChuLi_High_Weigh(char *p_name);


#endif
