class Obj
{
public:
	Obj();
	~Obj() {}

    void planetOrbit(GLdouble &speed);
    void planetOrbit2(GLdouble &speed);
    void moonOrbit(Obj planet, GLdouble &speed);
    void moonOrbit2(Obj planet, GLdouble &speed);
    void saturnRings();

	GLUquadricObj* getSphere() { return sphere; }
	GLuint getTexture() { return texture; }
	GLdouble getRadius() { return radius; }
	GLdouble getOrbitalDays() { return orbitalDays; }
	GLdouble getAngleOfRotation(GLfloat speed);
	GLdouble getDistance() { return distance; }
	GLfloat getXLocation() { return 0.0f; }
	GLfloat getYLocation() { return 0.0f; }
	GLfloat getZLocation() { return 0.0f; }
	GLfloat getYRotation() { return yRotation; }
	GLfloat getYRotationSpeed() { return yRotationSpeed; }
	GLfloat getX() { return x; }
	GLfloat getY() { return y; }
	GLfloat getZ() { return z; }

	void setTexture(const char* filename);
	void setRadius(GLdouble r) { radius = r; }
	void setOrbitalDays(GLdouble o) { orbitalDays = o; }
	void setDistance(GLdouble d) { distance = d; }
	void setAngleOfRotation(GLdouble a) { angle_of_rotation = a; }
	void setYRotation(GLfloat y) { yRotation = y; }
	void setYRotationSpeed(GLfloat y) { yRotationSpeed = y; }
	void setX(GLfloat v) { x = v; }
	void setY(GLfloat v) { y = v; }
	void setZ(GLfloat v) { z = v; }

private:
	GLUquadricObj *sphere;
	GLuint texture;
	GLdouble radius;
	GLdouble orbitalDays;
	GLdouble distance;
	GLdouble angle_of_rotation;
	GLfloat yRotation;
	GLfloat yRotationSpeed;
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

Obj::Obj()
{
	sphere = gluNewQuadric();
	texture = 0;
	radius = 0.0f;
	orbitalDays = 0.0f;
	distance = 0.0f;
	angle_of_rotation = 0.0f;
	yRotation = 0.0f;
	yRotationSpeed = 0.5f;
	x = 0;
	y = 0;
	z = 0;
}

void Obj::setTexture(const char* filename)
{
    Image* img = Image::loadBMP(filename);
    texture = Image::loadTextureFromImage(img);
    delete img;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluQuadricOrientation(sphere, GLU_OUTSIDE);
}

GLdouble Obj::getAngleOfRotation(GLfloat speed)
{
	angle_of_rotation += speed * (orbitalDays / 10);
	if (angle_of_rotation > 360.0f) angle_of_rotation -= 360.0f;
	return angle_of_rotation;
}

void Obj::planetOrbit(GLdouble &speed)
{
    glPushMatrix();
    setX(distance * sin(this->getAngleOfRotation(speed)*(PI/180)));
    setZ(distance * cos(this->getAngleOfRotation(speed)*(PI/180)));
    glTranslatef(x,y,z);
    glBindTexture(GL_TEXTURE_2D, texture);
    yRotation -=  yRotationSpeed;
    if (yRotation > 360.0f) yRotation -= 360.0f;
    glRotatef(yRotation * (speed * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

    gluSphere(sphere, radius, QUALITY, QUALITY);
    glPopMatrix();
}

void Obj::planetOrbit2(GLdouble &speed)
{
    glPushMatrix();
    setX(distance * sin(this->getAngleOfRotation(speed)*(PI/180)));
    setZ(distance * cos(this->getAngleOfRotation(speed)*(PI/180)));
    glTranslatef(x,y,z);
    glBindTexture(GL_TEXTURE_2D, texture);
    yRotation -=  yRotationSpeed;
    if (yRotation > 360.0f) yRotation -= 360.0f;
    glRotatef(yRotation * (speed * -20.0f), 0.0f, 0.0f, 1.0f);
    gluSphere(sphere, radius, QUALITY, QUALITY);
    glPopMatrix();
}

void Obj::moonOrbit(Obj planet, GLdouble &speed)
{
    glPushMatrix();
    setX(distance * sin(this->getAngleOfRotation(speed)*(PI/180)) + planet.getX());
    setZ(distance * cos(this->getAngleOfRotation(speed)*(PI/180)) + planet.getZ());
    glTranslatef(x,y,z);
    glBindTexture(GL_TEXTURE_2D, texture);
    yRotation -=  yRotationSpeed;
    if (yRotation > 360.0f) yRotation -= 360.0f;
    glRotatef(yRotation * (speed * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluSphere(sphere, radius, QUALITY, QUALITY);
    glPopMatrix();
}

void Obj::moonOrbit2(Obj planet, GLdouble &speed)
{
    glPushMatrix();
    setY(distance * sin(this->getAngleOfRotation(speed)*(PI/180)) + planet.getX());
    setZ(distance * cos(this->getAngleOfRotation(speed)*(PI/180)) + planet.getZ());
    glTranslatef(x,y,z);
    glBindTexture(GL_TEXTURE_2D, texture);
    yRotation -=  yRotationSpeed;
    if (yRotation > 360.0f) yRotation -= 360.0f;
    glRotatef(yRotation * (speed * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluSphere(sphere, radius, QUALITY, QUALITY);
    glPopMatrix();
}

void Obj::saturnRings()
{

    glDisable(GL_LIGHTING);
    GLUquadricObj *disc;
    disc = gluNewQuadric();
    glPushMatrix();
    glTranslatef(x,y,z);
    glRotatef(84.0f,1.0f,0.0f,0.0f);
    glColor4d(0.560784,0.560784,0.737255,0.40f);
    gluDisk(disc,66900.0f,74510.0f,QUALITY,8.0f);
    glPopMatrix();

    disc = gluNewQuadric();
    glPushMatrix();
    glTranslatef(x,y,z);
    glRotatef(84.0f,1.0f,0.0f,0.0f);
    glColor4d(0.510784,0.520784,0.797255,0.40f);
    gluDisk(disc,74658.0f,92000.0f,QUALITY,8.0f);
    glPopMatrix();
    
    disc = gluNewQuadric();
    glPushMatrix();
    glTranslatef(x,y,z);
    glRotatef(84.0f,1.0f,0.0f,0.0f);
    glColor4d(0.590784,0.580784,0.767255,0.40f);
    gluDisk(disc,92000.0f,117580.0f,QUALITY,8.0f);
    glPopMatrix();
    
    disc = gluNewQuadric();
    glPushMatrix();
    glTranslatef(x,y,z);
    glRotatef(84.0f,1.0f,0.0f,0.0f);
    glColor4d(0.790784,0.880784,0.967255,0.40f);
    gluDisk(disc,118580.0f,122170.0f,QUALITY,8.0f);
    glPopMatrix();

    disc = gluNewQuadric();
    glPushMatrix();
    glTranslatef(x,y,z);
    glRotatef(84.0f,1.0f,0.0f,0.0f);
    glColor4d(0.510784,0.520784,0.797255,0.40f);
    gluDisk(disc,122170.0f,136775.0f,QUALITY,8.0f);
    glPopMatrix();
    
    disc = gluNewQuadric();
    glPushMatrix();
    glTranslatef(x,y,z);
    glRotatef(84.0f,1.0f,0.0f,0.0f);
    glColor4d(0.790784,0.880784,0.967255,0.40f);
    gluDisk(disc,140180.0f,140500.0f,QUALITY,8.0f);
    glPopMatrix();
    
    disc = gluNewQuadric();
    glPushMatrix();
    glTranslatef(x,y,z);
    glRotatef(84.0f,1.0f,0.0f,0.0f);
    glColor4d(0.590784,0.580784,0.767255,0.40f);
    gluDisk(disc,149000.0f,154000.0f,QUALITY,8.0f);
    glPopMatrix();
    
    disc = gluNewQuadric();
    glPushMatrix();
    glTranslatef(x,y,z);
    glRotatef(84.0f,1.0f,0.0f,0.0f);
    glColor4d(0.290784,0.580784,0.967255,0.40f);
    gluDisk(disc,166000.0f,175000.0f,QUALITY,8.0f);
    glPopMatrix();
    
    disc = gluNewQuadric();
    glPushMatrix();
    glTranslatef(x,y,z);
    glRotatef(84.0f,1.0f,0.0f,0.0f);
    glColor4d(0.990784,0.980784,0.967255,0.40f);
    gluDisk(disc,194239.0f,197665.0f,QUALITY,8.0f);
    glPopMatrix();
    
    disc = gluNewQuadric();
    glPushMatrix();
    glTranslatef(x,y,z);
    glRotatef(84.0f,1.0f,0.0f,0.0f);
    glColor4d(0.590784,0.580784,0.767255,0.40f);
    gluDisk(disc,211000.0f,213500.0f,QUALITY,8.0f);
    glPopMatrix();

    glColor3d(1,1,1);
    glEnable(GL_LIGHTING);
}