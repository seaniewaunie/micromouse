#include "Locomotion.h"

	Motor *lMotor;
	Motor *rMotor;
	Sensor *lSensor;
	Sensor *rSensor;
	PID *encoderPID;
	PID *sensorPID;

Locomotion::Locomotion() {

		lMotor = new Motor(10,9,8,leftEncoderPinA,leftEncoderPinB);
	  rMotor = new Motor(rightMotorEnable,rightMotorIn1,rightMotorIn2,rightEncoderPinA,rightEncoderPinB);

	  lSensor = new Sensor(leftSensorEnable);
	  rSensor = new Sensor(rightSensorEnable);

	  encoderPID = new PID(10,0.7,0.07);
	  encoderPID->setPIDfunction(&(micromouse_pid_functions::encoderPID_setDutyCycle));
	  sensorPID = new PID(0.2,0,0);
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
	float desired = 18.0 + (encoderPID->getError()/100.0 * 18.0);
	encoderPID->resetParameters();
	lMotor->encoder.resetEncoderPosition();
	rMotor->encoder.resetEncoderPosition();

	int encoderWeight = 1, sensorWeight = 0.5;
	int encoderDutyCycle = 1;
	int sensorDutyCycle = 1;
	int dutyCycle = 1;

	Serial.print("desired ");
	Serial.println(desired);
	unsigned long encoderPreviousMillis, sensorPreviousMillis;
	do {
		unsigned long currentMillis = millis();
		if(currentMillis - encoderPreviousMillis > Locomotion::encoderSampleTime) {
			encoderDutyCycle = encoderPID->pid_func(desired);
			Serial.print("DutyCycle ");
			Serial.println(encoderDutyCycle);
			encoderPreviousMillis = currentMillis;
		}

		if(currentMillis - sensorPreviousMillis > sensorSampleTime) {
			sensorDutyCycle = sensorPID->pid_func(5.0);
			sensorPreviousMillis = currentMillis;
		}*/
		dutyCycle = encoderWeight * encoderDutyCycle + sensorWeight * sensorDutyCycle;
		lMotor->spinMotor(dutyCycle);
		rMotor->spinMotor(dutyCycle);
	} while(dutyCycle > 0);
}
