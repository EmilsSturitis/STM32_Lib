#ifndef __BUTTON_H
#define __BUTTON_H

#include "stm32f4xx.h"

typedef enum
{
	BUTTON_STATE_IDLE = 0;
	BUTTON_STATE_PRESSED,
	BUTTON_STATE_RELEASED,
	BUTTON_STATE_DEBOUNCING
} Button_State_t;

typedef enum
{
	BUTTON_EVENT_NONE = 0,
	BUTTON_EVENT_SHORT_PRESS,
	BUTTON_EVENT_LONG_PRESS,
	BUTTON_EVENT_DOUBLE_PRESS
} Button_Event_t;

void Button_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
Button_State_t Button_GetState(void);
Button_Event_t Button_GetEvent(void);

#endif /* __BUTTON_H */
