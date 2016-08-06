#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
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


//global variables

bool orto = true;
bool eixos = true;
bool wire = false;
float win = 10.0f;
float aspecto;
float angulo = 30.0f;
int objeto = 0;


//funcoes 
void desenhaCubo(float size);
void desenhaEsfera(float r, float s, float st);
//variaveis 

GLfloat rotX=0.0, rotY=0.0, rotX_ini, rotY_ini;
GLfloat obsX=0.0, obsY=00.0, obsZ=150.0, obsX_ini, obsY_ini, obsZ_ini;
int x_ini, y_ini, bot;

void inicializa(){

GLfloat ambient[] = {0.5, 0.5, 0.5 ,1.0};
GLfloat difusa[] = {0.5,0.5,0.5,1};
GLfloat especular[] = {1,1,1,1};
GLfloat posicao[] = {20,0,0,0};

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


int main (int argc, char *argv[]){
	//escopo de criacao de janela
	glutInit(&argc, argv);
	glutInitWindowSize(1000, 800);
	glutInitWindowPosition(10, 10);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Octogono");
	//fim do escopo de criacao

	//escopo de registro de callbacks
	inicializa();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

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

void escada(){
	glColor3f(0.7,0.7,0.7);
	glPushMatrix();
	glRotatef(90,0,0,1);
	glRotatef(90,1,0,0);
	glPushMatrix();
		glScalef(1,0.3,0.3);
		desenhaCubo(5);
	glPopMatrix();
	glPushMatrix();
		glScalef(1,0.6,0.3);
		glTranslatef(0,1.3,5);
		desenhaCubo(5);
	glPopMatrix();
	glPushMatrix();
		glScalef(1,0.9,0.3);
		glTranslatef(0,1.7,10);
		desenhaCubo(5);
	glPopMatrix();
	glPopMatrix();

}

void tela(){
	glColor3f(0.7,0.7,0.7);
	glBegin(GL_LINES);
			float x = 10;

		for(float i=0; i < x; i+=1){
			
			glVertex2f(0 , i); //lado a
			glVertex2f(i, 0);	//lado b
			
			glVertex2f(i , x); //lado a
			glVertex2f(x, i);	//lado b
	
			glVertex2f(x , i); //lado a
			glVertex2f(x-i, 0);	//lado b
			
			glVertex2f(x-i , x); //lado a
			glVertex2f(0, i);	//lado b
			
		}
	glEnd();
}

void grade(){
	glPushMatrix();
		glTranslatef(9,0,30);
		glScalef(0.05,1,0.05);
		desenhaCubo(20);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(9,9.5,20);
		glScalef(0.05,0.05,1);
		desenhaCubo(20);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(9,-9.5,20);
		glScalef(0.05,0.05,1);
		desenhaCubo(20);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(9,0,30);
		glPushMatrix();
			glScalef(1,1,2);
			glRotatef(90,0,1,0);
			tela();
		glPopMatrix();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(9,-10,30);
		glPushMatrix();
			glScalef(1,1,2);
			glRotatef(90,0,1,0);
			tela();
		glPopMatrix();
	glPopMatrix();
}

void octogonoPiece(){
	glColor3f(0.5,0.5,0.5);
	glPushMatrix();
		glTranslatef(14,0,0);
		glScalef(1,1,0.5);
		glPushMatrix();	
			grade();
			desenhaCubo(20);
		glPopMatrix();
	glPopMatrix();
}

void octogonoBase(){
	for(int i=0; i < 360; i+=45){
		glPushMatrix();
			glRotatef(i,0,0,1);
			octogonoPiece();
		glPopMatrix();
	}	
	glPushMatrix();
		glScalef(1,1,0.5);
		desenhaCubo(20);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(23,-3,10);
		glScalef(0.1,0.1,1);
		desenhaCubo(10);
	glPopMatrix();
	glPushMatrix();
		glRotatef(180,0,0,1);
		glTranslatef(23,-3,10);
		glScalef(0.1,0.1,1);
		desenhaCubo(10);
	glPopMatrix();
	
}

void octogono(){
				
			glPushMatrix();
				glTranslatef(-27.5,6,0);
				escada();
			glPopMatrix();
			glPushMatrix();
				glRotatef(180,0,0,1);
				glTranslatef(-27.5,6,0);
				escada();
			glPopMatrix();
			glPushMatrix();
				octogonoBase();
			glPopMatrix();
			glPushMatrix();
				glColor3f(0.2,0.2,0.2);
				glTranslatef(0,0,-3);
				glScalef(1,1,0.05);
				desenhaCubo(100);
			glPopMatrix();

}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
			glTranslatef(0,-10,0);
			glPushMatrix();
				glRotatef(-90,1,0,0);
				octogono();
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
		

		case 'w':
		case 'W':
			wire = !wire;
			break;

	}
	glutPostRedisplay();

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


