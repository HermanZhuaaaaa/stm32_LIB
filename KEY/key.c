#include "key.h"
#include "stdio.h"
#include "tim.h"

//按键列表
key_gpio_t key_list[] = {
	{KEY1_GPIO_Port,KEY1_Pin,0},	//端口，引脚，按下有效电平
};

//按键数量
#define KEY_NUM_MAX 		(sizeof(key_list)/sizeof(key_list[0]))

#define CONFIRM_TIME		20
#define LONG_PRESS_TIME	1500

//按键配置
#define SHORT_RELEASE_VALID	1	//0，短按按下即可生效
#define LONG_RELEASE_VALID	1	//1,长按释放之后生效

key_param_t key_param[KEY_NUM_MAX];	//保存所有按键状态

//读取按键状态
uint8_t key_read_state(uint8_t index)
{
	if(HAL_GPIO_ReadPin(key_list[index].port,key_list[index].pin) == key_list[index].pressed_state)
		return 1;	//按键按下
	return 0;
}

//扫描按键状态 （1ms）
uint8_t key_scan(void)
{
	uint8_t key_press;
	uint8_t index;
	
	for(index = 0;index < KEY_NUM_MAX;index ++)
	{
		key_press = key_read_state(index);
		
		switch (key_param[index].current_state)
		{
			case KEY_RELEASE:
			
				if(key_press)
					key_param[index].current_state = KEY_CONFIRM;
				else
					key_param[index].pressed_time = 0;
				break;
			
			case KEY_CONFIRM:
				if(key_press)
				{
					if(++key_param[index].pressed_time > CONFIRM_TIME)
					{
						key_param[index].current_state = KEY_SHORT_PRESSED;
						#if (SHORT_RELEASE_VALID == 0)
							key_param[index].key_event = EVENT_SHORT_PRESSED;
						#endif
					}
				}
				else
					key_param[index].current_state = KEY_RELEASE;
				break;
				
			case KEY_SHORT_PRESSED:
				if(key_press)
				{
					if(++key_param[index].pressed_time > LONG_PRESS_TIME)
					{
						key_param[index].current_state = KEY_LONG_PRESSED;
						#if (LONG_RELEASE_VALID == 0)
							key_param[index].key_event = EVENT_LONG_PRESSED;
						#endif
					}
				}
				else
				{
					key_param[index].current_state = KEY_RELEASE;
					#if (SHORT_RELEASE_VALID == 1)
						key_param[index].key_event = EVENT_SHORT_PRESSED;
					#endif
				}
				break;
				
			case KEY_LONG_PRESSED:
				if(!key_press)
				{
					key_param[index].current_state = KEY_RELEASE;
					#if (LONG_RELEASE_VALID == 1)
						key_param[index].key_event = EVENT_LONG_PRESSED;
					#endif
				}
				break;
				
			default:
				key_param[index].current_state = KEY_RELEASE;
			
		}
	}
	return 0;
}

void key_handle(void)
{
	uint8_t index;
	for (index = 0; index < KEY_NUM_MAX; index++)
    {// 检查有无按键按下
        if(key_param[index].key_event != 0)
        {// 有按键按下
			switch (index)
			{
				case 0:{// 按键1
					if(key_param[index].key_event == EVENT_SHORT_PRESSED)
					{// 短按
						printf("KEY1 SHORT PRESSED\n");
					}
					else if(key_param[index].key_event == EVENT_LONG_PRESSED)
					{// 长按
						printf("KEY1 LONG PRESSED\n");
					}
					break;
				}
				case 1:{// 按键2
					if(key_param[index].key_event == EVENT_SHORT_PRESSED)
					{// 短按
						printf("KEY2 SHORT PRESSED\n");
					}
					else if(key_param[index].key_event == EVENT_LONG_PRESSED)
					{// 长按
						printf("KEY2 LONG PRESSED\n");
					}
					break;
				}
				case 2:{// 按键3
					if(key_param[index].key_event == EVENT_SHORT_PRESSED)
					{// 短按
						printf("KEY3 SHORT PRESSED\n");
					}
					else if(key_param[index].key_event == EVENT_LONG_PRESSED)
					{// 长按
						printf("KEY3 LONG PRESSED\n");
					}
					break;
				}
				case 3:{// 按键4
					if(key_param[index].key_event == EVENT_SHORT_PRESSED)
					{// 短按
						printf("KEY4 SHORT PRESSED\n");
					}
					else if(key_param[index].key_event == EVENT_LONG_PRESSED)
					{// 长按
						printf("KEY4 LONG PRESSED\n");
					}
					break;
				}
				default:{
					break;
				}
			}
			key_param[index].key_event = EVENT_NULL;  // 清除该事件
        }
    }
}

//请重写1ms定时器中断回调函数，并执行函数key_scan()
