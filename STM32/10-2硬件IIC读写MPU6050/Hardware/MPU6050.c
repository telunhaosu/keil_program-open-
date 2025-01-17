#include "stm32f10x.h"                  // Device header
#include "MPU6050_Reg.h"

#define MPU6050_ADDRESS 0xD0

void WaitCheckEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT)
{
	uint16_t TimeOut = 10000;
	while (I2C_CheckEvent(I2Cx, I2C_EVENT) != SUCCESS) 
	{
		TimeOut--;
		if (TimeOut <= 0)
			break;
	};
}

void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)
{
	//开始生成
	I2C_GenerateSTART(I2C2, ENABLE);//起始条件
	WaitCheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);
	//发送标志
	I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);
	//应答位由硬件进行处理，通过事件是否发生就可以进行应答的判断
	WaitCheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);
	I2C_SendData(I2C2, RegAddress);
	WaitCheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING);
	//传输数据
	I2C_SendData(I2C2, Data);
	WaitCheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);
	//结束生成
	I2C_GenerateSTOP(I2C2, ENABLE);
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
	uint8_t Byte;
	
	//开始生成
	I2C_GenerateSTART(I2C2, ENABLE);//起始条件
	WaitCheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);
	//发送标志
	I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);
	//应答位由硬件进行处理，通过事件是否发生就可以进行应答的判断
	WaitCheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);
	//发送寄存器地址
	I2C_SendData(I2C2, RegAddress);
	WaitCheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);
	//生成重复起始条件
	I2C_GenerateSTART(I2C2, ENABLE);//起始条件
	WaitCheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);
	//读取标志
	I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Receiver);
	//应答位由硬件进行处理，通过事件是否发生就可以进行应答的判断
	WaitCheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);
	//停止时要提前失能ACK标志，和启动停止位，在接收字节后
	I2C_AcknowledgeConfig(I2C2, DISABLE);	//不给应答
	I2C_GenerateSTOP(I2C2, ENABLE);
	
	WaitCheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED);
	
	Byte = I2C_ReceiveData(I2C2);
	
	I2C_AcknowledgeConfig(I2C2, ENABLE);	//恢复应答
	return Byte;
}


void MPU6050_Init(void)
{	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;//在输入模式下该参数无用，可填可不填
	GPIO_Init(GPIOB,&GPIO_Initstructure);
	
	I2C_InitTypeDef I2C_InitStructure;
	I2C_InitStructure.I2C_ClockSpeed = 50000;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;//只有快速模式该参数才生效（100MHz）	
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;	//设置自身地址
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;		//默认应答
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2C2, &I2C_InitStructure);

	I2C_Cmd(I2C2, ENABLE);

	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);		//解除睡眠，选择陀螺仪时钟
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);		//6轴均不待机
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);		//采样分频为10
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06);			//滤波参数给最大
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);	//陀螺仪选择大量程
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);	//加速度计选择大量程
}

void MPU6050_GetData(int16_t *AccX,  int16_t *AccY, int16_t *AccZ,
					 int16_t *GyroX, int16_t *GyroY,int16_t *GyroZ)
{
	uint8_t DataH, DataL;
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	*AccX = (DataH << 8) | DataL; 
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*AccY = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*AccZ = (DataH << 8) | DataL;	
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	*GyroX = (DataH << 8) | DataL;
	
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*GyroY = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	*GyroZ = (DataH << 8) | DataL;
}
