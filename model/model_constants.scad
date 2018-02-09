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
//ARDUINO_L = 70;
//ARDUINO_W = 54;
//ARDUINO_H = 15;
ARDUINO_L = 68.961;
ARDUINO_W = 53.594;
ARDUINO_H = 15.1892; // height from usb input to lowest soldering on bottom

ARDUINO_PCB_L = 68.961;
ARDUINO_PCB_W = 53.594;
ARDUINO_PCB_H = 5.588;

ARDUINO_PINS_H = 10.3886-ARDUINO_PCB_H; // height of pins coming off board
ARDUINO_PINS_L = 47.752; // this is the longest length for the pins on the right side

// the pins and pcb measurements are there just in case you need them for the arduino

// Back wheel
BACK_WHEEL_D = 72;
BACK_WHEEL_H = 8;
BACK_WHEEL_NUB_D = 7;
BACK_WHEEL_NUB_H = 5;

// 32 mm wheel
32_MM_WHEEL_D = 32;
32_MM_WHEEL_H = 6.6;
32_MM_WHEEL_NUB_H = 2;
32_MM_WHEEL_NUB_D = 7;

// LED
LED_CASE_D = 5.334;
LED_CASE_H = 8.89;
LED_LEAD_D = 0.508;
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
SENSOR_BARREL_D = 16.002;
SENSOR_BARREL_H = 12.2682;
SENSOR_PCB_L = 20.574;
SENSOR_PCB_W = 45.339;
SENSOR_PCB_H = 3.302;

SENSOR_TOTAL_H = SENSOR_BARREL_H + SENSOR_PCB_H;
// 41.8084 is the length from the left barrel to the right barrel
// subtract 1/2 D from both sides to get the foci.
SENSOR_DISTANCE_BW_BARREL_FOCI = 41.8084 - SENSOR_BARREL_D;

// Sensor Pins
SENSOR_PINS_H = 4.4196-SENSOR_PCB_H;
SENSOR_PINS_L = 8.6106;
SENSOR_PINS_W = 10.2362;
SENSOR_PINS_OFFSET = 3; // amount that pins overlap PCB

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
H_BRIDGE_H = 29;

// Caster wheel
CASTER_WHEEL_PLATE_L = 39;
CASTER_WHEEL_PLATE_W = 33;
CASTER_WHEEL_PLATE_H = 1;
CASTER_WHEEL_D = 29;
CASTER_WHEEL_H = 13;
CASTER_WHEEL_Z_OFFSET = 27.5;
CASTER_WHEEL_Y_OFFSET = 32;

// Caster ball
CASTER_BALL_HOUSING_L = 19.05;
CASTER_BALL_HOUSING_W = 13;
CASTER_BALL_HOUSING_H = 6.35;
CASTER_BALL_D = 9.5;

// Wall segment
WALL_SEGMENT_H = 50;
WALL_SEGMENT_L = 167;
WALL_SEGMENT_W = 8;

// USB battery
USB_BATTERY_L = 95.25;
USB_BATTERY_W = 22.2;
USB_BATTERY_H = 25.4;
