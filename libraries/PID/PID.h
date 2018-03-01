/*
 * PID.h
 *
 *  Created on: Feb 19, 2018
 *      Author: Erfan
 */

#ifndef _PID_H_
#define _PID_H_

#include "Arduino.h"
#include "Motor.h"
#include "Sensor.h"

class PID {

public:

	float Kp;
	float Kd;
	float Ki;

	PID();
	PID(float,float,float);
	~PID();
	float calculateNewValue(float error);
	void setSamplingTime(float st);
	bool needToReverse();

private:

	float error;
	float last_error;
	float samplingTime;
	double integral;
	double derivative;

};

#ifndef __MM_PID_FUNC__
#define __MM_PID_FUNC__

namespace micromouse_pid_functions {

	static unsigned long encoderSampleTime = 200;
	static unsigned long sensorSampleTime = 500;

	void moveStraight(Motor* lMotor, Motor* RMotor, float distance);
	int encoderPID_setDutyCycle(const float desired_distance, Motor* lMotor, Motor* RMotor);
	//int sensorPID_setDutyCycle(const float desired_distance, Sensor* lSensor, Sensor* RSensor);
}

#endif

#endif /* _PID_H */


















