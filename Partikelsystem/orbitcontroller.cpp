//
//  orbitcontroller.cpp
//  Partikelsystem
//
//  Created by Rafaella Karassavidou on 30.04.23.
//

#include "orbitcontroller.hpp"

void orbitcontroller::update() {
    updateCamera();
}

void orbitcontroller::mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
           if (state == GLUT_DOWN) {
               isDragging = true;
               mouseX = x;
               mouseY = y;
           } else {
               isDragging = false;
           }
       }
}

void orbitcontroller::mouseMotion(int x, int y) {
    if (isDragging) {
           float dx = (x - mouseX) * sensitivity;
           float dy = (y - mouseY) * sensitivity;

           float newAzimuth = azimuth - dx;
           float newElevation = elevation + dy;

           azimuth = newAzimuth;
           elevation = newElevation;

           mouseX = x;
           mouseY = y;

           updateCamera();
       }
}

void orbitcontroller::updateCamera() {
    float rElevation = elevation * M_PI / 180.0f;
    float rAzimuth = azimuth * M_PI / 180.0f;

    float x = cameraTarget.x() + distance * cos(rElevation) * sin(rAzimuth);
    float y = cameraTarget.y() + distance * sin(rElevation);
    float z = cameraTarget.z() + distance * cos(rElevation) * cos(rAzimuth);

    cameraPosition = point3(x, y, z);

    gluLookAt(
        cameraPosition.x(), cameraPosition.y(), cameraPosition.z(),
        cameraTarget.x(), cameraTarget.y(), cameraTarget.z(),
        0.0f, 1.0f, 0.0f
    );
}
