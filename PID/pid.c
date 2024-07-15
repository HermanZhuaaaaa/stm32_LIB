#include "stm32f4xx.h"                  // Device header
#include "pid.h"

void PID_Init(PID_Set * pid,float Kp,float Ki,float Kd,float maxI,float maxO)
{
	pid->err = 0;
    pid->integral = 0;
    pid->maxIntegral = maxI; 
    pid->maxOutput = maxO;
    pid->lastErr = 0;
    pid->output = 0;
    pid->kp = Kp;
    pid->ki = Ki;
    pid->kd = Kd;
}


float PID_value(PID_Set* pid, float target, float current){
	//更新数据
	pid->lastErr = pid->err;
	pid->err = target - current;
	
	//计算 积分
	pid->integral += pid->err * pid->ki;      
	//计算 微分
	float d_out = (pid->err - pid->lastErr)*pid->kd;
	//计算 比例
	float p_out = pid->err * pid->kp;
	
	
	//积分限幅
	if(pid->integral > pid->maxIntegral)
	{
		pid->integral = pid->maxIntegral;
	}//大于正的最大值
	
	else if (pid->integral < - pid->maxIntegral)
	{
		pid->integral = -  pid->maxIntegral;
	}//小于负的最大值
	
	pid->output = p_out + d_out + pid->integral;
	
	
	//输出限幅
	if(pid->output > pid->maxOutput)
	{
		pid->output = pid->maxOutput;
	}//大于正的最大值
	else if (pid->output < - pid->maxOutput)
	{
		pid->output = -pid->maxOutput;
	}//小于负的最大值
	
	return pid->output;
}

float Cascade_PID_value(Cascade_PID *pid,float outer_target,float outer_feedback,float inner_feedback)
{
	PID_value(&pid->outer,outer_target,outer_feedback);
	PID_value(&pid->inner,pid->outer.output,inner_feedback);
	pid->output = pid->inner.output;
	return pid->output;
}
