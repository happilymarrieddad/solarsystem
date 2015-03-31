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
	/*
    if (keyStates['y'])
    {
        ACTUAL_DISTANCE = true;
    }
    else if (!keyStates['y'])
    {
        ACTUAL_DISTANCE = false;
    }
    */
    if (!keyStates['y'])
    {
        ACTUAL_DISTANCE = true;
    }
    else if (keyStates['y'])
    {
        ACTUAL_DISTANCE = false;
    }
    
    if (keyStates['e'])
    {
        SPRINT = true;
    } else SPRINT = false;
    if (keyStates['v'])
    {
        SIMULATION_SPEED = 0.0f;
    }
    if (keyStates['r'])
    {
        SIMULATION_SPEED = 0.00005f;
    }
    if (keyStates['-'])
    {
    	SIMULATION_SPEED -= 0.5f;
    }
    if (keyStates['='])
    {
    	SIMULATION_SPEED += 0.5f;
    }

	// Look at Sun
	if (keyStates['1'])
	{
		camera->setPosition(sun.getX(),sun.getY(),sun.getZ());
	}
	// Look at Mercury
	if (keyStates['2'])
	{
		camera->setPosition(mercury.getX(),mercury.getY(),mercury.getZ());
	}
	// Look at Venus
	if (keyStates['3'])
	{
		camera->setPosition(venus.getX(),venus.getY(),venus.getZ());
	}
	// Look at Earth
	if (keyStates['4'])
	{
		camera->setPosition(earth.getX(),earth.getY(),earth.getZ());
	}
	// Look at Mars
	if (keyStates['5'])
	{
		camera->setPosition(mars.getX(),mars.getY(),mars.getZ());
	}
	// Look at Jupiter
	if (keyStates['6'])
	{
		camera->setPosition(jupiter.getX(),jupiter.getY(),jupiter.getZ());		
	}
	// Look at Saturn
	if (keyStates['7'])
	{
		camera->setPosition(saturn.getX(),saturn.getY(),saturn.getZ());
	}
	// Look at Uranus
	if (keyStates['8'])
	{
		camera->setPosition(uranus.getX(),uranus.getY(),uranus.getZ());
	}
	// Look at Neptune
	if (keyStates['9'])
	{
		camera->setPosition(neptune.getX(),neptune.getY(),neptune.getZ());
	}
	// Look at Pluto
	if (keyStates['0'])
	{
		camera->setPosition(pluto.getX(),pluto.getY(),pluto.getZ());
	}
}

