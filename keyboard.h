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
		CAMERA_Z += 10000.0f;
	}
	// Backward
	if (keyStates['s'])
	{
		CAMERA_Z -= 10000.0f;
	}
	// Turn Left
	if (keyStates['a'])
	{
		CAMERA_X += 10000.0f;
	}
	// Turn Right
	if (keyStates['d'])
	{
		CAMERA_X -= 10000.0f;
	}
	// Look Up
	if (keyStates['t'])
	{
		CAMERA_X_ROTATION_ANGLE -= 0.5f;
		if (CAMERA_X_ROTATION_ANGLE < 0.0f) CAMERA_X_ROTATION_ANGLE += 360.0f;
	}
	// Look Down
	if (keyStates['y'])
	{
		CAMERA_X_ROTATION_ANGLE += 0.5f;
		if (CAMERA_X_ROTATION_ANGLE) CAMERA_X_ROTATION_ANGLE -= 360.0f;
	}
	// Look Left
	if (keyStates['g'])
	{
		CAMERA_Y_ROTATION_ANGLE -= 0.5f;
		if (CAMERA_Y_ROTATION_ANGLE < 0.0f) CAMERA_Y_ROTATION_ANGLE += 360.0f;
	}
	// Look Right
	if (keyStates['h'])
	{
		CAMERA_Y_ROTATION_ANGLE += 0.5f;
		if (CAMERA_Y_ROTATION_ANGLE) CAMERA_Y_ROTATION_ANGLE -= 360.0f;
	}
	// Rotate Left
	if (keyStates['b'])
	{
		CAMERA_Z_ROTATION_ANGLE -= 0.5f;
		if (CAMERA_Z_ROTATION_ANGLE < 0.0f) CAMERA_Z_ROTATION_ANGLE += 360.0f;
	}
	// Rotate Right
	if (keyStates['n'])
	{
		CAMERA_Z_ROTATION_ANGLE += 0.5f;
		if (CAMERA_Z_ROTATION_ANGLE) CAMERA_Z_ROTATION_ANGLE -= 360.0f;
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
			CAMERA_X, CAMERA_Y, CAMERA_Z,
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

