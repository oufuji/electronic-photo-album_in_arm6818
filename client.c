#include"main.h"
/*
 *功能：	线程函数1，主要是发送指令
 *参数：	void * arg ：空指针
 *返回值：  无
 */
void* client(void *argv){	// ./client port IP
	
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server;		
	server.sin_family = AF_INET;	//使用IPV4协议
	server.sin_port = htons(11111);		
	inet_pton(AF_INET, "192.168.22.153", &server.sin_addr);	//IP号
	socklen_t addrlen = sizeof(struct sockaddr_in);
	connect(sockfd, (struct sockaddr *)&server,addrlen);
	printf("请输入登录密码\n");

	while(1)
	{  
		while(buf_1==0) ;
		write(sockfd,&buf_1,4);	
		buf_1 = 0 ;
	}
	close(sockfd);
	
	return NULL;
}

/*
 *功能：	线程函数2，主要是接收图片缓存，并显示
 *参数：	void * arg ：空指针
 *返回值：  无
 */
void* client_recv(void* argv){
	int p=open("/dev/fb0",O_RDWR);
	buff_480_800_Hecheng=mmap(NULL,480*800*4,PROT_READ | PROT_WRITE,MAP_SHARED,p,0);
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	mmp = (unsigned int *)malloc(800*480*4);
	struct sockaddr_in server, client;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	server.sin_family = AF_INET;
	server.sin_port   = htons(11144);
	inet_pton(AF_INET, "192.168.22.253", &server.sin_addr);
	int ret = bind(sockfd, (struct sockaddr *)&server, addrlen);
	if(ret < 0)
	{
		perror("bind failed");
		return NULL;
	}	
	listen(sockfd, 5);
	int con_fd = accept(sockfd,(struct sockaddr *)&client, &addrlen); 
	while(1)
	{  	int n = 0;
		int filesize = 0;
		for(int j=0;j<120;j++)
			for(int i=0;i<200;i++){
				n = read(con_fd,buff_480_800_Hecheng+i+j*800,4);
				read(con_fd, mmp, 4-n);
				filesize += n;
		}	
		
	}
	
}

/*
 *功能：	触摸屏触摸产生指令
 *参数：	无
 *返回值：  无
 */
void zhiling(void){
		//触摸判断功能
		int x,y;
		int jiemianyi=1;
		int jiemianer=0;
		int jiemiansan=0;
		//for(int i=0;i<5;i++)
		Get_Ts(&x ,&y);
		if(x<400){ //判断进入图片
			jiemianyi =0;
			jiemianer =1;
			printf("%d,%d\n",x,y);
		}
		if(x>400){ //判断进入视频区
			buf_1=99;
			jiemianyi =0;
			jiemiansan=1;
		}
		if(jiemianyi==1){ //初始界面区
			show("kaishi.bmp");
		}
		if(jiemianer ==1){ //图片区
			show("22.bmp");	
			while(1){
				Get_Ts(&x ,&y);
				printf("%d,%d\n",x,y);
				if(x>400&&y>200){
					jiemiansan = 1;
					jiemianer = 0;
					x=0;
					y=0;
					break;
				}
				if(y>300)
					buf_1 = 2;
				else
					buf_1 = 3;
				
			}
			
		}
		if(jiemiansan == 1){ //视频区
			show("shiping.bmp");
			while(1){
				Get_Ts(&x ,&y);
					printf("%d,%d\n",x,y);
					if(x<300&&x>150&&y>300){
						jiemiansan = 0;
						jiemianyi = 1;
						x=0;
						y=0;
						buf_1 = 118;
						break;
					}
					if(y>200);
						buf_1 = x/100+(y-200)/150+110;
					if(y<100)
						buf_1 = 102;
				
			}
		}
			jiemiansan = 0;
}



int main(int argc ,char **argv){
	Lcd_Init("kaishi.bmp");
	pthread_t pid;
	pthread_create(&pid, NULL,client,NULL);
	usleep(100);
	pthread_t pid1;
	pthread_create(&pid1, NULL,client_recv,NULL);
	Ts_Init();
	//这里要封装成函数
	while(1){
		zhiling();
	}	
}
	
