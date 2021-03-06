//READ: THIS FILE IS NOT TO BE COMPILED STANDALONE
//Please #include from a proper program

void stopDriving(){
	//Stops all Driving Motors
	motor[frontRight] = 0;
	motor[frontLeft] = 0;
	motor[backRight] = 0;
	motor[backLeft] = 0;
}

void driveSpeed(int speed, string side){
	if (side == "both"){
		motor[backLeft] = speed;
		motor[frontLeft] = speed;
		motor[backRight] = speed;
		motor[frontRight] = speed;
	}
	else if (side == "left"){
		motor[backLeft] = speed;
		motor[frontLeft] = speed;
	}
	else if (side == "right"){
		motor[backRight] = speed;
		motor[frontRight] = speed;
	}
}


void leftDriveSpeed(int speed){
	//Make Left Motors drive at speed
	motor[backLeft] = speed;
	motor[frontLeft] = speed;
}


void rightDriveSpeed(int speed){
	//Make Right motors drive at speed
	motor[backRight] = speed;
	motor[frontRight] = speed;
}


void driveControl(int driveMode){
	// tank = 1 arcade = 2 RC = 3
	//Standard drive control
	float turnSpeed = 0.8;
	if (driveMode == 2){
		//Arcade Drive
		motor[frontLeft]  = vexRT[Ch3] + vexRT[Ch4] * turnSpeed;
		motor[frontRight] = vexRT[Ch3] - vexRT[Ch4] * turnSpeed;
		motor[backLeft]  = vexRT[Ch3] + vexRT[Ch4] * turnSpeed;
		motor[backRight] = vexRT[Ch3] - vexRT[Ch4] * turnSpeed;
		}else if(driveMode == 1){
		//Tank Drive
		motor[frontLeft]  = vexRT[Ch3];
		motor[frontRight] = vexRT[Ch2];
		motor[backLeft]  = vexRT[Ch3];
		motor[backRight] = vexRT[Ch2];
		}else if(driveMode == 3){
		//RC Car
		motor[frontLeft]  = vexRT[Ch3] + vexRT[Ch1] * turnSpeed;
		motor[frontRight] = vexRT[Ch3] - vexRT[Ch1] * turnSpeed;
		motor[backLeft]  = vexRT[Ch3] + vexRT[Ch1] * turnSpeed;
		motor[backRight] = vexRT[Ch3] - vexRT[Ch1] * turnSpeed;
	}
}


void servoOpen(int motnrNumb){
	motor[motnrNumb] = 127;
}


void servoClose(int motnrNumb){
	motor[motnrNumb] = -127;
}


void servoMid(int motnrNumb){
	motor[motnrNumb] = 0;
}


void servoSet(int motnrNumb, int pos){
	motor[motnrNumb] = pos;
}

/*void clawControl(int motorNumb){
	if(vexRT[Btn7U]||vexRT[Btn5D]){//close
		servoOpen(motorNumb);
	}
	else if(vexRT[Btn7D]||vexRT[Btn5U]) {//open
		servoClose(motorNumb);
	}
	else if(vexRT[Btn7R]) {//Mid
		servoMid(motorNumb);
	}
}

void clawPosControl(int motorNumb){
	if(vexRT[Btn8U]){
		servoOpen(motorNumb);
	}
	else if(vexRT[Btn8D]) {
		servoClose(motorNumb);
	}
	else if(vexRT[Btn8R]) {
		servoMid(motorNumb);
	}
}
*/

void driveStraight(float feet, int BOT_ID){
	float distance;
	//A bot:(256 per rotation / 13.25in per wheel rotation) * (12in / 1in) = 231.85 Counts per Foot & 19.33 Counts per Inch.
	//Omni-Directional Wheels
	//B bot:(650 per rotation / 13.25in per wheel rotation) * (12in / 1in) = 588.68 counts per foot & 49.06 Counts per Inch.
	if (BOT_ID==1){
		distance=231.85*feet;
		nMotorEncoder[frontRight]  =0;
		nMotorEncoder[frontLeft]  =0;
	}
	else if (BOT_ID==2){
		distance=588.68*feet;//motor calibration for b bot complete!
		nMotorEncoder[backRight]  =0;
		nMotorEncoder[backLeft]  =0;
	}
	float distanceTraveled = 0;
	int maxSpeed = 90;
	int rightSensor;
	int leftSensor;
	int rightPower;
	int leftPower;

	while (distance > distanceTraveled)
	{
		if (BOT_ID==1){
			rightSensor = nMotorEncoder[frontRight];
			leftSensor = nMotorEncoder[frontLeft];
		}
		else if (BOT_ID==2){
			rightSensor = nMotorEncoder[backRight];
			leftSensor = nMotorEncoder[backLeft];
		}
		distanceTraveled = rightSensor;
		distanceTraveled = abs(distanceTraveled);
		if(leftSensor>rightSensor){
			rightPower =maxSpeed;
			leftPower =maxSpeed-(leftSensor-rightSensor);
		}
		else if(rightSensor>leftSensor){
			leftPower =maxSpeed;
			rightPower =maxSpeed-(rightSensor-leftSensor);
		}
		else
		{
			rightPower =maxSpeed;
			leftPower =maxSpeed;
		}
		leftDriveSpeed(leftPower);
		rightDriveSpeed(rightPower);
	}
	stopDriving();
}


void turn(float deg){
	float targetDistance = 2*abs(deg); //Not sure if 2 is appropriate
	int currentDistance = 0;
	nMotorEncoder[frontRight]  =0;

	if (deg < 0){
		//Turning Left
		leftDriveSpeed(-127);
		rightDriveSpeed(127);
		}else{
		//Turning Right
		leftDriveSpeed(127);
		rightDriveSpeed(-127);
	}
	//Wait until desired angle is reached
	while(targetDistance > currentDistance){
		currentDistance = abs(nMotorEncoder[frontRight]);
	}
	//Stop Motors
	stopDriving();
}
////////////////////////////////////////////////////
//																								//
//************control for claws and arm***********//
//																								//
////////////////////////////////////////////////////

void digitalArmContol(int motorNumb, int forwardBtn, int backwardBtn, int speed){
	if (vexRT[forwardBtn]){//rotate arm forwards
		motor[motorNumb]=speed;
	}
	else if(vexRT[backwardBtn]) {//rotate arm backwards
		motor[motorNumb]=-speed;
	}
	else {
		motor[motorNumb]= 0;//stop motor
	}
}


void digitalServoControl(int motorNumb, int closeBtn, int openBtn){
	if(vexRT[closeBtn]){//close
		servoClose(motorNumb);
	}
	else if(vexRT[openBtn]) {//open
		servoOpen(motorNumb);
	}
}


void analogArmControl(int motorNumb, int analogChannel){
	if(vexRT[analogChannel] == 0){
		motor[motorNumb] = 0;
	}
	else{
		motor[motorNumb] = vexRT[analogChannel];
	}
}
