#include "GLApplication.h"
#include "GLTool.h"

#include "Car.h"

#include <iostream>


/*!
*
* @file
*
* @brief
* @author F. Aubert - Univ Lille 1
*
*/

using namespace std;
using namespace p3d;

GLApplication::~GLApplication() {
}

GLApplication::GLApplication() {

  _leftPanelMenu << "Car Setup" << "Follow Plane" << "Follow Car";

  _airplane.read("cessna.obj");
  _airplane.position(0,10,-10);

  _camera.frustum(-0.01,0.01,-0.01,0.01,0.01,1000);
  _camera.position(Vector3(0,1,10));
  _cameraMode = Camera_Car_Setup;

  _cameraStart=_camera;
  _cameraStop=_camera;

}




/** ********************************************************************** **/
void GLApplication::initialize() {
  // appelée 1 seule fois à l'initialisation du contexte
  // => initialisations OpenGL

  glClearColor(1,1,1,1);

//  glLineWidth(4);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glClearDepth(1);

  initGLTool();

  p3d::diffuseBackColor=Vector3(0,1,0);

  _ground.readMipmap("mosaic_pierre.jpg");


  _airplane.initDraw();

}

void GLApplication::resize(int width,int height) {
  // appelée à chaque dimensionnement du widget OpenGL
  // (inclus l'ouverture de la fenêtre)
  // => réglages liés à la taille de la fenêtre
  glViewport(0,0,width,height);
  _camera.viewport(0,0,width,height);
}

void GLApplication::update() {
  // appelée toutes les 20ms (60Hz)
  // => mettre à jour les données de l'application
  // avant l'affichage de la prochaine image (animation)
  // ...


  if (keyPressed(Qt::Key_F)) _cameraMode=Camera_Car_Setup;
  if (keyPressed(Qt::Key_G)) _cameraMode=Camera_Follow_Plane;
  if (keyPressed(Qt::Key_H)) _cameraMode=Camera_Follow_Car;

  _car.decelerate();
  if (_cameraMode==Camera_Follow_Car || _cameraMode==Camera_Car_Setup) {
    if (left()) {_car.turnLeft();}
    if (right()) {_car.turnRight();}
    if (forward()) {_car.accelerate();}
    if (backward()) {_car.brake();}

  }
  else {
    if (left()) _airplane.rollLeft();
    if (right()) _airplane.rollRight();
    if (forward()) _airplane.pitchDown();
    if (backward()) _airplane.pitchUp();
    if (rotateLeft()) _airplane.yawLeft();
    if (rotateRight()) _airplane.yawRight();
    if (accelerateWheel()) _airplane.accelerate();
    if (decelerateWheel()) _airplane.decelerate();
  }



  _car.move();
  _airplane.move();
  updateCamera();

}

void GLApplication::draw() {
  // appelée après chaque update
  // => tracer toute l'image
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  p3d::apply(_camera);

  _car.drawWorld();

  p3d::diffuseColor=Vector3(1,0,0);
  _airplane.drawWorld();
  drawGround();

  glUseProgram(0);


  snapshot(); // capture opengl window if requested
}

/** ********************************************************************** **/
/** i = button number, s = button text
 */
void GLApplication::leftPanel(int i,const std::string &s) {
  cout << "GLApplication : button clicked " << i << " " << s << endl;

  switch (i) {
  case 0:_cameraMode=Camera_Car_Setup;
      break;
  case 1:_cameraMode=Camera_Follow_Plane;
      break;
  case 2:_cameraMode=Camera_Follow_Car;
      break;
  }
  _cameraStart=_camera;
  _lambda=0;
}

/** *********************************************************** **/

void GLApplication::drawGround() {
  p3d::modelviewMatrix.push();
  p3d::textureMatrix.push();
  p3d::textureMatrix.scale(135,135,135);
  p3d::modelviewMatrix.translate(0,-3,0);
  p3d::modelviewMatrix.scale(10,10,10);
  p3d::ambientColor=Vector4(0.2,0.2,0.2,1);
  p3d::shaderTextureLight();
  p3d::drawGround(_ground);
  p3d::textureMatrix.pop();
  p3d::modelviewMatrix.pop();
}

void GLApplication::updateCamera() {
  _lambda+=0.02;
  if (_lambda>1) _lambda=1;


  switch (_cameraMode) {
    case Camera_Car_Setup:
      if (mouseLeft()) {
        _cameraStop.lookAt(_car.position());
        Vector3 t=_cameraStop.pointTo(Coordinate_Local,_car.position());
        Vector3 vertical=_cameraStop.directionTo(Coordinate_Local,Vector3(0,1,0));
        _cameraStop.translate(t,Coordinate_Local);
        _cameraStop.rotate(-deltaMouseX(),vertical,Coordinate_Local);
        _cameraStop.rotate(deltaMouseY(),Vector3(1,0,0),Coordinate_Local);
        _cameraStop.translate(-t,Coordinate_Local);
      }
      break;
    case Camera_Follow_Car: {
      //Q16
      _cameraStop.position(_car.position()+ _car.orientation() * Vector3(-9,4,0));
      _cameraStop.orientation(_car.orientation());
      _cameraStop.rotate(-90,Vector3(0,1,0));

      }
      break;
    case Camera_Follow_Plane: {

      /*
        _camera.position(_airplane.position()+Vector3(0,1,-3));
        _camera.orientation(180,Vector3(0,1,0));
      */

      //Q15
      _cameraStop.position(_airplane.position()+ _airplane.orientation() * Vector3(0,1,-3));
      _cameraStop.orientation(_airplane.orientation());
      _cameraStop.rotate(180,Vector3(0,1,0));

      }
      break;
    default:break;

  }

  //Q17
  _camera.position(_cameraStart.position() * ( 1 - _lambda) + _cameraStop.position() * _lambda);
  _camera.orientation(_cameraStart.orientation() * (1 - _lambda) + _cameraStop.orientation() * _lambda);
}


