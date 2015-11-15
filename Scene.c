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
float x = 0.0f;
float z = 5.0f;
float y = 1.0f;

// Actual vector representing the camera's direction
float vx =  0.0f;
float vz = -1.0f;
float vy =  0.0f;

// the key states. These variables will be zero
//when no key is being presses
float deltaXZangle = 0.0f;
float deltaYangle = 0.0f;

float deltaMove = 0;
int xOrigin = -1;
int yOrigin = -1;
int lstrafe = 0;
int rstrafe = 0;

// rollamount and fov control the degree of camera roll and zoom respectively
float rollamount = 0;
float fov = 45.0;

// Active global color
float r,g,b;

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
	gluPerspective(fov, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

void drawParapetX(float len)
{
	glColor3f(r,g,b);
    glBegin(GL_QUADS);
 
	int h;
    for(h=0;h<8;h++)
	{
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.6f, 0.1+h*0.3, 0.0f);
		glVertex3f(0.6f, 0.1+h*0.3, len);
		glVertex3f(0.6f, 0.3+h*0.3, len);
		glVertex3f(0.6f, 0.3+h*0.3, 0.0f);
	 
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.1+h*0.3, len);
		glVertex3f(0.0f, 0.3+h*0.3, len);
		glVertex3f(0.6f, 0.3+h*0.3, len);
		glVertex3f(0.6f, 0.1+h*0.3, len);

		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(0.0f, 0.1+h*0.3, 0.0f);
		glVertex3f(0.0f, 0.3+h*0.3, 0.0f);
		glVertex3f(0.0f, 0.3+h*0.3, len);
		glVertex3f(0.0f, 0.1+h*0.3, len);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.1+h*0.3, 0.0f);
		glVertex3f(0.6f, 0.1+h*0.3, 0.0f);
		glVertex3f(0.6f, 0.3+h*0.3, 0.0f);
		glVertex3f(0.0f, 0.3+h*0.3, 0.0f);
 	}
    glEnd();
}

void drawDoorX()
{
	glColor3f(r,g,b);
    glBegin(GL_QUADS);
 
    //Front
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.6f, -1.0f, 0.0f);
    glVertex3f(0.6f, -1.0f, 4.0f);
    glVertex3f(0.6f, 5.0f, 4.0f);
    glVertex3f(0.6f, 5.0f, 0.0f);
 
    //Right
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, 4.0f);
    glVertex3f(0.0f, 5.0f, 4.0f);
    glVertex3f(0.6f, 5.0f, 4.0f);
    glVertex3f(0.6f, -1.0f, 4.0f);
 
    //Back
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, 5.0f, 0.0f);
    glVertex3f(0.0f, 5.0f, 4.0f);
    glVertex3f(0.0f, -1.0f, 4.0f);
 
    //Left
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.6f, -1.0f, 0.0f);
    glVertex3f(0.6f, 5.0f, 0.0f);
    glVertex3f(0.0f, 5.0f, 0.0f);
 
    glEnd();
}

void drawDoorZ()
{
	glColor3f(r,g,b);
    glBegin(GL_QUADS);
 
    //Front
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, -1.0f, 0.6f);
    glVertex3f(4.0f, -1.0f, 0.6f);
    glVertex3f(4.0f, 5.0f, 0.6f);
    glVertex3f(0.0f, 5.0f, 0.6f);
 
    //Right
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(4.0f, -1.0f, 0.0f);
    glVertex3f(4.0f, 5.0f, 0.0f);
    glVertex3f(4.0f, 5.0f, 0.6f);
    glVertex3f(4.0f, -1.0f, 0.6f);
 
    //Back
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, 5.0f, 0.0f);
    glVertex3f(4.0f, 5.0f, 0.0f);
    glVertex3f(4.0f, -1.0f, 0.0f);
 
    //Left
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, 0.6f);
    glVertex3f(0.0f, 5.0f, 0.6f);
    glVertex3f(0.0f, 5.0f, 0.0f);
 
    glEnd();
}

void drawWallZ(float len)
{
	glColor3f(r,g,b);
    glBegin(GL_QUADS);

    //Front
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, -1.0f, 0.6f);
    glVertex3f(len, -1.0f, 0.6f);
    glVertex3f(len, 5.0f, 0.6f);
    glVertex3f(0.0f, 5.0f, 0.6f);
 
    //Right
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(len, -1.0f, 0.0f);
    glVertex3f(len, 5.0f, 0.0f);
    glVertex3f(len, 5.0f, 0.6f);
    glVertex3f(len, -1.0f, 0.6f);
 
    //Back
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, 5.0f, 0.0f);
    glVertex3f(len, 5.0f, 0.0f);
    glVertex3f(len, -1.0f, 0.0f);
 
    //Left
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, 0.6f);
    glVertex3f(0.0f, 5.0f, 0.6f);
    glVertex3f(0.0f, 5.0f, 0.0f);
 
    glEnd();
}

void drawWallX(float len)
{
	glColor3f(r,g,b);
    glBegin(GL_QUADS);

    //Front
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.6f, -1.0f, 0.0f);
    glVertex3f(0.6f, -1.0f, len);
    glVertex3f(0.6f, 5.0f, len);
    glVertex3f(0.6f, 5.0f, 0.0f);
 
    //Right
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, len);
    glVertex3f(0.0f, 5.0f, len);
    glVertex3f(0.6f, 5.0f, len);
    glVertex3f(0.6f, -1.0f, len);
 
    //Back
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, 5.0f, 0.0f);
    glVertex3f(0.0f, 5.0f, len);
    glVertex3f(0.0f, -1.0f, len);
 
    //Left
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, 0.0f);
    glVertex3f(0.6f, -1.0f, 0.0f);
    glVertex3f(0.6f, 5.0f, 0.0f);
    glVertex3f(0.0f, 5.0f, 0.0f);
 
    glEnd();
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
		x += vz * 0.5f, z += (-vx) * 0.5f;
	else if(rstrafe)
		x += (-vz) * 0.5f, z += vx * 0.5f;
	
	// Move on camera vector along ground - vxi + vzj
	else
		x += deltaMove * vx * 0.5f, z += deltaMove * vz * 0.5f;
}

// Main drawing function
void renderScene(void) 
{
	// Compute position if we move forward or left or right
	if (deltaMove || lstrafe || rstrafe)
		computePos(deltaMove);

	// Clear color and set background to blue sky
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 	glClearColor(102.0/255.0, 204.0/255.0, 1.0f, 1.0f);
 	
 	// Sets up viewing
 	// Eye is at recorded position x, y, z
 	// We are looking in the direction vx, vy, vz
 	// The up vector is in y direction
	glLoadIdentity();
	gluLookAt(	  x,    y,     z,
			   x+vx, y+vy,  z+vz,
			   0.0f, 1.0f,  0.0f  );
	
	// Roll the camera as required by roll amount
	glTranslatef(x,y,z);
	glRotatef(rollamount, vx, vy, vz);
	glTranslatef(-x, -y, -z);
	
	// Draw green grass
	glColor3f(0.0f, 0.65f, 0.0f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();

	// Drawing walls and doors
	
	//Door
	r = 0.7, g = 0.3, b = 0.3;
    glPushMatrix(); 
    glTranslatef(29.6,0,30);
    drawDoorZ();
    glPopMatrix();

	//Door attached wall
	r = 1.0, g = 1.0, b = 1.0;
	glPushMatrix();
    glTranslatef(33,0,30.6);
    drawWallX(10);
    glPopMatrix();

	//Door attached wall
	glPushMatrix();
    glTranslatef(26.6,0,30);
    drawWallZ(3);
    glPopMatrix();

	//Living room wall
	glPushMatrix();
    glTranslatef(26.6,0,30);
    drawWallX(-5);
    glPopMatrix();

	//Long living room wall	
	glPushMatrix();
    glTranslatef(26.6,0,25);
    drawWallZ(-30);
    glPopMatrix();

	//Balcony to hall living room connector	
	glPushMatrix();
    glTranslatef(-3.4,0,40);
    drawWallZ(15);
    glPopMatrix();

	//Balcony parapet
	r = 0.0, g = 0.0, b = 0.0;
	glPushMatrix();
    glTranslatef(-9.6,0,25.65);
    drawParapetX(14.2);
    glPopMatrix();

	r = 1.0, g = 1.0, b = 1.0;
	//Balcony wall
	glPushMatrix();
    glTranslatef(-3.4,0,25);
    drawWallZ(-6);
    glPopMatrix();

	//Balcony wall
	glPushMatrix();
    glTranslatef(-3.4,0,40);
    drawWallZ(-6);
    glPopMatrix();

	//Balcony slide doors
	glPushMatrix();
    glTranslatef(-3.4,0,25);
    drawWallX(6);
    glPopMatrix();

	//Balcony slide doors
	glPushMatrix();
    glTranslatef(-3.4,0,34);
    drawWallX(6);
    glPopMatrix();

	//Shoebox wall	
	glPushMatrix();
    glTranslatef(33,0,40);
   	drawWallZ(-6);
    glPopMatrix();
    
	//Hall wall to bathroom
	glPushMatrix();
    glTranslatef(27,0,40);
    drawWallX(15);
    glPopMatrix();

	//Hall wall
	glPushMatrix();
    glTranslatef(11.6,0,40);
    drawWallX(25);
    glPopMatrix();

	//Bathroom Door
	r = 0.7, g = 0.3, b = 0.3;
    glPushMatrix(); 
    glTranslatef(27,0,55);
    drawDoorX();
    glPopMatrix();

	//Bedroom bathroom separator
	r = 1.0, g = 1.0, b = 1.0;	
	glPushMatrix(); 
    glTranslatef(27,0,59);
    drawWallX(1);
    glPopMatrix();

	//Bathroom walls
	r = 0.0, g = 0.0, b = 0.9;	
	glPushMatrix(); 
    glTranslatef(27.6,0,59);
    drawWallZ(10);
    glPopMatrix();
	//Bathroom walls
	glPushMatrix(); 
    glTranslatef(27.6,0,49);
    drawWallZ(10);
    glPopMatrix();
	//Bathroom walls
	glPushMatrix(); 
    glTranslatef(37.6,0,59);
    drawWallX(-10);
    glPopMatrix();

	//Bedroom walls
	r = 1.0, g = 1.0, b = 1.0;
	glPushMatrix(); 
    glTranslatef(27.6,0,59.6);
    drawWallZ(10);
    glPopMatrix();
	//Bedroom walls
	glPushMatrix();     
	glTranslatef(37.6,0,59);
    drawWallX(10);
    glPopMatrix();
	//Bedroom walls
	glPushMatrix(); 
    glTranslatef(27.6,0,69);
    drawWallZ(10);
    glPopMatrix();
	//Bedroom walls
	glPushMatrix(); 
    glTranslatef(27.6,0,69);
    drawWallX(-4.8);
    glPopMatrix();
	//Bathroom Door
	r = 0.7, g = 0.3, b = 0.3;
    glPushMatrix(); 
    glTranslatef(27.6,0,60.2);
    drawDoorX();
    glPopMatrix();
	
	//Bedroom kitchen separator
	r = 1.0, g = 1.0, b = 1.0;	
	glPushMatrix(); 
    glTranslatef(27.6,0,69);
    drawWallZ(-5);
    glPopMatrix();

	//Kitchen walls
	glPushMatrix(); 
    glTranslatef(22.6,0,69);
    drawWallX(15);
    glPopMatrix();
	//Kitchen walls
	glPushMatrix();     
	glTranslatef(22.6,0,84);
    drawWallZ(-7);
    glPopMatrix();
	//Kitchen walls
	glPushMatrix();     
	glTranslatef(15.6,0,84);
    drawWallX(-15);
    glPopMatrix();

	//Kitchen bedroom separator
	glPushMatrix(); 
    glTranslatef(15.6,0,69);
    drawWallZ(-2);
    glPopMatrix();

	//Bedroom 2 walls
	glPushMatrix(); 
    glTranslatef(13.6,0,69);
    drawWallX(15);
    glPopMatrix();
	//Bedroom 2 walls
	glPushMatrix();     
	glTranslatef(13.6,0,84);
    drawWallZ(-15);
    glPopMatrix();
	//Bedroom 2 walls
	glPushMatrix();     
	glTranslatef(-2.6,0,84);
    drawWallX(-15);
    glPopMatrix();
	//Bedroom 2 walls
	glPushMatrix();     
	glTranslatef(-2.6,0,69);
    drawWallZ(12);
    glPopMatrix();

	//Bedroom Door
	r = 0.7, g = 0.3, b = 0.3;
    glPushMatrix(); 
    glTranslatef(9.6,0,69);
    drawDoorZ();
    glPopMatrix();

	//Bathroom 2 walls
	r = 1.0, g = 1.0, b = 1.0;	
	glPushMatrix(); 
    glTranslatef(5.6,0,65);
    drawWallZ(-13);
    glPopMatrix();
	//Bathroom 2 walls
	glPushMatrix();     
	glTranslatef(-7.4,0,65);
    drawWallX(-6);
    glPopMatrix();
	//Bathroom 2 walls
	glPushMatrix();     
	glTranslatef(-7.4,0,59);
    drawWallZ(19);
    glPopMatrix();
	//Bathroom 2 walls
	glPushMatrix();     
	glTranslatef(9.6,0,65);
   	drawWallZ(2);
    glPopMatrix();
	//Bathroom 2 Door
	r = 0.7, g = 0.3, b = 0.3;
    glPushMatrix(); 
    glTranslatef(5.59,0,65);
    drawDoorZ();
    glPopMatrix();
	
	//Bedroom 3 walls
	r = 1.0, g = 1.0, b = 1.0;	
	glPushMatrix(); 
    glTranslatef(-7.4,0,59);
    drawWallZ(-6);
    glPopMatrix();
	//Bedroom 3 walls
	glPushMatrix();     
	glTranslatef(-13.4,0,59);
    drawWallX(25);
    glPopMatrix();
	//Bedroom 3 walls
	glPushMatrix();     
	glTranslatef(-13.4,0,84);
    drawWallZ(15);
    glPopMatrix();
	//Bedroom 3 Door
	r = 0.7, g = 0.3, b = 0.3;
    glPushMatrix(); 
    glTranslatef(-2.6,0,65);
    drawDoorX();
    glPopMatrix();

    glPushMatrix(); 
    glTranslatef(-30,0,-30);
    glPopMatrix();
	glutSwapBuffers();
} 

void processNormalKeys(unsigned char key, int xx, int yy) 
{ 	
	// Exit the game
	if(key == 27)
   		exit(0);    
    
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

int main(int argc, char **argv) 
{

	// Initialize the window with depth, double buffering and RGBA colors
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("The Middle of Nowhere");

	// Enable depth calculations
	glEnable(GL_DEPTH_TEST);

	// renderScene will be our main drawing routine invoked everytime
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	
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
	
	// Start the scene
	glutMainLoop();

	return 0;
}


