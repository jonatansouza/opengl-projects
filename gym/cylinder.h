/**
*@author Jonatan Souza
*
*/

//Esta funcao desenha o cilindro simetrico
//raio - raio do cilindro,  heigth_c - altura do cilindro

void drawCylinder(float raio, float heigth_c){
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

//Esta funcao desenha o cilindro Assimetrico
//raio - raio do cilindro,  heigth_c - altura do cilindro, 
//deform - valor em porcentagem para deformar um cilindro,
//ex deform = 0.5 um lado do cilindro vai ter o valor do raio
//e o outro 50% do seu raio, formando algo perto de um cone

void drawCylinderDeform(float raio, float heigth_c, float deform){
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
          	glVertex3f(x*deform,y*deform,heigth_c);
      	}
      glEnd();
      glBegin(GL_QUAD_STRIP);
      	for(i=0;i<360;i++){
          	x = cos((i*M_PI)/180) * raio;
          	y = sin((i*M_PI)/180) * raio;
          	glVertex3f(x,y,0);
          	glVertex3f(x*deform,y*deform,heigth_c);
      	}
      glEnd();
  }


