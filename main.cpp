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

// Other includes
#include "Image.cpp"
#include "Moon.cpp"
#include "Planet.cpp"
#include "Star.cpp"
#include "Solarsystem.cpp"
#include "Camera.cpp"
#include "globals.h"
#include "keyboard.h"

// Global Functions
void initialize();
void display();
void render();
void reshape(int width, int height);

/***************************************************************************
* main()
* Run an OpenGL project
****************************************************************************/
int main(int argc, char** argv)
{
	glutInit(&argc, argv);               // Initialize glut
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
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
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);

    Star sun;
    sun.setSize(696000.0f);
    sun.addBMP("sunmap.bmp");

	solarsystem.initializeSolSystem(sun);
}

/********************************************************************************
* FUNCTION: Display()
********************************************************************************/
void display()
{
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(keySpecial);       // use GLUT_KEY_LEFT as an example for left arrow key
	glutSpecialUpFunc(keySpecialUp);   // keySpecialUp(int key, int x, int y)
	glutMouseFunc(mouse);              // Mouse Functions
	glutMotionFunc(motion);            
	glutPassiveMotionFunc(motionPassive);
	glutEntryFunc(entry);
	keyOperations(); // Must call before everything else to avoid artefacts... learned this the hard way...

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(WINDOW_STARTING_X,WINDOW_STARTING_Y,WINDOW_STARTING_Z); // Move the camera
	render(); // Render objects

	glutSwapBuffers();
}

/********************************************************************************
* FUNCTION: Render()
********************************************************************************/
void render()
{
	CURRENT_TIME -= SIMULATION_SPEED * SIMULATION_INCREASE;

	float lightType = GL_AMBIENT;
	float intensity = 1.0f;
	GLfloat lightColor[] = {intensity,intensity,intensity,1.0f};
	GLfloat lightPos0[] = {1.0f,0.0f,0.0f,1.0f};
	glLightfv(GL_LIGHT0,lightType,lightColor);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPos0);

	solarsystem.display();

}

/********************************************************************************
* FUNCTION: Reshape()
********************************************************************************/
void reshape(int width, int height)
{
	// SETUP
	glViewport(0,0,(GLsizei)width, (GLsizei)height); // sets the viewport to the size of the window
	glMatrixMode(GL_PROJECTION); // switch to the projection matrix so that we can manipulate how our scene is viewed
	glLoadIdentity(); // resets matricies to avoid unusual rendering/artefacts

	// FoV
	const GLdouble ASPECT = (GLfloat) width / (GLfloat) height;
	gluPerspective(WINDOW_FOV,ASPECT,WINDOW_Z_NEAR,WINDOW_Z_FAR);

	// Switch back to the Model View Matrix
	glMatrixMode(GL_MODELVIEW);
}