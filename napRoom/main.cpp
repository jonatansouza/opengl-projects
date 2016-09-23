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
void customSquare(float size);


//global variables
float moveWindow = 360;
bool openWindow = false;

bool orto = true;
bool eixos = true;
bool wire = false;
bool ligaLuzes = false;
float win = 10.0f;
float aspecto;
float angulo = 30.0f;
int objeto = 0;

//funcoes
void customSquare(float size);
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

void open(int i){
    if(openWindow){
      if(moveWindow >= 200)
        moveWindow -= 2;
    }else{
      if(moveWindow <= 358)
      moveWindow += 2;
    }
    glutPostRedisplay();
    glutTimerFunc(100,open,1);
}

int main (int argc, char *argv[]){
	//escopo de criacao de janela
	glutInit(&argc, argv);
	glutInitWindowSize(1000, 800);
	glutInitWindowPosition(10, 10);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Quarto da Soneca");
	//fim do escopo de criacao

	//escopo de registro de callbacks
	inicializa();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
  glutTimerFunc(100,open,1);

	//fim do escopo de registro

	//demais
	glutMainLoop();//nao colocar nada apos esta funcao pois nao aparecera
	return 0;
}

void customSquare(float size){
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
void desenhaEsfera(float r, float s, float st){

	if(wire){
		glutWireSphere(r, s, st);
	}else{
		glutSolidSphere(r, s, st);
	}

}

void cilindro(float raio, float heigth_c){
      float x, y;
      int i = 0;
      glLineWidth(1);
      glBegin(GL_POLYGON);
        for(i=0;i<360;i++){
            x = cos((i*M_PI)/180) * raio;
            y = sin((i*M_PI)/180) * raio;
             glVertex3f(x,y,0);
        }
      glEnd();
      glBegin(GL_POLYGON);
        for(i=0;i<360;i++){
            x = cos((i*M_PI)/180) * raio;
            y = sin((i*M_PI)/180) * raio;
            glVertex3f(x,y,heigth_c);
        }
      glEnd();
      glBegin(GL_QUAD_STRIP);
        for(i=0;i<360;i++){
            x = cos((i*M_PI)/180) * raio;
            y = sin((i*M_PI)/180) * raio;
            glVertex3f(x,y,0);
            glVertex3f(x,y,heigth_c);
        }
      glEnd();
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

void bed(){
  //colchao
  glPushMatrix();
  glTranslatef(0,5,0);
  glColor3f(0.8,0.8,1)  ;
  glScalef(0.85,0.05,0.45);
  customSquare(50);
  glPopMatrix();

  //base
  glColor3f(0.80,0.50,0.15)  ;
  glPushMatrix();
    glColor3f(1,1,1)  ;
    glScalef(0.9,0.2,0.5);
    customSquare(50);
  glPopMatrix();


  //cabeceira
  glPushMatrix();
    glTranslatef(21, 4,0);
    glScalef(0.07,0.5,0.5);
    customSquare(50);
  glPopMatrix();
  //pes
  glPushMatrix();
    glTranslatef(-20, -6.5, 10);
    glScalef(0.7,0.7,0.7);
    customSquare(5);
  glPopMatrix();
  glPushMatrix();
    glScalef(1,1,-1);
      glPushMatrix();
        glTranslatef(-20, -6.5, 10);
        glScalef(0.7,0.7,0.7);
        customSquare(5);
      glPopMatrix();
  glPopMatrix();
}

void wardrobeFoot(){
  glPushMatrix();
    glColor3f(0.8,0.8,1);
    glTranslatef(-15,-26,6);
    glScalef(0.8,1,0.8);
    customSquare(2);
  glPopMatrix();

}

//gaveta
void wardrobeDrawer(){
  //base
  glPushMatrix();
    glTranslatef(-8.5,-17.5,0.5);
    glScalef(0.8,0.2,0.8);
    customSquare(20);
  glPopMatrix();

  //puxador
  glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(-8.5,-17.5,9);
    glScalef(0.8,0.2,0.2);
    customSquare(5);
  glPopMatrix();

}

void wardrobePort(){
  //porta
  glPushMatrix();
    glColor3f(0.8,0.8,1);
    glTranslatef(-8.5,5,7.5);
    glScalef(0.33,0.75,0.03);
    customSquare(50);
  glPopMatrix();

  //puxador
  glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(-2,1,8.5);
    glScalef(0.2,0.8,0.2);
    customSquare(5);
  glPopMatrix();
}

//armario
void wardrobe(){
  //base
  glPushMatrix();
    glColor3f(1,1,1);
    glScalef(0.7,1,0.3);
    customSquare(50);
  glPopMatrix();

  //portas
  glPushMatrix();
    wardrobePort();
  glPopMatrix();
  glPushMatrix();
    glScalef(-1,1,1);
    wardrobePort();
  glPopMatrix();

  //gavetas
  glPushMatrix();
    glColor3f(0.8,0.8,1);
    wardrobeDrawer();
  glPopMatrix();
  glPushMatrix();
    glColor3f(0.8,0.8,1)  ;
    glTranslatef(0,-4.5,0);
    wardrobeDrawer();
  glPopMatrix();
  glPushMatrix();
    glColor3f(0.8,0.8,1)  ;
    glScalef(-1,1,1);
    glPushMatrix();
      wardrobeDrawer();
    glPopMatrix();
    glPushMatrix();
      glColor3f(0.8,0.8,1)  ;
      glTranslatef(0,-4.5,0);
      wardrobeDrawer();
    glPopMatrix();
  glPopMatrix();

  //pes
  glPushMatrix();
    wardrobeFoot();
  glPopMatrix();
  glPushMatrix();
    glScalef(-1,1,1);
    wardrobeFoot();
  glPopMatrix();
  glPushMatrix();
    glScalef(1,1,-1);
    wardrobeFoot();
  glPopMatrix();
  glPushMatrix();
    glScalef(1,1,-1);
    glPushMatrix();
      glScalef(-1,1,1);
      wardrobeFoot();
    glPopMatrix();
  glPopMatrix();
}

void floor(){
  glPushMatrix();
    glScalef(1,0.05,1);
    customSquare(70);
  glPopMatrix();
}

void wall(){
  glPushMatrix();
    glScalef(0.01,0.5,1);
    customSquare(70);
  glPopMatrix();
}

void landscape(){
  glPushMatrix();
    glColor3f(0.2,0.5,0.85);
    glScalef(1,0.7,0.05);
    customSquare(20);
  glPopMatrix();
}

void windowDoors(){
  glPushMatrix();
    glTranslatef(-10,0,0);
    glPushMatrix();
      glRotatef(moveWindow, 0,1,0);
      glTranslatef(5,0,0);
      glScalef(0.5,0.7,0.08);
      customSquare(20);
    glPopMatrix();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(10,0,0);
    glPushMatrix();
      glRotatef(-moveWindow, 0,1,0);
      glTranslatef(-5,0,0);
      glScalef(0.5,0.7,0.08);
      customSquare(20);
    glPopMatrix();
  glPopMatrix();


}
void windowFrame(){
  glPushMatrix();
    glTranslatef(0,7,0);
    glScalef(1,0.05,0.08);
    customSquare(20);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(-10,0,0);
    glScalef(0.05,0.75,0.08);
    customSquare(20);
  glPopMatrix();
}

void window(){
  //vista azul
  glPushMatrix();
    landscape();
  glPopMatrix();
  //trave superior
  glColor3f(0.5,0.2,0.1);
  glPushMatrix();
    windowFrame();
  glPopMatrix();

  //trave inferior
  glPushMatrix();
    glScalef(-1,-1,1);
    windowFrame();
  glPopMatrix();

  //portas da janela
  glPushMatrix();
    windowDoors();
  glPopMatrix();
}

void backWall(){
  glPushMatrix();
    glScalef(1,0.5,0.01);
    customSquare(70);
  glPopMatrix();
  //janela
  glPushMatrix();
    window();
  glPopMatrix();

  glColor3f(0.9,0.9,0.5);

}


void roomBase(){
  glColor3f(0.9,0.9,0.5);
  floor();
  //parede direita
  glPushMatrix();
    glTranslatef(34.7,16,0);
    wall();
  glPopMatrix();
  //parede esquerda
  glPushMatrix();
    glScalef(-1,1,1);
    glTranslatef(34.7,16,0);
    wall();
  glPopMatrix();
  //parede fundo
  glPushMatrix();
    glTranslatef(0,16,-34.7);
    backWall();
  glPopMatrix();
  glPushMatrix();
    glTranslatef(0,35,0);
    floor();
  glPopMatrix();

}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
      roomBase();
      /*bed();
      wardrobe();*/
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

    case 'j':
    case 'J':
      openWindow = !openWindow;
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
