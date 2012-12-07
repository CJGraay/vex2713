#pragma config(Sensor, dgtl1,  left,           sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  right,          sensorQuadEncoder)
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
	while(true) {
		// .....................................................................................
		// Insert user code here.
		// .....................................................................................
		bMotorReflected[port1] = false;
		bMotorReflected[port10] = true;
		bMotorReflected[port2] = true;
		bMotorReflected[port9] = false;

		if (SensorValue[left] < 5150) {

			if (SensorValue[left] > SensorValue[right]){

				motor[port1] = 100;  //left
				motor[port2] = 100;  //left
				motor[port9] = 127;  //right
				motor[port10] = 127; //right

			}
			else if (SensorValue[right] > SensorValue[left]){

				motor[port1] = 127;  //left
				motor[port2] = 127;  //left
				motor[port9] = 100;  //right
				motor[port10] = 100; //right

			}

			else{
				motor[port1] = 127;  //left
			motor[port2] = 127;  //left
			motor[port9] = 127;  //right
			motor[port10] = 127; //right
		}
	}
	else {

		motor[port1] = 0;
		motor[port2] = 0;
		motor[port9] = 0;
		motor[port10] = 0;



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
	// This is the main execution loop for the user control program. Each time through the loop
	// your program should update motor + servo values based on feedback from the joysticks.

	// .....................................................................................
	// Insert user code here. This is where you use the joystick values to update your motors, etc.
	// .....................................................................................


	bMotorReflected[port1] = false;
	bMotorReflected[port10] = true;
	bMotorReflected[port2] = true;
	bMotorReflected[port9] = false;

	while (true)

	{

		motor[port1] = vexRT[Ch3];
		motor[port2] = vexRT[Ch3];
		motor[port9] = vexRT[Ch2];
		motor[port10] = vexRT[Ch2];

	}
}
}
