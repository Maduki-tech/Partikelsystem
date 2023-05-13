//
//  plane.hpp
//  Partikelsystem
//
//  Created by Rafaella Karassavidou on 30.04.23.
//

#ifndef plane_hpp
#define plane_hpp

#define GL_SILENCE_DEPRECATION

#include <stdio.h>
#include <GLUT/glut.h>

#include "vec3.hpp"

class plane{
public:
    plane();
    
    void draw_plane();

    bool plane_hit(const point3 &position, point3 &hit_normal);
    
private:
    point3 x_farleft;
    point3 x_farright;
    point3 x_closeleft;
    point3 x_closeright;
    point3 normal_;
    
    bool is_inside_diagonal_plane(const point3& position, const point3& diag_v1, const point3& diag_v2, const point3& diag_v3, const point3& diag_v4);
};


#endif /* plane_hpp */
