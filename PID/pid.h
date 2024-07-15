#ifndef __PID_H__
#define __PID_H__

typedef struct{
	float kp,ki,kd;
    float err,lastErr;
    float integral,maxIntegral; 
    float output,maxOutput;
}PID_Set;

typedef struct
{
	PID_Set inner;
	PID_Set outer;
	float output;
}Cascade_PID;

void PID_Init(PID_Set * pid,float Kp,float Ki,float Kd,float maxI,float maxO);
float PID_value(PID_Set* pid, float target, float current);
float Cascade_PID_value(Cascade_PID *pid,float outer_target,float outer_feedback,float inner_feedback);

#endif
