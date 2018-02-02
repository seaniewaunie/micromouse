// File: model_constants.scad
// Author: Aksel Thomas
// Date: 12/18/2017

/********************
LETTER KEY
W   =   WIDTH
L   =   LENGTH
H   =   HEIGHT
D   =   DIAMETER
BW  =   BETWEEN

NOTE 1:
Cylinders are defined by two dimensions: D and H.

NOTE 2:
All units are in millimeters.
********************/

// Arduino
ARDUINO_L = 70;
ARDUINO_W = 54;
ARDUINO_H = 15;

// Back wheel
BACK_WHEEL_D = 72;
BACK_WHEEL_H = 8;
BACK_WHEEL_NUB_D = 7;
BACK_WHEEL_NUB_H = 5;

// LED
LED_CASE_D = 6;
LED_CASE_H = 9;
LED_LEAD_D = 0.5;
LED_LEAD_SHORT_H = 26;
LED_LEAD_LONG_H = 28;
LED_LEAD_OFFSET = 1;

// Motor
MOTOR_SHAFT_D = 3;
MOTOR_SHAFT_H = 10;
MOTOR_BODY_L = 31;
MOTOR_BODY_W = 10;
MOTOR_BODY_H = 12;

// Plate
PLATE_L = ARDUINO_L;
PLATE_W = ARDUINO_W;
PLATE_H = 0.1;

// Sensor
SENSOR_BARREL_D = 16;
SENSOR_BARREL_H = 12;
SENSOR_PCB_L = 21;
SENSOR_PCB_W = 46;
SENSOR_PCB_H = 3;
SENSOR_TOTAL_H = SENSOR_BARREL_H + SENSOR_PCB_H;
SENSOR_DISTANCE_BW_BARREL_FOCI = 30;

// Tenergy battery
TENERGY_W = 36;
TENERGY_H = 19;
TENERGY_L = 70;

// Pushbutton
PUSHBUTTON_BODY_L = 6;
PUSHBUTTON_BODY_W = PUSHBUTTON_BODY_L;
PUSHBUTTON_BODY_H = 3;
PUSHBUTTON_CYLINDER_D = 3.5;
PUSHBUTTON_CYLINDER_H = 1;

// H-bridge
H_BRIDGE_L = 43;
H_BRIDGE_W = H_BRIDGE_L;
H_BRIDGE_H = 26;

// Caster wheel
CASTER_WHEEL_PLATE_L = 39;
CASTER_WHEEL_PLATE_W = 33;
CASTER_WHEEL_PLATE_H = 1;
CASTER_WHEEL_D = 29;
CASTER_WHEEL_H = 13;
CASTER_WHEEL_Z_OFFSET = 27.5;
CASTER_WHEEL_Y_OFFSET = 32;

// Wall segment
WALL_SEGMENT_H = 50;
WALL_SEGMENT_L = 167;
WALL_SEGMENT_W = 8;