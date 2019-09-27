#include"Lcd.h"
/*
 *功能：	处理任意大小的bmp图片,内容存到buff_480_800_Hecheng
 *参数：	char *p_name：图片名字
 *返回值：  无
 */

void ChuLi_High_Weigh(char *p_name){
	int i,j;
	int k=0;
	int Han_Shu=0;
    int p1=open(p_name,O_RDWR);
	unsigned char head[54];
	read(p1, head , 54);	
	int weigh = head[21]<<24 | head[20]<<16 | head[19]<<8 | head[18];
	int high =  head[25]<<24 | head[24]<<16 | head[23]<<8 | head[22];	
	printf("w=====%d  h==%d\n",weigh ,high);
	lseek(p1,54,SEEK_SET);
	int offer = (weigh*3)%4;
	offer=offer==0?0:(4-offer);
	int Ji_Ou=weigh%2;
	//printf("offer====%d\n",offer);
	unsigned char *buff_char_High=(unsigned char *)malloc((weigh*3 +offer)*high);
	read(p1,buff_char_High,(weigh*3 +offer)*high);
	close(p1);
	printf("offer==%d\n",offer);
	unsigned char A,R,G,B;
	for( i=479;i>=0;i--){
		for( j=0;j<800;j++){
			if((j>=(400+weigh/2+Ji_Ou)||j<(400-weigh/2))||((i>240+high/2)||(i<240-high/2)))
			{		
					buff_480_800_Hecheng[i*800+j]=0xffffffff;
			}
			else {
				Han_Shu=k/weigh;
				//Han_Shu=0;
				A=0x00;
				B=*(buff_char_High+3*k+offer*Han_Shu); 
				G=*(1+buff_char_High+3*k+offer*Han_Shu);
				R=*(2+buff_char_High+3*k+offer*Han_Shu);
				*(buff_480_800_Hecheng+i*800+j)=A<<24 | R<<16 | G<<8 | B ;
				k++;
				//printf("k==%d  ",k);
			}
			
		}
	}
	free(buff_char_High);
}

/*
 *功能：	内存映射
 *参数：	unsigned int * p：指向内存首地址的指针
 *返回值：  无
 */
void YingShe(unsigned int * p){ 
	memcpy(mmp,p,480*800*4);
}

/*
 *功能：	LCD初始化并显示一张图片
 *参数：	char *p_name：图片名字
 *返回值：  返回LCD的文件描述符
 */
int Lcd_Init(char *pname){
	buff_yuan=(unsigned int *)malloc(7209*4);
	buff_480_800=(unsigned int *)malloc(800*480*4);
	buff_480_800_Hecheng=(unsigned int *)malloc(800*480*4);
	int p=open("/dev/fb0",O_RDWR);
	mmp=mmap(NULL,480*800*4,PROT_READ | PROT_WRITE,MAP_SHARED,p,0);
	ChuLi_High_Weigh(pname);
	YingShe(buff_480_800_Hecheng);
	p_all = p;
	printf("p======%d\n",p);
	return p;
}

/*
 *功能：	显示一张图片
 *参数：	char *p_name：图片名字
 *返回值：  无
 */
void show(char *p_name){
	ChuLi_High_Weigh(p_name);
	YingShe(buff_480_800_Hecheng);
}




