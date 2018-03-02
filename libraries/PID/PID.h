/*
 * PID.h
 *
 *  Created on: Feb 19, 2018
 *      Author: Erfan
 */

#ifndef _PID_H_
#define _PID_H_

#include "Arduino.h"

namespace micromouse_pid_functions {

	int encoderPID_setDutyCycle(const float);
	int sensorPID_setDutyCycle(const float);

}

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
	bool needToReverse();
	void setPIDfunction(int(*pid_func)(const float));
	inline float getError() { return error; }
	inline void setError(float error) { this->error = error; }
	void resetParameters();
	float samplingTime;
	pid_func_ptr pid_func;

private:

	float error;
	float last_error;
	double integral;
	double derivative;

};

#endif /* _PID_H */


















