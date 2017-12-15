// File: arduino.scad
// Author: Aksel Thomas
// Date: 12/15/2017

arduino_l = 70;
arduino_w = 54;
arduino_h = 15;

module arduino() {
    
color([0,0.5,0.5])
{
    translate([0,0,arduino_h/2])
    {
        cube([arduino_l, arduino_w, arduino_h], center = true);
    }
}

}