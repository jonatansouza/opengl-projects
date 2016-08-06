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

//sala de tv
void desenhaSofa();
void mesa();
void tv();
void tvImagem(int i);
void piso();
void parede();
void ventilador();
void helice();
void planta();

//global variables
bool orto = true;
bool eixos = true;
bool wire = false;
float win = 10.0f;
float aspecto;
float angulo = 30.0f;
int objeto = 0;

//variaveis sala
float telaR;
float telaG;
float telaB;
bool tvLiga = false;
bool ventLiga = false;
int girar = 0;

GLfloat rotX=0.0, rotY=0.0, rotX_ini, rotY_ini;
GLfloat obsX=0.0, obsY=0.0, obsZ=250.0, obsX_ini, obsY_ini, obsZ_ini;
int x_ini, y_ini, bot;

float randomNumber(){
	return (rand() % (1 - 99 + 1) + 1);
}

void vent(int i){
	//girar ventilador
	if(ventLiga){
		girar+=10;
	}
	glutPostRedisplay();
	glutTimerFunc(1,vent, 0);
}


void tvImagem(int i){
	if(tvLiga){	
		telaR = randomNumber()/100;
		telaG = randomNumber()/100;
		telaB = randomNumber()/100;
	}

	if(telaR > 1 && telaG > 1 && telaB > 1){
		telaR = 0;
		telaG = 0;
		telaB = 0;
	}

	
	glutPostRedisplay();
	glutTimerFunc(60,tvImagem, 0);
}

void inicia(){

GLfloat ambient[] = {0.5, 0.5, 0.5 ,1.0};
GLfloat difusa[] = {0.5,0.5,0.5,1};
GLfloat especular[] = {1,1,1,1};
GLfloat posicao[] = {0,40,0,0};

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

int main (int argc, char *argv[]){
	//escopo de criacao de janela
	glutInit(&argc, argv);
	glutInitWindowSize(1000, 800);
	glutInitWindowPosition(10, 10);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Sala de TV");
	//fim do escopo de criacao

	//escopo de registro de callbacks
	inicia();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutTimerFunc(60, tvImagem, 0);
	glutTimerFunc(10, vent, 0);
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

void desenhaCone(float size, float hgh){
	if(wire){
		glutWireCone(size, hgh,5, 5);
	}else{
		glutSolidCone(size, hgh,10, 10);
	}
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
			glTranslatef(0,-25,0);
			glPushMatrix();
				glTranslatef(-25,0,0);
				glRotatef(90,0,1,0);
				glPushMatrix();
					glTranslatef(0,2,70);
					glRotatef(180,0,1,0);
					glScalef(2,2,2);
					desenhaSofa();
				glPopMatrix();     
				glPushMatrix();	
					glTranslatef(0,0,-30);
					mesa();
				glPopMatrix();
			glPopMatrix();
			//piso
			glPushMatrix();
				glColor3f(0.6,0.35,0.2);
				glTranslatef(0,-5,0);
				piso();
			glPopMatrix();
			//teto
			glPushMatrix();
				glColor3f(1,0.85,0.75);
				glTranslatef(0,75,0);
				piso();
			glPopMatrix();

			//paredes
			glPushMatrix();
				glColor3f(1,0.95,0.95);
				glTranslatef(-100,35,0);
				glRotatef(90,0,1,0);
				parede();
			glPopMatrix();
			glPushMatrix();
				glScalef(-1,1,1);
				glTranslatef(-100,35,0);
				glRotatef(90,0,1,0);
				parede();
			glPopMatrix();
			glPushMatrix();
				glColor3f(1,0.9,0.8);
				glTranslatef(0,35,-100);
				parede();
			glPopMatrix();
			glPushMatrix();
				glRotatef(girar, 0,1,0);
				ventilador();
			glPopMatrix();
			//planta
			glPushMatrix();
				glTranslatef(-50,0,40);
				planta();
			glPopMatrix();
			glPushMatrix();
				glScalef(1,1,-1);
				glTranslatef(-50,0,40);
				planta();
			glPopMatrix();
		glPopMatrix();
	glutSwapBuffers();			
}

void parede(){
	glPushMatrix();
		glRotatef(90,1,0,0);
		glScalef(1,0.01,0.4);
		desenhaCubo(200);
	glPopMatrix();
}

void piso(){
	glPushMatrix();
		glScalef(1,0.01,1);
		desenhaCubo(200);
	glPopMatrix();

}

void ventilador(){
		glPushMatrix();
			glTranslatef(0,70,0);
			//haste	
			glPushMatrix();
				glColor3f(0.3,0.3,0.1);
				glRotatef(270,1,0,0);
				drawCylinder(0.3,6);
			glPopMatrix();
			//centro
			glPushMatrix();
				glRotatef(90,1,0,0);
				drawCylinder(3,2);
			glPopMatrix();
			//pas
			glPushMatrix();
				helice();
			glPopMatrix();
			glPushMatrix();
				glScalef(1,1,-1);
				helice();
			glPopMatrix();
			glPushMatrix();
				glRotatef(90,0,1,0);
				glScalef(1,1,-1);
				helice();
			glPopMatrix();
			glPushMatrix();
				glRotatef(90,0,1,0);
				helice();
			glPopMatrix();
		glPopMatrix();
}

void helice(){
	
	glPushMatrix();
		glTranslatef(0,0,10);
		glRotatef(10,0,0,1);
		glColor3f(0.4,0.4,0.3);
		glScalef(0.3, 0.05 ,1);
		glutSolidCube(15);
	glPopMatrix();
}

void planta(){
	glPushMatrix();
		glTranslatef(0,3,0);
		glRotatef(270,1,0,0);
		glPushMatrix();
			glColor3f(0.3,0.5,0);
			glTranslatef(0,0,-2);
			glRotatef(180,1,0,0);
			drawCylinderDeform(3,5,0.6);
		glPopMatrix();
		glPushMatrix();
			glColor3f(0,1,0);
			desenhaCone(2, 5);	
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,0,3.5);
			desenhaCone(2, 5);	
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,0,7);
			desenhaCone(2, 5);	
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,0,-2);
			glColor3f(0.8,0.4,0);
			drawCylinder(0.9,4);
		glPopMatrix();
	glPopMatrix();

}

void tv(){
	//externo
	glPushMatrix();
		glScalef(1.5,0.7,0.2);
		desenhaCubo(22);	
	glPopMatrix();
	//suport
	glPushMatrix();
		glTranslatef(0,-10,0);
		glRotatef(270,1,0,0);
		drawCylinderDeform(5,2,0.1);
	glPopMatrix();
	//tela	
	glPushMatrix();
		glColor3f(telaR,telaG,telaB);
		glTranslatef(0,0,2.5);
		glScalef(1.6,0.7,0.01);
		desenhaCubo(18);	
	glPopMatrix();
}


void desenhaSofa(){
	
	//assento
	glPushMatrix();
		glColor3f(0.5,0.5,0.4);
		glScalef(1,0.3,0.5);
		desenhaCubo(20);
	glPopMatrix();
	//lateral
	glPushMatrix();
		glColor3f(0.4,0.4,0.3);
		glTranslatef(11.5,1.9,0);
		glScalef(0.3,1,1);
		desenhaCubo(10);
	glPopMatrix();
	glPushMatrix();
		glScalef(-1,1,1);
		glTranslatef(11.5,1.9,0);
		glScalef(0.3,1,1);
		desenhaCubo(10);
	glPopMatrix();
	//encosto
	glPushMatrix();
		glColor3f(0.6,0.6,0.7);
		glTranslatef(0,3.5,-6);
		glScalef(2.1,1.3,0.2);
		desenhaCubo(10);
	glPopMatrix();

}

void mesa(){
	//tampo superior
	glPushMatrix();
		glColor3f(0.3,0.3,0.4);
		glScalef(1,0.1,0.7);
		desenhaCubo(30);
	glPopMatrix();
	//inferior
	glPushMatrix();
		glColor3f(0.3,0.3,0.4);
		glTranslatef(0,15,0);
		glScalef(1,0.1,0.7);
		desenhaCubo(30);
	glPopMatrix();
	//laterais
	glPushMatrix();
		glColor3f(0.5,0.5,0.4);
		glTranslatef(10,7.5,0);
		glScalef(0.1,0.6,1);
		desenhaCubo(20);
	glPopMatrix();
	glPushMatrix();
		glScalef(-1,1,1);
		glTranslatef(10,7.5,0);
		glScalef(0.1,0.6,1);
		desenhaCubo(20);
	glPopMatrix();
	//pes
	glPushMatrix();
		glScalef(-1,1,1);
		glColor3f(0.7,0.7,0.4);
		glTranslatef(10,-1.5,7);
		glRotatef(90,1,0,0);
		drawCylinder(2,3);
	glPopMatrix();	
	glPushMatrix();
		glScalef(-1,1,-1);
		glColor3f(0.7,0.7,0.4);
		glTranslatef(10,-1.5,7);
		glRotatef(90,1,0,0);
		drawCylinder(2,3);
	glPopMatrix();	
	glPushMatrix();
		glScalef(1,1,-1);
		glColor3f(0.7,0.7,0.4);
		glTranslatef(10,-1.5,7);
		glRotatef(90,1,0,0);
		drawCylinder(2,3);
	glPopMatrix();	
	glPushMatrix();
		glColor3f(0.7,0.7,0.4);
		glTranslatef(10,-1.5,7);
		glRotatef(90,1,0,0);
		drawCylinder(2,3);
	glPopMatrix();	
	glPushMatrix();
		glColor3f(0.1,0.1,0.1);
		glTranslatef(0,26.5,0);
		tv();
	glPopMatrix();
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

		case 'w':
		case 'W':
			wire = !wire;
			break;

		case 't':
		case 'T':
			tvLiga = !tvLiga;
			telaR = 0;
			telaG = 0;
			telaB = 0;

			break;

		case 'V':
		case 'v':
			ventLiga = !ventLiga;
			girar = 0;
			break;
	
	}
	glutPostRedisplay();

}



void formas(){

	switch (objeto){
	case 1:
		if( wire ){
			glutWireSphere ( 2 , 10 , 10 );
		}else{
			glutSolidSphere( 2 , 10 , 10 );
		}
	break;
	case 2:
		if( wire ){
			glutWireCube ( 2 );
		}else{
			glutSolidCube( 2 );
		}
	break;
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



