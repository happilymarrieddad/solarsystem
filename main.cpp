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
GLfloat SIMULATION_SPEED = 0.0005f;
GLfloat QUALITY = 64.0f;
GLfloat CURRENT_TIME = 100.0f;
bool* keyStates = new bool[256]();
bool* keySpecialStates = new bool[256]();
bool* mouseStates = new bool[256]();

#include "Obj.cpp"
#include "Camera.cpp"
Camera camera;
#include "keyboard.h"
#include "objects.h"

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
	glEnable(GL_SCISSOR_TEST); // only render what has changed
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);
	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);

	//img = Image::loadBMP("sunmap.bmp");
	sun.setRadius(696000.0f);

	mercury.setRadius(2439.7f);

	venus.setRadius(6051.8f);

	earth.setRadius(6378.1f);
	luna.setRadius(1738.0f);

	mars.setRadius(3396.2f);

	jupiter.setRadius(71492.0f);
	io.setRadius(1821.0f);
	europa.setRadius(1565.0f);
	ganymede.setRadius(2634.0f);
	callisto.setRadius(2403.0f);

	saturn.setRadius(60268.0f);
	mimas.setRadius(199.0f);
	enceladus.setRadius(249.0f);
	tethys.setRadius(530.0f);
	dione.setRadius(560.0f);
	rhea.setRadius(764.0f);
	titan.setRadius(2575.0f);
	hyperion.setRadius(143.0f);
	iapetus.setRadius(718.0f);
	phoebe.setRadius(110.0f);

	uranus.setRadius(25559.0f);
	miranda.setRadius(236.0f);
	ariel.setRadius(581.0f);
	umbriel.setRadius(585.0f);
	titania.setRadius(789.0f);
	oberon.setRadius(761.0f);

	neptune.setRadius(24764.0f);
	proteus.setRadius(209.0f);
	triton.setRadius(1353.0f);
	nereid.setRadius(170.0f);

	pluto.setRadius(1195.0f);
	charon.setRadius(603.0f);



	sun.setOrbitalDays(EARTH_ORBITAL_PERIOD / 24.47f);
	
	mercury.setOrbitalDays(EARTH_ORBITAL_PERIOD / 87.97f);
    
    venus.setOrbitalDays(EARTH_ORBITAL_PERIOD / 224.7f);
    
    earth.setOrbitalDays(EARTH_ORBITAL_PERIOD / EARTH_ORBITAL_PERIOD);
    luna.setOrbitalDays(EARTH_ORBITAL_PERIOD / 27.32f);
    
    mars.setOrbitalDays(EARTH_ORBITAL_PERIOD / 686.98f);
    
    jupiter.setOrbitalDays(EARTH_ORBITAL_PERIOD / 4332.71);
    
    saturn.setOrbitalDays(EARTH_ORBITAL_PERIOD / 10759.5);
    
    uranus.setOrbitalDays(EARTH_ORBITAL_PERIOD / 30685.0f);
    
    neptune.setOrbitalDays(EARTH_ORBITAL_PERIOD / 60190.0f);
    
    pluto.setOrbitalDays(EARTH_ORBITAL_PERIOD / 90550.0f);



    mercury.setDistance(750000.0f);
    
    venus.setDistance(780000.0f);
    
    earth.setDistance(810000.0f);
    luna.setDistance(12000.0f);
    
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
    luna.setTexture("moonmap.bmp");
    
    mars.setTexture("marsmap.bmp");
    
    jupiter.setTexture("jupitermap.bmp");
    
    saturn.setTexture("saturnmap.bmp");
    
    uranus.setTexture("uranusmap.bmp");
    
    neptune.setTexture("neptunemap.bmp");
    
    pluto.setTexture("plutomap.bmp");




    // Accurate as of 3/11/2015      http://www.theplanetstoday.com/
    
    mercury.setAngleOfRotation(353.0f);
    
    venus.setAngleOfRotation(150.0f);
    
    earth.setAngleOfRotation(255.0f);
    luna.setAngleOfRotation(295.0f);
    
    mars.setAngleOfRotation(110.0f);
    
    jupiter.setAngleOfRotation(225.0f);
    
    saturn.setAngleOfRotation(320.0f);
    
    uranus.setAngleOfRotation(105.0f);
    
    neptune.setAngleOfRotation(50.0f);
    
    pluto.setAngleOfRotation(265.0f);




    // This system is a little suspect because it's not clear that
    //    Earth's Y rotational speed is accurate.. I need to make
    //    sure it's correct and everything else will work.
    GLfloat compensation = 0.1f;  // This is probably not needed... remove later...
    earth.setYRotationSpeed(35.0f);
    luna.setYRotationSpeed((1 / 50.0f) + compensation);

    mercury.setYRotationSpeed((earth.getYRotationSpeed() / 58.7f) + compensation);
    
    venus.setYRotationSpeed((earth.getYRotationSpeed() / 243.0f) + compensation);
    
    mars.setYRotationSpeed((earth.getYRotationSpeed() / 1.026f) + compensation);
    
    jupiter.setYRotationSpeed(((24.0f/9.84f) * earth.getYRotationSpeed()) + compensation);
    
    saturn.setYRotationSpeed(((24.0f/10.2f) * earth.getYRotationSpeed()) + compensation);
    
    uranus.setYRotationSpeed(((24.0f/17.9f) * earth.getYRotationSpeed()) + compensation);
    
    neptune.setYRotationSpeed(((24.0f/19.1f) * earth.getYRotationSpeed()) + compensation);
    
    pluto.setYRotationSpeed((earth.getYRotationSpeed() / 6.39f) + compensation);
}

/********************************************************************************
* FUNCTION: Display()
********************************************************************************/
void display()
{
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutMouseFunc(mouse);
	keyOperations();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	CURRENT_TIME -= SIMULATION_SPEED * 200;

	float intensity = 1.0f;
	GLfloat lightColor[] = {intensity,intensity,intensity,1.0f};
	GLfloat lightPos0[] = {0.0f,0.0f,0.0f,1.0f};
	glLightfv(GL_LIGHT0,GL_AMBIENT,lightColor);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos0);

	glTranslatef(WINDOW_X,WINDOW_Y,WINDOW_Z); // Move back on the scene

    glPushMatrix();
	glRotatef(sun.getAngleOfRotation(-SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, sun.getTexture()); 
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(sun.getSphere(), sun.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	// Planets
	glPushMatrix();
	glRotatef(mercury.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(mercury.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, mercury.getTexture());
	mercury.setYRotation(mercury.getYRotation() - mercury.getYRotationSpeed());
	if (mercury.getYRotation() > 360.0f) mercury.setYRotation(mercury.getYRotation() - 360.0f);
	glRotatef(mercury.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(mercury.getSphere(), mercury.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(venus.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(venus.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, venus.getTexture());
	venus.setYRotation(venus.getYRotation() - venus.getYRotationSpeed());
	if (venus.getYRotation() > 360.0f) venus.setYRotation(venus.getYRotation() - 360.0f);
	glRotatef(venus.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(venus.getSphere(), venus.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(earth.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(earth.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, earth.getTexture());
	earth.setYRotation(earth.getYRotation() - earth.getYRotationSpeed());
	if (earth.getYRotation() > 360.0f) earth.setYRotation(earth.getYRotation() - 360.0f);
	glRotatef(earth.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(earth.getSphere(), earth.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(earth.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(earth.getDistance(), 0.0f, 0.0f);
	glRotatef(luna.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(luna.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, luna.getTexture());
	luna.setYRotation(luna.getYRotation() - luna.getYRotationSpeed());
	if (luna.getYRotation() > 360.0f) luna.setYRotation(luna.getYRotation() - 360.0f);
	glRotatef(luna.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(luna.getSphere(), luna.getRadius(), QUALITY, QUALITY);
	glPopMatrix();





	glPushMatrix();
	glRotatef(mars.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(mars.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, mars.getTexture());
	mars.setYRotation(mars.getYRotation() - mars.getYRotationSpeed());
	if (mars.getYRotation() > 360.0f) mars.setYRotation(mars.getYRotation() - 360.0f);
	glRotatef(mars.getYRotation() * (SIMULATION_SPEED * 20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(mars.getSphere(), mars.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(jupiter.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(jupiter.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, jupiter.getTexture());
	jupiter.setYRotation(jupiter.getYRotation() - jupiter.getYRotationSpeed());
	if (jupiter.getYRotation() > 360.0f) jupiter.setYRotation(jupiter.getYRotation() - 360.0f);
	glRotatef(jupiter.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(jupiter.getSphere(), jupiter.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(saturn.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(saturn.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, saturn.getTexture());
	saturn.setYRotation(saturn.getYRotation() - saturn.getYRotationSpeed());
	if (saturn.getYRotation() > 360.0f) saturn.setYRotation(saturn.getYRotation() - 360.0f);
	glRotatef(saturn.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(saturn.getSphere(), saturn.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(uranus.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(uranus.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, uranus.getTexture());
	uranus.setYRotation(uranus.getYRotation() - uranus.getYRotationSpeed());
	if (uranus.getYRotation() > 360.0f) uranus.setYRotation(uranus.getYRotation() - 360.0f);
	glRotatef(uranus.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 0.0f, 1.0f);
	gluSphere(uranus.getSphere(), uranus.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(neptune.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(neptune.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, neptune.getTexture());
	neptune.setYRotation(neptune.getYRotation() - neptune.getYRotationSpeed());
	if (neptune.getYRotation() > 360.0f) neptune.setYRotation(neptune.getYRotation() - 360.0f);
	glRotatef(neptune.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(neptune.getSphere(), neptune.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(pluto.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(pluto.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, pluto.getTexture());
	pluto.setYRotation(pluto.getYRotation() - pluto.getYRotationSpeed());
	if (pluto.getYRotation() > 360.0f) pluto.setYRotation(pluto.getYRotation() - 360.0f);
	glRotatef(pluto.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
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
	glTranslatef(
		(cos(CURRENT_TIME * (jupiter.getOrbitalDays() / 10000.0f))) * jupiter.getDistance(),
		jupiter.getYLocation(),
		(sin(CURRENT_TIME * (jupiter.getOrbitalDays() / 10000.0f))) * jupiter.getDistance()
	);
	*/