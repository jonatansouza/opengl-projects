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


