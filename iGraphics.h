/*
	author: S. M. Shahriar Nirjon
	last modified: March 12, 2008
*/

/* Modified by Prof. Ashikur Rahman
   for BMP file loading in CodeBlocks
   Last modified: April 27 2017
*/

// structure added by Prof. Ashikur Rahman

struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};

typedef struct Image Image;



# include <stdio.h>
# include <stdlib.h>
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glaux.lib")
#include <gl/glut.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <gl\glaux.h>

int iScreenHeight, iScreenWidth;
int iMouseX, iMouseY;
int ifft=0;
void (*iAnimFunction[10])(void)={0};
int iAnimCount=0;
int iAnimDelays[10];
int iAnimPause[10];


void iDraw();
void iKeyboard(unsigned char);
void iSpecialKeyboard(unsigned char);
void iMouseMove(int, int);
void iMouse(int button, int state, int x, int y);

static void  __stdcall iA0(HWND,unsigned int, unsigned int, unsigned long){if(!iAnimPause[0])iAnimFunction[0]();}
static void  __stdcall iA1(HWND,unsigned int, unsigned int, unsigned long){if(!iAnimPause[1])iAnimFunction[1]();}
static void  __stdcall iA2(HWND,unsigned int, unsigned int, unsigned long){if(!iAnimPause[2])iAnimFunction[2]();}
static void  __stdcall iA3(HWND,unsigned int, unsigned int, unsigned long){if(!iAnimPause[3])iAnimFunction[3]();}
static void  __stdcall iA4(HWND,unsigned int, unsigned int, unsigned long){if(!iAnimPause[4])iAnimFunction[4]();}
static void  __stdcall iA5(HWND,unsigned int, unsigned int, unsigned long){if(!iAnimPause[5])iAnimFunction[5]();}
static void  __stdcall iA6(HWND,unsigned int, unsigned int, unsigned long){if(!iAnimPause[6])iAnimFunction[6]();}
static void  __stdcall iA7(HWND,unsigned int, unsigned int, unsigned long){if(!iAnimPause[7])iAnimFunction[7]();}
static void  __stdcall iA8(HWND,unsigned int, unsigned int, unsigned long){if(!iAnimPause[8])iAnimFunction[8]();}
static void  __stdcall iA9(HWND,unsigned int, unsigned int, unsigned long){if(!iAnimPause[9])iAnimFunction[9]();}

int iSetTimer(int msec, void (*f)(void))
{
	int i = iAnimCount;

	if(iAnimCount>=10){printf("Error: Maximum number of already timer used.\n");return -1;}

	iAnimFunction[i] = f;
	iAnimDelays[i] = msec;
	iAnimPause[i] = 0;

	if(iAnimCount == 0) SetTimer(0, 0, msec, iA0);
	if(iAnimCount == 1) SetTimer(0, 0, msec, iA1);
	if(iAnimCount == 2) SetTimer(0, 0, msec, iA2);
	if(iAnimCount == 3) SetTimer(0, 0, msec, iA3);
	if(iAnimCount == 4) SetTimer(0, 0, msec, iA4);

	if(iAnimCount == 5) SetTimer(0, 0, msec, iA5);
	if(iAnimCount == 6) SetTimer(0, 0, msec, iA6);
	if(iAnimCount == 7) SetTimer(0, 0, msec, iA7);
	if(iAnimCount == 8) SetTimer(0, 0, msec, iA8);
	if(iAnimCount == 9) SetTimer(0, 0, msec, iA9);
	iAnimCount++;

	return iAnimCount-1;
}

void iPauseTimer(int index){
	if(index>=0 && index <iAnimCount){
		iAnimPause[index] = 1;
	}
}

void iResumeTimer(int index){
	if(index>=0 && index <iAnimCount){
		iAnimPause[index] = 0;
	}
}


// Added by Prof. Ashikur Rahman

int ImageLoad(char *filename, Image *image) {
    FILE *file;
    unsigned long size; // size of the image in bytes.
    unsigned long i; // standard counter.
    unsigned short int plane; // number of planes in image

    unsigned short int bpp; // number of bits per pixel
    char temp; // temporary color storage for
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL){
        printf("Hey HEY\n\n\n");
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    // read the height
    if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = image->sizeX * image->sizeY * 3;
    // read the planes
    if ((fread(&plane, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (plane != 1) {
        printf("Planes from %s is not 1: %u\n", filename, plane);
        return 0;
    }
    // read the bitsperpixel
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    // seek past the rest of the bitmap header.
    fseek(file, 24, SEEK_CUR);
    // read the data.
    image->data = (char *) malloc(size);
    if (image->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    if ((i = fread(image->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = image->data[i];
        image->data[i] = image->data[i+2];
        image->data[i+2] = temp;
    }
    fclose(file);
    // we're done.
    return 1;
}

// Added by Prof. Ashikur Rahman

Image * loadTexture(char* filename){
    Image *image1;
    // allocate space for texture
    image1 = (Image *) malloc(sizeof(Image));
    if (image1 == NULL) {
    printf("Error allocating space for image");
    exit(0);
    }
    //pic.bmp is a 64x64 picture
    if (!ImageLoad(filename, image1)) {
        exit(1);
    }
    return image1;
}

// Modified by Prof. Ashikur Rahman
void iShowBMP(int x, int y, char filename[])
{
    //Commented out by Prof. Ashikur Rahman

//	AUX_RGBImageRec *TextureImage;

//	TextureImage = auxDIBImageLoad(filename);

    // Added by Prof. Ashikur Rahman

    Image *TextureImage = loadTexture(filename);
    if(TextureImage == NULL){
       printf("Image was not returned from loadTexture\n");
       exit(0);
    }

     //Following was like before from Nirjon

     glRasterPos2f(x, y);
     glDrawPixels(TextureImage->sizeX, TextureImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);

    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TextureImage->sizeX, TextureImage->sizeY, 0, GL_RGB,GL_UNSIGNED_BYTE,TextureImage->data);//The change is here GL_UNSIGNED_BYTE,

	free(TextureImage->data);
	free(TextureImage);

}


void iGetPixelColor (int cursorX, int cursorY, int rgb[])
{
	GLubyte pixel[3];
	glReadPixels(cursorX, cursorY,1,1,
		GL_RGB,GL_UNSIGNED_BYTE,(void *)pixel);

	rgb[0] = pixel[0];
	rgb[1] = pixel[1];
	rgb[2] = pixel[2];

	//printf("%d %d %d\n",pixel[0],pixel[1],pixel[2]);
}

void iText(GLdouble x, GLdouble y, char *str, void* font=GLUT_BITMAP_8_BY_13)
{
   glRasterPos3d(x, y, 0);
   int i;
   for (i=0; str[i]; i++) {
      glutBitmapCharacter(font, str[i]); //,GLUT_BITMAP_8_BY_13, GLUT_BITMAP_TIMES_ROMAN_24
   }
}

void iPoint(double x, double y, int size=0)
{
	int i, j;
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	for(i=x-size;i<x+size;i++)
	{
		for(j=y-size; j<y+size;j++)
		{
			glVertex2f(i, j);
		}
	}
	glEnd();
}

void iLine(double x1, double y1, double x2, double y2)
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

void iFilledPolygon(double x[], double y[], int n)
{
	int i;
	if(n<3)return;
	glBegin(GL_POLYGON);
	for(i = 0; i < n; i++){
		glVertex2f(x[i], y[i]);
	}
	glEnd();
}

void iPolygon(double x[], double y[], int n)
{
	int i;
	if(n<3)return;
	glBegin(GL_LINE_STRIP);
	for(i = 0; i < n; i++){
		glVertex2f(x[i], y[i]);
	}
	glVertex2f(x[0], y[0]);
	glEnd();
}

void iRectangle(double left, double bottom, double dx, double dy)
{
	double x1, y1, x2, y2;

	x1 = left;
	y1 = bottom;
	x2=x1+dx;
	y2=y1+dy;

	iLine(x1, y1, x2, y1);
	iLine(x2, y1, x2, y2);
	iLine(x2, y2, x1, y2);
	iLine(x1, y2, x1, y1);
}

void iFilledRectangle(double left, double bottom, double dx, double dy)
{
	double xx[4], yy[4];
	double x1, y1, x2, y2;

	x1 = left;
	y1 = bottom;
	x2=x1+dx;
	y2=y1+dy;

	xx[0]=x1;
	yy[0]=y1;
	xx[1]=x2;
	yy[1]=y1;
	xx[2]=x2;
	yy[2]=y2;
	xx[3]=x1;
	yy[3]=y2;

	iFilledPolygon(xx, yy, 4);

}

void iFilledCircle(double x, double y, double r, int slices=100)
{
	double t, PI=acos(-1.0), dt, x1,y1, xp, yp;
	dt = 2*PI/slices;
	xp = x+r;
	yp = y;
	glBegin(GL_POLYGON);
	for(t = 0; t <= 2*PI; t+=dt)
	{
		x1 = x + r * cos(t);
		y1 = y + r * sin(t);

		glVertex2f(xp, yp);
		xp = x1;
		yp = y1;
	}
	glEnd();
}

void iCircle(double x, double y, double r, int slices=100)
{
	double t, PI=acos(-1.0), dt, x1,y1, xp, yp;
	dt = 2*PI/slices;
	xp = x+r;
	yp = y;
	for(t = 0; t <= 2*PI; t+=dt)
	{
		x1 = x + r * cos(t);
		y1 = y + r * sin(t);
		iLine(xp, yp, x1, y1);
		xp = x1;
		yp = y1;
	}
}

void iEllipse(double x, double y, double a, double b, int slices=100)
{
	double t, PI=acos(-1.0), dt, x1,y1, xp, yp;
	dt = 2*PI/slices;
	xp = x+a;
	yp = y;
	for(t = 0; t <= 2*PI; t+=dt)
	{
		x1 = x + a * cos(t);
		y1 = y + b * sin(t);
		iLine(xp, yp, x1, y1);
		xp = x1;
		yp = y1;
	}
}

void iFilledEllipse(double x, double y, double a, double b, int slices=100)
{
	double t, PI=acos(-1.0), dt, x1,y1, xp, yp;
	dt = 2*PI/slices;
	xp = x+a;
	yp = y;
	glBegin(GL_POLYGON);
	for(t = 0; t <= 2*PI; t+=dt)
	{
		x1 = x + a * cos(t);
		y1 = y + b * sin(t);
		glVertex2f(xp, yp);
		xp = x1;
		yp = y1;
	}
	glEnd();
}


void iSetColor(double r, double g, double b)
{
	double mmx;
	mmx = r;
	if(g > mmx)mmx = g;
	if(b > mmx)mmx = b;
	mmx = 255;
	if(mmx > 0){
		r /= mmx;
		g /= mmx;
		b /= mmx;
	}
	glColor3f(r, g, b);
}

void iDelay(int sec)
{
	int t1, t2;
	t1 = time(0);
	while(1){
		t2 = time(0);
		if(t2-t1>=sec)
			break;
	}
}


void iClear()
{
	glClear( GL_COLOR_BUFFER_BIT) ;
	glMatrixMode(GL_MODELVIEW) ;
	glClearColor(0,0,0,0);
		glFlush();
}

void displayFF(void){

	//iClear();
	iDraw();
	glutSwapBuffers() ;
}



void animFF(void)
{
	//iAnimation();
	if(ifft == 0){
		ifft = 1;
		iClear();
	}
	glutPostRedisplay();
}

void keyboardHandler1FF(unsigned char key, int x, int y)
{
	iKeyboard(key);
	glutPostRedisplay();
}
void keyboardHandler2FF(int key, int x, int y)
{
	iSpecialKeyboard(key);
	glutPostRedisplay();
}

void mouseMoveHandlerFF(int mx, int my)
{
	iMouseX = mx;
	iMouseY = iScreenHeight - my;
	iMouseMove(iMouseX, iMouseY);

	glFlush();
}

void mouseHandlerFF(int button, int state, int x, int y)
{
	iMouseX = x;
	iMouseY = iScreenHeight - y;

	iMouse(button, state, iMouseX, iMouseY);

	glFlush();
}

void iInitialize(int width=500, int height=500, char *title="iGraphics")
{
	iScreenHeight = height;
	iScreenWidth = width;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB) ;
	glutInitWindowSize(width , height ) ;
	glutInitWindowPosition( 10 , 10 ) ;
	glutCreateWindow(title) ;
	glClearColor( 0.0 , 0.0 , 0.0 , 0.0 ) ;
	glMatrixMode( GL_PROJECTION) ;
	glLoadIdentity() ;
	glOrtho(0.0 , width , 0.0 , height , -1.0 , 1.0) ;
	//glOrtho(-100.0 , 100.0 , -100.0 , 100.0 , -1.0 , 1.0) ;
	//SetTimer(0, 0, 10, timer_proc);

	iClear();

	glutDisplayFunc(displayFF) ;
	glutKeyboardFunc(keyboardHandler1FF); //normal
 	glutSpecialFunc(keyboardHandler2FF); //special keys
	glutMouseFunc(mouseHandlerFF);
	glutMotionFunc(mouseMoveHandlerFF);
	glutIdleFunc(animFF) ;

	glutMainLoop() ;
}

/*int main()
{
	iInitialize(600, 600);

	return 0 ;
}*/
