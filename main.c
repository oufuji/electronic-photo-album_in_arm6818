#include"main.h"
/*
 *功能：	往管道写入命令，控制视频播放
 *参数：	const  char *cmd ：命令的字符
 *返回值：  无
 */

void Write_Cmd(const  char *cmd)
{	
	int gg = write(fp_write, cmd, strlen(cmd));	
}


/*
 *功能：	创建管道文件
 *参数：	无
 *返回值：  无
 */

void  fifo_creat(void){
	if(access("/tmp/fifo", F_OK)) {
		int ret = mkfifo("/tmp/fifo", 0666);
		if(ret == -1){
			perror("mkfifo failed");
			return ;
		}
	}
}

/*
 *功能：	显示视频文件的略缩图
 *参数：	My_Node *d_list_avi ：视频链表头
 *返回值：  无
 */
void TuPian_Show(My_Node *d_list_avi ){
	
	struct list_head *p=&d_list_avi->ptr;
	p=p->next;
	char s[100];//命令缓存
	int x_qidian=0,y_qidian=0;
	int i=0;
	while(p!=&d_list_avi->ptr){
		sprintf(s,"./mplayer -quiet -slave -input file=/tmp/fifo -geometry %d:%d -zoom -x 100 -y 100 %s & ",x_qidian,y_qidian,list_entry(p, My_Node, ptr)->data);
		system(s);
		a[i]=list_entry(p, My_Node, ptr)->data;
		usleep(400000);
		write(fp_write,"quit\n",5);
		p=p->next;
		i++;
		x_qidian=x_qidian+100;
		if(x_qidian==300){
			x_qidian=0;
			y_qidian=y_qidian+100;
			if(y_qidian==400){
				exit(1);
			}
		}
	}
	suo = 1;
}

/*
 *功能：	动作命令，包括图片切换，视频播放等
 *参数：	My_Node *d_list_avi ：图片链表头
 *返回值：  无
 */
struct list_head * MoShi(struct list_head *qq){
	char s[100];//命令缓存
	
	//等待buf传送数据进来
	while(buf ==0) ; 
	
	//打印命令；
	printf("buf=====%d\n",buf);
	//命令选择 ------图片区
	if(buf!=0&&buf<20){
		qq = cmd_bmp(qq,buf);
		suo = 1;
	}
	if(buf == 99){
		
		TuPian_Show(d_avi);
		
		
	}//命令选择-----视频播放区
	if(buf>100&&buf<110){
		printf("a=====%s\n",a[buf-101]);
		sprintf(s,"./mplayer -quiet -slave -input \
		file=/tmp/fifo -geometry 0:0 -zoom \
		-x 800 -y 400 %s & ",a[buf-101]);
		Lcd_Init("11111.bmp");
		system(s);
		suo = 1;
		ll=10;
	}
	if(buf>=110){
		int gg = buf-110;
		if(gg==8)
			ll=1;
		Write_Cmd(opt[gg]);
		suo = 1;
		usleep(1000*500);
	}
	buf = 0;
	
	return qq;
}





int main(int argc,char** argv){
	int p = Lcd_Init("11111.bmp");
	fifo_creat();
	fp_write = open("/tmp/fifo",O_RDWR);
	//视频链表
	My_Node *d_list_avi=List_Init();
	ReadDir(".",".avi",d_list_avi);
	d_avi=d_list_avi;  //全局化
	//图片链表
	My_Node *d_list_bmp=List_Init();
	ReadDir(".",".bmp",d_list_bmp);
	//显示缩略图的视频
	TuPian_Show(d_avi);
	usleep(100000);//延时，然后清空控制台
	system("clear");
	//设置密码
	printf("是否需要更换密码？\n1:是\t 0:否\n");
	int d=0; 
	scanf("%d",&d);
	if(d==1){
		printf("输入链接密码\n");
		 scanf("%d",&d); //密码
	}
	//查看密码是否正确，buf为接受指令缓存
	//设置密码
	//建立线程1，接收指令
	pthread_t pid_recv;
	pthread_create(&pid_recv, NULL,server,NULL);
	while(d!=buf) ; //密码锁
	buf=0;//避免进行了一次操作
	while(ll==0) ;	//线程时序锁，由线程1服务器端有链接解开
	pthread_t pid_send; //线程2，发送图片，或者视频帧
	pthread_create(&pid_send, NULL,sendbuf,(void*)&p);
	struct list_head *qq=&d_list_bmp->ptr;//图片头部
	qq = qq->next;
	while(1){
		//判断进入什么模式
		//由buf进行读阻塞，当没有东西过来的时候阻塞
		qq = MoShi(qq); //图片链表正常传进去，视频链表用全局变量传进去了
	}	
	return 0;
}


