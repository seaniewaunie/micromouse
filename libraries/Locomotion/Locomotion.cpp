#include "Locomotion.h"

	Motor *lMotor;
	Motor *rMotor;
	Sensor *fSensor;
	Sensor *lSensor;
	Sensor *rSensor;
	PID *leftEncoderPID;
	PID *rightEncoderPID;

Locomotion::Locomotion() {

	  lMotor = new Motor(leftMotorEnable,leftMotorIn1,leftMotorIn2,leftEncoderPin);
	  rMotor = new Motor(rightMotorEnable,rightMotorIn1,rightMotorIn2,rightEncoderPin);

	  fSensor = new Sensor(frontSensorTrig,frontSensorEcho);
	  lSensor = new Sensor(leftSensorTrig,leftSensorEcho);
	  rSensor = new Sensor(rightSensorTrig,rightSensorEcho);

	  leftEncoderPID = new PID(0,0,0);
	  rightEncoderPID = new PID(0,0,0);

	  leftEncoderPID->setPIDfunction(&(micromouse_pid_functions::leftEncoderPID_setDutyCycle));
	  rightEncoderPID->setPIDfunction(&(micromouse_pid_functions::rightEncoderPID_setDutyCycle));

	  attachInterrupt(digitalPinToInterrupt(lMotor->encoder.getEncoderPin()),encoder_interrupt_functions::leftEncoderEvent_ISR_Wrapper,RISING);
	  attachInterrupt(digitalPinToInterrupt(rMotor->encoder.getEncoderPin()),encoder_interrupt_functions::rightEncoderEvent_ISR_Wrapper,RISING);
}

Locomotion::~Locomotion() {
	//do nothing;
}

void Locomotion::goForward() {

	lMotor->encoder.resetEncoderPosition();
	rMotor->encoder.resetEncoderPosition();

	leftEncoderPID->resetParameters();
	rightEncoderPID->resetParameters();

	leftEncoderPID->setCoefficients(23,0,0.068);
	rightEncoderPID->setCoefficients(22,0,0.063);

	lMotor->resetDirection();
	rMotor->resetDirection();
	rMotor->reverseDirection();


	float desired_straight = 8.0;
	float desired_side = 5;

	int lMotorDutyCycle = 1, rMotorDutyCycle = 1;
	do {
			lMotorDutyCycle = leftEncoderPID->pid_func(desired_straight);
			rMotorDutyCycle = rightEncoderPID->pid_func(desired_straight);


			long leftDistance = lSensor->getDistance();
			long rightDistance = rSensor->getDistance();
			int error = 0;
			if(leftDistance < 16 && rightDistance < 16) {
				error = rightDistance - leftDistance;
			}
			else if(leftDistance >= 16 && rightDistance < 16) {
				error = rightDistance - 5;
			}
			else if(leftDistance < 16 && rightDistance >= 16) {
				error = 5 - leftDistance;
			}
			else {
				error = 0;
			}

			if(lMotorDutyCycle != 0 && rMotorDutyCycle != 0) {
				lMotorDutyCycle += error*5;
				rMotorDutyCycle -= error*5;
			}
;
		rMotor->spinMotor(rMotorDutyCycle);
		lMotor->spinMotor(lMotorDutyCycle);
	} while(lMotorDutyCycle > 0 || rMotorDutyCycle > 0);
	//delay(500);
}

void Locomotion::turnRight() {

		lMotor->encoder.resetEncoderPosition();
		rMotor->encoder.resetEncoderPosition();
		leftEncoderPID->resetParameters();
		leftEncoderPID->setCoefficients(28,0,0.25);
		rightEncoderPID->resetParameters();
		rightEncoderPID->setCoefficients(28,0,0.25);

		lMotor->resetDirection();
		rMotor->resetDirection();

		float desired = 2.75; // 5.7 for turn around

		int lMotorDutyCycle = 1, rMotorDutyCycle = 1;

		unsigned long encoderPreviousMillis;
		do {
			unsigned long currentMillis = millis();
			lMotorDutyCycle = leftEncoderPID->pid_func(desired);
			rMotorDutyCycle = rightEncoderPID->pid_func(desired);

			rMotor->spinMotor(rMotorDutyCycle);
			lMotor->spinMotor(lMotorDutyCycle);
		} while(lMotorDutyCycle > 0 || rMotorDutyCycle > 0);

}

void Locomotion::turnLeft() {
	lMotor->encoder.resetEncoderPosition();
	rMotor->encoder.resetEncoderPosition();
	leftEncoderPID->resetParameters();
	leftEncoderPID->setCoefficients(28,0,0.43);
	rightEncoderPID->resetParameters();
	rightEncoderPID->setCoefficients(28,0,0.45);

	lMotor->resetDirection();
	rMotor->resetDirection();

	lMotor->reverseDirection();
	rMotor->reverseDirection();

	float desired = 2.5;

	int lMotorDutyCycle = 1, rMotorDutyCycle = 1;

	unsigned long encoderPreviousMillis;
	do {
		unsigned long currentMillis = millis();
		lMotorDutyCycle = leftEncoderPID->pid_func(desired);
		rMotorDutyCycle = rightEncoderPID->pid_func(desired);

		rMotor->spinMotor(rMotorDutyCycle);
		lMotor->spinMotor(lMotorDutyCycle);
	} while(lMotorDutyCycle > 0 || rMotorDutyCycle > 0);

}

void Locomotion::makeUTurn() {
	turnRight();
	delay(250);
	turnRight();
}
