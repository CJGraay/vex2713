#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,     rightIEM,             sensorQuadEncoderOnI2CPort,        , AutoAssign)
#pragma config(Sensor, I2C_2,     leftIEM,                 sensorQuadEncoderOnI2CPort,        , AutoAssign)
#pragma config(Motor,     port1,                        rightMotor,         tmotorVex269, openLoop, reversed, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,     port10,                    leftMotor,         tmotorVex269, openLoop, encoder, encoderPort, I2C_2, 1000)
//*!!Code automatically generated by 'ROBOTC' configuration wizard                             !!*//

task main
{
  wait1Msec(2000);
  nMotorEncoder[rightMotor] = 0;
  nMotorEncoder[leftMotor] = 0;

  //While less than 1000 encoder counts of the right motor
  while(nMotorEncoder[rightMotor] < 1000)
  {
    motor[rightMotor] = 63;
    motor[leftMotor]  = 63;
  }
}
