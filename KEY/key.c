#include "key.h"
#include "stdio.h"
#include "tim.h"

//�����б�
key_gpio_t key_list[] = {
	{KEY1_GPIO_Port,KEY1_Pin,0},	//�˿ڣ����ţ�������Ч��ƽ
};

//��������
#define KEY_NUM_MAX 		(sizeof(key_list)/sizeof(key_list[0]))

#define CONFIRM_TIME		20
#define LONG_PRESS_TIME	1500

//��������
#define SHORT_RELEASE_VALID	1	//0���̰����¼�����Ч
#define LONG_RELEASE_VALID	1	//1,�����ͷ�֮����Ч

key_param_t key_param[KEY_NUM_MAX];	//�������а���״̬

//��ȡ����״̬
uint8_t key_read_state(uint8_t index)
{
	if(HAL_GPIO_ReadPin(key_list[index].port,key_list[index].pin) == key_list[index].pressed_state)
		return 1;	//��������
	return 0;
}

//ɨ�谴��״̬ ��1ms��
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
    {// ������ް�������
        if(key_param[index].key_event != 0)
        {// �а�������
			switch (index)
			{
				case 0:{// ����1
					if(key_param[index].key_event == EVENT_SHORT_PRESSED)
					{// �̰�
						printf("KEY1 SHORT PRESSED\n");
					}
					else if(key_param[index].key_event == EVENT_LONG_PRESSED)
					{// ����
						printf("KEY1 LONG PRESSED\n");
					}
					break;
				}
				case 1:{// ����2
					if(key_param[index].key_event == EVENT_SHORT_PRESSED)
					{// �̰�
						printf("KEY2 SHORT PRESSED\n");
					}
					else if(key_param[index].key_event == EVENT_LONG_PRESSED)
					{// ����
						printf("KEY2 LONG PRESSED\n");
					}
					break;
				}
				case 2:{// ����3
					if(key_param[index].key_event == EVENT_SHORT_PRESSED)
					{// �̰�
						printf("KEY3 SHORT PRESSED\n");
					}
					else if(key_param[index].key_event == EVENT_LONG_PRESSED)
					{// ����
						printf("KEY3 LONG PRESSED\n");
					}
					break;
				}
				case 3:{// ����4
					if(key_param[index].key_event == EVENT_SHORT_PRESSED)
					{// �̰�
						printf("KEY4 SHORT PRESSED\n");
					}
					else if(key_param[index].key_event == EVENT_LONG_PRESSED)
					{// ����
						printf("KEY4 LONG PRESSED\n");
					}
					break;
				}
				default:{
					break;
				}
			}
			key_param[index].key_event = EVENT_NULL;  // ������¼�
        }
    }
}

//����д1ms��ʱ���жϻص���������ִ�к���key_scan()
