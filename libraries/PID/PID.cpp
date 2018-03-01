/*
 * PID.cpp
 *
 *  Created on: Feb 19, 2018
 *      Author: Erfan
 */

#include "PID.h"

PID::PID() {
	Kp = Kd = Ki = 0;
	error = last_error = 0;
	integral = derivative = 0;
	samplingTime = 0;
}

PID::PID(float Kp, float Kd, float Ki) {
	this->Kp = Kp;
	this->Kd = Kd;
	this->Ki = Ki;

	error = last_error = 0;
	integral = derivative = 0;
	samplingTime = 0;
}

PID::~PID() {
	/* do nothing */
}

float PID::calculateNewValue(float error) {
	this->derivative = error - last_error;
	float newValue = (error * Kp) + (derivative * Kd) + (integral * Ki);
	last_error = error;
	return newValue;
}

void PID::setSamplingTime(float st) {
	this->samplingTime = st;
}

bool PID::needToReverse() {
	if(error*last_error < 0)
		return true;
	else
		return false;
}


namespace micromouse_pid_functions {

	void moveStraight(Motor* lMotor, Motor* RMotor, float distance = 18.0) {
		int encoderDutyCycle = 1;
		int sensorDutyCycle = 1;
		int dutyCycle = 1;
		unsigned long encoderPreviousMillis, sensorPreviousMillis;
		do {
			unsigned long currentMillis = millis();
			if(currentMillis - encoderPreviousMillis > encoderSampleTime) {
				encoderDutyCycle = encoderPID_setDutyCycle(distance,lMotor,RMotor);
				encoderPreviousMillis = currentMillis;
			}/*
			if(currentMillis - sensorPreviousMillis > sensorSampleTime) {
				sensorDutyCycle = sensorPID_setDutyCycle(6.0,&leftSensor,&rightSensor);
				sensorPreviousMillis = currentMillis;
			}*/
			dutyCycle = encoderDutyCycle;// + (0.5 * sensorDutyCycle);
			lMotor->spinMotor(dutyCycle);
			RMotor->spinMotor(dutyCycle);
		} while (dutyCycle > 0);
	}

	int encoderPID_setDutyCycle(const float desired_distance, Motor* lMotor, Motor* RMotor) {
		static PID encoderPID = PID(1,0,0);

		long int lEncoderPos = lMotor->encoder.getEncoderPosition();
		long int REncoderPos = lMotor->encoder.getEncoderPosition();
		long int AvgEncoderPos = (lEncoderPos + REncoderPos)/2;

		float actual_distance = ((float)AvgEncoderPos/Encoder::CPR) * Motor::wheel_circum;
		float error = 100.0 * ((desired_distance - actual_distance)/desired_distance);
		float newDutyCycle = encoderPID.calculateNewValue(error);
		if(encoderPID.needToReverse()) {
			lMotor->reversePolarity();
			RMotor->reversePolarity();
		}

		if(newDutyCycle >= 255.0) {
			return 255;
		}
		else if(newDutyCycle < 45.0) {
			return 0;
		}
		else {
			return int(newDutyCycle);
		}
	}
/*
	int sensorPID_setDutyCycle(const flaot desired_distance, Sensor* lSensor, Sensor* RSensor) {
		static PID sensorPID = PID(1,0,0);

		float l_actual_distance = lSensor->getDistance();
		float r_actual_distance = RSensor->getDistance();

		bool l_valid = lSensor->isWall();
		bool r_valid = RSensor->isWall();

		float error = 0;

		if(l_valid && r_valid) {
			error = abs(l_actual_distance - r_actual_distance);
		}
		else if(l_valid && !r_valid) {
			error = desired_distance - l_actual_distance;
		}
		else if(!l_valid && r_valid) {
			error = desired_distance - r_actual_distance;
		}
		else {
			error = 0;
		}

		float newDutyCycle = sensorPID.calculateNewValue(error);

		return int(newDutyCycle)/2;
	}
*/

}
























