#include "Camera.h"

const double Camera::TO_RADIANS = 3.141592654 / 180.0;
 
Camera::Camera(float width, float height)
{
	initCamera();
	_width  = width;
	_height = height;
	glfwSetMousePos(_width/2.0f, _height/2.0f);
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
	_speed = 100.0;
	_pitch = 0.002;
	_yaw = 0.002;
	forward = false;
	backward = false;
	left  = false;
	right = false;
}
 
const double Camera::toRadians(const double &theAngleInDegrees) const
{
	return theAngleInDegrees * TO_RADIANS;
}
 
void Camera::handleMouseMove(int x, int y)
{
	double h = (x - (_width/2)+1) * _yaw;
	double v  = (y - (_height/2)) * _pitch;
	rotation.addX(v);
	rotation.addY(h);
 
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
	glfwSetMousePos(_width/2, _height/2);
}
 
void Camera::move(double deltaTime)
{
	Vec3<double> movement;
	double sinXRot = sin( toRadians( rotation.getX() ) );
	double cosXRot = cos( toRadians( rotation.getX() ) );
	double sinYRot = sin( toRadians( rotation.getY() ) );
	double cosYRot = cos( toRadians( rotation.getY() ) );
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
	double total = _speed * deltaTime;
	movement *= total;
	position += movement;
}