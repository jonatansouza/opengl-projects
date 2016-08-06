/**
*
*@autor Jonatan Souza
*
**/

#include <stdio.h>
#include <GL/glut.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include "cylinder.h"

#define SENS_ROT 5.0
#define SENS_OBS 20.0
#define SENS_TRANSL 30.0

void display();
void reshape(int w, int h);
void keyboard( unsigned char tecla, int x, int y);
void desenhaEixos();
void projecao();
void mouse( int button, int state, int x, int y );
void motion( int x, int y );
void initialize();
void formas();

float anilha = 4;
float pullDown = 0;
float turnFan = 0;
float biceps = 5;
float dropMe = 0;

int hour = 0;
int minutes = 0;
int seconds = 0;

void drawHalfSphere(int scaley, int scalex, GLfloat r);
void material();

void drawBed();
void drawBar();
void drawHead();
void drawMan();
void drawBody();
void drawArm();
void drawLeg();
void drawMoveArm();
void drawBedFeet();
void modelBedFeet();
void drawFloor();
void drawChessFloor();
void drawWall();
void drawDeck();
void drawSuport();
void drawBarSuport(float anilhaSize);
void drawFan();
void drawFanBlade();
void drawClock();
void drawDrop();
void drawBucket();

//global variables
float win = 10.0f;
float aspecto;
float angulo = 30.0f;
int rotateme = 0;


GLfloat rotX=0.0, rotY=0.0, rotX_ini, rotY_ini;
GLfloat obsX=0.0, obsY=0.0, obsZ=280.0, obsX_ini, obsY_ini, obsZ_ini;
int x_ini, y_ini, bot;


void initialize(){

GLfloat ambient[] = {0.5, 0.5, 0.5 ,1.0};
GLfloat difusa[] = {0.5,0.5,0.5,1};
GLfloat especular[] = {1,1,1,1};
GLfloat posicao[] = {0,20,0,0};

glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

//difusa da um ambiente sombrado
glLightfv(GL_LIGHT0, GL_DIFFUSE, ambient);
glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa);
glLightfv(GL_LIGHT0, GL_DIFFUSE, especular);
glLightfv(GL_LIGHT0, GL_POSITION, posicao);


glLightModelfv( GL_LIGHT_MODEL_AMBIENT, ambient );
glEnable( GL_LIGHTING );
glEnable(GL_LIGHT0);
glEnable( GL_COLOR_MATERIAL );
glEnable(GL_NORMALIZE);
glShadeModel(GL_SMOOTH);
glEnable( GL_DEPTH_TEST );
}


void setInitTimeClock(){
	time_t rawtime;
	struct tm *info;
	time (&rawtime);
	info = localtime(&rawtime);
	hour = 30*info->tm_hour;
	minutes = 6*info->tm_min;
	seconds = 6*info->tm_sec;
 
}

void timerClock(int i){
	seconds ++;
	if(seconds == 360){
		minutes++;
		seconds = 0;
	}
	if(minutes == 360){
		hour ++;
		minutes = 0;
	}
	glutPostRedisplay();
	glutTimerFunc(1000, timerClock, 1);


}

void timer(int i){
	if(pullDown > 0){
		pullDown -= (10/anilha)/10;
	}
	turnFan += 50;
	rotateme = pullDown*7;
	dropMe -= 6;
	if(dropMe < (-17)){
		dropMe = 80;
	}
	glutPostRedisplay();
	glutTimerFunc(60, timer, 1);

}


int main (int argc, char *argv[]){
	//escopo de criacao de janela
	setInitTimeClock();
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(10, 10);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("GYM");
	//fim do escopo de criacao

	//escopo de registro de callbacks
	initialize();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutTimerFunc(60, timer, 0);
	glutTimerFunc(1000, timerClock, 0);
	//fim do escopo de registro	
	
	//demais
	glutMainLoop();
	return 0;
}


void drawHalfSphere(int scaley, int scalex, GLfloat r) {
   int i, j;
   GLfloat v[scalex*scaley][3];
 
   for (i=0; i<scalex; ++i) {
     for (j=0; j<scaley; ++j) {
       v[i*scaley+j][0]=r*cos(j*2*M_PI/scaley)*cos(i*M_PI/(2*scalex));
       v[i*scaley+j][1]=r*sin(i*M_PI/(2*scalex));
       v[i*scaley+j][2]=r*sin(j*2*M_PI/scaley)*cos(i*M_PI/(2*scalex));
     }
   }
 
   glBegin(GL_QUADS);
     for (i=0; i<scalex-1; ++i) {
       for (j=0; j<scaley; ++j) {
         glVertex3fv(v[i*scaley+j]);
         glVertex3fv(v[i*scaley+(j+1)%scaley]);
         glVertex3fv(v[(i+1)*scaley+(j+1)%scaley]);
         glVertex3fv(v[(i+1)*scaley+j]);
       }
     }
   glEnd();

}

void drawBar(){
	int barSize = 70;
	glPushMatrix();
		glTranslatef(-(barSize/2),0,1.2);
		glRotatef(90,0,1,0);
	
	//barra central
		glPushMatrix();
			glColor3f(0.5,0.5,0.5);
			drawCylinder(1,barSize);
		glPopMatrix();
	//anilha direita
		glPushMatrix();
			glColor3f(0.7,0.7,0.7);
			glTranslatef(0,0,2);
			drawCylinder(anilha,2);
		glPopMatrix();
	//anilha esquerda
		glPushMatrix();
			glColor3f(0.7,0.7,0.7);
			glTranslatef(0,0,barSize-4);
			drawCylinder(anilha,2);
		glPopMatrix();
	glPopMatrix();
	//anti - BRAÇOS
	glPushMatrix();
		glTranslatef(-19,0,0);
		glRotatef(rotateme*0.3, 0,0,1);
		glRotatef(9, 0,0,1);
		drawArm();
	glPopMatrix();
	glPushMatrix();
		glScalef(-1,1,1);
		glTranslatef(-19,0,0);
		glRotatef(rotateme*0.3, 0,0,1);
		glRotatef(9, 0,0,1);
		drawArm();
	glPopMatrix();
glPopMatrix();

}



void drawHead(){
	


	glPushMatrix();
		glScalef(0.5,0.7,0.5);
		glColor3f(1,1,0.8);
		glutSolidSphere(10,50,50);
	glPopMatrix();
	//cabelo
	glPushMatrix();
		glColor3f(0,0,0);
		glTranslatef(0,5,0);
		glScalef(1,0.7,1);
		drawHalfSphere(20,20,4);
	glPopMatrix();
	//nariz
	glPushMatrix();
		glColor3f(1,1,0.8);
		glTranslatef(0,0,5);
		glutSolidCone(0.5,2,10,10);
	glPopMatrix();
	//sombracelha
	glPushMatrix();
		glColor3f(0,0,0);
		glLineWidth(3);
		glBegin(GL_LINES);
			glVertex3f(-3, 4, 5);
			glVertex3f(-0.5, 2, 5);
		glEnd();
	glPopMatrix();
	//sombracelha
	glPushMatrix();
		glScalef(-1,1,1);
		glColor3f(0,0,0);
		glLineWidth(3);
		glBegin(GL_LINES);
			glVertex3f(-3, 4, 5);
			glVertex3f(-0.5, 2, 5);
		glEnd();
	glPopMatrix();


	glPushMatrix();
		glTranslatef(-2,2,5);
		glColor3f(0.8,0.8,0);
		drawCylinder(1,0.5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(2,2,5);
		drawCylinder(1,0.5);
	glPopMatrix();
	//boca
	glPushMatrix();
		glColor3f(0,0,0);
		glLineWidth(3);
		glBegin(GL_LINES);
			glVertex3f(-2, -3, 4.5);
			glVertex3f(2, -5, 4.5);
		glEnd();
	glPopMatrix();
}

void drawBody(){
	glPushMatrix();
		glColor3f(0,0.8,0.5);
		glScalef(1,0.5,1);
		drawCylinderDeform(10,30,0.7);	
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,0,-2);
		glColor3f(1,1,0.8);
		drawCylinder(2,2);
	glPopMatrix();
	glPushMatrix();
		glScalef(1,0.6,1);
		glTranslatef(0,0,27);
		glColor3f(0,0,0);
		drawCylinder(8,4);
	glPopMatrix();	
}



void drawBed(){
	glPushMatrix();
		glRotatef(90,1,0,0);
		glPushMatrix();
			glColor3f(0.2,0.2,0.2);
			glRotatef(90,0,1,0);
			glScalef(0.05,0.8,0.3);
			glutSolidCube(70);
		glPopMatrix();
//suporte barra		
		glPushMatrix();
			glTranslatef(-9,-18,-20);
			drawCylinder(1,20);
			glPushMatrix();
				glRotatef(330,1,0,0);
				glTranslatef(0,0,4);
				glRotatef(90,0,0,1);
				glRotatef(90,0,1,0);
				drawCylinder(0.3,4);
			glPopMatrix();
		glPopMatrix();
//suporte barra		
		glPushMatrix();
			glScalef(-1,1,1);
			glTranslatef(-9,-18,-20);
			drawCylinder(1,20);
			glPushMatrix();
				glRotatef(330,1,0,0);
				glTranslatef(0,0,4);
				glRotatef(90,0,0,1);
				glRotatef(90,0,1,0);
				drawCylinder(0.3,4);
			glPopMatrix();
		glPopMatrix();
		

		//pes
		glPushMatrix();
			drawBedFeet();
		glPopMatrix();	
		glPushMatrix();
			glScalef(-1,-1,1);
			drawBedFeet();
		glPopMatrix();	
		glPushMatrix();
			glScalef(1,-1,1);
			drawBedFeet();
		glPopMatrix();	
		glPushMatrix();
			glScalef(-1,1,1);
			drawBedFeet();
		glPopMatrix();	
	glPopMatrix();
}

void drawBedFeet(){
	glTranslatef(8,18,7);
	glRotatef(90,1,0,0);
	modelBedFeet();	
}

void modelBedFeet(){
	glPushMatrix();
		glScalef(0.2,1,0.2);
		glutSolidCube(12);
	glPopMatrix();
}

void drawMoveArm(){
	
	glPushMatrix();
			glTranslatef(9,1,3.5);
			glRotatef(rotateme, 0,0,1);
			glPushMatrix();
				glRotatef(90,0,1,0);
				glColor3f(1,1,0.8);
				drawCylinderDeform(2,10,0.8);	
				glPushMatrix();
					glScalef(0.7,0.7,1);
					glTranslatef(0,0,4);
					glutSolidSphere(biceps,10,10);
				glPopMatrix();
			glPopMatrix();
	glPopMatrix();
	glPushMatrix();
			glTranslatef(-9,1,3.5);
			glRotatef(rotateme*(-1), 0,0,1);
			glPushMatrix();
				glRotatef(270,0,1,0);
				glColor3f(1,1,0.8);
				drawCylinderDeform(2,10,0.8);	
				glPushMatrix();
					glScalef(0.7,0.7,1);
					glTranslatef(0,0,4);
					glutSolidSphere(biceps,10,10);
				glPopMatrix();
			glPopMatrix();
	glPopMatrix();

}

void drawArm(){
	glPushMatrix();
		glColor3f(1,1,0.8);
		drawCylinderDeform(2, 2, 0.6);
		glTranslatef(0,-4,0);
		glRotatef(180, 1, 0, 0);
		glTranslatef(0,4,0);
		glPushMatrix();
			glRotatef(90,1,0,0);
			drawCylinderDeform(2, 7, 0.6);
		glPopMatrix();
	glPopMatrix();
}

void drawLeg(){
	glPushMatrix();
		glRotatef(20,0,1,0);
		glColor3f(0,0,0);
		drawCylinderDeform(4,20,0.6);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(7,0,20);
		glRotatef(90,1,0,0);
		glColor3f(0,0,0);
		drawCylinderDeform(2.5,16,0.6);
		glPushMatrix();
			glutSolidSphere(2.8,10,10);
		glPopMatrix();
		glTranslatef(0,-1,15);
		glRotatef(270,1,0,0);	
		glColor3f(1,0,0);
		drawCylinderDeform(2,6,0.7);
		
	glPopMatrix();
	
}


void drawMan(){
	glPushMatrix();
		glTranslatef(0,0,-8);
		glRotatef(270,1,0,0);
		drawHead();
	glPopMatrix();
	glPushMatrix();	
		drawBody();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(2.5,0,28);
		drawLeg();
	glPopMatrix();
	glPushMatrix();
		glScalef(-1,1,1);
		glTranslatef(2.5,0,28);
		drawLeg();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0,8,3);
		glPushMatrix();
			glTranslatef(0,pullDown,0);
			drawBar();
		glPopMatrix();
	glPopMatrix();

}

void drawFloor(){
	glPushMatrix();
		glTranslatef(0,-18,0);
		glRotatef(90,1,0,0);
		glScalef(1,0.7,0.020);
		glutSolidCube(200);
	glPopMatrix();
}

void drawChessFloor(){
	int j;
	bool chess = false;
	float paintR = 0;
	float paintG = 0;
	glPushMatrix();
		for(j=(-60); j<=60; j+=10){
		chess = !chess;
		paintR = chess ? 0.40 : 0.6;
		paintG = chess ? 0.20 : 0.35;
		glColor3f(paintR, paintG , 0);
			glPushMatrix();
				glTranslatef(0,-18,j);
				glRotatef(90,1,0,0);
				glScalef(19,1,0.2);
				glutSolidCube(10);
			glPopMatrix();
		}
	glPopMatrix();
}

void drawWall(){
	glPushMatrix();
		glTranslatef(95,30,0);
		glRotatef(90,0,1,0);
		glScalef(0.7,0.5,0.020);
		glutSolidCube(200);
	glPopMatrix();
}

void drawDeck(){
	glPushMatrix();
		glRotatef(47,0,1,0);
		drawSuport();
	glPopMatrix();
}

void drawSuport(){

	glPushMatrix();
		glPushMatrix();
			glScalef(1,1,-1);
			glTranslatef(0,9,0);
			drawBarSuport(6);
		glPopMatrix();
		glPushMatrix();
			glScalef(1,1,-1);
			glTranslatef(0,25,0);
			drawBarSuport(4);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0,9,0);
			drawBarSuport(6);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,25,0);
			drawBarSuport(4);
		glPopMatrix();


		glColor3f(0.2,0.2,0.2);
		glRotatef(270,1,0,0);
		drawCylinder(2,30);
		glPushMatrix();
			glScalef(1,1,0.7);
			glutSolidTorus(2,9,30,30);
			glPushMatrix();
				glTranslatef(0,9,0);
				glRotatef(90,1,0,0);
				drawCylinder(1,20);
			glPopMatrix();
			glPushMatrix();
				glRotatef(90,0,0,1);
				glTranslatef(0,9,0);
				glRotatef(90,1,0,0);
				drawCylinder(1,20);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
		
}

void drawBarSuport(float anilhaSize){
	glColor3f(0.0,0.0,0.0);
	drawCylinder(1,15);
	glColor3f(0.7,0.7,0.7);
	glPushMatrix();				
			glTranslatef(0,0,4);
			drawCylinder(anilhaSize,2);
	glPopMatrix();
	glPushMatrix();				
	
			glTranslatef(0,0,7);
			drawCylinder(anilhaSize,2);
	glPopMatrix();
	glPushMatrix();				
			glTranslatef(0,0,10);
			drawCylinder(anilhaSize,2);
	glPopMatrix();


}

void drawFan(){
		glPushMatrix();
			glTranslatef(0,70,0);
			//haste	
			glPushMatrix();
				glColor3f(1,1,0);
				glRotatef(270,1,0,0);
				drawCylinder(0.5,10);
			glPopMatrix();
			//centro
			glPushMatrix();
				glRotatef(90,1,0,0);
				drawCylinder(3,2);
			glPopMatrix();
			//pas
			glPushMatrix();
				drawFanBlade();
			glPopMatrix();
			glPushMatrix();
				glScalef(1,1,-1);
				drawFanBlade();
			glPopMatrix();
			glPushMatrix();
				glRotatef(90,0,1,0);
				glScalef(1,1,-1);
				drawFanBlade();
			glPopMatrix();
			glPushMatrix();
				glRotatef(90,0,1,0);
				drawFanBlade();
			glPopMatrix();
		glPopMatrix();
}

void drawFanBlade(){
	
	glPushMatrix();
		glTranslatef(0,0,10);
		glRotatef(10,0,0,1);
		glColor3f(1,1,0);
		glScalef(0.3, 0.05 ,1);
		glutSolidCube(15);
	glPopMatrix();
}

void drawClock(){
	glPushMatrix();
		glTranslatef(0,0,-2);
		glColor3f(0,0,0);
		glutSolidTorus(1,11,30,30);
		glColor3f(1,1,1);
		drawCylinder(10,2);
	glPopMatrix();
	//ponteiro 
	glPushMatrix();
		glRotatef(-seconds,0,0,1);
		glRotatef(180,0,0,1);
		glTranslatef(0,-3,0);
		glScalef(0.05,1,0.1);
		glColor3f(0,0,0);
		glutSolidCube(12);
	glPopMatrix();
	//ponteiro minuto
	glPushMatrix();
		glRotatef(-minutes,0,0,1);
		glRotatef(180,0,0,1);
		glTranslatef(1,-3,0);
		glScalef(0.2,1,0.2);
		glColor3f(0,0,0);
		glutSolidCube(8);
	glPopMatrix();
	//ponteiro hora
	glPushMatrix();
		glRotatef(-hour,0,0,1);
		glRotatef(180,0,0,1);
		glTranslatef(0,-3,0);
		glScalef(0.2,1,0.2);
		glColor3f(0,0,0);
		glutSolidCube(5);
	glPopMatrix();
	
}
void drawDrop(){
		glPushMatrix();
			glTranslatef(-60,0,0);
			glPushMatrix();	
				glTranslatef(0,dropMe,0);
				glPushMatrix();
					glScalef(0.2,0.2,0.2);	
					glPushMatrix();
						glColor3f(0.6,0.7,1);
						glRotatef(270,1,0,0);
						glutSolidCone(7,18,20,20);
						glutSolidSphere(6.8,20,20);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
}

void drawBucket(){
	glPushMatrix();
		glTranslatef(-60,-7,0);
		glPushMatrix();
			glRotatef(90,1,0,0);
			glColor3f(0.1,0.3,0);
			drawCylinderDeform(5,10,0.7);
		glPopMatrix();
	glPopMatrix();
}


void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
			glTranslatef(0,-30,0);
			glPushMatrix();
				drawMan();
				drawMoveArm();
				glPushMatrix();
					glTranslatef(0,-5,5);
					drawBed();
				glPopMatrix();

				//gota
				drawDrop();	
			
				//balde
				drawBucket();
				//clock	
				glPushMatrix();
					glTranslatef(-40,50,-50);
					drawClock();
				glPopMatrix();
				//ventilador	
				glPushMatrix();	
					glRotatef(turnFan, 0,1,0);
					drawFan();
				glPopMatrix();
				//deck de pesos
				glPushMatrix();
					glTranslatef(55, -15, -10);
					drawDeck();
				glPopMatrix();
				//chao	
				glPushMatrix();
					drawChessFloor();
				glPopMatrix();
				//teto
				glColor3f(0.5,0.7,1);
				glPushMatrix();
					glTranslatef(0,100,0);
					drawFloor();
				glPopMatrix();
			
				//paredes
				glColor3f(0.8,0.9,1);
				drawWall();
				
				glPushMatrix();
					glScalef(-1,1,1);
					glColor3f(0.8,0.9,1);
					drawWall();
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0,0,30);
					glScalef(1.4,1,1);
					glRotatef(90,0,1,0);
					glColor3f(0.7,0.8,1);
					drawWall();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glutSwapBuffers();			
}

void mouse( int button, int state, int x, int y ){
	if( state == GLUT_DOWN ){
		x_ini = x;
		y_ini = y;
		obsX_ini = obsX;
		obsY_ini = obsY;
		obsZ_ini = obsZ;
		rotX_ini = rotX;
		rotY_ini = rotY;
		bot = button;
	}
	else bot = -1;
}

void reshape(int w, int h){
	if(h == 0) h = 1;
	glViewport(0,0,w,h);
	aspecto = (float) w/h;
	projecao();
}

void projecao(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
		gluPerspective(angulo, aspecto, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsX, obsY, obsZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

}

void motion( int x, int y ){
	if( bot == GLUT_LEFT_BUTTON ){
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		rotY = rotY_ini - deltax/SENS_ROT;
		rotX = rotX_ini - deltay/SENS_ROT;
	}
	else if( bot == GLUT_RIGHT_BUTTON ){
		int deltaz = y_ini - y;
		obsZ = obsZ_ini + deltaz/SENS_OBS;
	}else if( bot == GLUT_MIDDLE_BUTTON ){
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		obsX = obsX_ini + deltax/SENS_TRANSL;
		obsY = obsY_ini - deltay/SENS_TRANSL;
	}

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glTranslatef( -obsX, -obsY, -obsZ );
	glRotatef( rotX, 1, 0, 0 );
	glRotatef( rotY, 0, 1, 0 );
	glutPostRedisplay();
}

void keyboard( unsigned char tecla, int x, int y){
	switch(tecla){
		case 27: exit(0);
			break;

		case 'p':
		case 'P':
			if(anilha < 15){
				anilha += 0.25;
			} 
			break;
		
		case 'o':
		case 'O':
			if(anilha > 2){
				anilha -= 0.25;
			}
			break;
		
		case 'k':
		case 'K':
			if(pullDown <= 5){
				pullDown += (10/anilha)/10;
			}
			break;

	
	}
	glutPostRedisplay();

}
