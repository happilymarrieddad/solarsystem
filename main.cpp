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

GLfloat CAMERA_X_ROTATION_ANGLE = 0.0f;
GLfloat CAMERA_Y_ROTATION_ANGLE = 0.0f;
GLfloat CAMERA_Z_ROTATION_ANGLE = 0.0f;
GLfloat SIMULATION_SPEED = 0.000005f;
GLfloat QUALITY = 64.0f;
GLfloat SIZE = 1.0f;
GLfloat CURRENT_TIME = 100.0f;
bool* keyStates = new bool[256]();
bool* keySpecialStates = new bool[256]();
bool* mouseStates = new bool[256]();

#include "Obj.cpp"
#include "objects.h"
#include "Camera.cpp"
Camera camera;
#include "keyboard.h"

// Global Functions
void initialize();
void display();
void reshape(int width, int height);
GLfloat randRotation() { return (GLdouble) (((int) (rand() * 684)) % 360); }
void lookAt();
void initObjects();
void drawObjects();

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
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);

	initObjects();
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

	lookAt();

	drawObjects();


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

/*******************************************************************************
* FUNCTION: Lookat()
*******************************************************************************/
void lookAt()
{
	gluLookAt(
		camera.getPosX() * SIZE, camera.getPosY() * SIZE, camera.getPosZ() * SIZE,
		camera.getCenterX(),camera.getCenterY(),camera.getCenterZ(),
		camera.getUpX(),camera.getUpY(),camera.getUpZ()
	);
}














void initObjects()
{	
	sun.setRadius(696000.0f * SIZE);

	mercury.setRadius(2439.7f * SIZE);

	venus.setRadius(6051.8f * SIZE);

	earth.setRadius(6378.1f * SIZE);
	luna.setRadius(1738.0f * SIZE);

	mars.setRadius(3396.2f * SIZE);

	jupiter.setRadius(71492.0f * SIZE);
	io.setRadius(1821.0f * SIZE);
	europa.setRadius(1565.0f * SIZE);
	ganymede.setRadius(2634.0f * SIZE);
	callisto.setRadius(2403.0f * SIZE);

	saturn.setRadius(60268.0f * SIZE);
	mimas.setRadius(199.0f * SIZE);
	enceladus.setRadius(249.0f * SIZE);
	tethys.setRadius(530.0f * SIZE);
	dione.setRadius(560.0f * SIZE);
	rhea.setRadius(764.0f * SIZE);
	titan.setRadius(2575.0f * SIZE);
	hyperion.setRadius(143.0f * SIZE);
	iapetus.setRadius(718.0f * SIZE);
	phoebe.setRadius(110.0f * SIZE);

	uranus.setRadius(25559.0f * SIZE);
	miranda.setRadius(236.0f * SIZE);
	ariel.setRadius(581.0f * SIZE);
	umbriel.setRadius(585.0f * SIZE);
	titania.setRadius(789.0f * SIZE);
	oberon.setRadius(761.0f * SIZE);

	neptune.setRadius(24764.0f * SIZE);
	proteus.setRadius(209.0f * SIZE);
	triton.setRadius(1353.0f * SIZE);
	nereid.setRadius(170.0f * SIZE);

	pluto.setRadius(1195.0f * SIZE);
	charon.setRadius(603.0f * SIZE);




    mercury.setDistance(750000.0f * SIZE);
    
    venus.setDistance(780000.0f * SIZE);
    
    earth.setDistance(810000.0f * SIZE);
    luna.setDistance(15384.0f * SIZE);
    
    mars.setDistance(840000.0f * SIZE);
    
    jupiter.setDistance(2000000.0f * SIZE);
    io.setDistance(76000 * SIZE);
    europa.setDistance(80000 * SIZE);
    ganymede.setDistance(85000 * SIZE);
    callisto.setDistance(90000 * SIZE);
    
    saturn.setDistance(3000000.0f * SIZE);
	mimas.setDistance(63000.0f * SIZE);
	enceladus.setDistance(64000.0f * SIZE);
	tethys.setDistance(65000.0f * SIZE);
	dione.setDistance(66000.0f * SIZE);
	rhea.setDistance(67000.0f * SIZE);
	titan.setDistance(68000.0f * SIZE);
	hyperion.setDistance(69000.0f * SIZE);
	iapetus.setDistance(71000.0f * SIZE);
	phoebe.setDistance(72000.0f * SIZE);
    
    uranus.setDistance(4000000.0f * SIZE);
	miranda.setDistance(28000.0f * SIZE);
	ariel.setDistance(30000.0f * SIZE);
	umbriel.setDistance(32000.0f * SIZE);
	titania.setDistance(34000.0f * SIZE);
	oberon.setDistance(36000.0f * SIZE);
    
    neptune.setDistance(5000000.0f * SIZE);
	proteus.setDistance(28000.0f * SIZE);
	triton.setDistance(31000.0f * SIZE);
	nereid.setDistance(32000.0f * SIZE);
    
    pluto.setDistance(6000000.0f * SIZE);
	charon.setDistance(3000.0f * SIZE);





	sun.setOrbitalDays(EARTH_ORBITAL_PERIOD / 24.47f);
	
	mercury.setOrbitalDays(EARTH_ORBITAL_PERIOD / 87.97f);
    
    venus.setOrbitalDays(EARTH_ORBITAL_PERIOD / 224.7f);
    
    earth.setOrbitalDays(EARTH_ORBITAL_PERIOD / EARTH_ORBITAL_PERIOD);
    luna.setOrbitalDays(EARTH_ORBITAL_PERIOD / (27.32f / 30.0f));
    
    mars.setOrbitalDays(EARTH_ORBITAL_PERIOD / 686.98f);
    
    jupiter.setOrbitalDays(EARTH_ORBITAL_PERIOD / 4332.71);
    io.setOrbitalDays(EARTH_ORBITAL_PERIOD / (1.77f / 30.0f));
    europa.setOrbitalDays(EARTH_ORBITAL_PERIOD / (3.55f / 30.0f));
    ganymede.setOrbitalDays(EARTH_ORBITAL_PERIOD / (7.15f / 30.0f));
    callisto.setOrbitalDays(EARTH_ORBITAL_PERIOD / (16.69f / 30.0f));
    
    saturn.setOrbitalDays(EARTH_ORBITAL_PERIOD / 10759.5);
    mimas.setOrbitalDays(EARTH_ORBITAL_PERIOD / (0.94f / 30.0f));
    enceladus.setOrbitalDays(EARTH_ORBITAL_PERIOD / (1.37f / 30.0f));
    tethys.setOrbitalDays(EARTH_ORBITAL_PERIOD / (1.89f / 30.0f));
    dione.setOrbitalDays(EARTH_ORBITAL_PERIOD / (2.74f / 30.0f));
    rhea.setOrbitalDays(EARTH_ORBITAL_PERIOD / (4.52f / 30.0f));
    titan.setOrbitalDays(EARTH_ORBITAL_PERIOD / (15.95f / 30.0f));
    hyperion.setOrbitalDays(EARTH_ORBITAL_PERIOD / (21.28f / 30.0f));
    iapetus.setOrbitalDays(EARTH_ORBITAL_PERIOD / (79.33f / 30.0f));
    phoebe.setOrbitalDays(EARTH_ORBITAL_PERIOD / (-550.48f / 30.0f));
    
    uranus.setOrbitalDays(EARTH_ORBITAL_PERIOD / 30685.0f);
    miranda.setOrbitalDays(EARTH_ORBITAL_PERIOD / (1.41f / 30.0f));
    ariel.setOrbitalDays(EARTH_ORBITAL_PERIOD / (2.52f / 30.0f));
    umbriel.setOrbitalDays(EARTH_ORBITAL_PERIOD / (4.14f / 30.0f));
    titania.setOrbitalDays(EARTH_ORBITAL_PERIOD / (8.71f / 30.0f));
    oberon.setOrbitalDays(EARTH_ORBITAL_PERIOD / (13.46f / 30.0f));
    
    neptune.setOrbitalDays(EARTH_ORBITAL_PERIOD / 60190.0f);
    proteus.setOrbitalDays(EARTH_ORBITAL_PERIOD / (1.12f / 30.0f));
    triton.setOrbitalDays(EARTH_ORBITAL_PERIOD / (-5.88f / 30.0f));
    nereid.setOrbitalDays(EARTH_ORBITAL_PERIOD / (360.13f / 30.0f));
    
    pluto.setOrbitalDays(EARTH_ORBITAL_PERIOD / 90550.0f);
    charon.setOrbitalDays(EARTH_ORBITAL_PERIOD / (6.39f / 30.0f));



    sun.setTexture("images/sun.bmp");
    
    mercury.setTexture("images/mercurymap.bmp");
    
    venus.setTexture("images/venus.bmp");
    
    earth.setTexture("images/earth.bmp");
    luna.setTexture("images/luna.bmp");
    
    mars.setTexture("images/mars.bmp");
    
    jupiter.setTexture("images/jupiter.bmp");
    io.setTexture("images/io.bmp");
    europa.setTexture("images/europa.bmp");
    ganymede.setTexture("images/ganymede.bmp");
    callisto.setTexture("images/callisto.bmp");
    
    saturn.setTexture("images/saturn.bmp");
    mimas.setTexture("images/mimas.bmp");
    enceladus.setTexture("images/enceladus.bmp");
    tethys.setTexture("images/tethys.bmp");
    dione.setTexture("images/dione.bmp");
    rhea.setTexture("images/rhea.bmp");
    titan.setTexture("images/titan.bmp");
    hyperion.setTexture("images/hyperion.bmp");
    iapetus.setTexture("images/iapetus.bmp");
    phoebe.setTexture("images/phoebe.bmp");
    
    uranus.setTexture("images/uranus.bmp");
    miranda.setTexture("images/miranda.bmp");
    ariel.setTexture("images/ariel.bmp");
    umbriel.setTexture("images/moonmap.bmp");
    titania.setTexture("images/titania.bmp");
    oberon.setTexture("images/oberon.bmp");
    
    neptune.setTexture("images/neptune.bmp");
    proteus.setTexture("images/proteus.bmp");
    triton.setTexture("images/triton.bmp");
    nereid.setTexture("images/moonmap.bmp");
    
    pluto.setTexture("images/plutomap.bmp");
    charon.setTexture("images/charon.bmp");




    // Accurate as of 3/11/2015      http://www.theplanetstoday.com/
    
    mercury.setAngleOfRotation(353.0f);
    
    venus.setAngleOfRotation(150.0f);
    
    earth.setAngleOfRotation(255.0f);
    luna.setAngleOfRotation(randRotation());
    
    mars.setAngleOfRotation(110.0f);
    
    jupiter.setAngleOfRotation(225.0f);
    io.setAngleOfRotation(randRotation());
    europa.setAngleOfRotation(randRotation());
    ganymede.setAngleOfRotation(randRotation());
    callisto.setAngleOfRotation(randRotation());
    
    saturn.setAngleOfRotation(320.0f);
    mimas.setAngleOfRotation(randRotation());
    enceladus.setAngleOfRotation(randRotation());
    tethys.setAngleOfRotation(randRotation());
    dione.setAngleOfRotation(randRotation());
    rhea.setAngleOfRotation(randRotation());
    titan.setAngleOfRotation(randRotation());
    hyperion.setAngleOfRotation(randRotation());
    iapetus.setAngleOfRotation(randRotation());
    phoebe.setAngleOfRotation(randRotation());
    
    uranus.setAngleOfRotation(105.0f);
    miranda.setAngleOfRotation(randRotation());
    ariel.setAngleOfRotation(randRotation());
    umbriel.setAngleOfRotation(randRotation());
    titania.setAngleOfRotation(randRotation());
    oberon.setAngleOfRotation(randRotation());
    
    neptune.setAngleOfRotation(50.0f);
    proteus.setAngleOfRotation(randRotation());
    triton.setAngleOfRotation(randRotation());
    nereid.setAngleOfRotation(randRotation());
    
    pluto.setAngleOfRotation(265.0f);
    charon.setAngleOfRotation(randRotation());




    // This system is a little suspect because it's not clear that
    //    Earth's Y rotational speed is accurate.. I need to make
    //    sure it's correct and everything else will work.
    GLfloat compensation = 0.1f;  // This is probably not needed... remove later...
    const GLfloat MOON_ROTATION_SPEED_CONSTANT = 1.0f / 50.0f;
    earth.setYRotationSpeed(35.0f);
    luna.setYRotationSpeed(MOON_ROTATION_SPEED_CONSTANT + compensation);

    mercury.setYRotationSpeed((earth.getYRotationSpeed() / 58.7f) + compensation);
    
    venus.setYRotationSpeed((earth.getYRotationSpeed() / 243.0f) + compensation);
    
    mars.setYRotationSpeed((earth.getYRotationSpeed() / 1.026f) + compensation);
    
    jupiter.setYRotationSpeed(((24.0f/9.84f) * earth.getYRotationSpeed()) + compensation);
    io.setYRotationSpeed(MOON_ROTATION_SPEED_CONSTANT + compensation);
    europa.setYRotationSpeed(MOON_ROTATION_SPEED_CONSTANT + compensation);
    ganymede.setYRotationSpeed(MOON_ROTATION_SPEED_CONSTANT + compensation);
    callisto.setYRotationSpeed(MOON_ROTATION_SPEED_CONSTANT + compensation);
    
    saturn.setYRotationSpeed(((24.0f/10.2f) * earth.getYRotationSpeed()) + compensation);
    mimas.setYRotationSpeed(MOON_ROTATION_SPEED_CONSTANT + compensation);
    enceladus.setYRotationSpeed(MOON_ROTATION_SPEED_CONSTANT + compensation);
    tethys.setYRotationSpeed(MOON_ROTATION_SPEED_CONSTANT + compensation);
    dione.setYRotationSpeed(MOON_ROTATION_SPEED_CONSTANT + compensation);
    rhea.setYRotationSpeed(MOON_ROTATION_SPEED_CONSTANT + compensation);
    titan.setYRotationSpeed(MOON_ROTATION_SPEED_CONSTANT + compensation);
    hyperion.setYRotationSpeed(MOON_ROTATION_SPEED_CONSTANT + compensation);
    iapetus.setYRotationSpeed(MOON_ROTATION_SPEED_CONSTANT + compensation);
    phoebe.setYRotationSpeed(MOON_ROTATION_SPEED_CONSTANT + compensation);
    
    uranus.setYRotationSpeed(((24.0f/17.9f) * earth.getYRotationSpeed()) + compensation);
    miranda.setYRotationSpeed(MOON_ROTATION_SPEED_CONSTANT + compensation);
    ariel.setYRotationSpeed(MOON_ROTATION_SPEED_CONSTANT + compensation);
    umbriel.setYRotationSpeed(MOON_ROTATION_SPEED_CONSTANT + compensation);
    titania.setYRotationSpeed(MOON_ROTATION_SPEED_CONSTANT + compensation);
    oberon.setYRotationSpeed(MOON_ROTATION_SPEED_CONSTANT + compensation);
    
    neptune.setYRotationSpeed(((24.0f/19.1f) * earth.getYRotationSpeed()) + compensation);
    proteus.setYRotationSpeed(MOON_ROTATION_SPEED_CONSTANT + compensation);
    triton.setYRotationSpeed(MOON_ROTATION_SPEED_CONSTANT + compensation);
    nereid.setYRotationSpeed(MOON_ROTATION_SPEED_CONSTANT + compensation);
    
    pluto.setYRotationSpeed((earth.getYRotationSpeed() / 6.39f) + compensation);
    charon.setYRotationSpeed(MOON_ROTATION_SPEED_CONSTANT + compensation);
}

void drawObjects()
{

    glPushMatrix();
	glRotatef(sun.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
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
	glRotatef(jupiter.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(jupiter.getDistance(), 0.0f, 0.0f);
	glRotatef(io.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(io.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, io.getTexture());
	io.setYRotation(io.getYRotation() - io.getYRotationSpeed());
	if (io.getYRotation() > 360.0f) io.setYRotation(io.getYRotation() - 360.0f);
	glRotatef(io.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(io.getSphere(), io.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(jupiter.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(jupiter.getDistance(), 0.0f, 0.0f);
	glRotatef(europa.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(europa.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, europa.getTexture());
	europa.setYRotation(europa.getYRotation() - europa.getYRotationSpeed());
	if (europa.getYRotation() > 360.0f) europa.setYRotation(europa.getYRotation() - 360.0f);
	glRotatef(europa.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(europa.getSphere(), europa.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(jupiter.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(jupiter.getDistance(), 0.0f, 0.0f);
	glRotatef(ganymede.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(ganymede.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, ganymede.getTexture());
	ganymede.setYRotation(ganymede.getYRotation() - ganymede.getYRotationSpeed());
	if (ganymede.getYRotation() > 360.0f) ganymede.setYRotation(ganymede.getYRotation() - 360.0f);
	glRotatef(ganymede.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(ganymede.getSphere(), ganymede.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(jupiter.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(jupiter.getDistance(), 0.0f, 0.0f);
	glRotatef(callisto.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(callisto.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, callisto.getTexture());
	callisto.setYRotation(callisto.getYRotation() - callisto.getYRotationSpeed());
	if (callisto.getYRotation() > 360.0f) callisto.setYRotation(callisto.getYRotation() - 360.0f);
	glRotatef(callisto.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(callisto.getSphere(), callisto.getRadius(), QUALITY, QUALITY);
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
	glRotatef(saturn.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(saturn.getDistance(), 0.0f, 0.0f);
	glRotatef(mimas.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(mimas.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, mimas.getTexture());
	mimas.setYRotation(mimas.getYRotation() - mimas.getYRotationSpeed());
	if (mimas.getYRotation() > 360.0f) mimas.setYRotation(mimas.getYRotation() - 360.0f);
	glRotatef(mimas.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(mimas.getSphere(), mimas.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(saturn.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(saturn.getDistance(), 0.0f, 0.0f);
	glRotatef(enceladus.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(enceladus.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, enceladus.getTexture());
	enceladus.setYRotation(enceladus.getYRotation() - enceladus.getYRotationSpeed());
	if (enceladus.getYRotation() > 360.0f) enceladus.setYRotation(enceladus.getYRotation() - 360.0f);
	glRotatef(enceladus.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(enceladus.getSphere(), enceladus.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(saturn.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(saturn.getDistance(), 0.0f, 0.0f);
	glRotatef(tethys.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(tethys.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, tethys.getTexture());
	tethys.setYRotation(tethys.getYRotation() - tethys.getYRotationSpeed());
	if (tethys.getYRotation() > 360.0f) tethys.setYRotation(tethys.getYRotation() - 360.0f);
	glRotatef(tethys.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(tethys.getSphere(), tethys.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(saturn.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(saturn.getDistance(), 0.0f, 0.0f);
	glRotatef(dione.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(dione.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, dione.getTexture());
	dione.setYRotation(dione.getYRotation() - dione.getYRotationSpeed());
	if (dione.getYRotation() > 360.0f) dione.setYRotation(dione.getYRotation() - 360.0f);
	glRotatef(dione.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(dione.getSphere(), dione.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(saturn.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(saturn.getDistance(), 0.0f, 0.0f);
	glRotatef(rhea.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(rhea.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, rhea.getTexture());
	rhea.setYRotation(rhea.getYRotation() - rhea.getYRotationSpeed());
	if (rhea.getYRotation() > 360.0f) rhea.setYRotation(rhea.getYRotation() - 360.0f);
	glRotatef(rhea.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(rhea.getSphere(), rhea.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(saturn.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(saturn.getDistance(), 0.0f, 0.0f);
	glRotatef(titan.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(titan.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, titan.getTexture());
	titan.setYRotation(titan.getYRotation() - titan.getYRotationSpeed());
	if (titan.getYRotation() > 360.0f) titan.setYRotation(titan.getYRotation() - 360.0f);
	glRotatef(titan.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(titan.getSphere(), titan.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(saturn.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(saturn.getDistance(), 0.0f, 0.0f);
	glRotatef(hyperion.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(hyperion.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, hyperion.getTexture());
	hyperion.setYRotation(hyperion.getYRotation() - hyperion.getYRotationSpeed());
	if (hyperion.getYRotation() > 360.0f) hyperion.setYRotation(hyperion.getYRotation() - 360.0f);
	glRotatef(hyperion.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(hyperion.getSphere(), hyperion.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(saturn.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(saturn.getDistance(), 0.0f, 0.0f);
	glRotatef(iapetus.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(iapetus.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, iapetus.getTexture());
	iapetus.setYRotation(iapetus.getYRotation() - iapetus.getYRotationSpeed());
	if (iapetus.getYRotation() > 360.0f) iapetus.setYRotation(iapetus.getYRotation() - 360.0f);
	glRotatef(iapetus.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(iapetus.getSphere(), iapetus.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(saturn.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(saturn.getDistance(), 0.0f, 0.0f);
	glRotatef(phoebe.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(phoebe.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, phoebe.getTexture());
	phoebe.setYRotation(phoebe.getYRotation() - phoebe.getYRotationSpeed());
	if (phoebe.getYRotation() > 360.0f) phoebe.setYRotation(phoebe.getYRotation() - 360.0f);
	glRotatef(phoebe.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(phoebe.getSphere(), phoebe.getRadius(), QUALITY, QUALITY);
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
	glRotatef(uranus.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(uranus.getDistance(), 0.0f, 0.0f);
	glRotatef(miranda.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(miranda.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, miranda.getTexture());
	miranda.setYRotation(miranda.getYRotation() - miranda.getYRotationSpeed());
	if (miranda.getYRotation() > 360.0f) miranda.setYRotation(miranda.getYRotation() - 360.0f);
	glRotatef(miranda.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(miranda.getSphere(), miranda.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(uranus.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(uranus.getDistance(), 0.0f, 0.0f);
	glRotatef(ariel.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(ariel.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, ariel.getTexture());
	ariel.setYRotation(ariel.getYRotation() - ariel.getYRotationSpeed());
	if (ariel.getYRotation() > 360.0f) ariel.setYRotation(ariel.getYRotation() - 360.0f);
	glRotatef(ariel.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(ariel.getSphere(), ariel.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(uranus.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(uranus.getDistance(), 0.0f, 0.0f);
	glRotatef(umbriel.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(umbriel.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, umbriel.getTexture());
	umbriel.setYRotation(umbriel.getYRotation() - umbriel.getYRotationSpeed());
	if (umbriel.getYRotation() > 360.0f) umbriel.setYRotation(umbriel.getYRotation() - 360.0f);
	glRotatef(umbriel.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(umbriel.getSphere(), umbriel.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(uranus.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(uranus.getDistance(), 0.0f, 0.0f);
	glRotatef(titania.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(titania.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, titania.getTexture());
	titania.setYRotation(titania.getYRotation() - titania.getYRotationSpeed());
	if (titania.getYRotation() > 360.0f) titania.setYRotation(titania.getYRotation() - 360.0f);
	glRotatef(titania.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(titania.getSphere(), titania.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(uranus.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(uranus.getDistance(), 0.0f, 0.0f);
	glRotatef(oberon.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(oberon.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, oberon.getTexture());
	oberon.setYRotation(oberon.getYRotation() - oberon.getYRotationSpeed());
	if (oberon.getYRotation() > 360.0f) oberon.setYRotation(oberon.getYRotation() - 360.0f);
	glRotatef(oberon.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(oberon.getSphere(), oberon.getRadius(), QUALITY, QUALITY);
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
	glRotatef(neptune.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(neptune.getDistance(), 0.0f, 0.0f);
	glRotatef(proteus.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(proteus.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, proteus.getTexture());
	proteus.setYRotation(proteus.getYRotation() - proteus.getYRotationSpeed());
	if (proteus.getYRotation() > 360.0f) proteus.setYRotation(proteus.getYRotation() - 360.0f);
	glRotatef(proteus.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(proteus.getSphere(), proteus.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(neptune.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(neptune.getDistance(), 0.0f, 0.0f);
	glRotatef(triton.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(triton.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, triton.getTexture());
	triton.setYRotation(triton.getYRotation() - triton.getYRotationSpeed());
	if (triton.getYRotation() > 360.0f) triton.setYRotation(triton.getYRotation() - 360.0f);
	glRotatef(triton.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(triton.getSphere(), triton.getRadius(), QUALITY, QUALITY);
	glPopMatrix();

	glPushMatrix();
	glRotatef(neptune.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(neptune.getDistance(), 0.0f, 0.0f);
	glRotatef(nereid.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(nereid.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, nereid.getTexture());
	nereid.setYRotation(nereid.getYRotation() - nereid.getYRotationSpeed());
	if (nereid.getYRotation() > 360.0f) nereid.setYRotation(nereid.getYRotation() - 360.0f);
	glRotatef(nereid.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(nereid.getSphere(), nereid.getRadius(), QUALITY, QUALITY);
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

	glPushMatrix();
	glRotatef(pluto.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(pluto.getDistance(), 0.0f, 0.0f);
	glRotatef(charon.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glTranslatef(charon.getDistance(), 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, charon.getTexture());
	charon.setYRotation(charon.getYRotation() - charon.getYRotationSpeed());
	if (charon.getYRotation() > 360.0f) charon.setYRotation(charon.getYRotation() - 360.0f);
	glRotatef(charon.getYRotation() * (SIMULATION_SPEED * -20.0f), 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(charon.getSphere(), charon.getRadius(), QUALITY, QUALITY);
	glPopMatrix();
}

