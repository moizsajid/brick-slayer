/*
 * bslayer->cpp
 *
 *  Created on: 5th April 2015
 *      Author: Moiz Sajid	
 */
#ifndef BSLAYER_CPP_
#define BSLAYER_CPP_
#include <GL/gl.h>
#include <GL/glut.h>
#include <time.h>
#include <iostream>
#include <cstdlib>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

//defining some MACROS

#define MAX(A,B) ((A) > (B) ? (A):(B)) // finds max of two numbers
#define MIN(A,B) ((A) < (B) ? (A):(B)) // find min of two numbers
#define ABS(A) ((A) < (0) ? -(A):(A))  // find ABS of a given number

// define some constants
// constant FPS (Frame per second) is  used to specify
// number of frames per second in your game.. if FPS is small
// your objects will move slowly and if large your objects
// will move faster, see the Timer function below for further help

#define FPS 10 // frame per seconds

// define another constant to hold ASCII for Escape key.
#define KEY_ESC 27 // A
#define BWIDTH 60
#define BHEIGHT 30

// define some colors as 2D arrays, we have five pre-defined colors here..
// you can add many more if you wish..


 float colors[10][3] = { { 1 / 255.0, 164 / 255.0, 164 / 255.0 },
                        { 215 / 255.0, 0 / 255.0, 96 / 255.0 },
                        { 208 / 255.0, 209 / 255.0, 2 / 255.0 },
                        { 0 / 255.0, 161 / 255.0, 203 / 255.0 },
                        { 50 / 255.0, 116 / 255.0, 44 / 255.0 },
                        {1, 0, 0},
                        {1, 1, 0},
                        {1, 0, 1},
                        {1, 1, 1},
                        {0, 0, 0} };

// defining some utility functions...
/*
 * This function converts an input angle from degree to radians */
 			float Deg2rad(float degree) {
 				return (degree / 180.0) * M_PI;
 			}
// seed the random numbers generator by current time (see the documentation of srand for further help)...
 			void InitRandomizer() {
            srand((unsigned int) time(0)); // time(0) returns number of seconds elapsed since January 1, 1970.
            }
//This function returns a random value within the specified range of [rmin, rmax] ...
long GetRandInRange(const long &rmin, const long &rmax) {
	long range = rmax - rmin; // find the range
	long value = (rand() % (long) range) + rmin; // translate the generated number ...
//	cout << value << endl << flush;
	return value;
}

/*To draw a triangle we need three vertices with each vertex having 2-coordinates [x, y] and a color for the triangle.
 * This function takes 4 arguments first three arguments (3 vertices + 1 color) to
 * draw the triangle with the given color.
 * */
 void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3,
 	float color[]) {
	glColor3fv(color); // Set the triangle color
	// ask library to draw triangle at given position...

	glBegin(GL_TRIANGLES);
	/*Draw triangle using given three vertices...*/
	glVertex4i(x1, y1, 0, 1);
	glVertex4i(x2, y2, 0, 1);
	glVertex4i(x3, y3, 0, 1);
	glEnd();
}
/*To draw a circle we center point coordinates (sx, sy) and the radius along
 * with color array for specifying drawing color ...
 * */
 void DrawCircle(int sx, int sy, float radius, float *color) {

 	const int nvertices = 722;
 	GLfloat vertices[nvertices][2];
 	float hdegree = M_PI / 360.0;
 	float angle = 0;
 	for (int i = 0; i < nvertices; ++i) {
 		vertices[i][0] = radius * cos(angle);
 		vertices[i][1] = radius * sin(angle);
 		angle += hdegree;
 	}
		glColor3fv(color); // set the Circle color
		glBegin(GL_TRIANGLE_FAN);
		glVertex4f(sx, sy, 0, 1);
		for (int i = 0; i < nvertices; ++i)
			glVertex4f(sx + vertices[i][0], sy + vertices[i][1], 0, 1);
//			glVertex4f(sx + mx - 1, sy + my - 1, 0, 1);
		glEnd();
	}
/*To draw a Rectangle we  need point coordinates of bottom left corner
 (sx, sy)  and its width and height (mx, my) and color
 * */
 void DrawRectangle(int sx, int sy, int mx, int my , float *color) {
 	glColor3fv(color);
 	glBegin(GL_TRIANGLES);
 	glVertex4f(sx, sy, 0, 1);
 	glVertex4f(sx + mx - 1, sy, 0, 1);
 	glVertex4f(sx + mx - 1, sy + my - 1, 0, 1);
 	glVertex4f(sx, sy, 0, 1);
 	glVertex4f(sx + mx - 1, sy + my - 1, 0, 1);
 	glVertex4f(sx, sy + my - 1, 0, 1);
 	glEnd();
 }

class Bricks
{
    private:
        int X;
        int Y;

    public :

        bool flag;

        Bricks() {
            X = 0;
            Y = 0;
            flag = false;

        }

        void setX(int x) {
            X = x;
        }

        void setY(int y) {
            Y = y;
        }

        int getX() {
            return X;
        }

        int getY() {
            return Y;
        }
};

class Circle
{
	private:
		int X;
		int Y;
		int inX;
		int inY;
	public:

	    int r;

		Circle() {
			X = GetRandInRange(0, 800);
			Y = GetRandInRange(0, 600);
			inX = 10;
			inY = 10;
			r = 10;
		}
		void setX(int a) {
			X = a;
		}

		void setY(int b) {
			Y = b;
		}

		int getX() {
			return X;
		}

		int getY() {
			return Y;
		}

		int getInX() {
            return inX;
		}

		int getInY() {
            return inY;
		}

		void setInX(int a) {
            inX = a;
		}

		void setInY(int b) {
            inY = b;
 		}
};

class Paddle {
	private:
		int X;
		int Y;
	public:

	    int w;
	    int h;

	    bool cen;
	    bool cor;

		Paddle() {
			X = GetRandInRange(0, 730);
			Y = 0;
			w = 120;
			h = 13;
		}
		void setX(int a) {
			X = a;
		}

		int getX() {
			return X;
		}

		void setY(int b) {
            Y = b;
		}

		int getY() {
            return Y;
		}

		bool collide(int posX, int posY) {

            cen = cor = false;

            if (posX <= X && posX >= X ) {
		        if (posY <= Y) {
                    cen = true;
                    return true;
		        }
            }
            else if ((posX >= X && posX <= X) || (posX <= X && posX >= X)) {
		        if (posY <= Y) {
		        	cor = true;
		            return true;
		        }
            }
            return false;
		}
};

 class BrickSlayer {
 public:

     Circle obj1;
     Paddle obj2;
     Bricks obj3[56];

 	BrickSlayer(int w, int h) {

 		width = w;
 		height = h;


 	}
	// Your  main drawing function, you will be doing all your drawing in this function
	// This function will be automatically called whenever re-drawing is needed, i.e.
	// glutPostRedisplay() function is called or window mouse is moved over the drawing
	// window...
 	void Draw() {

 		//int a = 100;
		//int b = 600;
		int c = 0; // GetRandInRange(0, 2);
		int iu = 0;

		for (int b = 400; b >= 200; b-=30) {
			for (int a = 165; a <= 600; a+=60) {
                obj3[iu].setX(a);
                obj3[iu].setY(b);
                if (obj3[iu].flag)
                    DrawRectangle(735, 565, BWIDTH, BHEIGHT, colors[8]);
                else
                    DrawRectangle(obj3[iu].getX(), obj3[iu].getY(), BWIDTH, BHEIGHT, colors[c]);
				iu++;
			}
			c++;

			if (c == 2) {
				c = 0;
			}
		}

		DrawCircle(obj1.getX(), obj1.getY(), obj1.r, colors[2]);
		DrawRectangle(obj2.getX(), obj2.getY(), obj2.w, obj2.h, colors[4]);

 	}
	/* Function sets canvas size (drawing area) in pixels...
	 *  that is what dimensions (x and y) your game will have
	 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
	 * */
	void Init() { // initialize the drawing canvas
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		// use orthogonal projection with lower left coordinates (0,0) and top right (width, height)
		glOrtho(0, width, 0, height, -1, 1);// set the screen size to given width and height.
	}

	void Reshape(int nw, int nh) {
		glViewport(0, 0, nw, nh);
		glutPostRedisplay();

	}

	int GetWidth() {
		return width;
	}

	int GetHeight() {
		return height;
	}
	// This function will be called automatically by this frequency: 1000.0 / FPS
	void Animate() {
		/*if (obj1.getX() < 100 && obj1.getX() > 400) {
            obj1.setX(obj1.getX() * -1);
		}
		else {
            obj1.setX(obj1.getX() + 10);
		}

		if (obj1.getY() < 100 && obj1.getY() > 400) {
            obj1.setY(obj1.getX() * -1);
		}
		else {
            obj1.setY(obj1.getY() + 10);
		}*/

		if (obj1.getX() < 10 || obj1.getX() > 790) {
            if (obj1.getY() == 0)
                obj1.setX(obj1.getX() + obj1.getInX());
            else
                obj1.setInX(obj1.getInX() * -1);
		}

        obj1.setX(obj1.getX() + obj1.getInX());


		if (/*obj1.getY() < 10 ||*/ obj1.getY() > 590) {
            if (obj1.getY() == 0)
                obj1.setY(obj1.getY() + obj1.getInY());
            else
                obj1.setInY(obj1.getInY() * -1);
		}
        obj1.setY(obj1.getY() + obj1.getInY());

        // Collision Detection
       /* int Dx, Dy;

        int c = 0;

		for (int b = 400; b >= 200; b-=30) {
			for (int a = 165; a <= 600; a+=60) {

			    float Dx, Dy;

                Dx = abs(a - obj1.getX()) - (obj1.r / 2.0 + BWIDTH / 2.0);
                Dy = abs(b - obj1.getY()) - (obj1.r / 2.0 + BHEIGHT / 2.0);

                if (Dx < 0 && Dy < 0) {
                    DrawRectangle(a, b, BWIDTH, BHEIGHT, colors[9]);
                }
			}
			c++;



			if (c == 2) {
				c = 0;
			}

			if ( (obj1.getX() >= obj2.getX()) && (obj1.getX() <= obj2.getX()) && (obj1.getY() == obj2.getY())) {
                obj1.setInX(obj1.getInX() * -1);
                obj1.setX(obj1.getX() + obj1.getInX());
            }

            if ((((obj2.getX() - obj2.w / 2) < obj1.getX()) || ((obj1.getX() > obj2.getX() + obj2.w / 2))) && obj1.getY() == obj2.getY()) {
                obj1.setInX(obj1.getInX() * -1);
                obj1.setX(obj1.getX() + obj1.getInX());
            }



            //if (obj2.collide(obj1.getX(), obj1.getY())) {
            //obj1.setInX(obj1.getInX() * -1);
                //obj1.setX(obj1.getX() + obj1.getInX());
            //}



            if (obj2.h + obj1.r < abs((obj2.getX() - obj1.getX()) - (obj2.getY() - obj1.getY())) ) {

            }

		}*/



		if ( ((obj2.getX()) <= obj1.getX()) && (obj1.getX() <= obj2.getX() + obj2.w) && (obj1.getY() <= obj2.getY() + 25) ) {
            //obj1.setInX(obj1.getInX() * -1);
            obj1.setInY(obj1.getInY() * -1);
            //obj1.setX(obj1.getX() + obj1.getInX());
            //obj1.setY(obj1.getY() + obj1.getInY());
        }
        else if (obj1.getY() < - 20) {
            exit(1);
        }



        // Collision Detection
        for (int i = 0; i < 56; i++) {
            int Dx;
            int Dy;

            Dx = abs(obj1.getX() - obj3[i].getX() + BWIDTH / 2.0 ) - (obj1.r + BWIDTH / 2.0) - 10;
            Dy = abs(obj1.getY() - obj3[i].getY() + BHEIGHT/ 2.0 ) - (obj1.r + BHEIGHT / 2.0) - 10;

            if (Dx < 0 && Dy < 0) {
                cout << "Collision" << (i + 1) << endl;
                obj1.setInX(obj1.getInX() * -1);
                obj1.setInY(obj1.getInY() * -1);
                obj1.setX(obj1.getX() + 30);
                obj1.setY(obj1.getY() + 30);
                obj3[i].flag = true;
            }
        }







		glutPostRedisplay(); // Once again call the Draw member function
	}
	// This function is called whenever the arrow keys on the keyboard are pressed...
	//
	void Move(int key, int x, int y) {
		if (key == GLUT_KEY_LEFT) { // left arrow key is pressed
            if (obj2.getX() > 0) {
				obj2.setX(obj2.getX() - 40);
            }
		} else if (key == GLUT_KEY_RIGHT) { // right arrow key is pressed
            if (obj2.getX() < 679) {
				obj2.setX(obj2.getX() + 40);
            }
		}
		glutPostRedisplay(); // Redo- the drawing by calling
	}
	~BrickSlayer() {

	}
private:
	int width, height;
};

BrickSlayer *bslayer;

//
void Display() {

	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(1.0/*Red Component*/, 1.0/*Green Component*/,
			1.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT); //Update the colors
	bslayer->Draw();
	glutSwapBuffers();
}
void Reshape(int nw, int nh) {
	bslayer->Reshape(nw, nh);
}
 /*This function is called (automatically by library)
 * whenever any non-printable key (such as up-arrow,
 * down-arraw) is pressed from the keyboard
 *
 * You will have to add the necessary code here
 * when the arrow keys are pressed or any other key
 * is pressed...
 * This function has three argument variable key contains
 * the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was
 * pressed.
 * */
void NonPrintableKeys(int key, int x, int y) {

 	bslayer->Move(key, x, y);

 }
 /*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == KEY_ESC/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */

 void Timer(int m) {
 	bslayer->Animate();
 	glutTimerFunc(1000.0 / FPS, Timer, 0);
 }
 int main(int argc, char*argv[]) {
	int width = 800, height = 600; // i have set my window size to be 800 x 600
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	// create a bricSlayer object ...
	bslayer = new BrickSlayer(width, height);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);// we will be using color display mode
	glutInitWindowPosition(50, 50); // set a starting position for game window...
	glutInitWindowSize(width, height);// set the size of our window
	glutCreateWindow("Brick Slayer");// set the title of our game window
	bslayer->Init();
	// Register your functions to the library,
	// you are telling the library  names of function to call for different tasks or input events.
	glutReshapeFunc(Reshape);// tell library which function to call for reshaping of window.
	glutDisplayFunc(Display);// tell library which function to call for drawing Canvas.
//	glutIdleFunc(Move);
	glutSpecialFunc(NonPrintableKeys);// tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys);  // tell library which function to call for printable ASCII characters

		// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0 / FPS, Timer, 0);
	// now handle the control to library and it will call our registered functions when
	// it deems necessary...

	glutMainLoop(); // give control to glut..;
	return 1;
}
#endif /* BSLAYER_CPP_ */
