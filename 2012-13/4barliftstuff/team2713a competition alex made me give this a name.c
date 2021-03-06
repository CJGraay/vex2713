#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  frontIEM,       sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  rightIEM,       sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_3,  backIEM,        sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_4,  leftIEM,        sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           thing1top,     tmotorVex393, openLoop)
#pragma config(Motor,  port4,           armMotor,      tmotorVex393, openLoop)
#pragma config(Motor,  port5,           armMotor2,     tmotorVex393, openLoop)
#pragma config(Motor,  port6,           thing2bottom,  tmotorVex393, openLoop)
#pragma config(Motor,  port7,           frontMotor,    tmotorVex269, openLoop, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port8,           rightMotor,    tmotorVex269, openLoop, encoder, encoderPort, I2C_2, 1000)
#pragma config(Motor,  port2,           backMotor,     tmotorVex269, openLoop, encoder, encoderPort, I2C_3, 1000)
#pragma config(Motor,  port10,          leftMotor,     tmotorVex269, openLoop, encoder, encoderPort, I2C_4, 1000)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main
{
	wait1Msec(2000);

	nMotorEncoder[rightMotor] = 0;
	nMotorEncoder[leftMotor] = 0;
	nMotorEncoder[frontMotor] = 0;
	nMotorEncoder[backMotor] = 0;
	while(SensorValue[rightIEM] <= 5000 && SensorValue[leftIEM]<= 5000)
	{

		motor[frontMotor] = 63;
		motor[backMotor]  = 63;
	}
	while(SensorValue[rightIEM] >= 5000)
	{
		motor[frontMotor] = 0;
		motor[backMotor] = 0;
	}
	nMotorEncoder[frontIEM] = 0;
	while(SensorValue[frontIEM] <= 1000)
	{
		motor[frontMotor] = -63;
		motor[backMotor] = -63;
	}
	while(nMotorEncoder[frontIEM] >= 1000)

	{
		motor[frontMotor] = 0;
		motor[backMotor] = 0;
	}
	nMotorEncoder[rightIEM] = 0;
	nMotorEncoder[rightIEM] = 0;
	{
		motor[thing1top] = 50;
		motor[thing2bottom] = -50;
	}
	while(SensorValue[rightIEM] <= 1000)
		{
			motor(rightMotor) = 63;
			motor(leftMotor) = 63;
		}
	while(SensorValue[rightIEM] >= 1000)
		{
			motor(rightMotor) = 0;
			motor(leftMotor) = 0;
		}


}
