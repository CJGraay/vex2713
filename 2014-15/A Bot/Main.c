#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  isTank,         sensorTouch)
#pragma config(Sensor, dgtl2,  pincherStart,   sensorTouch)
#pragma config(Sensor, dgtl3,  leftPincherStop, sensorTouch)
#pragma config(Sensor, dgtl4,  rightPincherStop, sensorTouch)
#pragma config(Sensor, I2C_1,  leftEncoder,    sensorNone)
#pragma config(Sensor, I2C_2,  rightEncoder,   sensorNone)
#pragma config(Sensor, I2C_4,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_5,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_6,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_7,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_8,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           MotorLeftFront, tmotorVex269_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           MotorRightFront, tmotorVex269_MC29, openLoop)
#pragma config(Motor,  port3,           MotorLeftBack, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           MotorRightBack, tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_4)
#pragma config(Motor,  port5,           armShoulder,   tmotorVex393_MC29, openLoop, encoderPort, I2C_5)
#pragma config(Motor,  port6,           armElbow,      tmotorVex393_MC29, openLoop, encoderPort, I2C_6)
#pragma config(Motor,  port7,           leftPincher,   tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port8,           rightPincher,  tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
#include "functions.c"
/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
	driveStraight(2);
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	// User control code here, inside the loop

	while (true)
	{
		pincherControl();

		// This is the main execution loop for the user control program. Each time through the loop
		// your program should update motor + servo values based on feedback from the joysticks.
		if (isTank == false){
			//Arcade Drive
			motor[MotorLeftFront]  = vexRT[Ch3] + vexRT[Ch4];
			motor[MotorRightFront] = vexRT[Ch3] - vexRT[Ch4];
			motor[MotorLeftBack]  = vexRT[Ch3] + vexRT[Ch4];
			motor[MotorRightBack] = vexRT[Ch3] - vexRT[Ch4];
		}
		else{
			motor[MotorLeftFront]  = vexRT[Ch2];
			motor[MotorRightFront] = vexRT[Ch3];
			motor[MotorLeftBack]  = vexRT[Ch2];
			motor[MotorRightBack] = vexRT[Ch3];
		}

		//Arm Control
		motor[armShoulder] = vexRT[Ch3Xmtr2]; //Xmtr2 == Partner Controller
		motor[armElbow] = vexRT[Ch2Xmtr2];
	}
}
