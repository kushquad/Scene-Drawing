#include<fstream>

using namespace std;

//Toggle variables for interactive objects
int radioon=0;
int doorrot[3] = {0,0,0};
int tvon=0;
int fanon=0;

//Draw a radio
void drawBoomBox()
{	
	//Communication code with Python module to play a song
	static int radioon = 0;
	if(interact && euclidean(15,3,-10)<16)
		radioon ^=1;
		
	if(!radioon)
		remove("radiosignal.txt");
	else
		{
			ofstream file;
			file.open("radiosignal.txt",fstream::out);
			file.close();
		}

	// Speakers
	glPushMatrix();
		glTranslatef(0.25,0.25,0);
		glScaled(0.5,0.5,0.5);		
		glColor3f(1,0.5,0);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
		glTranslatef(3,0,0);
		glColor3f(1,0.5,0);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();
		
	glPushMatrix();
		glTranslatef(0.25,0.25,0.26);
		glScaled(0.4,0.4,0.02);		
		glColor3f(0.0,0.0,0.0);	
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
		glTranslatef(1.5/0.4,0,0);
		glColor3f(0.0,0.0,0.0);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
		glColor3f(1, 0.5, 0);	
		glTranslatef(0.25,0.25,0.27);
		glutSolidTorus(0.02,0.15,30,30);
		glutSolidTorus(0.005,0.04,30,30);	
		glTranslatef(1.5,0.0,0.0);
		glutSolidTorus(0.02,0.15,30,30);
		glutSolidTorus(0.005,0.04,30,30);	
	glPopMatrix();
	
	// Player
	glPushMatrix();
		glTranslatef(1,0.2,0);	
		glScaled(1,0.4,0.4);		
		glColor3f(51/255.0,204/255.0,1);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
		glTranslatef(0,-0.15,0.45);
		glScaled(0.3,0.08,0.25);	
		glTranslatef(0,3.5,-0.1);
		glScaled(1.75,0.35/0.08,0.9);	
		glColor3f(0.0,0.0,0.0);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();
	
	// Antennae	
	glPushMatrix();
		glTranslatef(0.9,0.5,0);	
		glRotatef(45,0,0,1);	
		glScaled(0.01,0.6,0.01);		
		glColor3f(0.2,0.2,0.2);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);	
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.12,0.6,0);	
		glRotatef(-30,0,0,1);	
		glScaled(0.01,0.5,0.01);		
		glColor3f(0.2,0.2,0.2);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);	
	glPopMatrix();
	
	//Glow Radio LED if on
	if(radioon)
	{
		glPushMatrix();
			glColor3f(1,1,0);
			glTranslatef(1,0.22,0.22);	
			glBegin(GL_QUADS);
				glVertex3f(0,0,0);
				glVertex3f(0,0.05,0);
				glVertex3f(0.05,0.05,0);
				glVertex3f(0.05,0,0);
			glEnd();
			glTranslatef(0.1,0,0);
			glBegin(GL_QUADS);
				glVertex3f(0,0,0);
				glVertex3f(0,0.05,0);
				glVertex3f(0.05,0.05,0);
				glVertex3f(0.05,0,0);
			glEnd();
		glPopMatrix();
	}
}

//Draw a hard coded font doormat
void drawDoorMat()
{
	//Doormat shape
	glPushMatrix();
		glTranslatef(31.6, 0.075, 29.2);
		glScalef(2,0.10,1);
		glColor3f(204.0/256.0,102.0/256.0,0);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();	

	// Writing on the mat
	glPushMatrix();
		glTranslatef(10.75,-0.03,0);
		glColor3d(1.0, 1.0, 1.0);
		glScalef(0.66,1,1);
		glBegin(GL_LINES);
			// H
			glVertex3f(32.9, 0.16, 29.6);
			glVertex3f(32.9, 0.16, 28.8);
			glVertex3f(32.9, 0.16, 29.2);
			glVertex3f(32.3, 0.16, 29.2);
			glVertex3f(32.3, 0.16, 29.6);
			glVertex3f(32.3, 0.16, 28.8);
			// O
			glVertex3f(32.2, 0.17, 29.6);
			glVertex3f(32.2, 0.17, 28.8);
			glVertex3f(32.2, 0.17, 28.8);
			glVertex3f(31.6, 0.17, 28.8);
			glVertex3f(31.6, 0.17, 28.8);
			glVertex3f(31.6, 0.17, 29.6);
			glVertex3f(31.6, 0.17, 29.6);
			glVertex3f(32.2, 0.17, 29.6);
			// M
			glVertex3f(31.5, 0.17, 28.8);
			glVertex3f(31.5, 0.17, 29.6);
			glVertex3f(31.5, 0.17, 29.6);
			glVertex3f(31.2, 0.17, 29.2);
			glVertex3f(31.2, 0.17, 29.2);
			glVertex3f(30.9, 0.17, 29.6);
			glVertex3f(30.9, 0.17, 29.6);
			glVertex3f(30.9, 0.17, 28.8);
			// E
			glVertex3f(30.8, 0.17, 29.6);
			glVertex3f(30.8, 0.17, 28.8);
			glVertex3f(30.8, 0.17, 29.6);
			glVertex3f(30.2, 0.17, 29.6);
			glVertex3f(30.8, 0.17, 29.2);
			glVertex3f(30.2, 0.17, 29.2);
			glVertex3f(30.8, 0.17, 28.8);
			glVertex3f(30.2, 0.17, 28.8);
		glEnd();	
	glPopMatrix();
}

// Figure out which door is closest to player for interaction
int closetodoor(int doornum)
{
	if(doornum==1)
		return euclidean(0,2,0)<16;
	if(doornum==2)
		return euclidean(8,2,-9)<16;
	if(doornum==3)
		return euclidean(14,2,-9)<16;
}

// Draw door and animate if required (if interacted with player)
void drawDoor(int doornum)
{
	//Door
	glPushMatrix();
		glTranslatef(+0.75,0,-0.25);
		glRotatef(-abs(doorrot[doornum-1]),0,1,0);
		glTranslatef(-0.75,0,+0.25);
		glPushMatrix();
			glColor3f(102/255.0, 34/255.0, 0);
			glScalef(1.5,5.0,0.5);
			glutSolidCube(1);
			glColor3f(0,0,0);
			glutWireCube(1);
			glColor3f(1,179/255.0,26/255.0);
		glPopMatrix();
	
		//Doorknob
		glTranslatef(-0.55,1.0,0.25);
		glScalef(1,1,0.6);
		glutSolidSphere(0.1,20,20);

		//Interaction check
		if((doorrot[doornum-1]>0 && doorrot[doornum-1]<90)||(doorrot[doornum-1]<0 && doorrot[doornum-1]>-90))
			doorrot[doornum-1]+=5;
		if(doorrot[doornum-1]==0 && interact==1 && closetodoor(doornum))
			doorrot[doornum-1]=5;
		if(doorrot[doornum-1]==90 && interact==1 && closetodoor(doornum))
			doorrot[doornum-1]=-85;
	glPopMatrix();
}

	
void standsides(double thick, double breadth, double len)
{
	// Draws the legs/ sides for each stand/ table
	glPushMatrix();
		glTranslated(0, len / 2, 0);
		glScaled(thick, len, breadth);
		glColor3f(51.0/256.0,0,0);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();
}

// Sofa is drawn using scaled cubes and standsides()
void drawSofa(double tableWid, double tableThick, double tableBreadth, double legthick, double legLen)
{
	double dist = 0.95* tableWid / 2.0 - legthick / 2.0;

	// Legs of the sofa
	glPushMatrix();
		double legBreadth = 0.90*tableBreadth;
		glTranslated(dist, 0, 0);
		standsides(legthick, legBreadth, legLen);
	glPopMatrix();

	glPushMatrix();
		glTranslated(-dist, 0, 0);
		standsides(legthick, legBreadth, legLen);
	glPopMatrix();

	// Sofa Seat
	glPushMatrix();
		glTranslated(0, legLen, 0);
		glScaled(tableWid, tableThick, tableBreadth);
		glColor3f(1,1,0.5);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();

	// Sofa Back
	glPushMatrix();
		glRotated(-90,1,0,0);	
		glTranslated(0, 1.40*tableThick, 1.005*(tableBreadth+tableThick/2.0));
		glScaled(tableWid, tableThick/2, tableBreadth);
		glColor3f(1,1,0.5);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();
}

// Draw an empty basin (top missing) - to be used as a sink and bathtub
void drawBasin(float size)
{
	glColor3f(0.99,0.99,0.98);
	glPushMatrix();
		glTranslatef(0,-size/6.0,0);
		glScalef(2*size,size/20.0,size*0.95);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();
	
	glColor3f(0.67,0.67,0.98);
	glPushMatrix();
		glTranslatef(-size,size/18.0,0);
		glScalef(size/20.0,size/2.0,size*0.96);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();
	
	glColor3f(0.67,0.67,0.98);
	glPushMatrix();
		glTranslatef(size,size/18.0,0);
		glScalef(size/20.0,size/2.0,size*0.96);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();
	
	glColor3f(0.67,0.67,0.98);
	glPushMatrix();
		glTranslatef(0,size/18.0,-size/2.0);
		glScalef(1.95*size,size/2.0,size*0.04);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();
	
	glColor3f(0.67,0.67,0.98);
	glPushMatrix();
		glTranslatef(0,size/18.0,size/2.0);
		glScalef(1.95*size,size/2.0,size*0.04);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();
}

// Draw a fan using a sphere and three rectangles
// Use simple 0t = 0 + wt equation for fan physics
void drawFan(float len)
{
	static int fanon = 0;
	static float fanrotateangle = 0;
	static float fanrotatevelocity = 0;
	
	glColor3f(0,0,0);
	if(interact && euclidean(10,0.5,-5)<16)
		fanon^=1;
	
	//Fan velocity updated depending on switch flag
	fanrotatevelocity = (fanon)?((fanrotatevelocity<30)?(fanrotatevelocity+0.1):(30))
							   :((fanrotatevelocity>0)?(fanrotatevelocity-0.1):(0));
		
	fanrotateangle += fanrotatevelocity;
	if(fanrotateangle>=360)
		fanrotateangle-=360;
	
	glTranslatef(0,0,-2.0);
	glutSolidSphere(len/10.0,20,20);
	glRotatef(fanrotateangle,0,0,1);
	glBegin(GL_QUADS);
		glVertex3f(len/18.0,0,0);
		glVertex3f(len/18.0,len/2.0,0);
		glVertex3f(-len/18.0,len/2.0,0);
		glVertex3f(-len/18.0,0,0);
	glEnd();
	glRotatef(120,0,0,1);
	glBegin(GL_QUADS);
		glVertex3f(len/18.0,0,0);
		glVertex3f(len/18.0,len/2.0,0);
		glVertex3f(-len/18.0,len/2.0,0);
		glVertex3f(-len/18.0,0,0);
	glEnd();
	glRotatef(120,0,0,1);
	glBegin(GL_QUADS);
		glVertex3f(len/18.0,0,0);
		glVertex3f(len/18.0,len/2.0,0);
		glVertex3f(-len/18.0,len/2.0,0);
		glVertex3f(-len/18.0,0,0);
	glEnd();
	glRotatef(120,0,0,1);
}

// Shoe rack is drawn using standsides() and scaled cubes
void drawShoerack(double tableWid, double tableThick, double tableBreadth, double legthick, double legLen)
{
	double dist = 0.95* tableWid / 2.0 - legthick / 2.0;

	// Sides
	glPushMatrix();
		double legBreadth = 0.90*tableBreadth;
		glTranslated(dist, 0, 0);
		standsides(legthick, legBreadth, legLen);
	glPopMatrix();

	glPushMatrix();
		glTranslated(-1 * dist, 0, 0);
		standsides(legthick, legBreadth, legLen);
	glPopMatrix();

	// Top of Shoe Rack
	glPushMatrix();
		glTranslated(0, legLen, 0);
		glScaled(tableWid, tableThick, tableBreadth);
		glColor3f(51.0/256.0,0,0);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();

	// Intermediate slanted levels
	glPushMatrix();
		glRotated(-10,1,0,0);
		glTranslated(0, legLen/3.0, 0);
		glScaled(tableWid, tableThick, tableBreadth);
		glColor3f(51.0/256.0,0,0);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
		glRotated(-10,1,0,0);	
		glTranslated(0, 2*legLen/3.0, 0);	
		glScaled(tableWid, tableThick, tableBreadth);
		glColor3f(51.0/256.0,0,0);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();

	// Bottom level
	glPushMatrix();
		glTranslated(0, 0.04, 0);
		glScaled(tableWid, tableThick, tableBreadth);
		glColor3f(51.0/256.0,0,0);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();
}

void drawTable(float len)
{
	//Base
	glColor3f(0.2,0.05,0);
	glPushMatrix();
		glTranslatef(0,0.2*len,0);
		glScalef(len,0.05*len,0.5*len);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();
	
	//All legs
	glColor3f(0.2,0.05,0);
	glPushMatrix();
		glTranslatef(-0.475*len,0.085*len,-0.225*len);
		glScalef(0.05*len,0.18*len,0.05*len);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();
	
	glColor3f(0.2,0.05,0);
	glPushMatrix();
		glTranslatef(-0.475*len,0.085*len,0.225*len);
		glScalef(0.05*len,0.18*len,0.05*len);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();
	
	glColor3f(0.2,0.05,0);
	glPushMatrix();
		glTranslatef(0.475*len,0.085*len,0.225*len);
		glScalef(0.05*len,0.18*len,0.05*len);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();
	
	glColor3f(0.2,0.05,0);
	glPushMatrix();
		glTranslatef(0.475*len,0.085*len,-0.225*len);
		glScalef(0.05*len,0.18*len,0.05*len);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();
}

//Simple cuboid used for counter rendering
void drawCounter(float len,float rcol, float gcol, float bcol)
{
	glColor3f(rcol, gcol, bcol);
	glPushMatrix();
		glScalef(len,0.6*len,0.5*len);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();
}

// Uses the counter drawn from above and two tori to draw the stove
// Is interactive, the tori glow yellow and flicker
void drawGasStove()
{
	static int gasstove = 0;
	glPushMatrix();
		glTranslatef(0.8,-0.2,0);
		drawCounter(0.90,0.1,0.1,0.1);
		glColor3f(0,0,0);
	
		if(interact)
		{
			if(gasstove>0)
				gasstove=0;
			else
			{
				if(euclidean(3,3,-16)<16)
					gasstove=1;
				else
					gasstove=0;
			}
		}
			
		if(gasstove>0)
		{
			glColor3f(gasstove/10.0,gasstove/10.0,gasstove*0.01);
			gasstove = (gasstove==9)?(10):(gasstove%10+1);
		}
		
		glPushMatrix();
			glTranslatef(0.25,0.28,0);
			glRotatef(90,1,0,0);
			glutSolidTorus(0.01,0.12,20,20);
		glPopMatrix();
		glPushMatrix();	
			glTranslatef(-0.25,0.28,0);
			glRotatef(90,1,0,0);
			glutSolidTorus(0.01,0.12,20,20);
		glPopMatrix();
	glPopMatrix();
}

// Cuboid wall drawing with one face coloured for painted walls
void drawWall(float len, float colr, float colg, float colb)
{
	glColor3f(0.95,0.95,0.95);
	glPushMatrix();
		glScalef(len,5.0,0.5);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();
	glColor3f(colr,colg,colb);
	glBegin(GL_QUADS);
		glVertex3f(len/2.0,2.5,0.26);
		glVertex3f(len/2.0,-2.49,0.26);
		glVertex3f(-len/2.0,-2.49,0.26);
		glVertex3f(-len/2.0,2.5,0.26);
	glEnd();
}

// Combination of walls to leave a central empty space for the window
void drawWindowedWall(float len)
{
	glColor3f(0.98,0.98,0.98);
	glPushMatrix();
		glTranslatef(-0.3*len,0,0);
		glScalef(len/2.5,5.0,0.5);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();
	
	glColor3f(0.98,0.98,0.98);
	glPushMatrix();
		glTranslatef(0.3*len,0,0);
		glScalef(len/2.5,5.0,0.5);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();
	
	glColor3f(0.98,0.98,0.98);
	glPushMatrix();
		glTranslatef(0,2.125,0);
		glScalef(len/5.0,0.75,0.5);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();
	
	glColor3f(0.98,0.98,0.98);
	glPushMatrix();
		glTranslatef(0,0.25,0);
		glScalef(len/5.0,0.75,0.5);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();
}

// Uses the table object and adds a cuboid for mattress and pillow
void drawBed()
{
	drawTable(3);
	glPushMatrix();
		glColor3f(1, 153/255.0, 187/255.0);
		glTranslatef(0,0.8,0);
		glScalef(3,0.2,1.48);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(0.95, 0.98, 0.97);
		glTranslatef(1.25,0.95,0);
		glScalef(0.4,0.1,1.2);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);
	glPopMatrix();
}

// Constructs all boundary walls and the main door
void drawHouseBoundary()
{
	glPushMatrix();
		glTranslatef(2.5,0,0);
		glPushMatrix();
			glTranslatef(0.75,0,0);
			drawDoor(1);
			glTranslatef(8.25,0,0);
			glRotatef(-180,1,0,0);
			drawWall(15,0.8,0.8,0);
			glPushMatrix();
				glTranslatef(7.75,0,4.25);
				glRotatef(90,0,1,0);
				glRotatef(180,0,0,1);
				drawWindowedWall(9);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(7.75,0,12.25);
				glRotatef(90,0,1,0);
				glRotatef(180,0,0,1);
				drawWindowedWall(7);
			glPopMatrix();
			glTranslatef(4.5,0,16);
			glRotatef(-180,1,0,0);
			drawWall(7,0.8,0.4,0.4);
			glTranslatef(-7,0,0);
			drawWall(7,0.1,0.1,0.8);
			glTranslatef(-6,0,0);
			drawWall(5,1,214/255.0,0.2);
			glPushMatrix();
				glTranslatef(-2.75,0,2.75);
				glRotatef(90,0,1,0);
				drawWindowedWall(6);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-2.75,0,10.75);
				glRotatef(-90,0,1,0);
				glRotatef(-180,1,0,0);
				drawWall(10,0.98,0.98,0.98);
			glPopMatrix();
			glTranslatef(-1.75,0,16);
			glRotatef(180,1,0,0);
			drawWall(2.5,0.98,0.98,0.98);
		glPopMatrix();
	glPopMatrix();
}

// Constructs the inner walls of the house
void drawHouseWalls()
{
	glPushMatrix();
		glTranslatef(5.5,0,-9);
		glPushMatrix();
			glTranslatef(1,0,0);
			drawDoor(2);
			glTranslatef(3.75,0,0);
			drawWall(6,0.95,0.95,0.95);
			glTranslatef(3.75,0,0);
			drawDoor(3);
			glTranslatef(3.125,0,0);
			drawWall(4.75,0.95,0.95,0.95);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,0,-3.25);
			glRotatef(-90,0,1,0);
			glRotatef(180,1,0,0);
			drawWall(7,0.1,0.8,0.8);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(7,0,-3.5);
			glRotatef(-90,0,1,0);
			drawWall(6.5,0.1,0.8,0.8);
		glPopMatrix();
	glPopMatrix();
}

// Draw the floor for the house, with a special color for the bathroom
void drawTiles()
{
	glBegin(GL_QUADS);
		glColor3f(1,229/255.0,179/255.0);
		glVertex3f(0,0,0);
		glVertex3f(19,0,0);
		glVertex3f(19,0,-9);
		glVertex3f(0,0,-9);
		
		glVertex3f(0,0,-9);
		glVertex3f(0,0,-16);
		glVertex3f(5.5,0,-16);
		glVertex3f(5.5,0,-9);
		
		glVertex3f(12.5,0,-16);
		glVertex3f(12.5,0,-9);
		glVertex3f(19.5,0,-9);
		glVertex3f(19.5,0,-16);
		
		glColor3f(102/255.0, 217/255.0, 1);
		glVertex3f(5.5,0,-16);
		glVertex3f(5.5,0,-9);
		glVertex3f(12.5,0,-9);
		glVertex3f(12.5,0,-16);
	glEnd();
}

// Common ceiling for the house, which can be toggled on or off
void drawCeiling()
{
	if(ceilingon)
	{
		glColor3f(0.97,0.97,0.97);
		glBegin(GL_QUADS);
			glVertex3f(0,2.505,0.5);
			glVertex3f(19,2.505,0.5);
			glVertex3f(19,2.505,-16);
			glVertex3f(0,2.505,-16);
		glEnd();
	}
}

// Use the basin object to make a sink and bathtub
// Add a table for fun
void furnishBathroom()
{
	glPushMatrix();
		glTranslatef(5.5,0,-9);
		glPushMatrix();
			glTranslatef(4.75,0.4,-5.5);
			drawBasin(2);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.6,0.75,-2.5);
			glRotatef(-90,0,1,0);
			drawBasin(0.75);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(5,0,-1);
			drawTable(2);
		glPopMatrix();
	glPopMatrix();
}

// Bed, table and radio for furnishing
void furnishBedroom()
{
	glPushMatrix();
		glTranslatef(12.5,0,-9);
		glPushMatrix();
			glTranslatef(2,0,-5.5);
			glRotatef(180,0,1,0);
			drawBed();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(5,0,-1);
			drawTable(2.5);
			glTranslatef(1.0,0.6,0);
			glRotatef(180,0,1,0);
			drawBoomBox();
		glPopMatrix();
	glPopMatrix();
}

// Features two counters, gas stove, teapot and sink
void furnishKitchen()
{
	glPushMatrix();
		glTranslatef(0,0,-9);
		glPushMatrix();
			glTranslatef(4.5,0.75,-6.4);
			drawBasin(0.75);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(2,0,-6);
			drawCounter(2.8,217/255.0, 1, 179/255.0);
			glPushMatrix();
				glTranslatef(0,1,0);
				drawGasStove();
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(5,0,-1.5);
			glRotatef(-90,0,1,0);
			drawCounter(3,217/255.0, 1, 179/255.0);
			glPushMatrix();
				glTranslatef(0,1.1,0);
				glColor3f(0.4,0.4,0.1);
				glutSolidTeapot(0.3);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

// Check toggles for the TV and fan
// Draw the sofa, fan, TV, chairs, dining table, shoerack
void furnishLivingRoom()
{
	if(interact)
	{
		if(euclidean(14,3,0)<16)
			tvon ^= 1;
		fanon ^= 1;
	}
	
	glPushMatrix();
		glTranslatef(8,0,-2);
		drawTable(3);
		glPushMatrix();
			glTranslatef(2,0,0);
			glRotatef(-90,0,1,0);
			drawSofa(0.8, 0.3, 1, 0.1, 0.5);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-2,0,0);
			glRotatef(90,0,1,0);
			drawSofa(0.8, 0.3, 1, 0.1, 0.5);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,0,-1);
			drawSofa(0.8, 0.3, 1, 0.1, 0.5);
			glTranslatef(-1,0,0);
			drawSofa(0.8, 0.3, 1, 0.1, 0.5);
		glPopMatrix();
		glPushMatrix();
			glRotatef(180,0,-1,0);
			glTranslatef(0,0,-1);
			drawSofa(0.8, 0.3, 1, 0.1, 0.5);
			glTranslatef(1,0,0);
			drawSofa(0.8, 0.3, 1, 0.1, 0.5);
		glPopMatrix();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(15,0,-6);
		drawSofa(3, 0.3, 1, 0.1, 0.5);
		glPushMatrix();
			glTranslatef(2.5,0,1);
			glRotatef(-45,0,1,0);
			drawSofa(1, 0.3, 1, 0.1, 0.5);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-2.5,0,1);
			glRotatef(45,0,1,0);
			drawSofa(1, 0.3, 1, 0.1, 0.5);
		glPopMatrix();
		glTranslatef(0,0,2);
		drawTable(2.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.7,0,-2.5);
		glRotatef(-90,0,1,0);
		drawShoerack(2.5, 0.08, 1, 0.1, 1.2);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(14.5,1.5,-0.3);
		glScalef(3,1.5,0.125);
		glutSolidCube(1);
		glColor3f(0,0,0);
		glutWireCube(1);		
	glPopMatrix();

	// Draw the TV
	// Turned on TV features random colored bars for animation
	glPushMatrix();
		glTranslatef(13.1,0.75,-0.35);
		if(tvon==1)
		{
			for(int i=0;i<7;i++)
			{
				glColor3f((rand()%256)/255.0,(rand()%256)/255.0,(rand()%256)/255.0);					
				glBegin(GL_QUADS);
					glVertex3f(0,0.1,-0.05);
					glVertex3f(2.8*((i+1)/7.0),0.1,-0.05);
					glVertex3f(2.8*((i+1)/7.0),1.4,-0.05);
					glVertex3f(0,1.4,-0.05);
				glEnd();
			}
		}
	glPopMatrix();
	
	// Draw the fan
	// Animation code for the fan is written in the drawFan() routine
	glPushMatrix();
		glTranslatef(10,0.5,-5);
		glRotatef(90,1,0,0);
		drawFan(3);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(34.75,0,30);
		glRotatef(180,0,1,0);
		drawDoorMat();
	glPopMatrix();
}
