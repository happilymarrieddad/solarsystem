class Camera
{
public:
	Camera();
	~Camera();

	void lookAt(GLfloat x, GLfloat y, GLfloat z);
	void reset();

	GLfloat getPosX() { return pos_x; }
	GLfloat getPosY() { return pos_y; }
	GLfloat getPosZ() { return pos_z; }
	GLfloat getCenterX() { return center_x; }
	GLfloat getCenterY() { return center_y; }
	GLfloat getCenterZ() { return center_z; }
	GLfloat getUpX() { return up_x; }
	GLfloat getUpY() { return up_y; }
	GLfloat getUpZ() { return up_z; }

	void setPosX(GLfloat x) { pos_x = x; }
	void setPosY(GLfloat y) { pos_y = y; }
	void setPosZ(GLfloat z) { pos_z = z; }
	void setCenterX(GLfloat x) { center_x = x; }
	void setCenterY(GLfloat y) { center_y = y; }
	void setCenterZ(GLfloat z) { center_z = z; }
	void setUpX(GLfloat x) { up_x = x; }
	void setUpY(GLfloat y) { up_y = y; }
	void setUpZ(GLfloat z) { up_z = z; }

private:
	GLfloat pos_x;
	GLfloat pos_y;
	GLfloat pos_z;
	GLfloat center_x;
	GLfloat center_y;
	GLfloat center_z;
	GLfloat up_x;
	GLfloat up_y;
	GLfloat up_z;
};

Camera::Camera()
{
	pos_x = 0.0f;
	pos_y = 0.0f;
	pos_z = -5000000.0f;
	center_x = 0.0f;
	center_y = 0.0f;
	center_z = 0.0f;
	up_x = 0.0f;
	up_y = 1.0f;
	up_z = 0.0f;
}

Camera::~Camera()
{

}

void Camera::lookAt(GLfloat x, GLfloat y, GLfloat z)
{
	this->setPosX(x);
	this->setPosY(y);
	this->setPosZ(z);
}

void Camera::reset()
{
	pos_x = 0.0f;
	pos_y = 0.0f;
	pos_z = -5000000.0f;
	center_x = 0.0f;
	center_y = 0.0f;
	center_z = 0.0f;
	up_x = 0.0f;
	up_y = 1.0f;
	up_z = 0.0f;
}











