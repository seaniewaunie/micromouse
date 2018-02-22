// File: environment.scad
// Author: Aksel Thomas
// Date: 2/13/2018

// This file contains the environment for the robot.
// NOTE: The parts in this file are not part of the robot nor the frame.

include <plate.scad>
include <wall_segment.scad>

module environment(xt = 0, yt = 0, zt = 0) {
    translate([xt, yt, zt]) {
        // The ground (the size of one node in maze)
        plate(l = 180, w = 180, color = "palegreen");
 
        // Segment of wall
        wall_segment(xt = 0, yt = 180);        
    }
}
