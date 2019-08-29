#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <glut.h>

#define pi (2*acos(0.0))

double cameraHeight;
double cameraAngle;
int bullet=0;
int drawgrid;
int drawaxes;
double angle;
double angle_c_z=0;
double angle_c_x=0, angle_t_x=0, angle_t_z=0;
double limit=0.0;

struct point
{
	double x,y,z;
};

struct point pos,l,u,r;
double X=0,Z=0;
int Y=-1;
struct point arra[100];
void drawAxes()
{
	if(drawaxes==1)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);{
		    glColor3f(0.0f,1.0f,0.0f);
			glVertex3f( 1000,0,0);
			glVertex3f(-1000,0,0);

            glColor3f(1.0f,0.0f,0.0f);
			glVertex3f(0,-1000,0);
			glVertex3f(0, 1000,0);

            glColor3f(0.0f,0.0f,1.0f);
			glVertex3f(0,0, 1000);
			glVertex3f(0,0,-1000);
		}glEnd();
	}
}


void drawGrid()
{
	int i;
	if(drawgrid==1)
	{
		glColor3f(0.6, 0.6, 0.6);	//grey
		glBegin(GL_LINES);{
			for(i=-8;i<=8;i++){

				if(i==0)
					continue;	//SKIP the MAIN axes

				//lines parallel to Y-axis
				glVertex3f(i*10, -90, 0);
				glVertex3f(i*10,  90, 0);

				//lines parallel to X-axis
				glVertex3f(-90, i*10, 0);
				glVertex3f( 90, i*10, 0);
			}
		}glEnd();
	}
}


void draw_circle_line(double radius,int segments)
{
  int i;
    struct point points[100];
    glColor3f(0.7,0.7,0.7);

    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    glBegin(GL_LINES);
    {
        for(i=0;i<segments;i++)
        {

            glVertex3f(points[i].x,points[i].y,0);
            glVertex3f(points[i+1].x,points[i+1].y,0);

        }
    }
        glEnd();
}


void drawSphere(double radius,int slices,int stacks,float r,float g,float b)
{
	struct point points[100][100];
	int i,j;
	double h,r1;

	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r1=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r1*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r1*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
	}

	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        glColor3f(((double)i/(double)stacks)*r,((double)i/(double)stacks)*g,((double)i/(double)stacks)*b);

		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{

			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);

                //lower hemisphere
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
			}glEnd();
		}
	}
}

//////////// GENERATING THE SOLAR SYSTEM /////////////////////////////

void drawSS()
{
    drawSphere(50,30,30,1.5, 1.0, 0.0);    //SUN

     glPushMatrix();                       //MERCURY
        draw_circle_line(90,40);
        glRotatef(angle*4.64,0,0,1);
        glTranslatef(90,0,0);
        drawSphere(10,30,30,0.5, 0.4, 0.4);
    glPopMatrix();

    glPushMatrix();                        //VENUS
        draw_circle_line(130,40);
        glRotatef(angle*3.54,0,0,1);
        glTranslatef(130,0,0);
        drawSphere(15,30,30,0.6, 0.6, 0.2);
    glPopMatrix();

    glPushMatrix();                        //EARTH
        draw_circle_line(170,40);
        glRotatef(angle*2.97,0,0,1);
        glTranslatef(170,0,0);
        drawSphere(20,30,30,0.4, 1.3, 1.0);

        glPushMatrix();                   //EARTH MOON
            draw_circle_line(30,40);
            glRotatef(angle*5.3,0,0,1);
            glTranslatef(30,0,0);
            drawSphere(4,30,30,1.0, 1.0, 1.0);
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();                        //MARS
        draw_circle_line(230,40);
        glRotatef(angle*2.43,0,0,1);
        glTranslatef(230,0,0);
        drawSphere(22,30,30,1.0, 0.2, 0.0);
    glPopMatrix();


    glPushMatrix();                       //JUPITER
        draw_circle_line(300,40);
        glRotatef(angle*1.35,0,0,1);
        glTranslatef(300,0,0);
        drawSphere(32,30,30,0.8, 0.6, 0.3);
    glPopMatrix();

    glPushMatrix();                      //SATURN
        draw_circle_line(390,40);
        glRotatef(angle*0.99,0,0,1);
        glTranslatef(390,0,0);
        drawSphere(29,30,30,0.9, 0.8, 0.3);

        glPushMatrix();                 //TITAN [SATURN LARGEST MOON]
            draw_circle_line(37,40);
            glRotatef(angle*2.42,0,0,1);
            glTranslatef(37,0,0);
            drawSphere(7.5,30,30,1.0, 0.5, 0.0);
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();                     //URANUS
        draw_circle_line(470,40);
        glRotatef(angle*0.67,0,0,1);
        glTranslatef(470,0,0);
        drawSphere(25,30,30,0.4, 1.2, 1.7);
    glPopMatrix();

    glPushMatrix();                     //NEPTUNE
        draw_circle_line(556,40);
        glRotatef(angle*0.57,0,0,1);
        glTranslatef(556,0,0);
        drawSphere(23,30,30,0.0, 0.0, 0.5);

        glPushMatrix();                 //TRITON [NEPTUNE LARGEST MOON]
            draw_circle_line(32,40);
            glRotatef(angle*3.41,0,0,1);
            glTranslatef(32,0,0);
            drawSphere(3.6,30,30,0.9, 0.7, 0.7);
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();                     //PLUTO
        draw_circle_line(610,40);
        glRotatef(angle*0.45,0,0,1);
        glTranslatef(610,0,0);
        drawSphere(5,30,30,0.7, 0.7, 0.7);
    glPopMatrix();
}

void keyboardListener(unsigned char key, int xx,int yy){
    double x,y,z;
    double rate = 0.01;
	switch(key){

		case '1':

			{
            x=l.x;y=l.y;z=l.z;
			l.x = l.x*cos(rate)+1*r.x*sin(rate);
			l.y = l.y*cos(rate)+r.y*sin(rate);
			l.z = l.z*cos(rate)+r.z*sin(rate);

			r.x = r.x*cos(rate)-x*sin(rate);
			r.y = r.y*cos(rate)-y*sin(rate);
			r.z = r.z*cos(rate)-z*sin(rate);}
			break;
        case '2':

			{
            x=l.x;y=l.y;z=l.z;
			l.x = l.x*cos(-rate)+r.x*sin(-rate);
			l.y = l.y*cos(-rate)+r.y*sin(-rate);
			l.z = l.z*cos(-rate)+r.z*sin(-rate);

			r.x = r.x*cos(-rate)-x*sin(-rate);
			r.y = r.y*cos(-rate)-y*sin(-rate);
			r.z = r.z*cos(-rate)-z*sin(-rate);
			}
			break;
        case '3':
            x=l.x;y=l.y;z=l.z;
			l.x = l.x*cos(rate)+u.x*sin(rate);
			l.y = l.y*cos(rate)+u.y*sin(rate);
			l.z = l.z*cos(rate)+u.z*sin(rate);

			u.x = u.x*cos(rate)-x*sin(rate);
			u.y = u.y*cos(rate)-y*sin(rate);
			u.z = u.z*cos(rate)-z*sin(rate);
			break;
        case '4':
            x=l.x;y=l.y;z=l.z;
			l.x = l.x*cos(-rate)+1*u.x*sin(-rate);
			l.y = l.y*cos(-rate)+u.y*sin(-rate);
			l.z = l.z*cos(-rate)+u.z*sin(-rate);

			u.x = u.x*cos(-rate)-x*sin(-rate);
			u.y = u.y*cos(-rate)-y*sin(-rate);
			u.z = u.z*cos(-rate)-z*sin(-rate);
			break;
        case '6':
            x=r.x;y=r.y;z=r.z;
			r.x = r.x*cos(rate)+u.x*sin(rate);
			r.y = r.y*cos(rate)+u.y*sin(rate);
			r.z = r.z*cos(rate)+u.z*sin(rate);

			u.x = u.x*cos(rate)-x*sin(rate);
			u.y = u.y*cos(rate)-y*sin(rate);
			u.z = u.z*cos(rate)-z*sin(rate);
			break;
        case '5':
            x=r.x;y=r.y;z=r.z;
			r.x = r.x*cos(-rate)+u.x*sin(-rate);
			r.y = r.y*cos(-rate)+u.y*sin(-rate);
			r.z = r.z*cos(-rate)+u.z*sin(-rate);

			u.x = u.x*cos(-rate)-x*sin(-rate);
			u.y = u.y*cos(-rate)-y*sin(-rate);
			u.z = u.z*cos(-rate)-z*sin(-rate);
			break;
        case 'q':
            if(angle_c_z<45){
                angle_c_z+=1.5;
            }
            break;
        case 'w':
            if(angle_c_z>-45){
                angle_c_z-=1.5;
            }
            break;
        case 'e':
            if(angle_c_x<45){
                angle_c_x+=1.5;
            }
            break;
        case 'r':
            if(angle_c_x>-45){
                angle_c_x-=1.5;
            }
            break;
        case 'a':
            if ( angle_t_x<45){
                    angle_t_x+=1.5;
            }
            break;
        case 's':
            if ( angle_t_x>-45){
                    angle_t_x-=1.5;
            }
            break;
         case 'd':
            if ( angle_t_z<45){
                    angle_t_z+=1.5;
            }
            break;
        case 'f':
            if ( angle_t_z>-45){
                    angle_t_z-=1.5;
            }
            break;



		default:
			break;
	}

}


void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_UP:		//down arrow key
			pos.x+=l.x;
			pos.y+=l.y;
			pos.z+=l.z;
			break;
		case GLUT_KEY_DOWN:		// up arrow key
			pos.x-=l.x;
			pos.y-=l.y;
			pos.z-=l.z;
			break;

		case GLUT_KEY_LEFT :
			pos.x+=r.x;
			pos.y+=r.y;
			pos.z+=r.z;
			break;
		case GLUT_KEY_RIGHT :
			pos.x-=r.x;
			pos.y-=r.y;
			pos.z-=r.z;
			break;

		case GLUT_KEY_PAGE_UP:
		    pos.x+=u.x;
			pos.y+=u.y;
			pos.z+=u.z;
			break;
		case GLUT_KEY_PAGE_DOWN:
            pos.x-=u.x;
			pos.y-=u.y;
			pos.z-=u.z;
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
		    if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				/*bullet =1;
				double length = 649;
				//double length = (649/cos(angle_c_x*pi/180))/cos(angle_t_x*pi/180);
                printf("---> %lf\n",length);
                //X = length* sin(angle_c_z*pi/180);
                X= length* tan(angle_c_z*pi/180);

                Z=-100*sin(angle_c_x*pi/180)-(649-100*cos(angle_c_x*pi/180))*tan((angle_t_x+angle_c_x)*pi/180);*/



			}
			break;


		case GLUT_RIGHT_BUTTON:
		    if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				drawaxes=1-drawaxes;
				//(600/cos(angle_c_x*pi/180))/cos(angle_t_x*pi/180);
			}
			break;
			//........

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}



void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(100,100,100,	0,0,0,	0,0,1);
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	gluLookAt(pos.x,pos.y,pos.z,	pos.x+l.x,pos.y+l.y,pos.z+l.z,	u.x,u.y,u.z);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	drawGrid();

    drawSS();
	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){
	//display();
	angle+=.1;
	//codes for any changes in Models, Camera
	limit+=0.01;
	if(limit>=50.0)
    {
        limit=0;
    }
	glutPostRedisplay();
}

void init(){
	//codes for initialization
	drawgrid=0;
	drawaxes=1;
	//cameraHeight=150.0;
	//cameraAngle=1.0;
	//angle=0;

	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	5000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv){
    pos.x=0;
    pos.y=0;
    pos.z=-800;
    l.x=0;u.x=-1;r.x=0;
    l.y=0;u.y=0;r.y=1;
    l.z=1;u.z=0;r.z=0;
	glutInit(&argc,argv);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
