#ifndef _MORTOR_H_
#define _MORTOR_H_

#define motor_1 1
#define motor_2 2
#define motor_3 3
#define motor_4 4

extern void TIM_MOTOR_Init(void);
extern void Motor_Run(int motor_num,int speed_set);
extern void Test_Motor(void);

#endif /* _MORTOR_H_ */
