#include <stdio.h>
#include <GL/glut.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "cylinder.h"

#define SENS_ROT 5.0
#define SENS_OBS 20.0
#define SENS_TRANSL 30.0

void display();
void init();
void reshape(int w, int h);
void keyboard( unsigned char tecla, int x, int y);
void desenhaEixos();
void projecao();
void mouse( int button, int state, int x, int y );
void motion( int x, int y );
void formas();
void desenhaCubo(float size);

//escritorio
void mesa();
void mesaLaterais();
void monitor();
void gabinete();
void teclado();
void rato();
void mTime(int i);
void chao();
void som();

//variaveis
float sR = 0.1;
float sG = 0.1;
float sB = 0.1;
bool liga = false;


//global variables
bool orto = true;
bool eixos = true;
bool wire = true;
float win = 10.0f;
float aspecto;
float angulo = 30.0f;
int objeto = 0;

//variaveis sala

GLfloat rotX=0.0, rotY=0.0, rotX_ini, rotY_ini;
GLfloat obsX=0.0, obsY=00.0, obsZ=100.0, obsX_ini, obsY_ini, obsZ_ini;
int x_ini, y_ini, bot;

void inicializa(){

GLfloat ambient[] = {0.5, 0.5, 0.5 ,1.0};
GLfloat difusa[] = {0.5,0.5,0.5,1};
GLfloat especular[] = {1,1,1,1};
GLfloat posicao[] = {0,20,0,0};

glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

//difusa da um ambiente sombrado
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

void som(){
	glColor3f(0.3,0.3,0.3);
	
	glPushMatrix();
		glScalef(0.5,1,0.7);
		desenhaCubo(5);
	glPopMatrix();
	glPushMatrix();
		glColor3f(0.7,0.7,0.7);
		glTranslatef(0,0.5,1.9);
		glScalef(0.3,0.3,0.1);
		glutSolidSphere(3,20,20);	
	glPopMatrix();

}

void chao(){
	glColor3f(0.55,0.8,1);
	glPushMatrix();
		glScalef(1,0.01,1);
		desenhaCubo(200);
	glPopMatrix();

}

void mTime(int i){
	if(liga){
		if(sR <= 1){
			sR += 0.01;
			sG += 0.03;
			sB += 0.05;
		}else{
			sR = 0.1;
			sG = 0.1;
			sB = 0.1;
		}
	}else{
		sR = 0.1;
		sG = 0.1;
		sB = 0.1;
	}
	glutPostRedisplay();
	glutTimerFunc(60 , mTime, 0);
}

void gabinete(){
	
	glColor3f(0.3,0.3,0.3);
	glPushMatrix();
		glScalef(0.5,1,0.7);
		desenhaCubo(10);
	glPopMatrix();
	glColor3f(0.5,0.5,0.5);
	glPushMatrix();
		glScalef(0.1,0.1,0.1);	
		glTranslatef(9,18,37);
		drawCylinder(5,1);
	glPopMatrix();
}

void rato(){
	//base
	glColor3f(0.3,0.3,0.3);
	glPushMatrix();
		glScalef(0.5,0.2,0.7);
		desenhaCubo(10);
	glPopMatrix();
	//teclas
	glColor3f(0.5,0.5,0.5);
	glPushMatrix();
		glTranslatef(1,1,-1.4);
		glScalef(0.7,0.2,1);
		desenhaCubo(2);
	glPopMatrix();
	glPushMatrix();
		glScalef(-1,1,1);
		glTranslatef(1,1,-1.4);
		glScalef(0.7,0.2,1);
		desenhaCubo(2);
	glPopMatrix();
}

void monitor(){
	glPushMatrix();
		glRotatef(90,1,0,0);
		//base
		glPushMatrix();
			glColor3f(0.3,0.3,0.3);
			glRotatef(90,1,0,0);
			glScalef(1,0.5,0.1);
			desenhaCubo(20);
		glPopMatrix();
		//tela
		glPushMatrix();
			glColor3f(sR,sG,sB);
			glRotatef(90,1,0,0);
			glTranslatef(0,0,-1);
			glScalef(1,0.5,0.01);
			desenhaCubo(18);
		glPopMatrix();
		//base
		glPushMatrix();
			glColor3f(0.3,0.3,0.3);
			glRotatef(180,1,0,0);
			glScalef(0.3,0.3,0.3);
			glTranslatef(0,0,-22);
			drawCylinderDeform(7,5,0.3);
		glPopMatrix();
	glPopMatrix();
	
}

void mesa(){
	glColor3f(0.6,0.3,0.1);
	//superior
	glPushMatrix();
		glTranslatef(0,10,-5);
		glRotatef(90,1,0,0);
		glScalef(1,0.5,0.03);
		desenhaCubo(30);
	glPopMatrix();
	//medio
	glPushMatrix();	
		glRotatef(10,1,0,0);
		glPushMatrix();
			glRotatef(90,1,0,0);
			glTranslatef(0,0,-3);
			glScalef(1,0.5,0.03);
			desenhaCubo(30);
		glPopMatrix();
	glPopMatrix();
	//laterais
	glPushMatrix();
		glTranslatef(15,-4,-4.5);
		mesaLaterais();
	glPopMatrix();
	glPushMatrix();
		glScalef(-1,1,1);
		glTranslatef(15,-4,-4.5);
		mesaLaterais();
	glPopMatrix();
	//inferior
	glPushMatrix();
		glTranslatef(0,-17,-4.5);
		glRotatef(90,1,0,0);
		glScalef(1,0.3,0.05);
		desenhaCubo(30);
	glPopMatrix();

}


void mesaLaterais(){
	glPushMatrix();
		glScalef(0.01,1,0.3);
		desenhaCubo(30);
	glPopMatrix();
}

void teclado(){
	glPushMatrix();
	glRotatef(270,1,0,0);
	glColor3f(0.3,0.3,0.3);
	
	glPushMatrix();
		glScalef(1,0.4,0.08);
		desenhaCubo(15);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,0,0.5);
		int i,j;
		for(j=-2;j<=2;j++){
			for(i=-6;i<=6;i++){
				glColor3f(1,1,1);
				glPushMatrix();
					glTranslatef(i,j,0);
					desenhaCubo(0.7);
				glPopMatrix();
			}
		}
	glPopMatrix();
	glPopMatrix();
}

int main (int argc, char *argv[]){
	//escopo de criacao de janela
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(10, 10);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Escritorio");
	//fim do escopo de criacao

	//escopo de registro de callbacks
	inicializa();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutTimerFunc(10, mTime, 0);
	//fim do escopo de registro	
	
	//demais
	glutMainLoop();//nao colocar nada apos esta funcao pois nao aparecera
	return 0;
}

void desenhaCubo(float size){
	if(wire){
		glutWireCube(size);
	}else{
		glutSolidCube(size);
	}
}


void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
			mesa();		
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0,17,-4);
			monitor();
		glPopMatrix();
		
		glPushMatrix();
			glScalef(1.3,1.3,1.3);
			glTranslatef(7,-7.4,-3);
			gabinete();
		glPopMatrix();

		glPushMatrix();
			glRotatef(10,1,0,0);
			glTranslatef(-3,4,2);	
			teclado();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(13,13,0);
			som();
		glPopMatrix();

		glPushMatrix();
			glScalef(-1,1,1);
			glTranslatef(13,13,0);
			som();
		glPopMatrix();

		glPushMatrix();
			glRotatef(10,1,0,0);
			glTranslatef(9,4,2);
			glScalef(0.5,0.5,0.5);
			rato();
		glPopMatrix();
	
		glPushMatrix();
			glTranslatef(0,-20,0);
			chao();
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
	gluPerspective(angulo, aspecto, 1.0f, 1000.0f);
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
			orto = false;
			projecao();
			break;
		
		case 'o':
		case 'O':
			orto = true;
			projecao();
			break;
		
		case 'l':
		case 'L':
			liga = !liga;
			break;

		case 'w':
		case 'W':
			wire = !wire;
			break;

		
		case '1':
			objeto = 1;
			break;
		case '2':
			objeto = 2;
			break;
	
	}
	glutPostRedisplay();

}



void formas(){
		if( wire ){
			glutWireCube ( 2 );
		}else{
			glutSolidCube( 2 );
		}
}

void desenhaEixos(){
	glLineWidth( 2.0f );
	glBegin( GL_LINES );
		glColor3f ( 1.0f, 0.0f, 0.0f );
		glVertex3f( 0.0f, 0.0f, 0.0f );
		glVertex3f( 2.0f, 0.0f, 0.0f );
		glColor3f ( 0.0f, 1.0f, 0.0f );
		glVertex3f( 0.0f, 0.0f, 0.0f );
		glVertex3f( 0.0f, 2.0f, 0.0f );
		glColor3f ( 0.0f, 0.0f, 1.0f );
		glVertex3f( 0.0f, 0.0f, 0.0f );
		glVertex3f( 0.0f, 0.0f, 2.0f );
	glEnd();
}

void init(){
	glClearColor(0,0,1,0);
}


