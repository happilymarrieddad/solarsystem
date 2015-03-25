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

/******************************************************************************
* FUNCTION: Passive Mouse
******************************************************************************/
void mousePassive(int x, int y)
{
    camera->handleMouseMove(x,y);
}

/********************************************************************************
* FUNCTION: Key Operations
********************************************************************************/
void keyOperations()
{
	// Forward
	if (keyStates['w'])
	{
	    camera->forward = true;
	} else camera->forward = false;
	// Backward
	if (keyStates['s'])
	{
	    camera->backward = true;
	} else camera->backward = false;
	// Turn Left
	if (keyStates['a'])
	{
	    camera->left = true;
	} else camera->left = false;
	// Turn Right
	if (keyStates['d'])
	{
	    camera->right = true;
	} else camera->right = false;
	// quit
	if (keyStates['q'])
	{
	    exit(0);
	}
	if (keyStates['-'])
	{
		if (SIMULATION_SPEED > 0.0f) SIMULATION_SPEED -= 0.0005f;
	}
	if (keyStates['='])
	{
		SIMULATION_SPEED += 0.0005f;
	}
    if (keyStates['y'])
    {
        ACTUAL_DISTANCE = true;
    }
    else if (!keyStates['y'])
    {
        ACTUAL_DISTANCE = false;
    }
    if (keyStates['e'])
    {
        SPRINT = true;
    } else SPRINT = false;
    if (keyStates['r'])
    {
        SIMULATION_SPEED = 0.0005f;
    }
    if (keyStates['p'])
    {
        SIMULATION_SPEED = 0.0f;
    } else SIMULATION_SPEED = 0.0005f;



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

