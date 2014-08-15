#include<iostream>
#include<stdlib.h>
#include <glut.h>
#include<math.h>
#include<string>
#include<vector>
using namespace std;

//Variable initialisation
const int DELAY = 5 ;
const int MAX_POINTS = 100 ;
const int NO_OF_POINTS =  MAX_POINTS / 2 ;
 
float countx = 0;
float county = 0;
int delay=DELAY;
float dist[MAX_POINTS];
float movex[NO_OF_POINTS];
float movey[NO_OF_POINTS];
char xprint[32]; char yprint[32];

 extern vector <float> vect_coordx,vect_coordy;
 extern vector <float> :: iterator CoordIterx,CoordItery;
 extern float co_ordx,co_ordy;

float xm; //x co ordinate
float ym; //y co ordinate

void distance_calculate()
{
	int jump=0;
	float co_ordx1,co_ordx2;
	float co_ordy1,co_ordy2;

	CoordIterx=vect_coordx.begin();
	CoordItery=vect_coordy.begin();

	co_ordx1=*CoordIterx;
	co_ordy1=*CoordItery;

	xm=co_ordx1;
	ym=co_ordy1;

	while(true)
	{
		CoordIterx++; CoordItery++;
		if( CoordIterx == vect_coordx.end() || CoordItery == vect_coordy.end())
			break;
		co_ordx2 = *CoordIterx;
		co_ordy2 = *CoordItery;

		dist[jump] = (fabs(co_ordx2 - co_ordx1));

		if((co_ordx2 - co_ordx1)>0)
		movex[jump] = 1;

		else if((co_ordx2 - co_ordx1)<0)
		movex[jump] = -1;

		else
		movex[jump] = 0;

		movey[jump] = ((co_ordy2-co_ordy1)/(abs(co_ordx2 - co_ordx1)));

		jump++;

		co_ordx1=co_ordx2;
		co_ordy1=co_ordy2;
	}
}

void draw_axes()
{


	glLineWidth(3);
		glBegin(GL_LINES);
		glColor3f(1,1,1);
	   glVertex2f(0,-10000);
		glVertex2f(0,10000);
		glEnd();
		
		glLineWidth(3);
   		glBegin(GL_LINES);
		glColor3f(1,1,1);
	     glVertex2f(10000,0);
		glVertex2f(-10000,0);
		glEnd();
}

void draw_radius(int centerX,int centerY)
{
	int radius=1000;
	glLineWidth(1);
	glBegin(GL_LINE_LOOP);
		glColor3f(0.8,0,0);
		
		for(int outcir=0;outcir<5;outcir++)
		{
			for(int cir = 0; cir < 1000; cir++)
			{
				float theta = 2.0f * 3.1415926f * float(cir) / float(1000);//get the current angle

				float x = radius * cos(theta);//calculate the x component
				float y = radius * sin(theta);//calculate the y component

				glVertex2f(x + centerX, y + centerY);//output vertex
			}
			radius=radius+2000;
		}
    glEnd();
}

char *xTemp, *yTemp;
void disp_text(float xm, float ym)
{
	glColor3f(1,1,1);
	glRasterPos2f(xm+200,ym);
	sprintf_s(xprint, "( %0.2f ",xm);
	xTemp = &xprint[0];
	
	while( *xTemp)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,*xTemp++);

	glRasterPos2f(xm+1000,ym);
	sprintf_s(yprint, " , %0.2f )", ym);		
	yTemp = &yprint[0];

	while( *yTemp)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,*yTemp++);

		strcpy_s(xprint,"");
		strcpy_s(yprint,"");
}

void disp_static_points(char *msg)
{
	while( *msg)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*msg++);
}

void display()
{
	draw_axes(); //draws the x-axis and y-axis	

	draw_radius(0,0);

		glColor3f(0,0,1);
		glLineWidth(2);
		glBegin(GL_LINES);
		glVertex2f(xm-10,ym-10);
		glVertex2f(xm,ym);
		glEnd();
		glFlush();
		
		glColor3f(1,1,0);
		glRasterPos2f(50,-400);
		disp_static_points("[0,0]");

		glRasterPos2f(9100,-400);
		disp_static_points("[10000,0]");

		glRasterPos2f(-9950,-400);
		disp_static_points("[-10000,0]");

		glRasterPos2f(50,9600);
		disp_static_points("[0,10000]");

		glRasterPos2f(50,-9850);
		disp_static_points("[0,-10000]");
		
		glutSwapBuffers();
}

int index = 0 ;

void timer_function(int)
{		
	
		if( fabs(countx - dist[index]) < 10.1)
		{
			countx=county=0;
			index++;

			glColor3f(0,1,0);
		glPointSize(10);
		glBegin(GL_POINTS);
		glVertex2f(xm,ym);
		glEnd();

		disp_text(xm,ym);
		}
	if(countx <= dist[index])
		{
			xm = xm +movex[index]*10;
			countx=countx+10;
		}
		if(county <= dist[index])
		{
			ym = ym + movey[index]*10;
			county=county+10;
		}
		glutPostRedisplay();
		glutTimerFunc(delay,timer_function,0);
}	

void myinit()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1250,600);
	glutInitWindowPosition(0,0);
	glutCreateWindow ("Plotter");
	glutDisplayFunc(display);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor (0, 0, 0, 1);
    gluOrtho2D(-10000,10000,-10000,10000);
	distance_calculate();
	timer_function(50);
	glutMainLoop();
}
