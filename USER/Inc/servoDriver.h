#ifndef __SERVO_DRIVER_H__
#define __SERVO_DRIVER_H__

#include "stm32h7xx_hal.h"

//计数器最大值
#define TIM5_ARR  19999
#define TIM12_ARR 19999
#define TIM14_ARR 19999

/*

    载物台是否开启状态
    载物台编号

*/
#define CARGO_SET   1
#define CARGO_UNSET 0

#define CARGO_1 1
#define CARGO_2 2
#define CARGO_3 3

/*

    舵机时基脉冲 20ms
    角度对应比例(180度舵机为例)
    0.5ms--------------0度；
    1.0ms------------45度；
    1.5ms------------90度；
    2.0ms-----------135度；
    2.5ms-----------180度；


    定义最大角度对应占空比比例
    0.1 = 2/20
    0.025 = 0.5/20

*/
#define ANGLE_180   0.1
#define ANGLE_270   0.1
#define ANGLE_0     0.025

/*

    各个舵机转动的最大角度
    HOLDER 云台
    ARM    机械臂
    CARGO  货斗
    PAW    爪架

*/
#define PAW_FULL_ANGLE      ((TIM5_ARR)*(ANGLE_180))
#define CARGO_FULL_ANGLE    ((TIM5_ARR)*(ANGLE_180))
#define HOLDER_FULL_ANGLE   ((TIM14_ARR)*(ANGLE_270))
#define ARM_FULL_ANGLE      ((TIM12_ARR)*(ANGLE_180))
#define ZERO_ANGLE          ((uint16_t)((TIM12_ARR)*(ANGLE_0)))         //这里只用tim12的计数最大值定义了,计数区间不出意外的话应该都是一样的


/*

    servo1, 2 and 3     载物台舵机
    servo4              爪架舵机
    servo5              云台舵机
    servo6 and 7        大臂起降舵机



    servo1, 2, 3, 4     TIM5_channel_1, 2, 3, 4
    servo5              TIM14_channel_1
    servo6,7            TIM12_channel_2, TIM12_channel_1

*/
#define Servo1_Angle (TIM5->CCR1)
#define Servo2_Angle (TIM5->CCR2)
#define Servo3_Angle (TIM5->CCR3)
#define Servo4_Angle (TIM5->CCR4)
#define Servo5_Angle (TIM14->CCR1)
#define Servo6_Angle (TIM12->CCR1)
#define Servo7_Angle (TIM12->CCR2)

extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim12;
extern TIM_HandleTypeDef htim14;

extern uint8_t NowAngle_Cargo;
extern uint8_t NowAngle_Paw;
extern uint8_t NowAngle_LeftArm;
extern uint8_t NowAngle_RightArm;
extern uint16_t NowAngle_Holder;

extern uint8_t  CargoStatus_1;
extern uint8_t  CargoStatus_2;
extern uint8_t  CargoStatus_3;

void Servo_Init(void);
void InitServoAngle(uint8_t CargoAngle, uint8_t PawAngle, uint16_t HolderAngle, uint8_t LeftArmAngle, uint8_t RightArmAngle);
void HolderControl(uint16_t angle);
void PawControl(uint8_t angle);
void LeftArmControl (uint8_t LeftAngle);
void RightArmControl (uint8_t RightAngle);
void Servo_Init(void);
void CargoSet(uint8_t Cargo_pos, uint8_t SetStatus);


#endif
