//
//  plane.cpp
//  Partikelsystem
//
//  Created by Rafaella Karassavidou on 30.04.23.
//

#include "plane.hpp"

plane::plane(){

}

void plane::draw_plane()
{
    // plane bottom
    glVertex3f(-5.5f, -0.2f, -3.0f);
    glVertex3f(-2.5f, 0.0f, -3.0f);
    glVertex3f(-2.5f, 0.0f, 3.0f);
    glVertex3f(-5.5f, -0.2f, 3.0f);
    
    // plane diagonal
    glVertex3f(-2.5f, 0.0f, -3.0);
    glVertex3f(2.5f, 3.0f, -3.0f);
    glVertex3f(2.5f, 3.0f, 3.0f);
    glVertex3f(-2.5f, 0.0f, 3.0);
    
    // plane top
    glVertex3f(2.5f, 3.0f, -3.0f);
    glVertex3f(4.0f, 3.2f, -3.0f);
    glVertex3f(4.0f, 3.2f, 3.0f);
    glVertex3f(2.5f, 3.0f, 3.0f);

}

//bool plane::plane_hit(const point3 &position, point3 &hit_normal) {
//    // Collision with the top ground
//    if (position.x() >= 2.5f && position.x() <= 5.5f && position.y() >= 2.8f && position.y() <= 3.4 && position.z() >= -3.0f && position.y() <= 3.0f) {
//        hit_normal = point3(0.0f, 1.0f, 0.0f);
//        return true;
//    }
//    // Collision with the diagonal ground
//    else if (position.x() >= -2.5 && position.x() <= 2.5f && position.y() >= 0.0f && position.y() <= 3.0f && position.z() >= -3.0f && position.y() <= 3.0f) {
//        // Compute the normal vector of the plane
//        point3 v1(-2.5f, 0.0f, -3.0f);
//        point3 v2(-2.5f, 0.0f, 3.0f);
//        point3 v3(2.5f, 3.0f, 3.0f);
//        point3 normal = cross(v2 - v1, v3 - v1);
//        normal.normalize();
//
//        hit_normal = normal;
//        return true;
//    }
//    // Collision with the bottom ground
//    else if (position.x() >= -5.5f && position.x() <= -2.5f && position.y() >= -0.2f && position.y() <= 0.0f && position.z() >= -3.0f && position.y() <= 3.0f) {
//        hit_normal = point3(0.0f, -1.0f, 0.0f);
//        return true;
//    }
//
//    hit_normal = point3(0.0f, 0.0f, 0.0f);
//    return false;
//}

bool plane::plane_hit(const point3& position, point3& hit_normal) {
    // Define the plane vertices
    point3 bottom_v1(-5.5f, -0.2f, -3.0f);
    point3 bottom_v2(-2.5f, 0.0f, -3.0f);
    point3 bottom_v3(-2.5f, 0.0f, 3.0f);
    point3 bottom_v4(-5.5f, -0.2f, 3.0f);
    
    point3 top_v1(2.5f, 3.0f, -3.0f);
    point3 top_v2(4.0f, 3.2f, -3.0f);
    point3 top_v3(4.0f, 3.2f, 3.0f);
    point3 top_v4(2.5f, 3.0f, 3.0f);
    
    point3 diag_v1(-2.5f, 0.0f, -3.0f);
    point3 diag_v2(2.5f, 3.0f, -3.0f);
    point3 diag_v3(2.5f, 3.0f, 3.0f);
    point3 diag_v4(-2.5f, 0.0f, 3.0f);
    
     //Compute the plane normals
    point3 bottom_normal = cross(bottom_v2 - bottom_v1, bottom_v3 - bottom_v1);
    point3 top_normal = cross(top_v2 - top_v1, top_v3 - top_v1);
    point3 diag_normal = cross(diag_v2 - diag_v1, diag_v3 - diag_v1);

    // Normalize the normals
    bottom_normal.normalize();
    top_normal.normalize();
    diag_normal.normalize();
    
    if (is_inside_diagonal_plane(position, diag_v1, diag_v2, diag_v3, diag_v4)){
        hit_normal = diag_normal;
        return true;
    }

    if (is_inside_diagonal_plane(position, bottom_v1, bottom_v2, bottom_v3, bottom_v4)){
        hit_normal = bottom_normal;
        return true;
    }
    
    if (is_inside_diagonal_plane(position, top_v1, top_v2, top_v3, top_v4)){
        hit_normal = top_normal;
        return true;
    }
    
    return false;


//
////    // Check for collisions with each plane
//    if (std::abs(dot(position - bottom_v1, bottom_normal)) < 0.2f) {
//        hit_normal = bottom_normal;
//        return true;
//    }
//    if (std::abs(dot(position - top_v1, top_normal)) < 0.2f) {
//        hit_normal = top_normal;
//        return true;
//    }
//    if (std::abs(dot(position - diag_v1, diag_normal)) < 0.2f) {
//        hit_normal = diag_normal;
//        return true;
//    }
//
//    hit_normal = point3(0, 0, 0);
//    return false;
}

bool plane::is_inside_diagonal_plane(const point3& position, const point3& diag_v1, const point3& diag_v2, const point3& diag_v3, const point3& diag_v4) {
    // Create vectors from diag_v1 to the other vertices
    point3 v1 = diag_v2 - diag_v1;
    point3 v2 = diag_v3 - diag_v1;
    point3 v3 = diag_v4 - diag_v1;

    // Calculate the cross products of the vectors
    point3 cross1 = cross(position - diag_v1, v1);
    point3 cross2 = cross(position - diag_v1, v2);
    point3 cross3 = cross(position - diag_v1, v3);

    // Check if the position is within the plane's boundary
    bool inside = (std::abs(dot(cross1, cross2)) >= 0.1) && (std::abs(dot(cross2, cross3)) >= 0.1);
    return inside;
}


//bool plane::plane_hit(const point3 &position, point3 &hit_normal) {
//    // Define the plane vertices
//    point3 bottom_v1(-5.5f, -0.2f, -3.0f);
//    point3 bottom_v2(-2.5f, 0.0f, -3.0f);
//    point3 bottom_v3(-2.5f, 0.0f, 3.0f);
//
//    point3 top_v1(2.5f, 3.0f, -3.0f);
//    point3 top_v2(4.0f, 3.2f, -3.0f);
//    point3 top_v3(4.0f, 3.2f, 3.0f);
//
//    point3 diag_v1(-2.5f, 0.0f, -3.0f);
//    point3 diag_v2(-2.5f, 0.0f, 3.0f);
//    point3 diag_v3(2.5f, 3.0f, 3.0f);
//
//    // Compute the plane normals
//    point3 bottom_normal = cross(bottom_v2 - bottom_v1, bottom_v3 - bottom_v1);
//    point3 top_normal = cross(top_v2 - top_v1, top_v3 - top_v1);
//    point3 diag_normal = cross(diag_v2 - diag_v1, diag_v3 - diag_v1);
//
//    // Normalize the normals
//    bottom_normal.normalize();
//    top_normal.normalize();
//    diag_normal.normalize();
//
//    // Check for collisions with each plane
//    if(std::abs(dot(position - bottom_v1, bottom_normal)) < 0.2f){
//        hit_normal = bottom_normal;
//        return true;
//    }
//    if(std::abs(dot(position - top_v1, top_normal)) < 0.2f){
//        hit_normal = top_normal;
//        return true;
//    }
//    if(std::abs(dot(position - diag_v1, diag_normal)) < 0.2f){
//        hit_normal = diag_normal;
//        return true;
//    }
//
//    hit_normal = point3(0, 0, 0);
//    return false;
//}


