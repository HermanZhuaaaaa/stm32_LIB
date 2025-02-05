#ifndef __KEY_H__
#define __KEY_H__

#include "main.h"

//�������Ŷ���
typedef struct {
	GPIO_TypeDef* 	port;				//GPIOx
	uint16_t		pin;				//����
	uint16_t		pressed_state;		//��������ʱ��״̬
}key_gpio_t;

//����״̬
typedef enum {
	KEY_RELEASE,			//�����ͷ�
	KEY_CONFIRM,			//����ȷ��
	KEY_SHORT_PRESSED,		//�̰�
	KEY_LONG_PRESSED		//����
}key_state_t;

//�����¼�
typedef enum {
	EVENT_NULL,
	EVENT_SHORT_PRESSED,
	EVENT_LONG_PRESSED
}key_event_t;

typedef struct {
	key_state_t current_state;
	key_event_t key_event;
	uint16_t pressed_time;
}key_param_t;


/**
  * @brief ��ȡ����״̬
  * @note
  * @param	�����б�����
  * @retval	����״̬
  */
uint8_t key_read_state(uint8_t index);
/**
  * @brief	ɨ�谴���б�
  * @note
  * @param	void
  * @retval	����״̬
  */
uint8_t key_scan(void);
/**
  * @brief	��������
  * @note
  * @param	void
  * @retval	void
  */
void key_handle(void);
#endif
