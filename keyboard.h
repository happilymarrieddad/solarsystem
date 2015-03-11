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

/********************************************************************************
* FUNCTION: Key Operations
********************************************************************************/
void keyOperations()
{
	// Forward
	if (keyStates['w'])
	{
		WINDOW_Z += 10000.0f;
	}
	// Backward
	if (keyStates['s'])
	{
		WINDOW_Z -= 10000.0f;
	}
	// Turn Left
	if (keyStates['a'])
	{
		WINDOW_X += 10000.0f;
	}
	// Turn Right
	if (keyStates['d'])
	{
		WINDOW_X -= 10000.0f;
	}
	// Strafe Left
	if (keyStates['q'])
	{
		
	}
	// Strafe Right
	if (keyStates['e'])
	{
		
	}
	if (keyStates['-'])
	{
		if (SIMULATION_SPEED > 0.0f) SIMULATION_SPEED -= 0.0001f;
	}
	if (keyStates['='])
	{
		SIMULATION_SPEED += 0.0001f;
	}



	// Look at Sol
	if (keyStates['1'])
	{
		gluLookAt(
			WINDOW_X, WINDOW_Y, WINDOW_Z,
			0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f
		);
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

