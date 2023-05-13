//
//  particle.hpp
//  Partikelsystem
//
//  Created by Rafaella Karassavidou on 26.04.23.
//

#ifndef particle_hpp
#define particle_hpp

#define GL_SILENCE_DEPRECATION

#include <stdio.h>
#include <GLUT/glut.h>
#include "vec3.hpp"
#include "plane.hpp"

class particle{
public:
    particle();
    particle(point3 x_, point3 v_, float m_, point3 f_);
    
    void draw_part();
    
    std::vector<point3> get_State();

    void set_State(point3 new_x, point3 new_v);

    std::vector<point3> derivEval();
    
public:
    point3 x_;
    point3 v_;
    float m_;
    point3 f_;
    plane Plane;
};

#endif /* particle_hpp */

