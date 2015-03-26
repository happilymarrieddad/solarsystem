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
#include <cstdlib>

// OpenGL includes
#include <GL/glu.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <GL/glfw.h>

// Namespace
using namespace std;
#include "Image.cpp"

// Global Variables
const GLint WINDOW_WIDTH = 1620;
const GLint WINDOW_HEIGHT = 1080;
const GLint WINDOW_Z_NEAR = 1;
const GLdouble WINDOW_Z_FAR = 1199254740992;
const GLint WINDOW_FOV = 70;
const GLdouble PI = 3.14159265359f;
const GLfloat EARTH_ORBITAL_PERIOD = 365.26f;

GLdouble SIMULATION_SPEED = 0.0005f;
GLfloat QUALITY = 64.0f;
GLfloat SIZE = 1.0f;
GLdouble DELTA_TIME = 0.0f;
GLdouble OLD_TIMES_SINCE_START = 0.0f;
GLdouble frames = 0;
GLint FRAME = 0;
GLint TIME;
GLint TIMEBASE = 0;
GLdouble FPS;
const char *TITLE = "Nick's 3D Solar System Modeler";
bool SPRINT = false;
bool ACTUAL_DISTANCE = false;
bool* keyStates = new bool[256]();
bool* keySpecialStates = new bool[256]();
bool* mouseStates = new bool[256]();

#include "Obj.cpp"
#include "objects.h"
#include "Vec3.h"
#include "Camera.cpp"
Camera *camera;
#include "keyboard.h"


// Global Functions
void initialize();
void display();
void reshape(int width, int height);
GLfloat randRotation() { return (GLdouble) (((int) (rand() * 684)) % 360); }
void lookAt();
void initObjects();
void drawObjects();
void drawCameraLocation();

/***************************************************************************
* main()
* Run an OpenGL project
****************************************************************************/
int main(int argc, char** argv)
{
	glutInit(&argc, argv);               // Initialize glut
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL); // Requesting Buffers
	glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
	glutInitWindowPosition(100,100);
	glutCreateWindow(TITLE);
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
    glutSetCursor(GLUT_CURSOR_NONE);

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE); // dont render backside
	glEnable(GL_SCISSOR_TEST); // only render what has changed
	glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);

    glEnable(GL_LIGHTING);
    glDisable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    //glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);


	initObjects();
	camera = new Camera(WINDOW_WIDTH,WINDOW_HEIGHT);
}

/********************************************************************************
* FUNCTION: Display()
********************************************************************************/
void display()
{
    GLint TIME_SINCE_START = glutGet(GLUT_ELAPSED_TIME);
    DELTA_TIME = TIME_SINCE_START - OLD_TIMES_SINCE_START;
    OLD_TIMES_SINCE_START = TIME_SINCE_START;
    if (SPRINT) camera->move(DELTA_TIME * 20);
    else camera->move(DELTA_TIME);

    char s[128];
    FRAME++;
    TIME = glutGet(GLUT_ELAPSED_TIME);
    if (TIME - TIMEBASE > 1000) {
        FPS = (GLdouble) (FRAME * 1000.0f) / (GLdouble) (TIME - TIMEBASE);
        sprintf(s,"FPS:%4.2f",FPS);
        TIMEBASE = TIME;
        FRAME = 0;
    }

    glutSetWindowTitle(s);

    //cout << SIMULATION_SPEED << endl;

	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(mousePassive);
	keyOperations();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    GLfloat globalAmbient[] = { 0.2, 0.2, 0.2, 1.0 };
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, globalAmbient );


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
}

/*******************************************************************************
* FUNCTION: Draw Camera Location
*******************************************************************************/
void drawCameraLocation()
{
    glRotatef(camera->getXRot(), 1.0f, 0.0f, 0.0f);
    glRotatef(camera->getYRot(), 0.0f, 1.0f, 0.0f);
    glTranslatef(-camera->getXPos(), -camera->getYPos(), -camera->getZPos());
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



    if (ACTUAL_DISTANCE)
    {
        mercury.setDistance((sun.getRadius() + 57910000.0f) * SIZE);

        venus.setDistance((sun.getRadius() + 108200000.0f) * SIZE);

        earth.setDistance((sun.getRadius() + 149600000.0f) * SIZE);
        luna.setDistance((earth.getRadius() + 384000.0f) * SIZE);

        mars.setDistance((sun.getRadius() + 227940000.0f) * SIZE);

        jupiter.setDistance((sun.getRadius() + 778330000.0f) * SIZE);
        io.setDistance((jupiter.getRadius() + 422000.0f) * SIZE);
        europa.setDistance((jupiter.getRadius() + 671000.0f) * SIZE);
        ganymede.setDistance((jupiter.getRadius() + 1070000.0f) * SIZE);
        callisto.setDistance((jupiter.getRadius() + 1883000.0f) * SIZE);

        saturn.setDistance((sun.getRadius() + 1429400000.0f) * SIZE);
        mimas.setDistance((saturn.getRadius() + 186000.0f) * SIZE);
        enceladus.setDistance((saturn.getRadius() + 238000.0f) * SIZE);
        tethys.setDistance((saturn.getRadius() + 295000.0f) * SIZE);
        dione.setDistance((saturn.getRadius() + 377000.0f) * SIZE);
        rhea.setDistance((saturn.getRadius() + 527000.0f) * SIZE);
        titan.setDistance((saturn.getRadius() + 1222000.0f) * SIZE);
        hyperion.setDistance((saturn.getRadius() + 1481000.0f) * SIZE);
        iapetus.setDistance((saturn.getRadius() + 3561000.0f) * SIZE);
        phoebe.setDistance((saturn.getRadius() + 12952000.0f) * SIZE);

        uranus.setDistance((sun.getRadius() + 2870990000.0f) * SIZE);
        miranda.setDistance((uranus.getRadius() + 130000.0f) * SIZE);
        ariel.setDistance((uranus.getRadius() + 191000.0f) * SIZE);
        umbriel.setDistance((uranus.getRadius() + 266000.0f) * SIZE);
        titania.setDistance((uranus.getRadius() + 436000.0f) * SIZE);
        oberon.setDistance((uranus.getRadius() + 583000.0f) * SIZE);

        neptune.setDistance((sun.getRadius() + 4504300000.0f) * SIZE);
        proteus.setDistance((neptune.getRadius() + 118000.0f) * SIZE);
        triton.setDistance((neptune.getRadius() + 355000.0f) * SIZE);
        nereid.setDistance((neptune.getRadius() + 5513000.0f) * SIZE);

        pluto.setDistance((sun.getRadius() + 5913520000.0f) * SIZE);
        charon.setDistance((pluto.getRadius() + 20000.0f) * SIZE);
    }
    else
    {
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
    }




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
    
    earth.setTexture("images/Earth.bmp");
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

    if (ACTUAL_DISTANCE)
    {
        mercury.setDistance((sun.getRadius() + 57910000.0f) * SIZE);

        venus.setDistance((sun.getRadius() + 108200000.0f) * SIZE);

        earth.setDistance((sun.getRadius() + 149600000.0f) * SIZE);
        luna.setDistance((earth.getRadius() + 384000.0f) * SIZE);

        mars.setDistance((sun.getRadius() + 227940000.0f) * SIZE);

        jupiter.setDistance((sun.getRadius() + 778330000.0f) * SIZE);
        io.setDistance((jupiter.getRadius() + 422000.0f) * SIZE);
        europa.setDistance((jupiter.getRadius() + 671000.0f) * SIZE);
        ganymede.setDistance((jupiter.getRadius() + 1070000.0f) * SIZE);
        callisto.setDistance((jupiter.getRadius() + 1883000.0f) * SIZE);

        saturn.setDistance((sun.getRadius() + 1429400000.0f) * SIZE);
        mimas.setDistance((saturn.getRadius() + 186000.0f) * SIZE);
        enceladus.setDistance((saturn.getRadius() + 238000.0f) * SIZE);
        tethys.setDistance((saturn.getRadius() + 295000.0f) * SIZE);
        dione.setDistance((saturn.getRadius() + 377000.0f) * SIZE);
        rhea.setDistance((saturn.getRadius() + 527000.0f) * SIZE);
        titan.setDistance((saturn.getRadius() + 1222000.0f) * SIZE);
        hyperion.setDistance((saturn.getRadius() + 1481000.0f) * SIZE);
        iapetus.setDistance((saturn.getRadius() + 3561000.0f) * SIZE);
        phoebe.setDistance((saturn.getRadius() + 12952000.0f) * SIZE);

        uranus.setDistance((sun.getRadius() + 2870990000.0f) * SIZE);
        miranda.setDistance((uranus.getRadius() + 130000.0f) * SIZE);
        ariel.setDistance((uranus.getRadius() + 191000.0f) * SIZE);
        umbriel.setDistance((uranus.getRadius() + 266000.0f) * SIZE);
        titania.setDistance((uranus.getRadius() + 436000.0f) * SIZE);
        oberon.setDistance((uranus.getRadius() + 583000.0f) * SIZE);

        neptune.setDistance((sun.getRadius() + 4504300000.0f) * SIZE);
        proteus.setDistance((neptune.getRadius() + 118000.0f) * SIZE);
        triton.setDistance((neptune.getRadius() + 355000.0f) * SIZE);
        nereid.setDistance((neptune.getRadius() + 5513000.0f) * SIZE);

        pluto.setDistance((sun.getRadius() + 5913520000.0f) * SIZE);
        charon.setDistance((pluto.getRadius() + 20000.0f) * SIZE);
    }
    else
    {
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
    }

    drawCameraLocation();

    glPushMatrix();
	glRotatef(sun.getAngleOfRotation(SIMULATION_SPEED), 0.0f, 1.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, sun.getTexture()); 
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(sun.getSphere(), sun.getRadius(), QUALITY, QUALITY);
	glPopMatrix();


    mercury.planetOrbit(SIMULATION_SPEED);

    venus.planetOrbit(SIMULATION_SPEED);

    earth.planetOrbit(SIMULATION_SPEED);
    luna.moonOrbit(earth, SIMULATION_SPEED);

    mars.planetOrbit(SIMULATION_SPEED);

	jupiter.planetOrbit(SIMULATION_SPEED);
    io.moonOrbit(jupiter, SIMULATION_SPEED);
    europa.moonOrbit(jupiter, SIMULATION_SPEED);
    ganymede.moonOrbit(jupiter, SIMULATION_SPEED);
    callisto.moonOrbit(jupiter, SIMULATION_SPEED);

    saturn.planetOrbit(SIMULATION_SPEED);
    mimas.moonOrbit(saturn, SIMULATION_SPEED);
    enceladus.moonOrbit(saturn, SIMULATION_SPEED);
    tethys.moonOrbit(saturn, SIMULATION_SPEED);
    dione.moonOrbit(saturn, SIMULATION_SPEED);
    rhea.moonOrbit(saturn, SIMULATION_SPEED);
    titan.moonOrbit(saturn, SIMULATION_SPEED);
    hyperion.moonOrbit(saturn, SIMULATION_SPEED);
    iapetus.moonOrbit(saturn, SIMULATION_SPEED);
    phoebe.moonOrbit(saturn, SIMULATION_SPEED);

    uranus.planetOrbit2(SIMULATION_SPEED);
    miranda.moonOrbit(uranus, SIMULATION_SPEED);
    ariel.moonOrbit(uranus, SIMULATION_SPEED);
    umbriel.moonOrbit(uranus, SIMULATION_SPEED);
    titania.moonOrbit(uranus, SIMULATION_SPEED);
    oberon.moonOrbit(uranus, SIMULATION_SPEED);

    neptune.planetOrbit(SIMULATION_SPEED);
    proteus.moonOrbit(neptune, SIMULATION_SPEED);
    triton.moonOrbit(neptune, SIMULATION_SPEED);
    nereid.moonOrbit(neptune, SIMULATION_SPEED);

    pluto.planetOrbit(SIMULATION_SPEED);
    charon.moonOrbit(pluto, SIMULATION_SPEED);
}

