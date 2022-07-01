
//====================================================================
//�ļ����ƣ�main.c��Ӧ�ù�����������
//����ṩ��SD-Arm��sumcu.suda.edu.cn��
//�汾���£�2017.08, 2020.05
//�����������������̵�<01_Doc>�ļ�����Readme.txt�ļ�
//====================================================================

#define GLOBLE_VAR
#include "includes.h"      //������ͷ�ļ�
//----------------------------------------------------------------------
//����ʹ�õ����ڲ�����
//main.cʹ�õ��ڲ�����������

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
//��������һ������¿�����Ϊ����Ӵ˿�ʼ���У�ʵ�������������̼���壩
int main(void)
{

    //��1��======�������֣���ͷ��==========================================
    //��1.1������main����ʹ�õľֲ�����
    // uint8_t  mFlag;           //��ѭ��ʹ�õ���ʱ����
    uint8_t  mSec;	         //�ǵ�ǰ���ֵ
    int LED=1;
    //��1.2�������䡿�����ж�
    DISABLE_INTERRUPTS;
    wdog_stop();
    
    //��1.3����������ʹ�õľֲ���������ֵ
    // mFlag='A';              //��ѭ��ʹ�õ���ʱ����������״̬��־
    
    //��1.4����ȫ�ֱ�������ֵ
   	//"ʱ����"�����ʼ��(00:00:00)
   	gTime[2] = 14;	  	//��
   	mSec = gTime[2];	//��ס��ǰ���ֵ
    //��1.5���û�����ģ���ʼ��
    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);    //��ʼ������
    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);
    gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);
    timer_init(TIMER_USER,20);   //����TIMER_USERΪ20ms�ж�
    //��1.6��ʹ��ģ���ж�
    timer_enable_int(TIMER_USER);
    //��1.7�������䡿�����ж�
    ENABLE_INTERRUPTS;

    printf("------------------------------------------------------\n"); 
    printf("���«��ʾ��                                           \n");
    printf(" ��1��������˸\n");
   	printf(" ��2��ÿ20ms�жϴ���Timer��ʱ���жϴ�������һ�Ρ� \n");
   	printf(" ��3������Timer��ʱ���жϴ�������󣬾�̬����20ms��Ԫ+1�� \n");
   	printf(" ��4���ﵽһ��ʱ��������+1�����򣬼��㡰ʱ���֡��롱�� \n");
   	printf(" ��5��ʹ��ȫ�ֱ����ֽ�������gTime[3]���ֱ�洢��ʱ���֡��롱�� \n");
   	printf(" ��6����ͨ��ʱ����Գ���C#2019����30���ʱ������У׼Timer \n");
   	printf(" ��7��ע�����о�̬������ʹ�� \n");
    printf("------------------------------------------------------\n");
    printf("---------��ͨ�źŵƵ���ʱ--------- \n");

    //for(;;) {  }     //�ڴ˴�׮��������ɫ���������Ϊ���������ˣ�
    
    //��1��======�������֣���β��==========================================
    
    //��2��======��ѭ�����֣���ͷ��=========================================
    for(;;)     //for(;;)����ͷ��
    {
   		if (gTime[2] == mSec)   continue;
   		mSec=gTime[2];
        	switch(LED)
        	{
        	case 1:				// �̵ƹ���
        	 gpio_set(LIGHT_GREEN,LIGHT_ON);   //���õơ�����
        	 if(gTime[2]>=4 && gTime[2]<8){
        	 Delay_ms(60);
        	 gpio_set(LIGHT_GREEN,LIGHT_OFF); 		//�Ƶ�������ƴﵽһ�����Ƶ�Ч��
        	 }
        	 else if(gTime[2]>0 && gTime[2]<4){	//������󵹼�ʱ�׶����Ƶ�
        		yellow_LED_ON();
        		Delay_ms(60);
        		yellow_LED_OFF();
        		if(gTime[2]==1){
        		yellow_LED_OFF();
        		LED=2;
        		}	
        		}
        	 break;
        	case 2:		//������Ĺ���
        	 gpio_set(LIGHT_RED,LIGHT_ON);   //���õơ�����
        	 if(gTime[2]>0 && gTime[2]<7){
        	 Delay_ms(60);
        	 gpio_set(LIGHT_RED,LIGHT_OFF);
        	  if(gTime[2]==1){
        		LED=1;
        		}}
        	 break;
        }printf("ʣ��ʱ�䣺\t%d ��\n",gTime[2]);
    }//for(;;)��β
    //��2��======��ѭ�����֣���β��========================================
}

//======����Ϊ���������õ��Ӻ�����Ŵ�=====================================

//====================================================================
/*
֪ʶҪ�أ�
��1��main.c��һ��ģ�壬���ļ����д�������漰�����Ӳ���ͻ�����ͨ�����ù���
ʵ�ֶ�Ӳ���ĸ�Ԥ��
��2�����ļ��б��С����䡿�ĵط�Ϊϵͳ��������������������Ŀ�޹أ�����ɾ����
��3�����ļ��жԺ�GLOBLE_VAR�����˶��壬�����ڰ���"includes.h"ͷ�ļ�ʱ���ᶨ
��ȫ�ֱ������������ļ��а���"includes.h"ͷ�ļ�ʱ��
����ʱ���Զ�����extern
*/
