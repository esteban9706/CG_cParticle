//
//  cParticle.cpp
//  CG_demo
//
//  Created by Esteban Cortes Lozano on 08/11/19.
//  Copyright © 2019 Esteban Cortes Lozano. All rights reserved.
//

#include <stdio.h>
#include "cParticle.h"
 
Particle::Particle()
{
    alive = true;
    pos[0] = pos[1] = pos[2] = 0;
    oDiffuse[0] = 1;
    oDiffuse[1] = oDiffuse[2] = 0;
    diffuse[0] = oDiffuse[0];
    diffuse[1] = oDiffuse[1];
    diffuse[2] = oDiffuse[2];
 
    mass = 5;  // 5 kg
    oldPos[0] = pos[0];
    oldPos[1] = pos[1];
    oldPos[2] = pos[2];
    forces[0] = forces[1] = forces[2] = 0;
    dragForce[0] = dragForce[1] = dragForce[2] = 0;
    specular[0] = specular[1] = specular[2] = 0;
    shininess = 60;
    radius = mass / 10;
    age = 0;
    restitutionCoefficient = 0.8; // Elastic or inelastic collision
}
 
void Particle::draw()
{
    glPushMatrix();
    {
        glTranslatef(pos[0], pos[1], pos[2]);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess);
        glutSolidSphere(radius, 20, 20);
    }
    glPopMatrix();
}
 


void Particle::addForce(float force[3]){
    forces[0] += force[0];
    forces[1] += force[1];
    forces[2] += force[2];
}
 
void Particle::integrateVerlet(float dt)
{
    // Compute acceleration:
    float accel[3] = {forces[0] / mass, forces[1] / mass, forces[2] / mass};
    // Save a temporary copy of the current position:
    float temp[3] = { pos[0], pos[1], pos[2] };
    // Integrate the new position using Verlet's method:
    pos[0] = 2 * pos[0] - oldPos[0] + accel[0] * dt * dt;
    pos[1] = 2 * pos[1] - oldPos[1] + accel[1] * dt * dt;
    pos[2] = 2 * pos[2] - oldPos[2] + accel[2] * dt * dt;
    // Update the previous position:
    oldPos[0] = temp[0];
    oldPos[1] = temp[1];
    oldPos[2] = temp[2];
}

void Particle::checkFloorCollisions()
{
    if (pos[1] <= 0) {
        forces[1] = -forces[1] * restitutionCoefficient;
        pos[1] = 0;
    }
}
 
void Particle::stepSimulation(float dt)
{
    checkFloorCollisions();
    integrateVerlet(dt);
}

Particle::~Particle()
{
 
}
