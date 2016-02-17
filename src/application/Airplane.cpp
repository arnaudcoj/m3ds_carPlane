#include "Airplane.h"
#include "GLTool.h"
#include "Tools.h"

using namespace p3d;
using namespace std;

Airplane::Airplane() {
  _increment=1.0;
  _accelerate=0.1;
  _velocity=0.0;
  _orientation.setIdentity();
  _position.set(0,0,0);
  _angleX=_angleY=_angleZ=0.0;
}

Airplane::~Airplane() {

}

void Airplane::initDraw() {
  _obj.initDraw();

}


void Airplane::draw() {

  p3d::diffuseColor=Vector3(1,0,0);
  p3d::shaderLightPhong();
  _obj.draw();
}

void Airplane::drawWorld() {
  p3d::modelviewMatrix.push();
  p3d::modelviewMatrix.translate(_position);

  /*
  p3d::modelviewMatrix.rotate(_angleY,0,1,0); // yaw
  p3d::modelviewMatrix.rotate(_angleX,1,0,0); // pitch
  p3d::modelviewMatrix.rotate(_angleZ,0,0,1); // roll
  */
  //Q13
  p3d::modelviewMatrix.rotate(_orientation);

  p3d::modelviewMatrix.scale(2,2,2); // grossir un peu l'avion
  draw();

  p3d::modelviewMatrix.pop();
}

void Airplane::move() {
  _position += _orientation * Vector3(0,0,1) * _velocity;
}

void Airplane::pitchDown() {
  _orientation.rotate(_increment,Vector3(1,0,0));
}

void Airplane::pitchUp() {
  _orientation.rotate(_increment,Vector3(-1,0,0));
}

void Airplane::rollRight() {
  _orientation.rotate(_increment,Vector3(0,0,1));
}

void Airplane::rollLeft() {
  _orientation.rotate(_increment,Vector3(0,0,-1));
}

void Airplane::yawLeft() {
  _orientation.rotate(_increment,Vector3(0,1,0));
}

void Airplane::yawRight() {
  _orientation.rotate(_increment,Vector3(0,-1,0));
}

void Airplane::accelerate() {
  _velocity+=_accelerate;
  if (_velocity>3) _velocity=3;
}

void Airplane::decelerate() {
  _velocity-=_accelerate;
  if (_velocity<0) _velocity=0;
}

// lecture fichier .obj
void Airplane::read(const string &filename) {
  _obj.readInit(filename);
  _obj.rotateY(90);
}



