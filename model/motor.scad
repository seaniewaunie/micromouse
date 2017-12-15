//Scott Bohon
//MM6
//motor
//Date: 12/15/2017

//units in mm
//motor

module motor ()
{
    body_h = 12;
    body_w = 10;
    body_l = 31;
    
    //body
    translate([0, 0, 0]){
       color("gold")
        cube([body_l, body_w, body_h], center = true);
    }
    
    
    shaft_d = 3;
    shaft_h = 10;
     //shaft
    rotate(a=90, v=[0,1,0]){
    translate([0, 0, shaft_h/2+body_l/2]){
       color("silver")
        cylinder(d=shaft_d, h=shaft_h, center = true);
    }
    }
    
}

motor();