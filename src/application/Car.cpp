#include <math.h>
#include "Car.h"
#include "GLTool.h"
#include "GLRender.h"

using namespace p3d;
using namespace std;


// ************************************************************
Car::~Car() {
}

Car::Car() {
  _orientation.setIdentity();
  _position.set(0,0,0);
  _steering=0;
  _rotateWheel=0;
  _acceleration=0;
  _velocity=0;
}

// ******************************************************************
// méthodes à compléter lors du TP

//Q3
void Car::drawRim() {
    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.scale(0.2, 0.2, 4.);
    p3d::modelviewMatrix.translate(0., 0. ,-0.5);
    drawCylinder();
    p3d::modelviewMatrix.pop();

    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.rotate(45., 1., 0., 0.);
    p3d::modelviewMatrix.scale(0.2, 0.2, 4.);
    p3d::modelviewMatrix.translate(0., 0. ,-0.5);
    drawCylinder();
    p3d::modelviewMatrix.pop();

    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.rotate(90., 1., 0., 0.);
    p3d::modelviewMatrix.scale(0.2, 0.2, 4.);
    p3d::modelviewMatrix.translate(0., 0. ,-0.5);
    drawCylinder();
    p3d::modelviewMatrix.pop();

    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.rotate(-45., 1., 0., 0.);
    p3d::modelviewMatrix.scale(0.2, 0.2, 4.);
    p3d::modelviewMatrix.translate(0., 0. ,- 0.5);
    drawCylinder();
    p3d::modelviewMatrix.pop();
}

//Q4
void Car::drawWheel() {
    p3d::modelviewMatrix.push();
    drawRim();
    p3d::diffuseColor=Vector3(0., 0., 1.);
    p3d::modelviewMatrix.scale(2.5, 3., 3.);
    p3d::modelviewMatrix.rotate(90., 0., 1., 0.);
    drawTorus();
    p3d::diffuseColor=Vector3(1., 0., 0.);
    p3d::modelviewMatrix.pop();
}

//Q5
void Car::drawAxle() {

    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.translate(-4., 0. ,0.);
    drawWheel();
    p3d::modelviewMatrix.pop();

    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.rotate(90., 0., 1., 0.);
    p3d::modelviewMatrix.scale(0.5, 0.5, 8.);
    p3d::modelviewMatrix.translate(0., 0. ,-0.5);
    drawCylinder();
    p3d::modelviewMatrix.pop();

    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.translate(4, 0. ,0.);
    drawWheel();
    p3d::modelviewMatrix.pop();

}

//Q2
void Car::drawBody() {
    p3d::modelviewMatrix.push();
    p3d::diffuseColor=Vector3(0., 0., 1.);
    p3d::modelviewMatrix.translate(0., 1. ,0);
    drawCube();
    p3d::modelviewMatrix.translate(1.5, -2. ,0);
    p3d::modelviewMatrix.scale(2.5, 1.);
    drawCube();
    p3d::modelviewMatrix.pop();
}

void Car::draw() {
  //p3d::modelviewMatrix.push();

  //p3d::modelviewMatrix.translate(0., 2. ,0);

  //drawCube();
  //Q2
  //drawBody();
  //Q3
  //drawRim();
  //Q4
  //drawWheel();
  //Q5
  //drawAxle();

  //Q6
  p3d::modelviewMatrix.push();
  p3d::modelviewMatrix.translate(4., -1. , 0.);
  p3d::modelviewMatrix.rotate(90., 0., 1., 0.);
  p3d::modelviewMatrix.rotate(_steering, 0., 1., 0.);
  p3d::modelviewMatrix.rotate(_rotateWheel, 1., 0., 0.);
  p3d::modelviewMatrix.scale(0.5, 0.5, 0.5);
  drawAxle();
  p3d::modelviewMatrix.pop();

  p3d::modelviewMatrix.push();
  p3d::modelviewMatrix.translate(-1., -1. ,0.);
  p3d::modelviewMatrix.rotate(90., 0., 1., 0.);
  p3d::modelviewMatrix.rotate(_steering, 0., 1., 0.);
  p3d::modelviewMatrix.rotate(_rotateWheel, 1., 0., 0.);
  p3d::modelviewMatrix.scale(0.5, 0.5, 0.5);
  drawAxle();
  p3d::modelviewMatrix.pop();

  p3d::modelviewMatrix.push();
  p3d::modelviewMatrix.translate(-1., 2. ,0.);
  p3d::modelviewMatrix.scale(1.5, 1.5, 1.5);
  drawBody();
  p3d::modelviewMatrix.pop();
}


void Car::drawWorld() {

  p3d::modelviewMatrix.push();
//Q9
  p3d::modelviewMatrix.translate(_position);
  p3d::modelviewMatrix.rotate(_orientation);
  draw(); // tracé de la voiture dans son repère local
  p3d::modelviewMatrix.pop();
}

void Car::move() {
  _acceleration+=-_velocity/50;
  _velocity+=_acceleration;
  _rotateWheel+=_velocity*20;
  _steering-=_steering/10*fabs(_velocity);

  _orientation.rotate(_steering*_velocity/(1.0+fabs(_velocity)),Vector3(0,1,0)); // le /(1.0+fabs(_velocity)) a été déterminé empiriquement
  //Q10
  _position += _orientation * Vector3(1,0,0) * _velocity;
}


void Car::accelerate() {
  _acceleration=0.05;

}

void Car::decelerate() {
  _acceleration=0;
}

void Car::brake() {
  _acceleration=-0.02;

}

void Car::turnLeft() {
  _steering+=0.5;
  if (_steering>35) _steering=35;
}

void Car::turnRight() {
  _steering-=0.5;
  if (_steering<-35) _steering=-35;
}





