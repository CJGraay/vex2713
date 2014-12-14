#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    shoulderPot,    sensorPotentiometer)
#pragma config(Sensor, in2,    armPot,         sensorPotentiometer)
#pragma config(Sensor, dgtl1,  isTank,         sensorTouch)
#pragma config(Sensor, dgtl2,  pincherStart,   sensorTouch)
#pragma config(Sensor, dgtl3,  leftPincherStop, sensorTouch)
#pragma config(Sensor, dgtl4,  rightPincherStop, sensorTouch)
#pragma config(Sensor, dgtl5,  autoTrigger,    sensorTouch)
#pragma config(Sensor, I2C_1,  leftEncoder,    sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  rightEncoder,   sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           frontLeft, tmotorVex269_HBridge, openLoop, reversed, driveLeft, encoderPort, I2C_1)
#pragma config(Motor,  port2,           frontRight, tmotorVex269_MC29, openLoop, driveRight, encoderPort, I2C_2)
#pragma config(Motor,  port3,           backLeft, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           backRight, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           armShoulder,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           armElbow,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           leftPincher,   tmotorServoContinuousRotation, openLoop, reversed)
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
	while(true){
		driveStraight(2);
		turn(-90);
		driveStraight(2);
		turn(-135);
		driveStraight(3);

		while(SensorValue[autoTrigger]==0){
			//Wait for trigger to be pushed
		}
	}
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
			motor[frontLeft]  = vexRT[Ch3] + vexRT[Ch4];
			motor[frontRight] = vexRT[Ch3] - vexRT[Ch4];
			motor[backLeft]  = vexRT[Ch3] + vexRT[Ch4];
			motor[backRight] = vexRT[Ch3] - vexRT[Ch4];
		}
		else{
			motor[frontLeft]  = vexRT[Ch3];
			motor[frontRight] = vexRT[Ch2];
			motor[backLeft]  = vexRT[Ch3];
			motor[backRight] = vexRT[Ch2];
		}

		//armControl(); //this requires the potentiometers to be connected
		motor[armElbow] = vexRT[Ch2Xmtr2];
		motor[armShoulder] = vexRT[Ch3Xmtr2]; //Xmtr2 == Partner Controller
	}
}
