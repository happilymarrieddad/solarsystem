bool* keyStates = new bool[256]();
bool* keySpecialStates = new bool[256]();
bool* mouseStates = new bool[256]();

/***************************************************************************
* FUNCTION: Key Pressed
* Summary - Assign some bool value when key is pressed.
***************************************************************************/
void keyPressed (unsigned char key, int x, int y)
{
	keyStates[key] = true;
	glutPostRedisplay();  // Redisplays the scene after a button is pressed
}

/***************************************************************************
* FUNCTION: Key Up
* Summary - Reverse the bool value when key is let go
***************************************************************************/
void keyUp (unsigned char key, int x, int y)
{
	keyStates[key] = false;
	glutPostRedisplay();  // Redisplays the scene after a button is pressed
}

/***************************************************************************
* FUNCTION: Special Key Pressed
* Summary - Assign some bool value when a special key is pressed.
***************************************************************************/
void keySpecial (int key, int x, int y)
{
	keySpecialStates[key] = true;
	glutPostRedisplay();  // Redisplays the scene after a button is pressed
}

/***************************************************************************
* FUNCTION: Key Up
* Summary - Reverse the bool value when key is let go
***************************************************************************/
void keySpecialUp (int key, int x, int y)
{
	keySpecialStates[key] = false;
	glutPostRedisplay();  // Redisplays the scene after a button is pressed
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
* FUNCTION: Tests to see if the mouse is in the scene
***************************************************************************/
void entry(int state)
{
	if (state == GLUT_ENTERED)
	{
		mouseStates['e'] = true;
	}
	else
	{
		mouseStates['e'] = false;
	}
}

/***************************************************************************
* FUNCTION: Mouse motion when button is pressed
***************************************************************************/
void motion(int x, int y)
{

}

/***************************************************************************
* FUNCTION: Mouse motion when button is not pressed
***************************************************************************/
void motionPassive(int x, int y)
{

}

/***************************************************************************
* FUNCTION: Key States
***************************************************************************/
void keyOperations (void)
{
	GLfloat move = 0.1f;
	/* KEYBOARD OPERATIONS */
	if (keyStates['w'])
	{
		//camera.rotateY(move);
	}
	if (keyStates['s'])
	{
		//camera.rotateY(-move);
	}
	if (keyStates['a'])
	{
	}
	if (keyStates['d'])
	{
	}
	if (keyStates[' '])
	{
	}
	if (keyStates['c'])
	{
	}
	if (keyStates['-'])
	{
		if (SIMULATION_INCREASE  > 1.0f)
		{
		    SIMULATION_INCREASE -= 0.1f;
		}
	}
	if (keyStates['='])
	{
		SIMULATION_INCREASE += 0.1f;
	}
	if (keyStates['p'])
	{
	}
	
	/* MOUSE OPERATIONS 
	if (mouseStates['l'])
	{
		/*
		X_START_POS = sun.getXLocation();
		Y_START_POS = sun.getYLocation();
		Z_START_POS = sun.getZLocation() - (sun.getSize() * 3);
		
	}
	if (mouseStates['m'])
	{

	}
	if (mouseStates['r'])
	{

	}*/
}