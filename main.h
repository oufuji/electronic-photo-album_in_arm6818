#ifndef _MAIN_H
#define _MAIN_H

#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>	
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>	
#include <pthread.h>
#include"Lcd.h"
#include "kernel_list.h"
int buf_1;
extern void show(char *p_name);
extern int Lcd_Init(char *pname);
extern unsigned int* buff_480_800_Hecheng;
extern unsigned int* mmp;
extern void show(char *p_name);
extern int Lcd_Init(char *pname);
extern void Get_Ts(int *x ,int *y);
extern void Ts_Init(void);


#endif