// File: plate.scad
// Author: Aksel Thomas
// Date: 12/15/2017

module plate(l=70, w=54, h=0.1, color="silver") {
    color(color)
    cube([l, w, h], center = true);
}