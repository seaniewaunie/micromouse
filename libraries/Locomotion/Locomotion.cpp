#include "Locomotion.h"

	Motor *lMotor;
	Motor *rMotor;
	Sensor *lSensor;
	Sensor *rSensor;
	PID *leftEncoderPID;
	PID *rightEncoderPID;
	PID *sensorPID;

Locomotion::Locomotion() {

		lMotor = new Motor(leftMotorEnable,leftMotorIn1,leftMotorIn2,leftEncoderPinA,leftEncoderPinB);
	  rMotor = new Motor(rightMotorEnable,rightMotorIn1,rightMotorIn2,rightEncoderPinA,rightEncoderPinB);

	  lSensor = new Sensor(leftSensorEnable);
	  rSensor = new Sensor(rightSensorEnable);


	  leftEncoderPID = new PID(0,0,0);
	  rightEncoderPID = new PID(0,0,0);

	  leftEncoderPID->setPIDfunction(&(micromouse_pid_functions::leftEncoderPID_setDutyCycle));
	  rightEncoderPID->setPIDfunction(&(micromouse_pid_functions::rightEncoderPID_setDutyCycle));

	  sensorPID = new PID(1,0.5,0);
	  sensorPID->setPIDfunction(&(micromouse_pid_functions::sensorPID_setDutyCycle));

	  attachInterrupt(digitalPinToInterrupt(lMotor->encoder.getEncoderAPin()),encoder_interrupt_functions::leftEncoderEventA_ISR_Wrapper,RISING);
	  attachInterrupt(digitalPinToInterrupt(lMotor->encoder.getEncoderBPin()),encoder_interrupt_functions::leftEncoderEventB_ISR_Wrapper,RISING);
	  attachInterrupt(digitalPinToInterrupt(rMotor->encoder.getEncoderAPin()),encoder_interrupt_functions::rightEncoderEventA_ISR_Wrapper,RISING);
	  attachInterrupt(digitalPinToInterrupt(rMotor->encoder.getEncoderBPin()),encoder_interrupt_functions::rightEncoderEventB_ISR_Wrapper,RISING);
}

Locomotion::~Locomotion() {
	//do nothing;
}


void Locomotion::goForward() {

	lMotor->encoder.resetEncoderPosition();
	rMotor->encoder.resetEncoderPosition();
	leftEncoderPID->resetParameters();
	leftEncoderPID->setCoefficients(7,0,-0.015);
	rightEncoderPID->resetParameters();
	rightEncoderPID->setCoefficients(10,0,-0.006);
	sensorPID->resetParameters();

	lMotor->resetDirection();
	rMotor->resetDirection();

	rMotor->reverseDirection();

	float desired = 18.0;

	int lMotorDutyCycle = 1, rMotorDutyCycle = 1;
	unsigned long encoderPreviousMillis,sensorPreviousMillis;
	do {
		unsigned long currentMillis = millis();
		if(currentMillis - encoderPreviousMillis > Locomotion::encoderSampleTime) {
			lMotorDutyCycle = leftEncoderPID->pid_func(desired);
			rMotorDutyCycle = rightEncoderPID->pid_func(desired);
			encoderPreviousMillis = currentMillis;
		}/*
		if(currentMillis - sensorPreviousMillis > Locomotion::sensorSampleTime) {
			sensorDutyCycle = sensorPID->pid_func(5.0) / 2;
			sensorPreviousMillis = currentMillis;
		}*/
		rMotor->spinMotor(rMotorDutyCycle);
		lMotor->spinMotor(lMotorDutyCycle);
	} while(lMotorDutyCycle > 0 || rMotorDutyCycle > 0);
}

void Locomotion::turnRight() {

		lMotor->encoder.resetEncoderPosition();
		rMotor->encoder.resetEncoderPosition();
		leftEncoderPID->resetParameters();
		leftEncoderPID->setCoefficients(3.5,0,0.025);
		rightEncoderPID->resetParameters();
		rightEncoderPID->setCoefficients(3.7,0,0.04);

		lMotor->resetDirection();
		rMotor->resetDirection();

		float desired = 6;

		int lMotorDutyCycle = 1, rMotorDutyCycle = 1;

		unsigned long encoderPreviousMillis;
		do {
			unsigned long currentMillis = millis();
			if(currentMillis - encoderPreviousMillis > Locomotion::encoderSampleTime/2) {
				lMotorDutyCycle = leftEncoderPID->pid_func(desired);
				rMotorDutyCycle = rightEncoderPID->pid_func(desired);
				encoderPreviousMillis = currentMillis;
			}
			rMotor->spinMotor(rMotorDutyCycle);
			lMotor->spinMotor(lMotorDutyCycle);
		} while(lMotorDutyCycle > 0 || rMotorDutyCycle > 0);

}

void Locomotion::turnLeft() {
	lMotor->encoder.resetEncoderPosition();
	rMotor->encoder.resetEncoderPosition();
	leftEncoderPID->resetParameters();
	leftEncoderPID->setCoefficients(3.7,0,0.021);
	rightEncoderPID->resetParameters();
	rightEncoderPID->setCoefficients(3.85,0,0.068);

	lMotor->resetDirection();
	rMotor->resetDirection();

	lMotor->reverseDirection();
	rMotor->reverseDirection();

	float desired = 6;

	int lMotorDutyCycle = 1, rMotorDutyCycle = 1;

	unsigned long encoderPreviousMillis;
	do {
		unsigned long currentMillis = millis();
		if(currentMillis - encoderPreviousMillis > Locomotion::encoderSampleTime/2) {
			lMotorDutyCycle = leftEncoderPID->pid_func(desired);
			rMotorDutyCycle = rightEncoderPID->pid_func(desired);
			encoderPreviousMillis = currentMillis;
		}
		rMotor->spinMotor(rMotorDutyCycle);
		lMotor->spinMotor(lMotorDutyCycle);
	} while(lMotorDutyCycle > 0 || rMotorDutyCycle > 0);

}

void Locomotion::makeUTurn() {
	turnRight();
	delay(250);
	turnRight();
}
