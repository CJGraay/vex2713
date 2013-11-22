#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  altControl,     sensorTouch)
#pragma config(Sensor, I2C_1,  leftMotorEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port2,           frontLeft,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port3,           frontRight,    tmotorVex393, openLoop)
#pragma config(Motor,  port4,           backLeft,      tmotorVex269, openLoop, reversed)
#pragma config(Motor,  port5,           backRight,     tmotorVex393, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton(){

	bStopTasksBetweenModes = true;
}

void stopMotors(){
	motor[frontRight] = 0;
	motor[frontLeft]  = 0;
	motor[backRight] = 0;
	motor[backLeft]  = 0;
}

void moveForward(float tileDist)
{
	//Moves forward X tiles

	//1 tile = 24in
	//15.7 = 1 Rotation (inches traveled)
	//24 / 15.7 = 1.528 = Rotation per tile
	//1 rotation = 240.448 counts
	//367.563 = Counts per tile
	float countGoal = tileDist * 367.563;
	float currentCount = 0;
	//Motors at full speed

	nMotorEncoder[leftMotorEncoder] = 0; //Reset encoder count
	currentCount = nMotorEncoder[leftMotorEncoder];

	motor[frontRight] = 127;
	motor[frontLeft]  = 127;
	motor[backRight] = 127;
	motor[backLeft]  = 127;

	while(currentCount < countGoal){
		currentCount = nMotorEncoder[leftMotorEncoder];
	}

	stopMotors();
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous(){


	//Steps for starting on the blue tile in the hanging zone
	//1. Move Forward for ? ft
	moveForward(1);
	//2. Turn 90 degrees to the right
	//3. Move forward over bump and under barrier
	moveForward(3);
	//4. Stop
	stopMotors();

	//Steps for starting on the blue tile in the hanging zone
	//TODO
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

	word strafeLeft=false;
	word strafeRight=false;
	word rotateLeft=false;
	word rotateRight=false;
	bool altControlUse=SensorValue(altControl);

	while(true){
		//Update buttons
		if(altControlUse==1){
			strafeLeft=vexRT[Btn7L];
			strafeRight=vexRT[Btn7R];
			rotateLeft=vexRT[Btn8L];
			rotateRight=vexRT[Btn8R];
		}
		else{
			strafeLeft=vexRT[Btn5U];
			strafeRight=vexRT[Btn6U];
			rotateLeft=vexRT[Btn5D];
			rotateRight=vexRT[Btn6D];
		}


		//Set motor direction based on button
		if(strafeLeft==1){
			//Move straight to the left
			motor[frontLeft]  = -127;
			motor[frontRight] = 127;
			motor[backLeft]  = 127;
			motor[backRight] = -127;
		}
		else if(strafeRight==1){
			//Move straight to the right
			motor[frontLeft]  = 127;
			motor[frontRight] = -127;
			motor[backLeft]  = -127;
			motor[backRight] = 127;
		}

		else if(rotateRight==1){
			//Rotate Clockwise
			motor[frontLeft]  = 127;
			motor[frontRight] = -127;
			motor[backLeft]  = 127;
			motor[backRight] = -127;
		}

		else if(rotateLeft==1){
			//Rotate Counter-Clockwise
			motor[frontLeft]  = -127;
			motor[frontRight] = 127;
			motor[backLeft]  = -127;
			motor[backRight] = 127;
		}
		else{
			//Tank Drive
			motor[frontLeft]  = vexRT[Ch2];
			motor[frontRight] = vexRT[Ch3];
			motor[backLeft]  = vexRT[Ch2];
			motor[backRight] = vexRT[Ch3];
		}
	}
}
