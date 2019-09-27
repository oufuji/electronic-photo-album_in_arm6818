#ifndef _CMD_H
#define _CMD_H

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

extern void show(char *p_name);
extern int buf;
extern int suo;

#endif
