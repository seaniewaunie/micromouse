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

void PID::setPIDfunction(int(*pid_func)(const float desired_distance)) {
	this->pid_func = pid_func;
}

void PID::resetParameters() {
	error = last_error = derivative = integral = 0;
}

float PID::getError() {
	return error;
}

void PID::setError(float error) {
	this->error = error;
}

void PID::setCoefficients(float kp,float kd,float ki) {
	this->Kp = kp;
	this->Kd = kd;
	this->Ki = ki;
}


namespace micromouse_pid_functions {

	int leftEncoderPID_setDutyCycle(const float desired_distance) {
		long int leftEncoderPos = abs(lMotor->encoder.getEncoderPosition());
		float actual_distance = ((float)leftEncoderPos/Encoder::CPR) * Motor::wheel_circum;
		float error = 100.0 * ((desired_distance - actual_distance)/desired_distance);
		float newDutyCycle = leftEncoderPID->calculateNewValue(error);

		Serial.print("L:"); Serial.println(actual_distance);
		if(newDutyCycle >= 255.0) {
			return 255;
		}
		else {
			if(newDutyCycle < 45.0) {
				return 0;
			}
			return int(newDutyCycle);
		}
	}

	int rightEncoderPID_setDutyCycle(const float desired_distance) {
			long int rightEncoderPos = abs(rMotor->encoder.getEncoderPosition());
			float actual_distance = ((float)rightEncoderPos/Encoder::CPR) * Motor::wheel_circum;
			float error = 100.0 * ((desired_distance - actual_distance)/desired_distance);
			float newDutyCycle = rightEncoderPID->calculateNewValue(error);

			Serial.print("R:"); Serial.println(actual_distance);

			if(newDutyCycle >= 255.0) {
				return 255;
			}
			else {
				if(newDutyCycle < 50.0) {
					return 0;
				}
				return int(newDutyCycle);
			}
		}


	int sensorPID_setDutyCycle(const float desired_distance) {

		int sign = 1;

		float left_actual_distance = lSensor->getDistance();
		float right_actual_distance = rSensor->getDistance();


		bool l_valid = lSensor->isWall();
		bool r_valid = rSensor->isWall();

		float error = 0;

		if(l_valid && r_valid) {
			error = left_actual_distance - right_actual_distance;
			if(error < 0)
				sign = -1;
		}
		else if(l_valid && !r_valid) {
			error = desired_distance - left_actual_distance;
			if(error > 0)
					sign = -1;
		}
		else if(!l_valid && r_valid) {
			error = desired_distance - right_actual_distance;
			if(error < 0)
				sign = -1;
		}
		else {
			error = 0;
		}
		float newDutyCycle = abs(error);

		return int(newDutyCycle*sign ) % 10;
	}
}
























