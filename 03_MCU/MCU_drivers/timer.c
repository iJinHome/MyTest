//=====================================================================
//�ļ����ƣ�timer.c
//���ܸ�Ҫ��timer�ײ���������Դ�ļ�
//������λ�����ݴ�ѧǶ��ʽϵͳ���������о���(sumcu.suda.edu.cn)
//��    ����  2019-11-15  V2.0
//����оƬ��STM32
//=====================================================================
#include "timer.h"

//=======================================================================
//�������ƣ�timer_init
//�������أ���
//����˵����timer_No��ʱ��ģ��ţ�ʹ�ú궨��TIMER1��TIMER2������
//          time_ms����ʱ���жϵ�ʱ��������λΪ���룬����Χ��TIM1��TIM15��TIM16��TIM6��
//          TIM7���жϵ�ʱ��������ΧΪ��1~2^16ms��TIM2���жϵ�ʱ��������ΧΪ��1~2^32ms
//���ܸ�Ҫ��ʱ��ģ���ʼ��������TIM1Ϊ�߼���ʱ����TIM2��TIM15��TIM16Ϊͨ�ö�ʱ����
//          TIM6��TIM7Ϊ������ʱ��	
//=======================================================================

void timer_init(uint8_t timer_No,uint32_t time_ms)
{
    switch(timer_No)
    {
    case 1:
	{
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;//ʹ�ܶ�ʱ��ʱ��
		TIM1->CR1 &= ~(TIM_CR1_DIR | TIM_CR1_CMS);//�������ϼ���ģʽ
		TIM1->ARR = (uint16_t)(time_ms-1) ;//��������
		TIM1->PSC = MCU_SYSTEM_CLK_KHZ-1;//����Ԥ��Ƶ
		TIM1->EGR = TIM_EGR_UG;//��ʼ��������
		TIM1->CR1 |= TIM_CR1_CEN_Msk;//������ʹ��
		break;
	}
	case 2:
	{
		RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;//ʹ�ܶ�ʱ��ʱ��
		TIM2->CR1 &= ~(TIM_CR1_DIR | TIM_CR1_CMS);//�������ϼ���ģʽ
		TIM2->ARR = (uint32_t)(time_ms-1) ;//��������   //time_ms*48000/PSC
		TIM2->PSC = MCU_SYSTEM_CLK_KHZ-1;//����Ԥ��Ƶ  //��Ƶ֮���Ƶ��=ѡ����ʱ��ԴƵ��/(PSC+1),   (ARR+1)*(PSC+1)/fclk
		TIM2->EGR = TIM_EGR_UG;//��ʼ��������
		TIM2->CR1 |= TIM_CR1_CEN_Msk;//������ʹ��
		break;
	}
	case 6: //TIM6ֻ�����ϼ���
	{
		RCC->APB1ENR1 |= RCC_APB1ENR1_TIM6EN;
		TIM6->ARR = (uint16_t)(time_ms-1) ;
		TIM6->PSC = MCU_SYSTEM_CLK_KHZ-1;
		TIM6->EGR = TIM_EGR_UG;
		TIM6->CR1 |= TIM_CR1_CEN_Msk;
		break;
	}
	case 7: //TIM7ֻ�����ϼ���
	{
		RCC->APB1ENR1 |= RCC_APB1ENR1_TIM7EN;
		TIM7->ARR = (uint16_t)(time_ms-1) ;
		TIM7->PSC = MCU_SYSTEM_CLK_KHZ-1;
		TIM7->EGR = TIM_EGR_UG;
		TIM7->CR1 |= TIM_CR1_CEN_Msk;
		break;
	}
	case 15: //TIM15ֻ�����ϼ���
	{
		RCC->APB2ENR |= RCC_APB2ENR_TIM15EN;
		TIM15->ARR = (uint16_t)(time_ms-1) ;
		TIM15->PSC = MCU_SYSTEM_CLK_KHZ-1;
		TIM15->EGR = TIM_EGR_UG;
		TIM15->CR1 |= TIM_CR1_CEN_Msk;
		break;
	}
	case 16: //TIM16ֻ�����ϼ���
	{
	    RCC->APB2ENR |= RCC_APB2ENR_TIM16EN;
		TIM16->ARR = (uint16_t)(time_ms-1) ;
		TIM16->PSC = MCU_SYSTEM_CLK_KHZ-1;
		TIM16->EGR = TIM_EGR_UG;
		TIM16->CR1 |= TIM_CR1_CEN_Msk;
		break;
	}
	}

}


//============================================================================
//�������ƣ�timer_enable_int
//�������أ���
//����˵���� timer_No:ʱ��ģ��ţ�ʹ�ú궨��TIMER1��TIMER2������
//���ܸ�Ҫ��ʱ��ģ��ʹ�ܣ�����ʱ��ģ���жϼ���ʱ���ж�
//============================================================================
void timer_enable_int(uint8_t timer_No)
{
    switch(timer_No)
    {
    case 1:
	{
		TIM1->DIER |= TIM_DIER_UIE;
		NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);    //���жϿ�����IRQ�ж�
	    break;
	}
	case 2:
	{
		TIM2->DIER |= TIM_DIER_UIE;
		NVIC_EnableIRQ(TIM2_IRQn);    //���жϿ�����IRQ�ж�
	    break;
	}
	case 6:
	{
		TIM6->DIER |= TIM_DIER_UIE;
		NVIC_EnableIRQ(TIM6_DAC_IRQn);    //���жϿ�����IRQ�ж�
	    break;
	}
	case 7:
	{
		TIM7->DIER |= TIM_DIER_UIE;
		NVIC_EnableIRQ(TIM7_IRQn);    //���жϿ�����IRQ�ж�
	    break;
	}
	case 15:
	{
		TIM15->DIER |= TIM_DIER_UIE;
		NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn);    //���жϿ�����IRQ�ж�
	    break;
	}
	case 16:
	{
		TIM16->DIER |= TIM_DIER_UIE;
		NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);    //���жϿ�����IRQ�ж�
	    break;
	}
    }
}

//============================================================================
//�������ƣ�timer_disable_int
//�������أ���
//����˵���� timer_No:ʱ��ģ��ţ�ʹ�ú궨��TIMER1��TIMER2������
//���ܸ�Ҫ����ʱ���жϳ���
//============================================================================
void timer_disable_int(uint8_t timer_No)
{
    switch(timer_No)
	{
	case 1:
	{
		TIM1->DIER &= ~TIM_DIER_UIE;
		NVIC_DisableIRQ(TIM1_UP_TIM16_IRQn);    //��ֹ�жϿ�����IRQ�ж�
	    break;
	}
	case 2:
	{
		TIM2->DIER &= ~TIM_DIER_UIE;
		NVIC_DisableIRQ(TIM2_IRQn);    //��ֹ�жϿ�����IRQ�ж�
	    break;
	}
	case 6:
	{
		TIM6->DIER &= ~TIM_DIER_UIE;
		NVIC_DisableIRQ(TIM6_DAC_IRQn);    //��ֹ�жϿ�����IRQ�ж�
	    break;
	}
	case 7:
	{
		TIM7->DIER &= ~TIM_DIER_UIE;
		NVIC_DisableIRQ(TIM7_IRQn);    //��ֹ�жϿ�����IRQ�ж�
	    break;
	}
	case 15:
	{
		TIM15->DIER &= ~TIM_DIER_UIE;
		NVIC_DisableIRQ(TIM1_BRK_TIM15_IRQn);    //��ֹ�жϿ�����IRQ�ж�
	    break;
	}
	case 16:
	{
		TIM16->DIER &= ~TIM_DIER_UIE;
		NVIC_DisableIRQ(TIM1_UP_TIM16_IRQn);    //��ֹ�жϿ�����IRQ�ж�
	    break;
	}
	}
}

//===================================================================
//�������ƣ�timer_get_int
//����˵���� timer_No:ʱ��ģ��ţ�ʹ�ú궨��TIMER1��TIMER2������
//���ܸ�Ҫ����ȡtimerģ���жϱ�־
//�������أ��жϱ�־ 1=�ж�Ӧģ���жϲ���;0=�޶�Ӧģ���жϲ���
//===================================================================
uint8_t timer_get_int(uint8_t timer_No)
{
    if(timer_No==1)
    {
		if((TIM1->SR & TIM_SR_UIF)==TIM_SR_UIF)
			return 1;
	}
	else if(timer_No==2)
	{
		if((TIM2->SR & TIM_SR_UIF)==TIM_SR_UIF)
			return 1;
	}
	else if(timer_No==6)
	{
		if((TIM6->SR & TIM_SR_UIF)==TIM_SR_UIF)
			return 1;
	}
	else if(timer_No==7)
	{
		if((TIM7->SR & TIM_SR_UIF)==TIM_SR_UIF)
			return 1;
	}
	else if(timer_No==15)
	{
		if((TIM15->SR & TIM_SR_UIF)==TIM_SR_UIF)
			return 1;
	}
	else if(timer_No==16)
	{
		if((TIM16->SR & TIM_SR_UIF)==TIM_SR_UIF)
			return 1;
	}
	return 0;
}

//============================================================================
//�������ƣ�timer_clear_int
//�������أ���
//����˵���� timer_No:ʱ��ģ��ţ�ʹ�ú궨��TIMER1��TIMER2������
//���ܸ�Ҫ����ʱ������жϱ�־
//============================================================================
void timer_clear_int(uint8_t timer_No)
{
    switch(timer_No)
    {
    case 1:TIM1->SR &=  ~TIM_SR_UIF;break;
	case 2:TIM2->SR &=  ~TIM_SR_UIF;break;
	case 6:TIM6->SR &=  ~TIM_SR_UIF;break;
	case 7:TIM7->SR &=  ~TIM_SR_UIF;break;
	case 15:TIM15->SR &=  ~TIM_SR_UIF;break;
	case 16:TIM16->SR &=  ~TIM_SR_UIF;break;
    }
}
