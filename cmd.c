#include"cmd.h"
/*
 *功能：	图片显示翻页幻灯片播放等
 *参数：	struct list_head *p ：图片链表
			int cmd ：命令代表码
 *返回值：  struct list_head* ：返回当前指向的图片
 */
struct list_head* cmd_bmp(struct list_head *p,int cmd){
  
   if(cmd ==1)//显示第一张
		show(list_entry(p, My_Node, ptr)->data);
	if(cmd==2){//显示下一张
		p=p->next;
		show(list_entry(p, My_Node, ptr)->data);
	}
	if(cmd==3){//显示上一张
		p=p->prev;
		show(list_entry(p, My_Node, ptr)->data);
	}
	if(cmd==4){//幻灯片播放
		buf=0;
		while(buf==0){ //退出前提为有外部指令干扰到buf
			show(list_entry(p, My_Node, ptr)->data);
			suo = 1;
			usleep(1000*1000);//延时一段时间
			p=p->next;
			
		}
	}
	
	return p;
}