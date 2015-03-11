/****************************************************************
* Author:
*    Nick Kotenberg
* Summary:
*    This is a 3D solar system modeler.
*
*    1.0f for size = 1km. For example, 100.0f = 100km.
****************************************************************/
// C++ includes
#include <ctime>
#include <cmath>
#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

// OpenGL includes
#include <GL/glu.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <SOIL/SOIL.h>

// Namespace
using namespace std;
#include "Image.cpp"

// Global Variables
const GLint WINDOW_WIDTH = 1024;
const GLint WINDOW_HEIGHT = 768;
const GLint WINDOW_Z_NEAR = 1;
const GLdouble WINDOW_Z_FAR = 1199254740992;
const GLint WINDOW_FOV = 70;
const GLdouble PI = 3.14159265359f;
const GLfloat EARTH_ORBITAL_PERIOD = 365.26f;
GLfloat WINDOW_X = 0.0f;
GLfloat WINDOW_Y = 0.0f;
GLfloat WINDOW_Z = -5000000.0f;
GLfloat SIMULATION_SPEED = 0.5f;
GLfloat QUALITY = 64.0f;

class Obj
{
public:
	Obj();
	~Obj() {}

	GLUquadricObj* getSphere() { return sphere; }
	GLuint getTexture() { return texture; }
	GLdouble getRadius() { return radius; }
	GLdouble getOrbitalDays(GLfloat speed);
	GLdouble getDistance() { return distance; }

	void setTexture(const char* filename);
	void setRadius(GLdouble r) { radius = r; }
	void setOrbitalDays(GLdouble o) { orbitalDays = o; }
	void setDistance(GLdouble d) { distance = d; }

private:
	GLUquadricObj *sphere;
	GLuint texture;
	GLdouble radius;
	GLdouble orbitalDays;
	GLdouble distance;
	GLdouble angle_of_rotation;
};

Obj::Obj()
{
	sphere = gluNewQuadric();
	texture = 0;
	radius = 0.0f;
	orbitalDays = 0.0f;
	distance = 0.0f;
	angle_of_rotation = 0.0f;
}

void Obj::setTexture(const char* filename)
{
    Image* img = Image::loadBMP(filename);
    texture = Image::loadTextureFromImage(img);
    delete img;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_FLAT);
}

GLdouble Obj::getOrbitalDays(GLfloat speed)
{
	angle_of_rotation += speed * orbitalDays;
	if (angle_of_rotation > 360.0f) angle_of_rotation = 0.0f;
	return angle_of_rotation;
}

Obj sun;
Obj mercury;
Obj venus;
Obj earth;
Obj mars;
Obj jupiter;
Obj saturn;
Obj uranus;
Obj neptune;
Obj pluto;

// Global Functions
void initialize();
void display();
void reshape(int width, int height);

/***************************************************************************
* main()
* Run an OpenGL project
****************************************************************************/
int main(int argc, char** argv)
{
	glutInit(&argc, argv);               // Initialize glut
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // Requesting Buffers
	glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Nick's 3D Solar System Modeler");
	initialize();
	glutDisplayFunc(display);              // Tell glut to use display function
	glutIdleFunc(display);                 // Use display as idle
	glutReshapeFunc(reshape);              // Tell glut to use reshape whenever the window changes
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF); // Allows for multiple key presses
    glutMainLoop();
    return 0;
}

/********************************************************************************
* FUNCTION: Initialize()
********************************************************************************/
void initialize()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE); // dont render backside
	//glEnable(GL_SCISSOR_TEST); // only render what has changed
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);

	//img = Image::loadBMP("sunmap.bmp");
	sun.setRadius(696000.0f);
	mercury.setRadius(2439.7f);
	venus.setRadius(6051.8f);
	earth.setRadius(6378.1f);
	mars.setRadius(3396.2f);
	jupiter.setRadius(71492.0f);
	saturn.setRadius(60268.0f);
	uranus.setRadius(25559.0f);
	neptune.setRadius(24764.0f);
	pluto.setRadius(1195.0f);

	sun.setOrbitalDays(EARTH_ORBITAL_PERIOD / 24.47f);
	mercury.setOrbitalDays(EARTH_ORBITAL_PERIOD / 87.97f);
    venus.setOrbitalDays(EARTH_ORBITAL_PERIOD / 224.7f);
    earth.setOrbitalDays(EARTH_ORBITAL_PERIOD / EARTH_ORBITAL_PERIOD);
    mars.setOrbitalDays(EARTH_ORBITAL_PERIOD / 686.98f);
    jupiter.setOrbitalDays(EARTH_ORBITAL_PERIOD / 4332.71);
    saturn.setOrbitalDays(EARTH_ORBITAL_PERIOD / 10759.5);
    uranus.setOrbitalDays(EARTH_ORBITAL_PERIOD / 30685.0f);
    neptune.setOrbitalDays(EARTH_ORBITAL_PERIOD / 60190.0f);
    pluto.setOrbitalDays(EARTH_ORBITAL_PERIOD / 90550.0f);

    mercury.setDistance(750000.0f);
    venus.setDistance(780000.0f);
    earth.setDistance(810000.0f);
    mars.setDistance(840000.0f);
    jupiter.setDistance(2000000.0f);
    saturn.setDistance(3000000.0f);
    uranus.setDistance(4000000.0f);
    neptune.setDistance(5000000.0f);
    pluto.setDistance(6000000.0f);

    sun.setTexture("sunmap.bmp");
    mercury.setTexture("mercurymap.bmp");
    venus.setTexture("venusmap.bmp");
    earth.setTexture("earthmap.bmp");
    mars.setTexture("marsmap.bmp");
    jupiter.setTexture("jupitermap.bmp");
    saturn.setTexture("saturnmap.bmp");
    uranus.setTexture("uranusmap.bmp");
    neptune.setTexture("neptunemap.bmp");
    pluto.setTexture("plutomap.bmp");

}

/********************************************************************************
* FUNCTION: Display()
********************************************************************************/
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float lightType = GL_AMBIENT;
	float intensity = 1.0f;
	GLfloat lightColor[] = {intensity,intensity,intensity,1.0f};
	GLfloat lightPos0[] = {1.0f,0.0f,0.0f,1.0f};
	glLightfv(GL_LIGHT0,lightType,lightColor);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos0);

	glTranslatef(WINDOW_X,WINDOW_Y,WINDOW_Z);

    glPushMatrix();
	glRotatef(sun.getOrbitalDays(-SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, sun.getTexture()); 
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(sun.getSphere(), sun.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	// Planets
	glPushMatrix();
	glRotatef(mercury.getOrbitalDays(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(mercury.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, mercury.getTexture());
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(mercury.getSphere(), mercury.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(venus.getOrbitalDays(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(venus.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, venus.getTexture());
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(venus.getSphere(), venus.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(earth.getOrbitalDays(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(earth.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, earth.getTexture());
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(earth.getSphere(), earth.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(mars.getOrbitalDays(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(mars.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, mars.getTexture());
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(mars.getSphere(), mars.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(jupiter.getOrbitalDays(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(jupiter.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, jupiter.getTexture());
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(jupiter.getSphere(), jupiter.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(saturn.getOrbitalDays(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(saturn.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, saturn.getTexture());
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(saturn.getSphere(), saturn.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(uranus.getOrbitalDays(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(uranus.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, uranus.getTexture());
	gluSphere(uranus.getSphere(), uranus.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(neptune.getOrbitalDays(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(neptune.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, neptune.getTexture());
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(neptune.getSphere(), neptune.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(pluto.getOrbitalDays(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(pluto.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, pluto.getTexture());
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(pluto.getSphere(), pluto.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glutSwapBuffers();
}

/********************************************************************************
* FUNCTION: Reshape()
********************************************************************************/
void reshape(int width, int height)
{
	if(height == 0) height = 1;
	glViewport(0,0,(GLsizei)width, (GLsizei)height); // sets the viewport to the size of the window
	glMatrixMode(GL_PROJECTION); // switch to the projection matrix so that we can manipulate how our scene is viewed
	glLoadIdentity(); // resets matricies to avoid unusual rendering/artefacts
	const GLdouble ASPECT = (GLfloat) width / (GLfloat) height;
	gluPerspective(WINDOW_FOV,ASPECT,WINDOW_Z_NEAR,WINDOW_Z_FAR);

	// Switch back to the Model View Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}





/*

int LoadGLTextures()                                    // Load Bitmaps And Convert To Textures
{
    /* load an image file directly as a new OpenGL texture *
    texture[0] = SOIL_load_OGL_texture
        (
        "Data/NeHe.bmp",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
        );
 
    if(texture[0] == 0)
        return false;
 
 
    // Typical Texture Generation Using Data From The Bitmap
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
 
    return true;                                        // Return Success
}

*/