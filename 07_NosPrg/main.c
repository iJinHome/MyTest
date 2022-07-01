
//====================================================================
//文件名称：main.c（应用工程主函数）
//框架提供：SD-Arm（sumcu.suda.edu.cn）
//版本更新：2017.08, 2020.05
//功能描述：见本工程的<01_Doc>文件夹下Readme.txt文件
//====================================================================

#define GLOBLE_VAR
#include "includes.h"      //包含总头文件
//----------------------------------------------------------------------
//声明使用到的内部函数
//main.c使用的内部函数声明处

void Delay_ms(uint16_t u16ms)
{
    for(volatile uint32_t i = 0; i < 8000*u16ms; i++) __ASM("NOP");
}


void yellow_LED_OFF(){
     gpio_set(LIGHT_RED,LIGHT_OFF);
     gpio_set(LIGHT_GREEN,LIGHT_OFF);    
}

void yellow_LED_ON(){
     gpio_set(LIGHT_RED,LIGHT_ON);
     gpio_set(LIGHT_GREEN,LIGHT_ON); 
}

//----------------------------------------------------------------------
//主函数，一般情况下可以认为程序从此开始运行（实际上有启动过程见书稿）
int main(void)
{

    //（1）======启动部分（开头）==========================================
    //（1.1）声明main函数使用的局部变量
    // uint8_t  mFlag;           //主循环使用的临时变量
    uint8_t  mSec;	         //记当前秒的值
    int LED=1;
    //（1.2）【不变】关总中断
    DISABLE_INTERRUPTS;
    wdog_stop();
    
    //（1.3）给主函数使用的局部变量赋初值
    // mFlag='A';              //主循环使用的临时变量：蓝灯状态标志
    
    //（1.4）给全局变量赋初值
   	//"时分秒"缓存初始化(00:00:00)
   	gTime[2] = 14;	  	//秒
   	mSec = gTime[2];	//记住当前秒的值
    //（1.5）用户外设模块初始化
    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);    //初始化蓝灯
    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);
    gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);
    timer_init(TIMER_USER,20);   //设置TIMER_USER为20ms中断
    //（1.6）使能模块中断
    timer_enable_int(TIMER_USER);
    //（1.7）【不变】开总中断
    ENABLE_INTERRUPTS;

    printf("------------------------------------------------------\n"); 
    printf("金葫芦提示：                                           \n");
    printf(" （1）蓝灯闪烁\n");
   	printf(" （2）每20ms中断触发Timer定时器中断处理程序一次。 \n");
   	printf(" （3）进入Timer定时器中断处理程序后，静态变量20ms单元+1， \n");
   	printf(" （4）达到一秒时，调用秒+1，程序，计算“时、分、秒”。 \n");
   	printf(" （5）使用全局变量字节型数组gTime[3]，分别存储“时、分、秒”。 \n");
   	printf(" （6）可通过时间测试程序C#2019测试30秒的时间间隔来校准Timer \n");
   	printf(" （7）注意其中静态变量的使用 \n");
    printf("------------------------------------------------------\n");
    printf("---------交通信号灯倒计时--------- \n");

    //for(;;) {  }     //在此打桩，理解蓝色发光二极管为何亮起来了？
    
    //（1）======启动部分（结尾）==========================================
    
    //（2）======主循环部分（开头）=========================================
    for(;;)     //for(;;)（开头）
    {
   		if (gTime[2] == mSec)   continue;
   		mSec=gTime[2];
        	switch(LED)
        	{
        	case 1:				// 绿灯规则
        	 gpio_set(LIGHT_GREEN,LIGHT_ON);   //设置灯“亮”
        	 if(gTime[2]>=4 && gTime[2]<8){
        	 Delay_ms(60);
        	 gpio_set(LIGHT_GREEN,LIGHT_OFF); 		//灯的亮灭控制达到一个闪灯的效果
        	 }
        	 else if(gTime[2]>0 && gTime[2]<4){	//进入最后倒计时阶段闪黄灯
        		yellow_LED_ON();
        		Delay_ms(60);
        		yellow_LED_OFF();
        		if(gTime[2]==1){
        		yellow_LED_OFF();
        		LED=2;
        		}	
        		}
        	 break;
        	case 2:		//红灯亮的规则
        	 gpio_set(LIGHT_RED,LIGHT_ON);   //设置灯“亮”
        	 if(gTime[2]>0 && gTime[2]<7){
        	 Delay_ms(60);
        	 gpio_set(LIGHT_RED,LIGHT_OFF);
        	  if(gTime[2]==1){
        		LED=1;
        		}}
        	 break;
        }printf("剩余时间：\t%d 秒\n",gTime[2]);
    }//for(;;)结尾
    //（2）======主循环部分（结尾）========================================
}

//======以下为主函数调用的子函数存放处=====================================

//====================================================================
/*
知识要素：
（1）main.c是一个模板，该文件所有代码均不涉及具体的硬件和环境，通过调用构件
实现对硬件的干预。
（2）本文件中标有【不变】的地方为系统保留，此类代码与具体项目无关，不宜删除。
（3）本文件中对宏GLOBLE_VAR进行了定义，所以在包含"includes.h"头文件时，会定
义全局变量，在其他文件中包含"includes.h"头文件时，
编译时会自动增加extern
*/

