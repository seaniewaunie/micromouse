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

	  attachInterrupt(digitalPinToInterrupt(lMotor->encoder.encoderPin),encoder_interrupt_functions::leftEncoderEvent_ISR_Wrapper,RISING);
	  attachInterrupt(digitalPinToInterrupt(rMotor->encoder.encoderPin),encoder_interrupt_functions::rightEncoderEvent_ISR_Wrapper,RISING);
}

Locomotion::~Locomotion() {
	//do nothing;
}

void Locomotion::goForward() {

	lMotor->encoder.resetEncoderPosition();
	rMotor->encoder.resetEncoderPosition();
	leftEncoderPID->resetParameters();
	rightEncoderPID->resetParameters();
	lMotor->resetDirection();
	rMotor->resetDirection();
	rMotor->reverseDirection();

	leftEncoderPID->setCoefficients(23,0,0.068);
	rightEncoderPID->setCoefficients(22,0,0.063);

	float desired_straight = 16;
	float desired_side = 4.5;

	int lMotorDutyCycle = 1, rMotorDutyCycle = 1;
	do {
			lMotorDutyCycle = leftEncoderPID->pid_func(desired_straight);
			rMotorDutyCycle = rightEncoderPID->pid_func(desired_straight);

			long leftDistance = lSensor->getDistance();
			long rightDistance = rSensor->getDistance();
			long frontDistance = fSensor->getDistance();



			int error = 0;

			if(frontDistance <= 5 && frontDistance != 0) {
					lMotorDutyCycle = 0;
					rMotorDutyCycle = 0;
					goto apply;
			}

			if(leftDistance < 16 && rightDistance < 16) {
				error = rightDistance - leftDistance;
			}
			else if(leftDistance >= 16 && rightDistance < 16) {
				error = rightDistance - desired_side;
			}
			else if(leftDistance < 16 && rightDistance >= 16) {
				error = desired_side - leftDistance;
			}
			else {
				error = 0;
			}

			if(lMotorDutyCycle != 0 && rMotorDutyCycle != 0) {
				if(error > 0) {
					lMotorDutyCycle += 30;
					rMotorDutyCycle -= 30;
				}
				else if(error < 0) {
					lMotorDutyCycle -= 30;
					rMotorDutyCycle += 30;
				}
				else {}
			}

apply:		rMotor->spinMotor(rMotorDutyCycle);
					lMotor->spinMotor(lMotorDutyCycle);

	} while(lMotorDutyCycle > 0 || rMotorDutyCycle > 0);
}

void Locomotion::turnRight() {

		lMotor->encoder.resetEncoderPosition();
		rMotor->encoder.resetEncoderPosition();
		leftEncoderPID->resetParameters();
		rightEncoderPID->resetParameters();
		lMotor->resetDirection();
		rMotor->resetDirection();

		leftEncoderPID->setCoefficients(28,0,0.43);
		rightEncoderPID->setCoefficients(28,0,0.45);

		float desired = 2.9;

		int lMotorDutyCycle = 1, rMotorDutyCycle = 1;
		do {
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
	rightEncoderPID->resetParameters();
	lMotor->resetDirection();
	rMotor->resetDirection();

	lMotor->reverseDirection();
	rMotor->reverseDirection();

	leftEncoderPID->setCoefficients(28,0,0.43);
	rightEncoderPID->setCoefficients(28,0,0.45);

	float desired = 2.9;

	int lMotorDutyCycle = 1, rMotorDutyCycle = 1;
	do {
		lMotorDutyCycle = leftEncoderPID->pid_func(desired);
		rMotorDutyCycle = rightEncoderPID->pid_func(desired);
		rMotor->spinMotor(rMotorDutyCycle);
		lMotor->spinMotor(lMotorDutyCycle);
	} while(lMotorDutyCycle > 0 || rMotorDutyCycle > 0);

}

void Locomotion::makeUTurn() {
			lMotor->encoder.resetEncoderPosition();
			rMotor->encoder.resetEncoderPosition();
			leftEncoderPID->resetParameters();
			rightEncoderPID->resetParameters();
			lMotor->resetDirection();
			rMotor->resetDirection();

			leftEncoderPID->setCoefficients(28,0,0.43);
			rightEncoderPID->setCoefficients(28,0,0.45);

			float desired = 6;

			int lMotorDutyCycle = 1, rMotorDutyCycle = 1;
			do {
				lMotorDutyCycle = leftEncoderPID->pid_func(desired);
				rMotorDutyCycle = rightEncoderPID->pid_func(desired);
				rMotor->spinMotor(rMotorDutyCycle);
				lMotor->spinMotor(lMotorDutyCycle);
			} while(lMotorDutyCycle > 0 || rMotorDutyCycle > 0);
}
