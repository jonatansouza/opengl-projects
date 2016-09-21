/**
   @AUTHOR Priscila Silva
   *Trabalho de icg
   *Professora Sicilia
 */

#include <GL/glut.h>

#include <iostream>

#include <cstdio>
#include <cstdlib>
#include <cmath>


/** Limites da orto.  */
float minx = -5.0, maxx = 5.0,
      miny = -1.0, maxy = 8.0,
      minz = -5.0, maxz = 5.0;

//trava o botao key up
bool onTheFloor = true;

/** N�mero de screens que ser�o desenhadas.  */
const int n_screens = 32;

/** Deslocamento da orto.  */
float px = 0.0, py = 0.0;

/** Deslocamento do personagem.  */
float dx = 0.0, dy = 0.0;

/** Deslocamento do bug.  */
float bx = 0.0;

/** Cores Padr�o  */
const float cores[3] = { 0.6, 0.8, 0.99 };

/** Exibir eixos?  */
bool eixos = false;

/** Textura sonic running.  */
int t_android_w, t_android_h;
GLuint t_android, t_android_running;

/**
 * Escopo de cria��o de janela.
 */
void initSystem(int *argc, char *argv[]);

/**
 * Callback que gera e exibe novo quadro.
 */
void display();

/**
 * Fun��es para carregar uma textura de arquivo de imagem no formato bmp.
 */
void colocaImagem(GLuint tex);
void loadTex(const char *c, GLuint *texid, int *w, int *h);
char *load_bmp(const char *name, int *w, int *h);

/**
 * Callback que redimensiona a janela.  Veja ``projecao''.
 */
void reshape(int w, int r);

/**
 * Callback que captura eventos (somente ASCII) do teclado.
 */
void keyboard(unsigned char c, int x, int y);

/**
 * Callback que captura eventos (n�o ASCII) do teclado.
 */
void special(int c, int x, int y);

/**
 * Callback que captura clicks do mouse.
 */
void mouse(int b, int s, int x, int y);

/**
 * Envelopa a l�gica para redimensionar a janela.
 */
void projecao();

/**
 * Escopo de registro de callbacks.
 */
void registerCallbacks();

/**
 * Desenha os eixos para 2D.
 */
void desenhaEixos();

/**
 * Desenha um quadrado de largura `w', altura `h' e origem no ponto
 * (`x', `y').
 */
void drawSquare(float x, float y, float w, float h);

/**
 * Desenha um c�rculo simples.  O ponto central � (`cx', `cy') e o raio mede
 * `r'.
 */
void drawCirle(float r, float cx, float cy);

/**
 * Desenha o personagem.
 */
void gameHero();

/**
 * Desenha o cenario.
 */
void scene();

/**
 * Desenha o ch�o por um n�mero de `screens' a partir de `minx'.
 */

void sceneFloor(int screens);
void sceneBackgroud(int screens);
void sceneObjects(int screens, float distance, float occur);
void sceneMontain(float x, float largura, float altura);

/**
 * Centralizar.
 */
void center();

/**
 * Faz o personagem saltar.
 */
void jumpStandBy(int i);


int main(int argc, char *argv[])
{
  initSystem(&argc, argv);
  registerCallbacks();

  glutMainLoop();

  return 0;
}


void initSystem(int *argc, char *argv[])
{
  glutInit(argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Android Adventure");

  loadTex("android.bmp", &t_android, &t_android_w, &t_android_h);
}

void registerCallbacks()
{
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutMouseFunc(mouse);
}


char *load_bmp(const char *name, int *w, int *h)
{
  int of;
  int by;
  int x, y, i;
  char *tmp_m, *m;

  FILE *f = fopen(name, "rb");

  if (f == NULL)
    {
      exit(0);
    }

  fseek(f, 10, SEEK_SET);
  fread(&of, sizeof(int), 1, f);
  fseek(f, 4, SEEK_CUR);
  fread(w, sizeof(int), 1, f);
  fread(h, sizeof(int), 1, f);

  fseek(f, of, SEEK_SET);

  by = ((*w * 3 + 3) / 4) * 4 - (*w * 3 % 4);
  tmp_m = (char*)malloc(sizeof(char) * by * (*h));
  m = (char*)malloc(sizeof(char) * (*w) * (*h) * 3);

  fread(tmp_m, sizeof(char) * by * (*h), 1, f);

  for (y = 0; y < *h; y++)
    {
      for (x = 0; x < *w; x++)
        {
          for (i = 0; i < 3; i++)
            {
              m[3 * ((*w) * y + x) + i] = tmp_m[3 * ((*w) * y + x) + (2 - i)];
            }
        }
    }

  free(tmp_m);
  return m;
}

void loadTex(const char *c, GLuint *texid, int *w, int *h)
{
  char *wa = load_bmp(c, w, h);

  glGenTextures(1, texid);
  glBindTexture(GL_TEXTURE_2D, *texid);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, *w, *h, 0, GL_RGB, GL_UNSIGNED_BYTE, wa);

  free(wa);
}


void colocaImagem(GLuint tex)
{
  float cores_borda[4] = { 1.0, 1.0, 1.0, 1.0 };

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, tex);

  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, cores_borda);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  scene();
  gameHero();

  glutSwapBuffers();
}

void reshape(int w, int h)
{
  glViewport(0, 0, w, h);
  projecao();
}

void projecao()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(minx + px, maxx + px, miny + py, maxy + py, minz, maxz);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void keyboard(unsigned char c, int x, int y)
{
  switch (c)
    {
    case 'a':                             /* axis */
      eixos = !eixos;
      break;

    case 'q':                             /* quit */
    case 27:                             /* ESCAPE */
      exit(0);
    }
  glutPostRedisplay();
}

void center()
{
  dx = px = 0;
  dy = py = 0;
}

void special(int c, int x, int y)
{
// TODO: pegar o n�mero de janelas (30) dinamicamente.
  const float meio_tela = (maxx - minx) / 2.0f;
  const float passo = 0.3f;

  switch (c)
    {
    case GLUT_KEY_RIGHT:
      //t_android = t_android_running;
      if (dx < (maxx * n_screens))
        {
          dx += passo;
          px += passo;
        }
      break;

    case GLUT_KEY_LEFT:
      //t_android = t_android_running;
      if (dx > (minx + meio_tela))
        {
          dx += -passo;
          px += -passo;
        }
      break;

    case GLUT_KEY_UP:
      if (onTheFloor)
        {
          glutTimerFunc(0, jumpStandBy, 1);
        }
      break;

    case GLUT_KEY_HOME:
      center();
      break;
    }

  projecao();
  glutPostRedisplay();
}

void mouse(int b, int s, int x, int y)
{
  switch (b)
    {
    case GLUT_LEFT_BUTTON:
      if (s == GLUT_DOWN)
        {
          glutTimerFunc(0, jumpStandBy, 1);
        }
    }
}


void jumpBackToFloor(int i)
{
  if (dy <= 0.1)
    {
      dy = 0;
      onTheFloor = true;
      glutPostRedisplay();
      return;
    }
  dy -= 0.1;
  glutPostRedisplay();
  glutTimerFunc(50, jumpBackToFloor, ++i);
}

void jumpStandBy(int i)
{
  onTheFloor = false;
  if (i == 20)
    {
      glutPostRedisplay();
      glutTimerFunc(50, jumpBackToFloor, ++i);
      return;
    }
  dy += 0.1;

  glutPostRedisplay();
  glutTimerFunc(50, jumpStandBy, ++i);
}
void drawSquare(float x, float y, float w, float h)
{
  glVertex2f(x, y + h);
  glVertex2f(x, y);
  glVertex2f(x + w, y);
  glVertex2f(x + w, y + h);
}

void drawTriangle(float x, float y, float w, float h)
{
  glVertex2f(x, y);
  glVertex2f(x + w, y);
  glVertex2f(x + (w / 2), y + h);
}


void drawCirle(float r, float cx, float cy)
{
  int t;
  float x, y, t_rad;

  for (t = 0; t < 360; t += 10)
    {
      t_rad = t * M_PI / 180.0;

      x = cos(t_rad) * r + cx;
      y = sin(t_rad) * r + cy;

      glVertex2f(x, y);
    }
}

void gameHero()
{
  const float r = 1.0;

  colocaImagem(t_android);
  glColor3f(0.6, 0.8, 0.99);
  glBegin(GL_QUADS);
  glTexCoord2f(0, 1); glVertex2f(dx, dy + r);
  glTexCoord2f(1, 1); glVertex2f(dx + r, dy + r);
  glTexCoord2f(1, 0); glVertex2f(dx + r, dy);
  glTexCoord2f(0, 0); glVertex2f(dx, dy);
  glEnd();
}



void scene()
{
  sceneBackgroud(n_screens);
  sceneFloor(n_screens);
  sceneObjects(n_screens, 10, 80);
}

void sceneFloor(int screens)
{
  const float screenWidth = maxx - minx;
  const float floorWidth = screens * screenWidth;

  int itr;

  for (itr = 0; itr < floorWidth; itr++)
    {
      glBegin(GL_QUADS);
      if ((itr % 2) == 0)
        {
          glColor3f(0.8, 0.8, 0.8);
        }
      else
        {
          glColor3f(0, 0, 0);
        }
      drawSquare(minx + itr, 0.0, 1, -5);
      glColor3f(cores[0], cores[1], cores[2]);
      glEnd();
    }
}

void sceneBackgroud(int screens)
{
  const float screenWidth = (maxx - minx) * screens;

  glBegin(GL_QUADS);
  glColor3f(0.6, 0.8, 0.99);
  glVertex2f(minx + screenWidth, maxy);
  glVertex2f(minx, maxy);
  glVertex2f(minx, 0);
  glVertex2f(minx + screenWidth, 0);
  glColor3f(cores[0], cores[1], cores[2]);
  glEnd();
}

void sceneSun(float CustomDistance)
{
  glColor3f(1, 0.85, 0);
  glBegin(GL_POLYGON);
  drawCirle(0.7, CustomDistance, 7);
  glEnd();
}

void sceneCloud(float varX, float varY)
{
  glColor3f(1, 1, 1);
  glBegin(GL_POLYGON);
  drawCirle(0.2, 4 + varX, 5 + varY);
  glEnd();
  glBegin(GL_QUADS);
  drawSquare(4 + varX, 4.80 + varY, 2, 0.4);
  glEnd();
  glBegin(GL_POLYGON);
  drawCirle(0.2, 6 + varX, 5 + varY);
  glEnd();

  glBegin(GL_POLYGON);
  drawCirle(0.4, 4.5 + varX, 5 + varY);
  glEnd();
  glBegin(GL_QUADS);
  drawSquare(4.5 + varX, 4.6 + varY, 1, 0.80);
  glEnd();
  glBegin(GL_POLYGON);
  drawCirle(0.4, 5.5 + varX, 5 + varY);
  glEnd();

  glBegin(GL_POLYGON);
  drawCirle(0.55, 5 + varX, 5 + varY);
  glEnd();
}

void sceneObjects(int screens, float distance, float occur)
{
  const float screenWidth = maxx - minx;
  const float floorWidth = screens * screenWidth;
  int r;

  sceneSun((floorWidth / 4));

  srand(2);

  for (int i = 0; i*distance < floorWidth; ++i)
    {
      r = rand() % 100;
      if (r < occur)
        {
          sceneMontain(minx + i * distance, 4, 1);
        }
    }

  for (int i = -3; i <= screens; i++)
    {
      if (i % 2 == 0)
        {
          sceneCloud(i * 10, 1);
        }
      else if (i % 5 == 0)
        {
          sceneCloud(i * 10, 2);
        }
      else
        {
          sceneCloud(i * 10, -0.5);
        }
    }
}

void sceneMontain(float x, float largura, float altura)
{
  glBegin(GL_TRIANGLES);
  glColor3f(0.40, 0.60, 0.40);
  drawTriangle(x, 1, 0.3 * largura,
               0.3 * largura);
  drawTriangle(x, 1.5, 0.3 * largura,
               0.3 * largura);
  drawTriangle(x, 2, 0.3 * largura,
               0.3 * largura);
  glColor3f(cores[0], cores[1], cores[2]);
  glEnd();

  glBegin(GL_QUADS);
  glColor3f(0.349, 0.203, 0.0);
  drawSquare(x + 0.13 * largura, 0.0, 0.1 * largura / 2, altura);
  glColor3f(cores[0], cores[1], cores[2]);
  glEnd();
}
