#pragma config(Sensor, in1,    Potentiometer,  sensorPotentiometer)
#pragma config(Motor,  port1,           arm,           tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port2,           arm2,          tmotorVex393, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	int TARGET = 3255;
		int Kp = 0;// needs to be changed once achieve real value
	while(true)
	{
			int position = SensorValue(Potentiometer);
			float error = TARGET - position;
			float output =abs( Kp * error);

		if(true)
		{
			motor[armMotor] = output;
			motor[armMotor2] = output;
		}
	}
}
