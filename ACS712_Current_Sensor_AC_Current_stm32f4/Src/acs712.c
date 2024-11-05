

#include "stm32f4xx.h"
#include "acs712.h"
#include "math.h"


float calc,result;

#define size_of_data 100


uint16_t current_data1[size_of_data];

uint16_t current_data2[size_of_data];


volatile uint8_t finished;

#define offset 2010


float current_result, current_previous;



static float kalman_filter(float RMS_Value)
{
    float x_k1_k1,x_k_k1;

    static float RMS_OLD_Value=0;

    float Z_k;

    static float P_k1_k1;

    static float Q = 0.01;//Q: Regulation noise, Q increases, dynamic response becomes faster, and convergence stability becomes worse
    static float R = 0.5; //R: Test noise, R increases, dynamic response becomes slower, convergence stability becomes better
    static float Kg = 0;
    static float P_k_k1 = 1;

    float kalman_rms;
    static float kalman_rms_old=0;
    Z_k = RMS_Value;
    x_k1_k1 = kalman_rms_old;

    x_k_k1 = x_k1_k1;
    P_k_k1 = P_k1_k1 + Q;

    Kg = P_k_k1/(P_k_k1 + R);

    kalman_rms = x_k_k1 + Kg * (Z_k - kalman_rms_old);
    P_k1_k1 = (1 - Kg)*P_k_k1;
    P_k_k1 = P_k1_k1;

    RMS_OLD_Value = RMS_Value;
    kalman_rms_old = kalman_rms;

    return kalman_rms;
}


void acs712_init()
{
	/*Enable floating point unit:  Enable CP10 and CP11 full access*/
	SCB->CPACR |=(1<<20);
	SCB->CPACR |=(1<<21);
	SCB->CPACR |=(1<<22);
	SCB->CPACR |=(1<<23);

	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN; //enable gpio a clock
	GPIOA->MODER|=GPIO_MODER_MODER1;  //set the PA1 to analog mode

	GPIOA->MODER|=	GPIO_MODER_MODE5_0;
	GPIOA->MODER&=~GPIO_MODER_MODE5_1;


	/*ADC related set up*/

	RCC->APB2ENR		|=RCC_APB2ENR_ADC1EN;
	ADC1->CR2			|=ADC_CR2_DMA|ADC_CR2_DDS;
	ADC1->CR2			|=ADC_CR2_EXTEN_0;
	ADC1->CR2			|=ADC_CR2_EXTSEL_1|ADC_CR2_EXTSEL_2;
	ADC1->SQR3			|=(1<<ADC_SQR3_SQ1_Pos);
	ADC1->SMPR2			|=(0x07<<ADC_SMPR2_SMP1_Pos);

	/*DMA related setup*/
	RCC->AHB1ENR		|=RCC_AHB1ENR_DMA2EN;
	DMA2_Stream0->CR	&=~DMA_SxCR_EN;

	while(DMA2_Stream0->CR ==DMA_SxCR_EN){;}

	DMA2_Stream0->CR	|=DMA_SxCR_MSIZE_0|DMA_SxCR_PSIZE_0|DMA_SxCR_MINC|DMA_SxCR_HTIE|DMA_SxCR_CIRC|DMA_SxCR_DBM;

	DMA2_Stream0->PAR	 =(uint32_t)(&(ADC1->DR));

	DMA2_Stream0->M0AR 	 =(uint32_t )(current_data1);

	DMA2_Stream0->M1AR 	 =(uint32_t )(current_data2);

	DMA2_Stream0->NDTR	 =size_of_data;

	NVIC_EnableIRQ(DMA2_Stream0_IRQn);

	/* Timer related setup*/
	RCC->APB1ENR		|=RCC_APB1ENR_TIM2EN;
	TIM2->PSC			 =1600-1;
	TIM2->ARR			 =10-1;
	TIM2->CR2			|=TIM_CR2_MMS_1;
	/*Launch the ADC*/
	ADC1->CR2			|=ADC_CR2_ADON;
	/*Launch the DMA*/
	DMA2_Stream0->CR 	|=DMA_SxCR_EN;
	/*Launch the timer*/
	TIM2->CR1			|=TIM_CR1_CEN;

}



float calculate_rms(uint16_t * values)
{
	calc=0;
	for (int i=0;i<size_of_data;i++)
	{
		calc=calc+((values[i]-offset) * (values[i]-offset));
	}
	calc=calc/size_of_data;
	calc=sqrt(calc);

	result=kalman_filter(calc);
	result=0.0206*result-0.2;
	current_previous=result;
	return result;
}


float get_acs712_current()
{
	if(finished==1)
	{
		finished=0;

		if((DMA2_Stream0->CR & DMA_SxCR_CT)>> DMA_SxCR_CT_Pos == 1 )
		{
			return calculate_rms(current_data2);
		}

		else
		{
			return calculate_rms(current_data1);
		}

	}

	else
	{
		return current_previous;
	}

}


void DMA2_Stream0_IRQHandler(void)
{

	if(((DMA2->LISR)&DMA_LISR_HTIF0))
	{
		finished=1;
		DMA2->LIFCR=DMA_LIFCR_CHTIF0;
		}
		NVIC_ClearPendingIRQ(DMA2_Stream0_IRQn);
	}
