//
//  particle.cpp
//  Partikelsystem
//
//  Created by Rafaella Karassavidou on 26.04.23.
//

#include "particle.hpp"

particle::particle(){}

particle::particle(point3 x, point3 v, float m, point3 f) : x_(x), v_(v), m_(m), f_(f) {};

void particle::draw_part(){
    glVertex3f(x_.x(), x_.y(), x_.z());
}

std::vector<point3> particle::get_State(){
    std::vector<point3> state;
    state.push_back(x_);
    state.push_back(v_);
    
    return state;
}

std::vector<point3> particle::derivEval(){
    //TODO: weiß noch nicht ob void oder nicht weil ja ableitung zurückgegeben wird
    std::vector<point3> derivation;
    
    f_ *= 0.0f;
    f_[1] += m_ * (-9.81f);
     
    derivation.push_back(v_);
    derivation.push_back(f_ / m_);
    
    return derivation;
}

//void particle::set_State(point3 new_x, point3 new_v) {
//
//    x_ = new_x;
//    v_ = new_v;
//
//    // Check for collision with the ground (assuming ground plane is at y = 0)
//    if (x_.y() <= 0) {
//        // Compute the normal vector of the plane (assuming ground plane is at y = 0)
//        point3 normal(0, 3, 0);
//
//        // Reflect the velocity vector about the plane
//        v_ = reflect(v_, normal);
//
//        // Apply restitution to the reflected velocity
//        float restitution = 0.8f;
//        v_ *= restitution;
//
//        // Resolve penetration
//        x_[1] += -x_.y();
//    }
//
//    // Apply gravity
//    f_ *= 0.0f;
//    f_[1] += m_ * (-9.81f);
//
//    // Update the position using the velocity and the time step, taking into account the force of gravity
//    x_ = x_ + (v_ + f_ / m_ * 0.001) * 0.001;
//}

void particle::set_State(point3 new_x, point3 new_v) {
    const float restitution = 0.1f; // Restitution factor
    const float gravity = -9.81f;  // Acceleration due to gravity
    const float threshold = 0.01f; // Velocity threshold for coming to rest

    x_ = new_x;
    v_ = new_v;

    // Check for collision with the ground
    point3 hit_normal;
    if (Plane.plane_hit(x_, hit_normal)) {
        // Project the velocity vector onto the plane
        point3 velocity_tangent = v_ - dot(v_, hit_normal) * hit_normal;

        // Apply restitution to the tangent velocity
        velocity_tangent *= restitution;

        // Apply damping to the tangent velocity
        float damping = 0.9f; // Adjust the damping factor as desired
        velocity_tangent *= damping;

        // Apply gravity along the normal direction
        float gravity_normal = gravity * dot(point3(0, -1, 0), hit_normal);

        // Calculate new velocity
        v_ = velocity_tangent + hit_normal * gravity_normal;

        // Update the position using the new velocity and the time step
        float time_step = 0.0001f; // Adjust the time step as desired
        x_ = x_ + v_ * time_step;

        // Check if velocity magnitude is below threshold
        if (v_.length() < threshold) {
            v_ = point3(0.0f, 0.0f, 0.0f); // Particle comes to rest
        }
    } else {
        // Apply gravity
        point3 gravity_force(0.0f, gravity, 0.0f);

        // Update the position and velocity using the force of gravity and the time step
        float time_step = 0.0001f; // Adjust the time step as desired
        v_ = v_ + gravity_force * time_step;
        x_ = x_ + v_ * time_step;
    }
}






