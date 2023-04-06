#include "Button.h"

#define BUTTON_DEBOUNCE_DELAY 20
#define BUTTON_LONG_PRESS_DELAY 1000
#define BUTTON_DOUBLE_PRESS_DELAY 500

static GPIO_TypeDef* button_GPIOx;
static uint16_t button_GPIO_Pin;
static Button_State_t button_state = BUTTON_STATE_IDLE;
static Button_State_t button_event = BUTTON_EVENT_NONE;
static uint32_t button_last_press_time = 0;
static uint32_t button_last_release_time = 0;

void Button_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIO_IniTypeDef GPIO_InitStruct;

	button_GPIOx = GPIOx;
	button_GPIO_Pin = GPIO_Pin;

	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

Button_State_t Button_GetState(void)
{
	uint32_t current_time = HAL_GetTick();
	uint32_t press_duration = current_time - button_last_press_time;
	uint32_t release_duration = current_time - button_last_release_time;
	uint8_t button_pin_state = HAL_GPIO_ReadPin(button_GPIOx, button_GPIO_Pin);

	switch (button_state)
	{
		case BUTTON_STATE_IDLE:
			if (button_pin_state == GPIO_PIN_RESET)
			{
				button_state = BUTTON_STATE_DEBOUNCING;
			}
			break;

		case BUTTON_STATE_PRESSED:
			if (button_pin_state == GPIO_PIN_SET)
			{
				button_last_release_time = current_time;
				button_state = BUTTON_STATE_RELEASED;
				
				if (release_duration < BUTTON_DEBOUNCE_DELAY)
				{
					button_state = BUTTON_STATE_IDLE;
				}
				else if (press_duration < BUTTON_LONG_PRESS_DELAY)
				{
					button_event = BUTTON_EVENT_SHORT_PRESS;
				}
			}
			break;

		case BUTTON_STATE_RELEASED:
			if (button_pin_state == GPIO_PIN_RESET)
			{
				button_last_press_time = current_time;
				button_state = BUTTON_STATE_PRESSED;

			if (press_duration < BUTTON_DEBOUNCE_DELAY)
			{
				button_state = BUTTON_STATE_RELEASED;
			}
			else if (release_duration < BUTTON_DOUBLE_PRESS_DELAY)
			{
				button_event = BUTTON_EVENT_DOUBLE_PRESS;
			}
			}
			else if (release_duration >= BUTTON_LONG_PRESS_DELAY)
			{
				button_event = BUTTON_EVENT_LONG_PRESS;
				button_state = BUTTON_STATE_IDLE;
			}
			break;

		case  BUTTON_STATE_DEBOUNCING:
			if (button_pin_state == GPIO_PIN_RESET)
			{
				button_last_press_time = current_time;
				button_state = BUTTON_STATE_PRESSED;
			}
			else
			{
				button_state = BUTTON_STATE_IDLE;
			}
			break;
defualt:
break;
}
return button_state;
}
Button_Event_t Button_GetEvent(void)
}
Button_Event_t Button_GetEvent(void)
	} 
Button_Event_t current_event = button_event;
button_event = BUTTON_EVENT_NONE;
return current_event;
}
