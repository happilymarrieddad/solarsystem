#include "Camera.h"

const double Camera::TO_RADS = 3.141592654 / 180.0;
 
Camera::Camera(float theWindowWidth, float theWindowHeight)
{
	initCamera();
	windowWidth  = theWindowWidth;
	windowHeight = theWindowHeight;
	windowMidX = windowWidth  / 2.0f;
	windowMidY = windowHeight / 2.0f;
	glfwSetMousePos(windowMidX, windowMidY);
}
 
Camera::~Camera()
{
}
 
void Camera::initCamera()
{
	position.zero();
	position.setZ(-3000000.0f);
	rotation.zero();
	speed.zero();
	movementSpeedFactor = 100.0;
	pitchSensitivity = 0.002;
	yawSensitivity   = 0.002;
	forward     = false;
	backward    = false;
	left  = false;
	right = false;
}
 
const double Camera::toRads(const double &theAngleInDegrees) const
{
	return theAngleInDegrees * TO_RADS;
}
 
void Camera::handleMouseMove(int mouseX, int mouseY)
{
	double horizMovement = (mouseX - windowMidX+1) * yawSensitivity;
	double vertMovement  = (mouseY - windowMidY) * pitchSensitivity;
	rotation.addX(vertMovement);
	rotation.addY(horizMovement);
 
	if (rotation.getX() < -85)
	{
		rotation.setX(-85);
	}
 
	if (rotation.getX() > 85)
	{
		rotation.setX(85);
	}
	if (rotation.getY() < 0)
	{
		rotation.addY(360);
	}
	if (rotation.getY() > 360)
	{
		rotation.addY(-360);
	}
	glfwSetMousePos(windowMidX, windowMidY);
}
 
void Camera::move(double deltaTime)
{
	Vec3<double> movement;
	double sinXRot = sin( toRads( rotation.getX() ) );
	double cosXRot = cos( toRads( rotation.getX() ) );
	double sinYRot = sin( toRads( rotation.getY() ) );
	double cosYRot = cos( toRads( rotation.getY() ) );
	double pitchLimitFactor = cosXRot;
 
	if (forward)
	{
		movement.addX(sinYRot * pitchLimitFactor);
		movement.addY(-sinXRot);
		movement.addZ(-cosYRot * pitchLimitFactor);
	}
 
	if (backward)
	{
		movement.addX(-sinYRot * pitchLimitFactor);
		movement.addY(sinXRot);
		movement.addZ(cosYRot * pitchLimitFactor);
	}
 
	if (left)
	{
		movement.addX(-cosYRot);
		movement.addZ(-sinYRot);
	}
 
	if (right)
	{
		movement.addX(cosYRot);
		movement.addZ(sinYRot);
	}
 
	movement.normalize();
	double framerateIndependentFactor = movementSpeedFactor * deltaTime;
	movement *= framerateIndependentFactor;
	position += movement;
}