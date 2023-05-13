//
//  orbitcontroller.hpp
//  Partikelsystem
//
//  Created by Rafaella Karassavidou on 30.04.23.
//

#ifndef orbitcontroller_hpp
#define orbitcontroller_hpp

#define GL_SILENCE_DEPRECATION

#include <stdio.h>
#include <GLUT/glut.h>
#include <cmath>

#include "vec3.hpp"

class orbitcontroller {
public:
    orbitcontroller()
         : isDragging(false), mouseX(0), mouseY(0), sensitivity(0.2f),
           distance(25.0f) {
               cameraPosition = point3(0.0f, 0.0f, 20.0f);
               cameraTarget = point3(0.0f, 1.0f, 0.0f);
     }
    
    void update();
    void mouseButton(int button, int state, int x, int y);
    void mouseMotion(int x, int y);

private:
    bool isDragging;
    int mouseX;
    int mouseY;
    float sensitivity;

    void updateCamera();

  protected:
    float azimuth;
    float elevation;
    float distance;
    float minDistance;
    float maxDistance;
    float zoomSensitivity;
    float rotateSensitivity;
    float translateSensitivity;

    point3 cameraPosition;
    point3 cameraTarget;
};

#endif /* orbitcontroller_hpp */
