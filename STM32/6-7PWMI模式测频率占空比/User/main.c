#include "stm32f10x.h"                  // Device head
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "InputCapture.h"


uint8_t i;
int main(void)
{	
	OLED_Init();
	PWM_Init();
	IC_Init();
	
	OLED_ShowString(1, 1, "Freq:00000Hz");
	OLED_ShowString(2, 1, "Duty:00%");
	
	PWM_SetPrescale(720 - 1);	//Fre = 72MHz/(PSC + 1)/(ARR + 1)	Current:ARR = 100-1
	PWM_SetCompare1(80); 
	
	while(1)
	{
		OLED_ShowNum(1, 6, IC_GetFreq(), 5);
		OLED_ShowNum(2, 6, IC_GetDuty(), 2);
	}
}

