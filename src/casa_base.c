#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>


float posX=0.0,posY=0.0,posZ=0.0;
float transX=0.0,transY=0.0,transZ=0.0;

#define MOV_PLUS_VALUE 3.433
#define HOUSE_WIDTH 4
#define HOUSE_DEPTH 6
#define HOUSE_HEIGHT 2
#define WALLS_THICKNESS 0.2


void movimento(int key,int x,int y){
    //Movimento
    switch (key){
        //movimento para direita
        case GLUT_KEY_RIGHT:
          posY += MOV_PLUS_VALUE;
        break;
        //movimento para esquerda.
        case GLUT_KEY_LEFT:
          posY -= MOV_PLUS_VALUE;
        break;
        //identifica o movimento para cima
        case GLUT_KEY_UP:
          posX += MOV_PLUS_VALUE;
        break;
        //identifica o movimento para baixo.
        case GLUT_KEY_DOWN:
          posX -= MOV_PLUS_VALUE;
        break;

        case GLUT_KEY_F1:
          transZ += MOV_PLUS_VALUE;
        break;

        case GLUT_KEY_F2:
          transZ -= MOV_PLUS_VALUE;
        break;

        case GLUT_KEY_F3:
          transY += MOV_PLUS_VALUE;
        break;

        case GLUT_KEY_F4:
          transY -= MOV_PLUS_VALUE;
        break;

        case GLUT_KEY_F5:
          transX += MOV_PLUS_VALUE;
        break;

        case GLUT_KEY_F6:
          transX -= MOV_PLUS_VALUE;
        break;

        case GLUT_KEY_F7:
          transX = 0.0;
          transY = 0.0;
          transZ = 0.0;
        break;

        default:
         break;
    }
    glutPostRedisplay();
}

void draw_wall(double w, double h, double thickness)
{
	glPushMatrix();
	/*glTranslated(0.5, 0.5 * thickness, 0.5);*/
	glScaled(w, h, thickness);
	glutSolidCube(1);
	glPopMatrix();
}
void draw_hole_wall(double w, double h, double thickness, double hw, double hh)
{
	glPushMatrix();
        glTranslatef(-w/2+(w-hw)/4,0,0);
	glScaled((w-hw)/2, h, thickness);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
        glTranslatef(+w/2-(w-hw)/4,0,0);
	glScaled((w-hw)/2, h, thickness);
	glutSolidCube(1);
	glPopMatrix();
        /*glColor3f(1,0,0);*/

	glPushMatrix();
        glTranslatef(0,+h/2-(h-hh)/4,0);
	glScaled(hw, (h-hh)/2, thickness);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();

        glTranslatef(0,(-h/2+(h-hh)/4),0);
	glScaled(hw, (h-hh)/2, thickness);
	glutSolidCube(1);
	glPopMatrix();
        /*glColor3f(0,0,1);*/
}
void draw_table(double w, double h, double thickness)
{
        glPushMatrix();
        glTranslated(0, 0, 0);
        draw_wall(thickness,h,thickness);
        glPopMatrix();
        glPushMatrix();
        glTranslated(w, 0, 0);
        draw_wall(thickness,h,thickness);
        glPopMatrix();
        glPushMatrix();
        glTranslated(0, 0, w);
        draw_wall(thickness,h,thickness);
        glPopMatrix();
        glPushMatrix();
        glTranslated(w, 0, w);
        draw_wall(thickness,h,thickness);
        glPopMatrix();
        glPushMatrix();
        glTranslated(w/2, h/2+thickness/2, w/2);
        glRotatef(90,1.0,0.0,0.0);
        draw_wall(w+thickness,w+thickness,thickness);
        glPopMatrix();
        /*glPushMatrix();*/
}

void desenha () {

    if (posX==360)
      posX=0;

    if (posY==360)
        posY=0;

    /* clear window */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* future matrix manipulations should affect the modelview matrix */
    glMatrixMode(GL_MODELVIEW);

    glColor3f(0.5f,0.5f,0.5f);

    glPushMatrix();
        //movimentos de rotacao e translacao
        glRotatef(posX,1.0,0.0,0.0);
        glRotatef(posY,0.0,1.0,0.0);
        glTranslatef(transX, transY, transZ);

        // floor
        glColor3f(0.1f,0.4f,0.1f);
        glPushMatrix();
            glTranslatef(0, -HOUSE_HEIGHT/2-WALLS_THICKNESS/2+0.00001, 0);
            glRotatef(90,1.0,0.0,0.0);
            draw_wall(HOUSE_WIDTH*4,HOUSE_DEPTH*4,WALLS_THICKNESS*0.93);
        glPopMatrix();
		
        /*glColor3f(0.2f,0.3f,0.6f);*/
        // right side of the house
        glColor3f(0.444f,0.234f,0.1f);
        glPushMatrix();
            glTranslatef(HOUSE_WIDTH/2, 0, 0);
            glRotatef(90,0.0,1.0,0.0);
            /*draw_wall(HOUSE_DEPTH,HOUSE_HEIGHT,WALLS_THICKNESS);*/
            draw_hole_wall(HOUSE_DEPTH,HOUSE_HEIGHT,WALLS_THICKNESS,HOUSE_DEPTH/3.0,HOUSE_HEIGHT/3.0);
        glPopMatrix();
        /*glColor3f(0.4f,0.3f,0.6f);*/
        // left side of the house
        glPushMatrix();
            glTranslatef(-HOUSE_WIDTH/2, 0, 0);
            glRotatef(90,0.0,1.0,0.0);
            /*draw_wall(HOUSE_DEPTH,HOUSE_HEIGHT,WALLS_THICKNESS);*/
            draw_hole_wall(HOUSE_DEPTH,HOUSE_HEIGHT,WALLS_THICKNESS,HOUSE_DEPTH/3.0,HOUSE_HEIGHT/3.0);
        glPopMatrix();
        /*glColor3f(0.4f,0.3f,0.8f);*/
        // front part of the house
        glPushMatrix();
            glTranslatef(0, 0, HOUSE_DEPTH/2+WALLS_THICKNESS/2);
            /*glRotatef(90,0.0,1.0,0.0);*/
            draw_wall(HOUSE_WIDTH+WALLS_THICKNESS,HOUSE_HEIGHT,WALLS_THICKNESS);
        glPopMatrix();
        // back part of the house
        glPushMatrix();
            glTranslatef(0, 0, -HOUSE_DEPTH/2-WALLS_THICKNESS/2);
            draw_wall(HOUSE_WIDTH+WALLS_THICKNESS,HOUSE_HEIGHT,WALLS_THICKNESS);
        glPopMatrix();
        /*glColor3f(0.8f,0.3f,0.1f);*/
        // floor of the house
        glColor3f(0.644f,0.234f,0.1f);
        glPushMatrix();
            glTranslatef(0, -HOUSE_HEIGHT/2-WALLS_THICKNESS/2+0.01, 0);
            glRotatef(90,1.0,0.0,0.0);
            draw_wall(HOUSE_WIDTH+WALLS_THICKNESS,HOUSE_DEPTH+WALLS_THICKNESS*2,WALLS_THICKNESS);
        glPopMatrix();
        glColor3f(0.444f,0.234f,0.1f);
        /*glColor3f(0.415f,0.1f,0.3f);*/
        // ceil of the house
        glPushMatrix();
            glTranslatef(0, HOUSE_HEIGHT/2+WALLS_THICKNESS/2, 0);
            glRotatef(90,1.0,0.0,0.0);
            draw_wall(HOUSE_WIDTH+WALLS_THICKNESS,HOUSE_DEPTH+WALLS_THICKNESS*2,WALLS_THICKNESS);
        glPopMatrix();
        // ceil top of the house
        glColor3f(0.344f,0.134f,0.0f);
        glPushMatrix();
            glTranslatef(0, HOUSE_HEIGHT/2+WALLS_THICKNESS/2+WALLS_THICKNESS/2, 0);
            glRotatef(-90,1.0,0.0,0.0);
            glScaled((HOUSE_WIDTH+WALLS_THICKNESS)/2,(HOUSE_DEPTH+WALLS_THICKNESS*2)/2,WALLS_THICKNESS);
            glRotatef(-45,0.0,0.0,1.0);
            /*glRotatef(90,1.0,0.0,0.0);*/
            glutSolidCone(1.5,5,4,9);
            /*glutSolidSphere(0.15,20,20);*/
            /*draw_wall(HOUSE_WIDTH+WALLS_THICKNESS,HOUSE_DEPTH+WALLS_THICKNESS*2,WALLS_THICKNESS);*/
        glPopMatrix();
        // door
        glPushMatrix();
            glTranslatef(0, -(HOUSE_HEIGHT-HOUSE_HEIGHT*2.5/3)/2, HOUSE_DEPTH/2+WALLS_THICKNESS/2);
            glColor3f(0.415f,0.4f,0.4f);
            draw_wall(HOUSE_WIDTH/3,HOUSE_HEIGHT*2.5/3,WALLS_THICKNESS+0.001);
        glPopMatrix();

        // Cone outside
        glColor3f(0.415f,0.4f,0.4f);
        glPushMatrix();
            glTranslatef(3, -HOUSE_HEIGHT/2, HOUSE_DEPTH/2+WALLS_THICKNESS/2+1);
            glRotatef(-90,1.0,0.0,0.0);
            glutSolidCone(1,HOUSE_HEIGHT,30,30);
        glPopMatrix();
        // table
        float table_height = 0.5;
        float table_width = 1.0;
        /*glPushMatrix();*/
            /*glTranslatef(-0.5, -HOUSE_HEIGHT/2+table_height/2, HOUSE_DEPTH/2+WALLS_THICKNESS/2-3);*/
            /*[>glRotatef(-90,1.0,0.0,0.0);<]*/
            /*draw_table(1, table_height, 0.1);*/
        /*glPopMatrix();*/

        glPushMatrix();
            glColor3f(0.215f,0.2f,0.2f);
            glTranslatef(-0.5, -HOUSE_HEIGHT/2+table_height/2, HOUSE_DEPTH/2+WALLS_THICKNESS/2-3.7);
            /*glRotatef(-90,1.0,0.0,0.0);*/
            draw_table(table_width, table_height, 0.1);
            glColor3f(0.415f,0.2f,0.2f);
            glTranslatef(table_width/2,table_height,table_width/2);
            glutSolidSphere(0.15,20,20);
        glPopMatrix();
        glPushMatrix();
            glColor3f(0.215f,0.2f,0.2f);
            glTranslatef(-2.5, -HOUSE_HEIGHT/2+table_height/2, HOUSE_DEPTH/2+WALLS_THICKNESS/2+1);
            /*glRotatef(-90,1.0,0.0,0.0);*/
            draw_table(table_width, table_height, 0.1);
            glColor3f(0.415f,0.2f,0.2f);
            glTranslatef(table_width/2,table_height,table_width/2);
            glutSolidSphere(0.15,20,20);
        glPopMatrix();
	/*glPushMatrix();*/
        /*[>glTranslated(0.5, 0.5 * thickness, 0.5);<]*/
        /*glTranslatef(1, -HOUSE_HEIGHT/2+table_height/2, HOUSE_DEPTH/2+WALLS_THICKNESS/2+1.3);*/
	/*glScaled(1, 1,1);*/
	/*glutSolidCube(1);*/
	/*glPopMatrix();*/

    glPopMatrix();

    /* flush drawing routines to the window */
    glFlush();
}

void inicializar(){

    /* set up depth-buffering */
    glEnable(GL_DEPTH_TEST);

    /* define the projection transformation */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //FovY, Aspect, zNear, ZFar
    gluPerspective(45,1,4,20);

    /* define the viewing transformation */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
        glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
glEnable(GL_COLOR_MATERIAL);
GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_position[] = { 1.0, 1.0, 0.0, 0.0 };

glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
glLightfv(GL_LIGHT0, GL_POSITION, light_position);

/*GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 0.0 };*/
   /*GLfloat mat_shininess[] = { 0.001 };*/
   /*glShadeModel (GL_SMOOTH);*/

   /*glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);*/
   /*glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);*/
/*glEnable(GL_LIGHTING);*/
/*glEnable(GL_LIGHT0);*/

/*// Create light components.*/
/*GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };*/
/*GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };*/
/*GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };*/
/*GLfloat position[] = { 0.0f, 0.0f, 0.0f, 1.0f };*/

/*// Assign created components to GL_LIGHT0.*/
/*glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);*/
/*glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);*/
/*glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);*/
/*glLightfv(GL_LIGHT0, GL_POSITION, position);*/

    // set lights
	// eyeX, eyeY, eyeZ
	// Especifica a posicao do olho. Câmera
	//
	// centerX, centerY, centerZ
	// Especifica a posicao do ponto de referencia. Para onde a câmera aponta.
	//
	// upX, upY, upZ
	// Especifica a direção do vetor "Cima". Geralmente, Y.
    gluLookAt(0.0,0.0,10.0,0.0,0.0,0.0,0.0,1.0,0.0);
}

void manage_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
            case 27: 
                exit (0);
                break;

    }
    glutPostRedisplay();
}


int main ( int argc, char * argv[] ) {

    /* initialize GLUT, using any commandline parameters passed to the
       program */
    glutInit(&argc,argv);

    /* setup the size, position, and display mode for new windows */
    glutInitWindowSize(1000,1000);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH);
    /* create and set up a window */
    glutCreateWindow("3D Home");
    glutDisplayFunc(desenha);
    inicializar();
    glutSpecialFunc(movimento);
    glutKeyboardFunc(manage_keyboard);
    glutMainLoop();
}
