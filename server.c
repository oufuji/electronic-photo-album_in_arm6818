#include"server.h"
/*
 *功能：	线程函数2，主要是发送当前LCD屏幕数据
 *参数：	void * arg ：LCD设备文件描述符的地址指针
 *返回值：  无
 */

void* sendbuf(void * arg){	//循环读取套接字中的数据
	int p =*(int *)arg;
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	//2, 准备对方的IP和端口号 
	struct sockaddr_in server;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	
	server.sin_family = AF_INET;
	server.sin_port   = htons(11144);
	inet_pton(AF_INET,"192.168.22.253", &server.sin_addr);	//对方IP
	connect(sockfd, (struct sockaddr *)&server,addrlen);	
	//3, 循环从键盘获取字符串发送给对方
	
	while(1){
		if(ll==1)
			while(suo==0) ;
		//printf("p===%d\n",p);
		int hh = read(p,buff_480_800_Hecheng,800*480*4);
		lseek(p,0,SEEK_SET);
		//perror("????");
		//printf("hh=====%d\n",hh);
		//printf("hh===%d\n",hh);
			int gg;
			for(int j=0;j<480;j=j+4)
				for(int i=0;i<800;i=i+4){
					gg = write(sockfd,buff_480_800_Hecheng+i+j*800,4);	
				
			}
	//	printf("send===%d\n\n\n\n",gg);
		suo =0;
	}
	close(sockfd);
}


/*
 *功能：	线程函数2，主要是发送当前LCD屏幕数据
 *参数：	void * arg ：无，空指针
 *返回值：  无
 */
void* server(void *argv){

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		perror("socket failed");
		return NULL;
	}
	struct sockaddr_in server, client;
	server.sin_family = AF_INET;
	server.sin_port   = htons(11111);	//通信双方必须使用同一个端口
	inet_pton(AF_INET, "192.168.22.153", &server.sin_addr);
	socklen_t addrlen = sizeof(struct sockaddr_in);
	int ret = bind(sockfd, (struct sockaddr *)&server, addrlen);
	if(ret == -1)
	{
		perror("bind failed");
		exit(1);
	}
	listen(sockfd, 5);
	int con_fd = accept(sockfd, (struct sockaddr *)&client, &addrlen); 	//tcp建立连接的时候可以获取客户端的IP和端口号
	ll=1;  //链接上了才建立线程2，否则不建立线程2，堵塞，死循环
	while(1)
	{
		read(con_fd,&buf,4);//也会阻塞接受数据，	
		printf("buf=====%d\n",buf);
	}
	close(con_fd);
	close(sockfd);
	return 0;
}