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
}

PID::PID(float Kp, float Kd, float Ki) {
	this->Kp = Kp;
	this->Kd = Kd;
	this->Ki = Ki;
	error = last_error = 0;
	integral = derivative = 0;
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

void PID::setCoefficients(float kp,float kd,float ki) {
	this->Kp = kp;
	this->Kd = kd;
	this->Ki = ki;
}


namespace micromouse_pid_functions {

	int leftEncoderPID_setDutyCycle(const float desired_distance) {
		long int leftEncoderPos = abs(lMotor->encoder.getEncoderPosition());
		float actual_distance = ((float)leftEncoderPos/Encoder::CPR) * Motor::wheel_circum;
		float error = desired_distance - actual_distance;
		float newDutyCycle = leftEncoderPID->calculateNewValue(error);

		//Serial.print("L:"); Serial.println(actual_distance);

		if(newDutyCycle >= 180.0) {
			return 180;
		}
		else {
			if(newDutyCycle < 50.0) {
				return 0;
			}
			return int(newDutyCycle);
		}
	}

	int rightEncoderPID_setDutyCycle(const float desired_distance) {
			long int rightEncoderPos = abs(rMotor->encoder.getEncoderPosition());
			float actual_distance = ((float)rightEncoderPos/Encoder::CPR) * Motor::wheel_circum;
			float error = desired_distance - actual_distance;
			float newDutyCycle = rightEncoderPID->calculateNewValue(error);

			//Serial.print("R:"); Serial.println(actual_distance);

			if(newDutyCycle >= 180.0) {
				return 180;
			}
			else {
				if(newDutyCycle < 50.0) {
					return 0;
				}
				return int(newDutyCycle);
			}
	}
}
