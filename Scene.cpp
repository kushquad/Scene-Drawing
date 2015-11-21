#include "Scene.h"
#include "Objects.h"
#include <time.h>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

// Active global color
float r,g,b;

// Main drawing function
void renderScene(void) 
{
	// Compute position if we move forward or left or right
	if (deltaMove || lstrafe || rstrafe)
		computePos(deltaMove);

	// Clear color and set background to blue sky
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 	glClearColor(0,0,0.3, 1.0f);
 	
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
	glColor3f(0.0f, 0.65f, 0.15f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, -0.01f, -100.0f);
		glVertex3f(-100.0f, -0.01f,  100.0f);
		glVertex3f( 100.0f, -0.01f,  100.0f);
		glVertex3f( 100.0f, -0.01f, -100.0f);
	glEnd();

	//All drawing routines
	drawHouseBoundary();
	drawHouseWalls();
	drawTiles();
	furnishBathroom();
	furnishBedroom();
	furnishKitchen();
	furnishLivingRoom();
	drawCeiling();
	
	if(parachutejump)
	{
		printf("%f\n",y);
		y -= 0.5;
		if(y<=3)
			parachutejump = 0;  
	}
	
	glutSwapBuffers();

	//Switch off interact toggle after drawing all objects
	interact = 0;
} 

int main(int argc, char **argv) 
{
	// Initialize graphics and plant a random seed
	initGraphics(argc, argv);
	srand(time(NULL));
	
	// renderScene will be our main drawing routine invoked everytime
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	
	// Start the scene
	glutMainLoop();
	return 0;
}


