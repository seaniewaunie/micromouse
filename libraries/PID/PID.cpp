/*
 * PID.cpp
 *
 *  Created on: Feb 19, 2018
 *      Author: Erfan
 */

#include "PID.h"
#include "Locomotion.h"

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
	this->integral += error;
	float newValue = (error * Kp) + (derivative * Kd) + (integral * Ki);
	last_error = error;
	return newValue;
}

bool PID::needToReverse() {
	if(error*last_error < 0)
		return true;
	else
		return false;
}

void PID::setPIDfunction(int(*pid_func)(const float desired_distance)) {
	this->pid_func = pid_func;
}

void PID::resetParameters() {
	error = last_error = derivative = integral = 0;
}

namespace micromouse_pid_functions {

	int encoderPID_setDutyCycle(const float desired_distance) {
		long int leftEncoderPos = lMotor->encoder.getEncoderPosition();
		long int rightEncoderPos = lMotor->encoder.getEncoderPosition();
		long int AverageEncoderPos = (leftEncoderPos + rightEncoderPos)/2;

		float actual_distance = ((float)leftEncoderPos/Encoder::CPR) * Motor::wheel_circum;
		float error = 100.0 * ((desired_distance - actual_distance)/desired_distance);
		float newDutyCycle = encoderPID->calculateNewValue(error);
		if(encoderPID->needToReverse()) {
			lMotor->reversePolarity();
			rMotor->reversePolarity();
		}

		Serial.print("Actual_distance: ");
		Serial.println(actual_distance);

		if(newDutyCycle >= 255.0) {
			return 255;
		}
		else if(newDutyCycle < 45.0) {
			encoderPID->setError(error);
			return 0;
		}
		else {
			return int(newDutyCycle);
		}
	}

	int sensorPID_setDutyCycle(const float desired_distance) {

		float left_actual_distance = lSensor->getDistance();
		float right_actual_distance = rSensor->getDistance();

		bool l_valid = lSensor->isWall();
		bool r_valid = rSensor->isWall();

		float error = 0;

		if(l_valid && r_valid) {
			error = abs(left_actual_distance - right_actual_distance);
		}
		else if(l_valid && !r_valid) {
			error = desired_distance - left_actual_distance;
		}
		else if(!l_valid && r_valid) {
			error = desired_distance - right_actual_distance;
		}
		else {
			error = 0;
		}
		float newDutyCycle = sensorPID->calculateNewValue(error);
		return int(newDutyCycle);
	}
}
























