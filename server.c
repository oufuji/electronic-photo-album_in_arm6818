#include"server.h"
/*
 *���ܣ�	�̺߳���2����Ҫ�Ƿ��͵�ǰLCD��Ļ����
 *������	void * arg ��LCD�豸�ļ��������ĵ�ַָ��
 *����ֵ��  ��
 */

void* sendbuf(void * arg){	//ѭ����ȡ�׽����е�����
	int p =*(int *)arg;
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	//2, ׼���Է���IP�Ͷ˿ں� 
	struct sockaddr_in server;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	
	server.sin_family = AF_INET;
	server.sin_port   = htons(11144);
	inet_pton(AF_INET,"192.168.22.253", &server.sin_addr);	//�Է�IP
	connect(sockfd, (struct sockaddr *)&server,addrlen);	
	//3, ѭ���Ӽ��̻�ȡ�ַ������͸��Է�
	
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
 *���ܣ�	�̺߳���2����Ҫ�Ƿ��͵�ǰLCD��Ļ����
 *������	void * arg ���ޣ���ָ��
 *����ֵ��  ��
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
	server.sin_port   = htons(11111);	//ͨ��˫������ʹ��ͬһ���˿�
	inet_pton(AF_INET, "192.168.22.153", &server.sin_addr);
	socklen_t addrlen = sizeof(struct sockaddr_in);
	int ret = bind(sockfd, (struct sockaddr *)&server, addrlen);
	if(ret == -1)
	{
		perror("bind failed");
		exit(1);
	}
	listen(sockfd, 5);
	int con_fd = accept(sockfd, (struct sockaddr *)&client, &addrlen); 	//tcp�������ӵ�ʱ����Ի�ȡ�ͻ��˵�IP�Ͷ˿ں�
	ll=1;  //�������˲Ž����߳�2�����򲻽����߳�2����������ѭ��
	while(1)
	{
		read(con_fd,&buf,4);//Ҳ�������������ݣ�	
		printf("buf=====%d\n",buf);
	}
	close(con_fd);
	close(sockfd);
	return 0;
}