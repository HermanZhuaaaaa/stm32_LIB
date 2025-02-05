#ifndef __KEY_H__
#define __KEY_H__

#include "main.h"

//按键引脚定义
typedef struct {
	GPIO_TypeDef* 	port;				//GPIOx
	uint16_t		pin;				//引脚
	uint16_t		pressed_state;		//按键按下时的状态
}key_gpio_t;

//按键状态
typedef enum {
	KEY_RELEASE,			//按键释放
	KEY_CONFIRM,			//消抖确认
	KEY_SHORT_PRESSED,		//短按
	KEY_LONG_PRESSED		//长按
}key_state_t;

//按键事件
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
  * @brief 读取按键状态
  * @note
  * @param	按键列表索引
  * @retval	按键状态
  */
uint8_t key_read_state(uint8_t index);
/**
  * @brief	扫描按键列表
  * @note
  * @param	void
  * @retval	按键状态
  */
uint8_t key_scan(void);
/**
  * @brief	按键处理
  * @note
  * @param	void
  * @retval	void
  */
void key_handle(void);
#endif
