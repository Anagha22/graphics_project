#include<stdio.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
int c_eggs=0,m_eggs=0,level_count=1,points=0;
int p=1;
// for incrementing the points based on color
int d=0;
// for color selection
int egg_xc,egg_yc;
// for coordinates of egg
int basket_x,basket_y;
// for coordinates of basket
int a=500,b=500; // for default size of the screen
int s=0;
// for menu option
int d_eggs=0;
int speed_1=1,speed_2=2,speed_3=3,speed_4=4;
int w=48,h=48,t=10,e=9,g=12;
void myinit();
void start_screen(int,int);
void egg();
void basket(int,int);
void print_score();
void score();
void egg_start();
void display(void);
void basket_set(int,int);
void myReshape(int,int);
void keys(unsigned char,int,int);

void myinit()
{
	glViewport(0,0,a,b);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,(GLdouble)a,0,(GLdouble)b);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

void start_screen(int i,int j)
{

	//The writing on the screen: CATCH OR HATCH
	glColor3f(0,1,0);
	glRasterPos2i(120,260);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,"CATCH");
	glColor3f(1,1,1);
	glRasterPos2i(210,260);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,"OR");
	glColor3f(1,0,0);
	glRasterPos2i(250,260);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,"HATCH");
	glColor3f(1,0,0);
	glRasterPos2i(20,170);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,"Instructions:");
	glColor3f(1,0,0);
	glRasterPos2i(40,150);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,"Q-quit the game");
	glColor3f(1,0,0);
	glRasterPos2i(40,130);
        glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,"S-start the game");
	
        glColor3f(1,1,1);

}

//To draw the egg
void egg()
{
	float x,y,z;
	int t;
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	for(t=0;t<=360;t+=1)
	{	
		x = egg_xc+8*(cos(t));
		y = egg_yc+16*(sin(t));
		z = 0;
		glVertex3f(x,y,z);
	}
	glEnd();
}

//To draw the basket
void basket(int i,int j)
{
	j=10;					//The initial position of the basket
	if(i>=a-60)
		i=a-60;
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);
	glVertex2f(0.0+i,30.0+j);
	glVertex2f(10.0+i,10.0+j);
	glVertex2f(50.0+i,10.0+j);
	glVertex2f(60.0+i,30.0+j);
	glEnd();
}




void print_score()
{
	printf("\nLevel reached: %d\n\n",level_count);
	printf("\n\n\nyour score=%d\n\n",points);
	getchar();
	exit(0);
}

void egg_start()
{
	egg_yc=375;

	//Game over condition
	if(m_eggs>=10)
	{
		printf("\n\n\t\t\t\tGAME OVER\n\n");
		print_score();
	}
	d_eggs++;
	
		switch(rand()%3)
		{
			case 0:
				egg_xc=105;
				 
				break;
			case 1:
				egg_xc=245;
				
				break;
			case 2:
				egg_xc=380;
				 
				break;
			
		}
}




void score()
{
	if(egg_yc<=50 && (egg_xc>=basket_x && egg_xc<=basket_x+60))
	{
		printf("\a");
		c_eggs++;
		points+=p;
		egg_yc=-10;
	}
	m_eggs=d_eggs-c_eggs;
}

void display(void)
{
	int i;
        glClear(GL_COLOR_BUFFER_BIT);
	
	

	//Start condition
	if(s>=1)
	{

	glBegin(GL_QUADS);			//SKY
	
	glColor3f(0.6, 0.5, 1.0);
	glVertex2f(1000,0);
	glVertex2f(1000,1870);
	glVertex2i(-600,150);
	glVertex2i(500,150);
	glFlush();
	glEnd();
	glBegin(GL_QUADS);			//ground
	glColor3f(0.2,0.7,0.2);
	glVertex2f(-600,150);
	glVertex2f(500,150);
	glVertex2i(-600,0);
	glVertex2i(500,0);
	glFlush();
	glEnd();
		//To display the level on the screen
		if(level_count==1)
		{
			glColor3f(1,1,1);
			glRasterPos2i(400,300);
			glutBitmapString(GLUT_BITMAP_8_BY_13,"LEVEL 1");
		}
		else if(level_count==2)
		{
			glColor3f(1,1,1);
			glRasterPos2i(400,300);
			glutBitmapString(GLUT_BITMAP_8_BY_13,"LEVEL 2");
		}
		else if(level_count==3)
		{
			glColor3f(1,1,1);
			glRasterPos2i(400,300);
			glutBitmapString(GLUT_BITMAP_8_BY_13,"LEVEL 3");
		}
		if(level_count==4)
		{		
			glColor3f(1,1,1);
			glRasterPos2i(400,300);
                        glutBitmapString(GLUT_BITMAP_8_BY_13,"LEVEL 4");
		}

		

		//level 1
		if(egg_yc<=10)
			egg_start();
                egg();
		basket(basket_x,basket_y);

		//level 2
		if(c_eggs>=2)
		{
			egg_yc-=speed_2;
			level_count=2;

		}

		//level 3
		if(c_eggs>=20)
		{
			egg_yc-=speed_3;
			level_count=3;
		}

		//level 4
		if(c_eggs>=30)
		{
		egg_yc-=speed_4;
		level_count=4;
		}
		else
			egg_yc-=speed_1;
		score();
	}
	else
		start_screen(40,300);

	glFlush();
	glutSwapBuffers();
}


void basket_set(int a,int b)
{
	basket_x=a;
	basket_y=b;
	glutPostRedisplay();
}


void myReshape(int w,int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,(GLdouble)w,0.0,(GLdouble)h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0,0,w,h);
	a=w;
	b=h;
}

void keys(unsigned char key,int x,int y)
{
	if(key=='q'||key=='Q')					//Q-quit the game
	{
		printf("\n\n\n\t\tQUIT BY PLAYER\n\n");
		print_score();
	}
	if(key=='s'||key=='S') 					//S-start the game
		s+=1;
	if(key=='a'||key=='A')					//A-to move the egg towards left
	{
		egg_xc-=10;
		if(egg_xc<=0) 
			egg_xc=10;
	}
	if(key=='d'||key=='D')					//D-to move the egg towards right
	{
		egg_xc+=10;
		if(egg_xc>=500) 
			egg_xc=490;
	}a;
}


int main(int argc,char **argv)
{
	printf("\nHow to Play..?\n\n1-The objective of the game is to catch the eggs in the basket.\n\t To move Basket use mouse.\n");
	printf("\n 2-To Start, press key 's' or 'S' or \n\tClick Right mouse button then click 'Start Game'.\n");
	printf("\n 3-To Quit manually, press key 'q' or 'Q'.\n");
	printf("\n\n RULES : If the player misses 10 eggs,then 'Game Over'.\n");
	printf("\nFor each level, speed is doubled\n\n");
	printf("\n\nBEST OF LUCK\n");
	

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(a,b);
	glutCreateWindow("EGG GAME");
	myinit();

        glutDisplayFunc(display);
	glutKeyboardFunc(keys);
	glutPassiveMotionFunc(basket_set);			//Mouse moves
	glutIdleFunc(display);
	glutReshapeFunc(myReshape);
	glutMainLoop();
}



