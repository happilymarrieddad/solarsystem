/********************************************************************************
* FUNCTION: Key Pressed
********************************************************************************/
void keyPressed(unsigned char key, int x, int y)
{
	keyStates[key] = true;
	glutPostRedisplay();
}

/********************************************************************************
* FUNCTION:: Key Up
********************************************************************************/
void keyUp(unsigned char key, int x, int y)
{
	keyStates[key] = false;
	glutPostRedisplay();
}

/***************************************************************************
* FUNCTION: Special Key Pressed
***************************************************************************/
void specialKeyPressed(int key, int x, int y)
{
    for (int i = 0; i < 256; i++)
    {
        keySpecialStates[i] = false;
    }
    keySpecialStates[key] = true;
}

/***************************************************************************
* FUNCTION: Mouse - When 1 or more buttons are pressed
***************************************************************************/
void mouse(int button, int state, int x, int y) 
{
	if (state == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			mouseStates['l'] = true;
		}
		else if (button == GLUT_MIDDLE_BUTTON)
		{
			mouseStates['m'] = true;
		}
		else if (button == GLUT_RIGHT_BUTTON)
		{
			mouseStates['r'] = true;
		}
	}
	else
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			mouseStates['l'] = false;
		}
		else if (button == GLUT_MIDDLE_BUTTON)
		{
			mouseStates['m'] = false;
		}
		else if (button == GLUT_RIGHT_BUTTON)
		{
			mouseStates['r'] = false;
		}
	}
}

/***************************************************************************
* FUNCTION: Passive Mouse
***************************************************************************/
void passiveMouse(int x, int y)
{

    glutWarpPointer(1024/2,768/2);
}

/********************************************************************************
* FUNCTION: Key Operations
********************************************************************************/
void keyOperations()
{
	// Forward
	if (keyStates['w'])
	{
	    camera.offsetPosition(camera.forward() * MOVE_SPEED);
	}
	// Backward
	if (keyStates['s'])
	{
	    camera.offsetPosition(-camera.forward() * MOVE_SPEED);
	}


	if (keyStates['q'])
	{
	    camera.offsetOrientation(1.0f, 1.0f);
	}
	if (keyStates['e'])
	{
	    camera.offsetOrientation(-1.0f, -1.0f);
	}


	if (keyStates['-'])
	{
		if (SIMULATION_SPEED > 0.0f) SIMULATION_SPEED -= 0.0001f;
	}
	if (keyStates['='])
	{
		SIMULATION_SPEED += 0.0001f;
	}
    if (keyStates['y'])
    {
        ACTUAL_DISTANCE = true;
    }
    else if (!keyStates['y'])
    {
        ACTUAL_DISTANCE = false;
    }
    if (keySpecialStates[GLUT_KEY_F12])
    {
        exit(0);
    }

	// Look at Sol
	if (keyStates['1'])
	{
	}
	// Look at Mercury
	if (keyStates['2'])
	{
	}
	// Look at Venus
	if (keyStates['2'])
	{
		
	}
	// Look at Earth
	if (keyStates['3'])
	{
		
	}
	// Look at Mars
	if (keyStates['4'])
	{
		
	}
	// Look at Jupiter
	if (keyStates['5'])
	{
		
	}
	// Look at Saturn
	if (keyStates['6'])
	{
		
	}
	// Look at Uranus
	if (keyStates['7'])
	{
		
	}
	// Look at Neptune
	if (keyStates['8'])
	{
		
	}
	// Look at Pluto
	if (keyStates['9'])
	{
		
	}
}

