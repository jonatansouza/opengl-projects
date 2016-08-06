#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>

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

//Show
void caixaDeSomV();
void caixaDeSomH();
void caixaDeSomDual();
void palco();
void luzA();
void paredes();
void hofote();
void hasteHolofote();

//variaveis
int hCentral = 0;
int hLateral = 5;
int hLateral2 = 5;
bool inc = true;
bool incL = true;
bool incL2 = true;

//global variables
bool orto = true;
bool eixos = true;
bool wire = false;
bool ligaLuzes = false;
float win = 10.0f;
float aspecto;
float angulo = 30.0f;
int objeto = 0;

//variaveis sala

GLfloat rotX=0.0, rotY=0.0, rotX_ini, rotY_ini;
GLfloat obsX=0.0, obsY=00.0, obsZ=150.0, obsX_ini, obsY_ini, obsZ_ini;
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

void girarHolofote(int i){
		if(ligaLuzes){	
			if(inc){
				hCentral += 1;
				
			}else{
				hCentral -= 1;
			}	
			
			if(hCentral == 20){
				inc = false;
			}
			if(hCentral == (-20)){
				inc = true;
			}

			if(incL){
				hLateral+=1;
			}else{
				hLateral -=1;
			}

			if(hLateral == 45){
				incL = false;
			}

			if(hLateral == 5){
				incL = true;
			}
		}
		
	glutPostRedisplay();
	glutTimerFunc(10,girarHolofote,1);
}

void girarHolofoteLento(int i){
	if(ligaLuzes){
			if(incL2){
				hLateral2+=1;
			}else{
				hLateral2 -=1;
			}

			if(hLateral2 == 45){
				incL2 = false;
			}

			if(hLateral2 == 5){
				incL2 = true;
			}
	}

	glutPostRedisplay();
	glutTimerFunc(30, girarHolofoteLento, 1);

}

int main (int argc, char *argv[]){
	//escopo de criacao de janela
	glutInit(&argc, argv);
	glutInitWindowSize(1000, 800);
	glutInitWindowPosition(10, 10);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Palco");
	//fim do escopo de criacao

	//escopo de registro de callbacks
	inicializa();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutTimerFunc(10, girarHolofote, 0);
	glutTimerFunc(10, girarHolofoteLento, 0);

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

void desenhaEsfera(float r, float s, float st){

	if(wire){
		glutWireSphere(r, s, st);
	}else{
		glutSolidSphere(r, s, st);
	}

}

void caixaDeSomV(){
		glPushMatrix();
			glScalef(0.3,0.3,0.3);
			glRotatef(180,0,0,1);
			glPushMatrix();	
				glColor3f(0.2,0.2,0.2);
				glScalef(0.7,1,0.7);
				desenhaCubo(40);
			glPopMatrix();
			
			glPushMatrix();
				glScalef(1,1,0.6);
				glTranslatef(0,-5,19);
				glColor3f(0.4,0.4,0.4);
				desenhaEsfera(12,30,30);
			glPopMatrix();
			
			glPushMatrix();
				glScalef(1,1,0.6);
				glTranslatef(8, 12 , 22);
				glColor3f(0.4,0.4,0.4);
				desenhaEsfera(4,30,30);
			glPopMatrix();
			
			glPushMatrix();
				glScalef(-1,1,1);
				glScalef(1,1,0.6);
				glTranslatef(8, 12 , 22);
				glColor3f(0.4,0.4,0.4);
				desenhaEsfera(4,30,30);
			glPopMatrix();
		glPopMatrix();

}


void caixaDeSomH(){
		glPushMatrix();
			glRotatef(90,0,0,1);
			glScalef(0.3,0.3,0.3);
			glRotatef(180,0,0,1);
			glPushMatrix();	
				glColor3f(0.2,0.2,0.2);
				glScalef(0.7,1,0.7);
				desenhaCubo(40);
			glPopMatrix();
			glPushMatrix();
				glScalef(1,1,0.6);
				glTranslatef(0,-10,19);
				glColor3f(0.4,0.4,0.4);
				desenhaEsfera(9,30,30);
			glPopMatrix();
			glPushMatrix();
				glScalef(1,-1,1);
				glScalef(1,1,0.6);
				glTranslatef(0,-10,19);
				glColor3f(0.4,0.4,0.4);
				desenhaEsfera(9,30,30);
			glPopMatrix();
		glPopMatrix();		

}

void caixaDeSomDual(){
	glPushMatrix();
		caixaDeSomH();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0,10,0);
		caixaDeSomV();
	glPopMatrix();

}



void palco(){
	glPushMatrix();
		glTranslatef(0,-25,0);
		glColor3f(0.3,0.2,0.1);	
		glScalef(1,0.3,0.6);
		desenhaCubo(80);
	glPopMatrix();
}
void teto(){
	glPushMatrix();
		glTranslatef(0,-15,0);
		glColor3f(0.3,0.2,0.1);	
		glScalef(1,0.05,0.6);
		desenhaCubo(80);
	glPopMatrix();
}

void luzA(){
	glPushMatrix();
		glRotatef(-90,1,0,0);
		glutSolidCone(7,50,100,100);
	glPopMatrix();

}

void paredes(){
	glPushMatrix();
		glTranslatef(39,2,0);
		glScalef(0.05,1,0.1);
		desenhaCubo(40);
	glPopMatrix();

}

void holofote(){
	glPushMatrix();
	glRotatef(90,1,0,0);
	glScalef(0.3,0.3,0.3);	
	//cubo
	glPushMatrix();
		glColor3f(0.1,0.1,0.1);
		desenhaCubo(6.5);
	glPopMatrix();
	//globo de luz
	glPushMatrix();
		glColor3f(1,1,1);
		glTranslatef(0,0,3);
		glScalef(1,1,0.3);
		desenhaEsfera(3,30,30);
	glPopMatrix();
	glPopMatrix();

}

void hasteHolofote(){
	glPushMatrix();
		glColor3f(0.1,0.1,0.1);
		glScalef(0.05,0.8,0.05);
		desenhaCubo(4);
	glPopMatrix();
	
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		glTranslatef(0,5,0);
		glPushMatrix();
			palco();		
		glPopMatrix();
		//paredes
		glPushMatrix();
			paredes();
			glPushMatrix();
				glTranslatef(0,0,20);	
				paredes();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,0,-20);	
				paredes();
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glScalef(-1,1,1);
			paredes();
			glPushMatrix();
				glTranslatef(0,0,20);	
				paredes();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,0,-20);	
				paredes();
			glPopMatrix();
		glPopMatrix();
	
	
		//caixas atras
		glPushMatrix();
			glPushMatrix();
				glTranslatef(0,-9,-17);
				caixaDeSomDual();
			glPopMatrix();
			glPushMatrix();
				glRotatef(15, 0,1,0);
				glTranslatef(-23,-9,-17);
				caixaDeSomDual();
			glPopMatrix();		
			glPushMatrix();
				glScalef(-1,1,1);
				glRotatef(15, 0,1,0);
				glTranslatef(-23,-9,-17);
				caixaDeSomDual();
			glPopMatrix();		
		glPopMatrix();
		//caixas frente
		glPushMatrix();
			glTranslatef(32,-10,15);
			glScalef(0.5,0.5,0.5);
			caixaDeSomV();
		glPopMatrix();
		glPushMatrix();
			glScalef(-1,1,1);
			glTranslatef(32,-10,15);
			glScalef(0.5,0.5,0.5);
			caixaDeSomV();
		glPopMatrix();
		//central
		glPushMatrix();
			glTranslatef(15,-11,5);
			glScalef(0.5,0.5,0.5);
			caixaDeSomH();
		glPopMatrix();
		glPushMatrix();
			glScalef(-1,1,1);
			glTranslatef(15,-11,5);
			glScalef(0.5,0.5,0.5);
			caixaDeSomH();
		glPopMatrix();
	
		//teto
		glPushMatrix();
			glTranslatef(0,25,0);
			glScalef(1,0.2,1);
			teto();
		glPopMatrix();
		//hastes holofote
		glPushMatrix();
			glTranslatef(28,20,20);
			hasteHolofote();
		glPopMatrix();

		glPushMatrix();
			glScalef(-1,1,1);
			glTranslatef(28,20,20);
			hasteHolofote();
		glPopMatrix();
		glPushMatrix();
			glScalef(1,1,-1);
			glTranslatef(28,20,20);
			hasteHolofote();
		glPopMatrix();
		glPushMatrix();
			glScalef(-1,1,-1);
			glTranslatef(28,20,20);
			hasteHolofote();
		glPopMatrix();
		//central hastes
		glPushMatrix();
			glTranslatef(0,20,0);
			hasteHolofote();
		glPopMatrix();
	
		glPushMatrix();
			glTranslatef(15,20,0);
			hasteHolofote();
		glPopMatrix();
		glPushMatrix();
			glScalef(-1,1,1);
			glTranslatef(15,20,0);
			hasteHolofote();
		glPopMatrix();


		//holofote central
		glPushMatrix();
			glTranslatef(0,19,0);
			glPushMatrix();
				glRotatef(hCentral, 0,0,1);
				holofote();
			glPopMatrix();
		glPopMatrix();
	
		glPushMatrix();	
				glPushMatrix();
					glTranslatef(15,19,0);
					glRotatef(90, 0,1,0);
					glPushMatrix();
						glRotatef(hCentral, 0,0,1);
						holofote();
					glPopMatrix();
				glPopMatrix();
		glPopMatrix();
		
		glPushMatrix();
				glPushMatrix();
					glScalef(-1,1,1);
					glTranslatef(15,19,0);
					glRotatef(90, 0,1,0);
					glPushMatrix();
						glRotatef(hCentral, 0,0,1);
						holofote();
					glPopMatrix();
				glPopMatrix();
		glPopMatrix();
		//holofotes Laterais

		glPushMatrix();
			glTranslatef(28,19,20);
			glRotatef(135,0,1,0);
			glPushMatrix();
				glRotatef(hLateral2, 0,0,1);
				holofote();
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();	
				glScalef(-1,1,1);
				glPushMatrix();
					glTranslatef(28,19,20);
					glRotatef(135,0,1,0);
					glPushMatrix();
						glRotatef(hLateral, 0,0,1);
						holofote();
					glPopMatrix();
				glPopMatrix();
		glPopMatrix();		
		
		glPushMatrix();
				glScalef(1,1,-1);
				glPushMatrix();
					glTranslatef(28,19,20);
					glRotatef(135,0,1,0);
					glPushMatrix();
						glRotatef(hLateral, 0,0,1);
						holofote();
					glPopMatrix();
				glPopMatrix();
		glPopMatrix();
		glPushMatrix();
				glScalef(-1,1,-1);
				glPushMatrix();
					glTranslatef(28,19,20);
					glRotatef(135,0,1,0);
					glPushMatrix();
						glRotatef(hLateral2, 0,0,1);
						holofote();
					glPopMatrix();
				glPopMatrix();
		glPopMatrix();
	if(ligaLuzes){
			//luzes
			glPushMatrix();
				glTranslatef(0,19,0);
				glRotatef(hCentral, 0,0,1);
				glTranslatef(0,-50,0);
				glPushMatrix();	
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glColor4f(0,1,0,0.2);
					luzA();
				glPopMatrix();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(15,19,0);
				glRotatef(90,0,1,0);
				glRotatef(hCentral, 0,0,1);
				glTranslatef(0,-50,0);
				glPushMatrix();	
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glColor4f(0.8,0.5,0.1,0.2);
					luzA();
				glPopMatrix();
			glPopMatrix();

			glPushMatrix();
				glScalef(-1,1,1);
				glTranslatef(15,19,0);
				glRotatef(90,0,1,0);
				glRotatef(hCentral, 0,0,1);
				glTranslatef(0,-50,0);
				glPushMatrix();	
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glColor4f(0.6,0.1,0.3,0.2);
					luzA();
				glPopMatrix();
			glPopMatrix();



			//luzes laterais
				glPushMatrix();
					glTranslatef(28,0,20);
					glRotatef(135,0,1,0);
					glPushMatrix();
						glTranslatef(0,19,0);
						glRotatef(hLateral2, 0,0,1);
						glTranslatef(0,-50,0);
						glPushMatrix();	
							glEnable(GL_BLEND);
							glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
							glColor4f(1,0,0,0.2);
							luzA();
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			

				glPushMatrix();
					glScalef(-1,1,1);
					glTranslatef(28,0,20);
					glRotatef(135,0,1,0);
					glPushMatrix();
						glTranslatef(0,19,0);
						glRotatef(hLateral, 0,0,1);
						glTranslatef(0,-50,0);
						glPushMatrix();	
							glEnable(GL_BLEND);
							glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
							glColor4f(0,0,1,0.2);
							luzA();
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
				
				glPushMatrix();
					glScalef(1,1,-1);
					glTranslatef(28,0,20);
					glRotatef(135,0,1,0);
					glPushMatrix();
						glTranslatef(0,19,0);
						glRotatef(hLateral, 0,0,1);
						glTranslatef(0,-50,0);
						glPushMatrix();	
							glEnable(GL_BLEND);
							glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
							glColor4f(0,1,1,0.2);
							luzA();
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
				
				
				glPushMatrix();
					glScalef(-1,1,-1);
					glTranslatef(28,0,20);
					glRotatef(135,0,1,0);
					glPushMatrix();
						glTranslatef(0,19,0);
						glRotatef(hLateral2, 0,0,1);
						glTranslatef(0,-50,0);
						glPushMatrix();	
							glEnable(GL_BLEND);
							glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
							glColor4f(0.2,1,0.5,0.2);
							luzA();
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
	}
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

		case 'l':
		case 'L':
			ligaLuzes = !ligaLuzes;
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


