#include"Ts.h"

/*
 *功能：	初始化触摸屏
 *参数：	无
 *返回值：  无
 */
void Ts_Init(void){
	ts = open("/dev/input/event0", O_RDONLY); 
	bzero(&buf, sizeof(buf)); 

}


/*
 *功能：	获取手指离开屏幕的坐标
 *参数：	int *x ,int *y : x，y的地址
 *返回值：  无
 */
void Get_Ts(int *x ,int *y){
	int i=1;	
	while(i){
		read(ts, &buf, sizeof(buf)); 
		if(buf.type==EV_ABS)		
		switch(buf.code){
			case ABS_X:  *x = buf.value;break;
			case ABS_Y:  *y = buf.value;break; 						
			case ABS_PRESSURE: 
				if(buf.value==200){
					Flag_SongShou=1;
				}
				else{
					Flag_SongShou=0;
					i=0;
				}
		} 
	} 
}


/*
 *功能：	释放触摸屏资源
 *参数：	无
 *返回值：  无
 */
void Ts_Uninit(void){
	close(ts);
}









