#include<iostream>
#include<fstream>
using namespace std;
#ifdef MACOSX
#include<GLUT/glut.h>
#else
#include<GL/glut.h>
#endif
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<cstdlib>
#include<sstream>
#include<string>
#include<assert.h>
#include"texture.h"

// window
double WIDTH = 600;  // width of the user window
double HEIGHT = 350;  // height of the user window
char programName[] = "Main Menu";

int secondWIDTH = 600;  // width of the second user window
int secondHEIGHT = 300;  // height of the second user window
int currentOpp = 0;

// window info:  store the id of a window when it is created, and
//   set this id to zero when the window is destroyed
int mainWindowID = 0, secondWindowID = 0, thirdWindowID = 1;
int createNewWindow(const char *windowTitle);  // declare this function
void drawSecondWindow(); // declare this function
void drawThirdWindow();
void runProgram(int i);

// list area
double listMargin = 40;
double listWidth = WIDTH/2 - listMargin*2; // width of the list area
double listHeight = HEIGHT - listMargin - 150; // height of the list area
double listArea[] = { listMargin, 150, listWidth, listHeight };

double listMargin2 = 320;
double listWidth2 = (WIDTH/2 - listMargin*3 + 270)/2; // width of the list area
double listHeight2 = (HEIGHT - listMargin2 - 310)/2; // height of the list area
double listArea2[] = { listMargin2, 300, listWidth2, listHeight2 };

// about area
double aboutArea[] = { WIDTH-listMargin-listWidth, listArea[1],  listWidth, listHeight };
int img;  // texture id

// item boxes
const int numItems = 2;
double itemMargin = 5;
double itemWidth = listWidth-itemMargin*2;
double itemHeight = (listHeight-(itemMargin*((numItems-1)+1)) ) / (numItems-1);
double** itemList = new double* [numItems]; // allocated in main
bool overItem[numItems];

char line[100];

const int numItems2 = 1;
double itemMargin2 = 5;
double itemWidth2 = listWidth2-itemMargin2*2;
double itemHeight2 = ( listHeight2 - (itemMargin2*(numItems2+1)) ) / numItems2;
double** itemList2 = new double* [numItems2]; // allocated in main
bool overItem2[numItems2];

// text
char txtTitle[] = "P A S S    C E S S I B I L I T Y";
char txtOpps[] = "Left-Handed";
char txtForum[] = "Right-Handed";
char txtQuest[] = "Your suggested password is: ";
char** itemText = new char* [numItems];
char** itemText2 = new char* [numItems2];
char** password = new char*[2];
int count = 0;

//------------------------------------------


// draw rectangle, given upper left vertex, width, and height
void drawBox(double x, double y, double width, double height) {
  glBegin(GL_POLYGON);
    glVertex2f(x, y);  // upper left
    glVertex2f(x, y + height);  // lower left
    glVertex2f(x + width, y + height);  // lower right
    glVertex2f(x + width, y);  // upper right
  glEnd();
}
void drawBox(double *pos) {
  drawBox(pos[0], pos[1], pos[2], pos[3]);
}

// the drawText function draws some text at location x, y
void drawText(double x, double y, const char *text) {
  glRasterPos2f( x, y );
  int length = strlen(text);
  for (int i = 0; i < length; i++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
}
void drawText2(double x, double y, const char *text) {
  glRasterPos2f( x, y );
  int length = strlen(text);
  for (int i = 0; i < length; i++)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}


//------------------------------------------


void drawWindow() {
  int len;
  
  // clear the buffer
  glClear(GL_COLOR_BUFFER_BIT);
 

  //draw the title
  glColor3f(1,1,1);
  for (len=0; txtTitle[len]!='\0'; len++);
  drawText(300-len*4.5, 60, txtTitle);

  //for (len=0; txtQuest[len]!='\0'; len++);
  //drawText(WIDTH/2-len*4, 130, txtQuest);
  
  // draw the list/about areas
  glColor3f(.1, .1, .1); // dark gray
  drawBox(listArea);
  glColor3f(.1, .1, .1); // dark gray
  drawBox(listArea2);
  //glColor3f(.8, .8, .8);
  //drawBox(aboutArea);
  //drawTexture(img, aboutArea);
  
  //draw the list items
  //for (int i=0; i<numItems; i++) {
    if ( overItem[0] ) glColor3f(1, 1, 1);
    else glColor3f(.75, .75, .75);
    drawBox(itemList[0]);
    //}

   //draw the list items2
    //for (int i=0; i<numItems2; i++) {
    if ( overItem[1] )        glColor3f(1, 1, 1);
    else glColor3f(.75, .75, .75);
    drawBox(itemList[1]);

  // draw the text
  glColor3f(0, 0, 0); // black
  for (int i=0; i<1; i++) {
    double y = itemList[i][1] + (itemHeight/2) + 5;
    for (len=0; itemText[i][len]!='\0'; len++);
    double x = itemList[i][0] + itemWidth/2 - (len*5);
    drawText2(x, y, itemText[0]);
  }

  // draw the text2
  glColor3f(0, 0, 0); // black
  for (int i=1; i<2; i++) {
    double y = (itemList[i][1] + (itemHeight2/2) + 5);
    for (len=1; itemText[i][len]!='\0'; len++);
    double x = (itemList[i][0] + itemWidth2/2 - (len*5));
    drawText2(x, y, itemText[1]);
  }
   
  
  // tell the graphics card that we're done-- go ahead and draw!
  // (technically, we are switching between two color buffers...)
  glutSwapBuffers();
}

// close the window and finish the program
void exitAll() {
  if ( secondWindowID ) {
    glutDestroyWindow(secondWindowID);
    secondWindowID = 0;
    glutSetWindow(mainWindowID);
    return;
   }
  else if ( thirdWindowID ) {
    glutDestroyWindow(thirdWindowID);
    thirdWindowID = 0;
    glutSetWindow(mainWindowID);
  }
  else if ( mainWindowID ) {
    glutDestroyWindow(mainWindowID);
    exit(0);
  }
}


// process keyboard events
void keyboard( unsigned char c, int x, int y ) {
  switch(c) {
    case 'q':
    case 'Q':
    case 27:
      exitAll();
      break;
    case 'x':
      WIDTH = 1200;
      HEIGHT = 700;
      glClearColor(0,0,0,0);
      glutDisplayFunc(drawWindow);
    default:
      break;
  }
  glutPostRedisplay();
}

// the reshape function handles the case where the user changes the size
//   of the window.  We need to fix the coordinate
//   system, so that the drawing area is still the unit square.
void reshape(int w, int h) {

   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   if ( mainWindowID == glutGetWindow() ) {
     WIDTH = w;  HEIGHT = h;
   } else {
     secondWIDTH = w;  secondHEIGHT = h;
   }
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0., w-1, h-1, 0., -1.0, 1.0);
}

// test whether point (x,y) is inside rectangle pos
bool onRect(int x, int y, double* pos) {
  return x >= pos[0]  && y >= pos[1] &&
         x <= pos[0] + pos[2] &&
         y <= pos[1] + pos[3];
}


//----------------------------------------


void mouse(int mouseButton, int state, int x, int y) {
  if ( GLUT_LEFT_BUTTON == mouseButton ) {
    if ( GLUT_DOWN == state ) {   // left mouse button is pressed

    } else {   // mouse is no longer pressed
      
      //for (int i=0; i<numItems; i++) {
	if ( overItem[0] ) runProgram(0);
	//}
	//for (int j=0; j<numItems2; j++) {
	else if ( overItem[1] ) runProgram(1);
	//}
    }
  } else if ( GLUT_RIGHT_BUTTON == mouseButton ) {
    // right mouse button pressed
  }
  glutPostRedisplay();
}


// gives mouse location while mouse is being dragged
void mouse_motion(int x,int y) {
  // check if mouse is over item boxes
  //for (int i=0; i<numItems; i++) {
    if ( onRect(x,y,itemList[0]) ){
      overItem[0] = true;
      //overItem2[0] = false;
    }
    else {
       overItem[0] = false;
    }
    overItem[1] = false;
    if (!onRect(x,y,itemList[1])) {
      overItem[1] = true;
    }
    else{
      overItem[1] = false;
      //overItem2[0] = false;
    }
  glutPostRedisplay();

}


//--------------------------------------



// the createNewWindow function creates a window and returns its id
int createNewWindow(const char *windowTitle) {
  int id = glutCreateWindow(windowTitle);
  assert( 0 != id );
  // clear the window to black
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  // begin setting up the coordinate system

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // allow blending (for transparent textures)
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  // register callbacks
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMotionFunc(mouse_motion);
  glutPassiveMotionFunc(mouse_motion);

  return id;
}


void drawSecondWindow()
{
  glutSetWindow(secondWindowID);  // this call may not be necessary

  // clear the buffer
  glClear(GL_COLOR_BUFFER_BIT);

  // draw the box
  glColor3f(.75, .75, .75); //light gray
  drawBox(20,20,460,260);


  // tell the graphics card that we're done-- go ahead and draw!
  //   (technically, we are switching between two color buffers...)
  glutSwapBuffers();
}


//----------------------------------------



// the init function sets up the graphics card to draw properly
void init(void)
{
  // clear the window to black
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  // set up the coordinate system:  number of pixels along x and y
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0., WIDTH-1, HEIGHT-1, 0., -1.0, 1.0);

  
  // allow blending (for transparent textures)
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
}

// init_gl_window is the function that starts the ball rolling, in
//  terms of getting everything set up and passing control over to the
//  glut library for event handling.  It needs to tell the glut library
//  about all the essential functions:  what function to call if the
//  window changes shape, what to do to redraw, handle the keyboard,
//  etc.
void init_gl_window() {
  char *argv[] = { programName };
  int argc = sizeof(argv) / sizeof(argv[0]);
  glutInit(&argc, argv);
  glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInitWindowPosition(10,10);
  mainWindowID = glutCreateWindow(programName);
  img = loadTexture("img.pam");  // loading in the main window
  init();

  glutDisplayFunc(drawWindow);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutMotionFunc(mouse_motion);
  glutPassiveMotionFunc(mouse_motion);
  glutMainLoop();
}

void drawThirdWindow(){
   int len;
   glutSetWindow(thirdWindowID);

   // clear the buffer
   glClear(GL_COLOR_BUFFER_BIT);
  
   //draw the title
   glColor3f(0,0,0);
   for (len=0; txtQuest[len]!='\0'; len++);
   drawText(secondWIDTH/2-len*9, 60, txtQuest);

   // draw the text2
   glColor3f(0, 0, 0); // black
   int x = secondWIDTH/2-len*6;
   int y = 160;
   drawText(x, y, line);
   
  
  // tell the graphics card that we're done-- go ahead and draw!
  // (technically, we are switching between two color buffers...)
  glutSwapBuffers();
}

//----------------------------------------

void runProgram(int i) {
  ifstream infile;
  char x;
  int n;
  switch(i) {
  case 0:
    system("python password_generation/generate_passwordl.py >> passwordl.txt");
    WIDTH = 300; HEIGHT = 200; 
    infile.open("passwordl.txt");
    n = 0;
    while(infile >> x){
      line[n] = x;
      n++;
    }
    infile.close();
    remove("passwordl.txt");
    glClearColor(.75, .75, .75, .75); 
    glutDisplayFunc(drawThirdWindow);
    break;
  case 1:
    system("python password_generation/generate_passwordr.py >> passwordr.txt");
    WIDTH = 300; HEIGHT = 200;
    infile.open("passwordr.txt");
    n = 0;
    while(infile >> x){
      line[n] = x;
      n++;
    }
    infile.close();
    remove("passwordr.txt");
    glClearColor(.75, .75, .75, .75); 
    glutDisplayFunc(drawThirdWindow);
    break;
  }
}

void stop() {
  //run code on exit here
}


//----------------------------------------


int main() {

  // allocate item box sizes
  double h = (itemMargin*(0+1)) + (itemHeight*0) + listArea[1];
  double size[] = { listMargin+itemMargin, h,   itemWidth, itemHeight };
  itemList[0] = new double [4];
  for (int j=0; j<4; j++)
    itemList[0][j] = size[j];

  double h2 = (itemMargin2*(0+1)) + (itemHeight2*0) + listArea2[1];
  double size2[] = { listMargin2+itemMargin2, h2,   itemWidth2, itemHeight2 };
  itemList[1] = new double [4];
  for (int j=0; j<4; j++)
    itemList[1][j] = size2[j];
 
  itemText[0] = txtOpps;
  itemText[1] = txtForum;


  atexit(stop);
  
  init_gl_window();

  return 0;
}
