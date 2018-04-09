/*
 * PID.h
 *
 *  Created on: Feb 19, 2018
 *      Author: Erfan
 */

#ifndef _PID_H_
#define _PID_H_

#include "Arduino.h"

class PID {

public:

	typedef int(*pid_func_ptr)(const float);

	float Kp;
	float Kd;
	float Ki;

	PID();
	PID(float,float,float);
	~PID();
	float calculateNewValue(float error);
	void setPIDfunction(int(*pid_func)(const float));
	float getError();
	void setError(float);
	void setCoefficients(float,float,float);
	void resetParameters();
	float samplingTime;
	pid_func_ptr pid_func;

	float error;
	float last_error;
	double integral;
	double derivative;

};

namespace micromouse_pid_functions {

	int leftEncoderPID_setDutyCycle(const float);
	int rightEncoderPID_setDutyCycle(const float);

	int sensorPID_setDutyCycle(const float);

}

#endif /* _PID_H */


















