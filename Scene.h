#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>

/* Viewing setup and camera mechanics

		 y
		 |
		 |
		 |_ _ _ x
		/
	   /  xz plane of movement (strafe, forward, backward)
	  /
	 z
	 
	 Camera pan is rotation about y-axis and xz-plane.
	 Camera zoom is achieved through changing field of view angle in perspective.
	 Camera roll is rotation about the camera vector.
	 2D Movement happens only in XZ-plane at constant Y, so we consider only XZ components of the camera vector.
	 Strafing is achieved by moving along vectors perpendicular to XZ component of camera vector.
	 Moving upward and downward is done by moving along Y-axis.
	 Moving forward and backward is moving along the XZ component of the camera vector.
*/

//  Angles of rotation for the camera direction
//	XZangle is the angle made by the camera vector projected on XZ plane with the x-axis
//  Y angle is the angle made by the camera vector with the XZ plane (or 90-angle made with Y axis)
// 	axis angle is the rotation about the camera vector (used for roll)
float XZangle = 0.0f;
float Yangle = 0.0f;
float axisangle = 0.0f;

// Camera position in 3D space
float x = -25.0f;
float z = 25.0f;
float y = 300.0f;

// Actual vector representing the camera's direction
float vx =  0.007f;
float vz = -0.007f;
float vy = -0.986f;

// the key states. These variables will be zero
//when no key is being presses
float deltaXZangle = 0.0f;
float deltaYangle = 85.0f;

float deltaMove = 0;
int xOrigin = -1;
int yOrigin = -1;
int lstrafe = 0;
int rstrafe = 0;

// rollamount and fov control the degree of camera roll and zoom respectively
float rollamount = 0;
float fov = 60.0;
int interact = 0;
int ceilingon=1;
int parachutejump = 1;

//Calculate the euclidean square distance between two points
float euclidean(float x1, float y1, float z1)
{
	return (x-x1)*(x-x1) + (y-y1)*(y-y1) + (z-z1)*(z-z1);
}

// To handle window resizing
void changeSize(int w, int h) 
{
	// Compute the aspect ratio
	float ratio = w*1.0/h;
	
	// Projection matrix incorporate perspective projection
	// with perspective angle = fov
	// This helps maintain zoom degree across all window sizes
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(fov, ratio, 0.1f, 500.0f);
	glMatrixMode(GL_MODELVIEW);
}

// Compute new position of camera in world
// due to movement

// deltaMove allows for both positive and negative movement
// with its sign.
void computePos(float deltaMove)
{
	// If the current camera vector along ground is vxi + vzj
	// the left and right perpendicular vectors will be -vxi + vzj and vxi - vzj
	if(lstrafe)
		x += vz * 0.125f, z += (-vx) * 0.125f;
	else if(rstrafe)
		x += (-vz) * 0.125f, z += vx * 0.125f;
	
	// Move on camera vector along ground - vxi + vzj
	else
		x += deltaMove * vx * 0.25f, z += deltaMove * vz * 0.25f;
}

void processNormalKeys(unsigned char key, int xx, int yy) 
{ 	
	// Exit the game
	if(key == 27)
	{   
		remove("radiosignal.txt");
    	printf("%f",z);
    	exit(0);
    }
    
    // Movement upward and downward
    if(key == 'W')
        y+=0.5;
    if(key == 'S')
        y-=0.5;
        
    // Camera roll limited between -45° to 45°
   	if(key == 'M')
		if(rollamount>-45)
			rollamount-=1;
    if(key == 'N')
		if(rollamount<45)
			rollamount+=1;
	
	//Keys to toggle interaction and ceiling
	if(key == 'Q')
		interact = 1;
	if(key == 'C')
		ceilingon ^= 1;
} 

// Forward and backward movement, strafing keys
void pressKey(int key, int xx, int yy) 
{
       switch (key) 
	   {
             case GLUT_KEY_UP : deltaMove = 0.8f; break;
             case GLUT_KEY_DOWN : deltaMove = -0.8f; break;	
		 	 case GLUT_KEY_RIGHT: rstrafe = 1; break;
			 case GLUT_KEY_LEFT: lstrafe = 1; break;
       }
}

// Reset all key effects
void releaseKey(int key, int x, int y) 
{ 	
        switch (key) 
		{
             case GLUT_KEY_UP :
             case GLUT_KEY_DOWN : deltaMove = 0; break;
			 case GLUT_KEY_LEFT : lstrafe = 0; break;
			 case GLUT_KEY_RIGHT : rstrafe = 0; break;       
		}
} 

// Change the camera vector if pan is performed
void mouseMove(int x, int y) 
{ 	
		// If xOrigin is positive => We have panned across XZ plane
		// i.e rotation along y-axis. This rotation is also called yaw.
        if(xOrigin >= 0) 
		{
			deltaXZangle = (x - xOrigin) * 0.010f;

			vx = sin(XZangle + deltaXZangle);
			vz = -cos(XZangle + deltaXZangle);
		}

		// If xOrigin is positive => We have panned across y-axis
		// i.e rotation along camera vector. This rotation is also called pitch.
		if(yOrigin >= 0)
		{
			deltaYangle = (yOrigin - y) * 0.006f;
			vy = sin(Yangle + deltaYangle);
		}
}

// Zoom and pan control
void mouseButton(int button, int state, int x, int y) 
{

	// Left button used for panning of camera
	if(button == GLUT_LEFT_BUTTON) 
	{
		// If pressed, the mouse cursor controls the panning
		// xOrigin and yOrigin store last known position of cursor
		if(state == GLUT_UP)
	    {
			XZangle += deltaXZangle, xOrigin = -1;
			Yangle += deltaYangle, yOrigin = -1;		
		}
		else
			xOrigin = x, yOrigin = y;
	}
	
	// button = 3 or 4 is triggered by mouse wheel up and down
	// This is used to control zoom
	if (button == 3 || button == 4)
	{
		// Increase or decrease zoom using mouse wheel
		// Zoom is controlled by changing fov angle
		// Small fov angle or smaller fov => High zoom 
		// Large fov angle or larger fov => Low zoom
		if(fov >= 1.0f && fov <= 45.0f)
	  		fov += (button==3)?(-1):(1);
	  	if(fov <= 1.0f)
	  		fov = 1.0f;
	  	if(fov >= 45.0f)
	  		fov = 45.0f;
	  			
	  	// Set up perspective projection again to reflect FOV change
  		int w = glutGet(GLUT_WINDOW_WIDTH);
  		int h = glutGet(GLUT_WINDOW_HEIGHT);
  		
  		float ratio =  w * 1.0 / h;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(0, 0, w, h);
		gluPerspective(fov, ratio, 0.1f, 100.0f);
		glMatrixMode(GL_MODELVIEW);
	}
}

//Initial graphics setup required by GLUT
void initGraphics(int argc, char **argv)
{
	// Initialize the window with depth, double buffering and RGBA colors
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,640);
	glutCreateWindow("The Middle of Nowhere");

	// Enable depth and AA calculations
	glEnable(GL_DEPTH_TEST);
	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST ); 
	glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST ); 
	glEnable( GL_LINE_SMOOTH ); 
	glEnable( GL_POLYGON_SMOOTH ); 
	glEnable( GL_MULTISAMPLE );
	
	// If the window is resized
	glutReshapeFunc(changeSize);

	// Keyboard event processing
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);

	// Mouse event processing
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);
}
