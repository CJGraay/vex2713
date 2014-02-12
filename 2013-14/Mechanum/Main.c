 #pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  altControl,     sensorTouch)
#pragma config(Sensor, dgtl2,  altControlLED,  sensorLEDtoVCC)
#pragma config(Sensor, dgtl3,  debugLED,       sensorLEDtoVCC)
#pragma config(Sensor, dgtl4,  autonomousConfig1, sensorTouch)
#pragma config(Sensor, dgtl5,  autonomousConfig2, sensorTouch)
#pragma config(Sensor, I2C_1,  leftMotorEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           armMotor,      tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port2,           frontLeft,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port3,           frontRight,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port4,           backLeft,      tmotorVex269, openLoop, reversed, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port5,           backRight,     tmotorServoContinuousRotation, openLoop)
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

	nMotorEncoder[backLeft] = 0;
	bStopTasksBetweenModes = true;
	writeDebugStreamLine("Pre Autonomus Called");
}

void stopMotors(){
	motor[frontRight] = 0;
	motor[frontLeft]  = 0;
	motor[backRight] = 0;
	motor[backLeft]  = 0;
	writeDebugStreamLine("Stop Motors Called");
}

void moveForward(float tileDist)
{
	/*
	Moves forward X tiles

	1 tile = 24in
	15.7 = 1 Rotation (inches traveled)
	24 / 15.7 = 1.528 = Rotation per tile
	1 rotation = 240.448 counts
	367.563 = Counts per tile
	*/
	float countGoal = tileDist * 367.563;
	float currentCount = 0;
	//Motors at full speed
	writeDebugStreamLine("Move Forward Called");


	nMotorEncoder[backLeft] = 0; //Reset encoder count
	currentCount = abs(nMotorEncoder[backLeft]);

	motor[frontRight] = 127;
	motor[frontLeft]  = 127;
	motor[backRight] = 127;
	motor[backLeft]  = 127;

	while(currentCount < countGoal){
		currentCount = abs(nMotorEncoder[backLeft]);
	}

	stopMotors();
	writeDebugStreamLine("Move forward ended");
}
void strafeLeft(float tileDist)
{
	/*
	Moves Left X tiles

	1 tile = 24in
	15.7 = 1 Rotation (inches traveled)
	24 / 15.7 = 1.528 = Rotation per tile
	1 rotation = 240.448 counts
	367.563 = Counts per tile
	*/
	float countGoal = tileDist * 367.563;
	float currentCount = 0;
	//Motors at full speed
	writeDebugStreamLine("Move Forward Called");


	nMotorEncoder[backLeft] = 0; //Reset encoder count
	currentCount = abs(nMotorEncoder[backLeft]);

	motor[frontRight] = 127;
	motor[frontLeft]  = 127;
	motor[backRight] = -127;
	motor[backLeft]  = -127;

	while(currentCount < countGoal){
		currentCount = abs(nMotorEncoder[backLeft]);
	}

	stopMotors();
	writeDebugStreamLine("Move forward ended");
}

void moveBackward(float tileDist)
{
	/*
	Moves forward X tiles

	1 tile = 24in
	15.7 = 1 Rotation (inches traveled)
	24 / 15.7 = 1.528 = Rotation per tile
	1 rotation = 240.448 counts
	367.563 = Counts per tile
	*/
	float countGoal = tileDist * 367.563;
	float currentCount = 0;
	//Motors at full speed
	writeDebugStreamLine("Move Backward Called");


	nMotorEncoder[backLeft] = 0; //Reset encoder count
	currentCount = abs(nMotorEncoder[backLeft]);

	motor[frontRight] = -127;
	motor[frontLeft]  = -127;
	motor[backRight] = -127;
	motor[backLeft]  = -127;

	while(currentCount < countGoal){
		currentCount = abs(nMotorEncoder[backLeft]);
	}

	stopMotors();

}

void turn(float degrees){
	/*
	360 Completely rotate
	-180 turn around
	-90 Turn to the right
	270 turn to the right
	-270 turn to the left
	90 turn to the left

	2 * PI * radius = 360 degrees
	Radius = 9.5
	PI = 3.14159
	59.69in = 360 degrees
	367.563 = Counts per tile
	15.315 = Counts per inch
	59.69 / 360 = 0.166
	Counts per degree = 2.54
	*/
	bool turnLeft = false;
	if(degrees < 0){
		turnLeft = true;
	}
	float countGoal = abs(degrees) * 2.54;
	float currentCount = 0;

	nMotorEncoder[backLeft] = 0; //Reset encoder count
	currentCount = abs(nMotorEncoder[backLeft]);

	if(turnLeft == true){
		motor[frontLeft]  = 127;
		motor[frontRight] = -127;
		motor[backLeft]  = 127;
		motor[backRight] = -127;
	}
	else{
		motor[frontLeft]  = -127;
		motor[frontRight] = 127;
		motor[backLeft]  = -127;
		motor[backRight] = 127;
	}
	while(currentCount > countGoal){
		currentCount = abs(nMotorEncoder[backLeft]);
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
	writeDebugStreamLine("Autonomous Started");
	word autonomousMode;

	if(SensorValue(autonomousConfig1)==0 && SensorValue(autonomousConfig2)==0){
		autonomousMode=5;
		//Blue back with 2nd offensive
		writeDebugStreamLine("Position: Blue Scoring");
	}
	else if(SensorValue(autonomousConfig1)==0 && SensorValue(autonomousConfig2)==1){
		autonomousMode=2;
		//Blue Dead
		writeDebugStreamLine("Position: Blue Dead");
	}
	else if(SensorValue(autonomousConfig1)==1 && SensorValue(autonomousConfig2)==0){
		autonomousMode=3;
		//Red Scoring
		writeDebugStreamLine("Position: Red Scoring");
	}
	else if(SensorValue(autonomousConfig1)==1 && SensorValue(autonomousConfig2)==1){
		autonomousMode=4;
		//Red Dead
		writeDebugStreamLine("Position: Red Dead");
	}

	writeDebugStreamLine("Autonomus mode: %d",(autonomousMode));

	if(autonomousMode==1)
	{
		//Blue Scoring
		//Steps for starting on the blue tile in the scoring zone
		moveForward(3.25);
		turn(120); //Left
		stopMotors();
		moveForward(0.4);
		stopMotors();
		moveBackward(2.2);
		motor[armMotor] = -127; //Extend Arm
		wait1Msec(1000);
		stopMotors();
		motor[armMotor] = 0; //Stop Arm
		moveForward(0.2); //Move a tad forward
		wait1Msec(500);
		moveBackward(0.2); //Move a tad back
		//motor[armMotor] = 127; //Un-Extend Arm
		wait1Msec(500);
		stopMotors();
		motor[armMotor] = 0; //Stop Arm
		moveForward(4);
		stopMotors();
	}
	else if(autonomousMode==2)
	{
		//Blue Dead
		//Steps for starting on the blue tile in the hanging zone
		moveForward(1.75);
		turn(-120); //right
		stopMotors();
		moveForward(2.25);
		stopMotors();
		//motor[armMotor] = -127; //Un-Extend Arm
		wait1Msec(500);
		motor[armMotor] = 0; //Stop Arm
		stopMotors();
		moveForward(1.5);
		stopMotors();
	}
	else if(autonomousMode==3)
	{
		//Red Scoring
		moveForward(3.25);
		turn(-120); //Right
		stopMotors();
		moveForward(0.4);
		stopMotors();
		moveBackward(2.2);
		motor[armMotor] = 127; //Extend Arm
		wait1Msec(1000);
		stopMotors();
		motor[armMotor] = 0; //Stop Arm
		moveForward(0.2); //Move a tad forward
		wait1Msec(500);
		moveBackward(0.2); //Move a tad back
		//motor[armMotor] = -127; //Un-Extend Arm
		wait1Msec(500);
		stopMotors();
		motor[armMotor] = 0; //Stop Arm
		moveForward(4);
		stopMotors();
	}
	else if(autonomousMode==4)
	{
		//Red Dead
		moveForward(1.75);
		turn(120); //left
		stopMotors();
		moveForward(2.25);
		stopMotors();
		//motor[armMotor] = -127; //Un-Extend Arm
		wait1Msec(500);
		motor[armMotor] = 0; //Stop Arm
		stopMotors();
		moveForward(1.5);
		stopMotors();
	}
else if(autonomousMode==5)
	{
		//Blue Dead
		//for if there is  a second offensive robot
		strafeLeft(1.75);
		turn(-120); //right
		stopMotors();
		moveForward(2.25);
		//motor[armMotor] = -127; //Un-Extend Arm
		wait1Msec(500);
		motor[armMotor] = 0; //Stop Arm
		stopMotors();
		moveForward(1.5);
		stopMotors();
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
	writeDebugStreamLine("User Control Started");

	word strafeLeft=false;
	word strafeRight=false;
	word rotateLeft=false;
	word rotateRight=false;
	word altControlUse=SensorValue(altControl);

	while(true){
		//Update buttons
		altControlUse=SensorValue(altControl);
		if(altControlUse==1){
			writeDebugStreamLine("Controls: Alternate");
			strafeLeft=vexRT[Btn7L];
			strafeRight=vexRT[Btn7R];
			rotateLeft=vexRT[Btn8L];
			rotateRight=vexRT[Btn8R];
			SensorValue(altControlLED) = 1;
		}
		else{
			writeDebugStreamLine("Controls: Regular");
			strafeLeft=vexRT[Btn5U];
			strafeRight=vexRT[Btn6U];
			rotateLeft=vexRT[Btn5D];
			rotateRight=vexRT[Btn6D];
			SensorValue[altControlLED] = 0;
		}


		//Set motor direction based on button
		if(strafeLeft==1){
			//Move straight to the left
			motor[frontLeft]  = -120;
			motor[frontRight] = 120;
			motor[backLeft]  = 127;
			motor[backRight] = -127;
		}
		else if(strafeRight==1){
			//Move straight to the right
			motor[frontLeft]  = 122;
			motor[frontRight] = -122;
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
			motor[frontLeft]  = vexRT[Ch3];
			motor[frontRight] = vexRT[Ch2];
			motor[backLeft]  = vexRT[Ch3];
			motor[backRight] = vexRT[Ch2];
		}

		if(vexRT[Btn7U]){
			motor[armMotor] = 80;
		}
		else if(vexRT[Btn7D]){
			motor[armMotor] = -80;
		}
		else{
			motor[armMotor] = 0;
		}

	}
}
