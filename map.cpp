#include<GL/gl.h>

#include<GL/glut.h>

#include<stdio.h>

struct point2D {
  GLint x;
  GLint y;
}
p1, p2; //structure of point

struct colorPixel {
  GLfloat r;
  GLfloat g;
  GLfloat b;
}; //structure of Color value

//Function for setting new pixel color to given Point
void setPixelColor(GLint x, GLint y, colorPixel color) {
  glColor3f(color.r, color.g, color.b);
  glBegin(GL_POINTS);
  glVertex2i(x, y);
  glEnd();
  glFlush();

}
//initial window condition setting
void window_Init() {
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glColor3f(0.0, 0.0, 0.0);
  glPointSize(1.0); //setting point size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 650, 0, 450); //for 2D view
}

//finding current color pixel to given Point
colorPixel get_pixelColor(GLint x, GLint y) {
  colorPixel color;
  glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, & color);
  return color;
}

//cHECKING TWO COLOR ARE DIFFRENT IF YES THEN GIVE 1 ELSE NO

int isDiffrent(colorPixel c1, colorPixel c2) {
  if (c1.r != c2.r || c1.g != c2.g || c1.b != c2.b)
    return 1;
  else
    return 0;

}
//Checking Boundary Point
int isBoundary(colorPixel currentColor) {
  if (currentColor.g == 1.0 && currentColor.b == 0.0 && currentColor.r == 0.0)
    return 1;
  else
    return 0;
}
int count = 0;
//function for filling India Map using BoundaryFill algorithm
void boundary_fill(int x, int y, colorPixel fill_color, colorPixel boundary_color) {

  colorPixel currentColor = get_pixelColor(x, y); //check current pixel color

  colorPixel c1 = get_pixelColor(x - 1, y);
  colorPixel c2 = get_pixelColor(x + 1, y);

  colorPixel c3 = get_pixelColor(x, y - 1);

  colorPixel c4 = get_pixelColor(x, y + 1);
  //checking Boundary Condition
  if (isBoundary(c1) || isBoundary(c2) || isBoundary(c3) || isBoundary(c4))
    return;

  //if current pixel is diffrent from fill color and not equal to boundary color then go to up,down,left,right and fill
  if (isDiffrent(currentColor, fill_color) && isDiffrent(boundary_color, currentColor)) {
    setPixelColor(x, y, fill_color);
    boundary_fill(x - 1, y, fill_color, boundary_color);
    boundary_fill(x, y - 1, fill_color, boundary_color);
    boundary_fill(x + 1, y, fill_color, boundary_color);
    boundary_fill(x, y + 1, fill_color, boundary_color);

  }
  
}

//function for scaling x_coordinate
int getx(int X) {

  return ((int)(((-1.0) + X / 40.0) * 100) + 200) * 2 - 50;
}
//function for scaling y_coordinate
int gety(int Y) {

  return ((int)(((0.5) - Y / 40.0) * 150 + 150)) * 2 - 40;
}
//function for drawing line between to point using DDA
void DrawLine(int xx1, int yy1, int xx2, int yy2) {

  p1.x = xx1;
  p1.y = yy1;
  p2.x = xx2;
  p2.y = yy2;
  GLfloat dx = p2.x - p1.x;
  GLfloat dy = p2.y - p1.y;

  GLfloat x1 = p1.x;
  GLfloat y1 = p1.y;

  GLfloat step = 0;

  if (abs(dx) > abs(dy)) {
    step = abs(dx);
  } else {
    step = abs(dy);
  }

  GLfloat xInc = dx / step;
  GLfloat yInc = dy / step;

  for (float i = 1; i <= step; i++) {
    glVertex2i(x1, y1);
    x1 += xInc;
    y1 += yInc;
  }
}

//function for sketching map
void draw_Map() {
  DrawLine(getx(20), gety(0), getx(25), gety(0));
  DrawLine(getx(25), gety(0), getx(26), gety(1));
  DrawLine(getx(26), gety(1), getx(29), gety(1));
  DrawLine(getx(29), gety(1), getx(30), gety(2));
  DrawLine(getx(30), gety(2), getx(35), gety(2));
  DrawLine(getx(36), gety(3), getx(35), gety(2));
  DrawLine(getx(36), gety(3), getx(35), gety(4));
  DrawLine(getx(35), gety(5), getx(35), gety(4));
  DrawLine(getx(35), gety(5), getx(33), gety(6));
  DrawLine(getx(35), gety(7), getx(33), gety(6));
  DrawLine(getx(35), gety(7), getx(31), gety(8));
  DrawLine(getx(33), gety(9), getx(31), gety(8));
  DrawLine(getx(33), gety(9), getx(36), gety(10));
  DrawLine(getx(36), gety(11), getx(36), gety(10));
  DrawLine(getx(36), gety(11), getx(38), gety(13));
  DrawLine(getx(40), gety(15), getx(38), gety(13));
  DrawLine(getx(40), gety(15), getx(41), gety(15));
  DrawLine(getx(41), gety(15), getx(42), gety(16));
  DrawLine(getx(47), gety(16), getx(42), gety(16));
  DrawLine(getx(47), gety(16), getx(48), gety(17));
  DrawLine(getx(48), gety(17), getx(50), gety(17));
  DrawLine(getx(50), gety(17), getx(52), gety(15));
  DrawLine(getx(55), gety(17), getx(52), gety(15));
  DrawLine(getx(55), gety(17), getx(57), gety(14));
  DrawLine(getx(59), gety(17), getx(57), gety(14));
  DrawLine(getx(59), gety(17), getx(62), gety(17));
  DrawLine(getx(63), gety(16), getx(62), gety(17));
  DrawLine(getx(63), gety(16), getx(63), gety(15));
  DrawLine(getx(66), gety(15), getx(63), gety(15));
  DrawLine(getx(69), gety(12), getx(66), gety(15));
  DrawLine(getx(69), gety(12), getx(74), gety(12));
  DrawLine(getx(75), gety(13), getx(74), gety(12));
  DrawLine(getx(75), gety(13), getx(78), gety(12));
  DrawLine(getx(76), gety(14), getx(78), gety(12));
  DrawLine(getx(76), gety(14), getx(74), gety(14));
  DrawLine(getx(74), gety(15), getx(74), gety(14));
  DrawLine(getx(74), gety(15), getx(72), gety(15));
  DrawLine(getx(71), gety(16), getx(72), gety(15));
  DrawLine(getx(71), gety(16), getx(72), gety(17));
  DrawLine(getx(72), gety(17), getx(71), gety(17));
  DrawLine(getx(71), gety(19), getx(71), gety(17));
  DrawLine(getx(71), gety(19), getx(69), gety(21));
  DrawLine(getx(68), gety(21), getx(69), gety(21));
  DrawLine(getx(68), gety(21), getx(68), gety(23));
  DrawLine(getx(67), gety(20), getx(68), gety(23));
  DrawLine(getx(67), gety(20), getx(67), gety(22));
  DrawLine(getx(66), gety(22), getx(67), gety(22));
  DrawLine(getx(63), gety(19), getx(66), gety(22));
  DrawLine(getx(63), gety(19), getx(60), gety(19));
  DrawLine(getx(59), gety(18), getx(60), gety(19));
  DrawLine(getx(59), gety(18), getx(57), gety(19));
  DrawLine(getx(57), gety(21), getx(57), gety(19));
  DrawLine(getx(57), gety(21), getx(60), gety(23));
  DrawLine(getx(56), gety(23), getx(60), gety(23));
  DrawLine(getx(56), gety(23), getx(55), gety(24));
  DrawLine(getx(54), gety(24), getx(55), gety(24));
  DrawLine(getx(54), gety(24), getx(51), gety(27));
  DrawLine(getx(47), gety(27), getx(51), gety(27));
  DrawLine(getx(47), gety(27), getx(47), gety(29));
  DrawLine(getx(47), gety(29), getx(45), gety(30));
  DrawLine(getx(43), gety(30), getx(45), gety(30));
  DrawLine(getx(43), gety(30), getx(43), gety(31));
  DrawLine(getx(42), gety(33), getx(43), gety(31));
  DrawLine(getx(42), gety(33), getx(40), gety(33));
  DrawLine(getx(36), gety(38), getx(40), gety(33));
  DrawLine(getx(36), gety(38), getx(36), gety(39));
  DrawLine(getx(35), gety(39), getx(36), gety(39));
  DrawLine(getx(35), gety(39), getx(35), gety(42));
  DrawLine(getx(33), gety(44), getx(35), gety(42));
  DrawLine(getx(33), gety(44), getx(32), gety(43));
  DrawLine(getx(30), gety(45), getx(32), gety(43));
  DrawLine(getx(27), gety(45), getx(30), gety(45));
  DrawLine(getx(27), gety(45), getx(26), gety(44));
  DrawLine(getx(26), gety(43), getx(26), gety(44));
  DrawLine(getx(26), gety(43), getx(25), gety(42));
  DrawLine(getx(25), gety(41), getx(25), gety(42));
  DrawLine(getx(25), gety(41), getx(18), gety(33));
  DrawLine(getx(18), gety(27), getx(18), gety(33));
  DrawLine(getx(18), gety(27), getx(17), gety(27));
  DrawLine(getx(17), gety(22), getx(17), gety(27));
  DrawLine(getx(17), gety(22), getx(15), gety(25));
  DrawLine(getx(11), gety(25), getx(15), gety(25));
  DrawLine(getx(11), gety(25), getx(9), gety(23));
  DrawLine(getx(8), gety(23), getx(9), gety(23));
  DrawLine(getx(8), gety(23), getx(6), gety(22));
  DrawLine(getx(6), gety(21), getx(6), gety(22));
  DrawLine(getx(6), gety(21), getx(7), gety(20));
  DrawLine(getx(12), gety(20), getx(7), gety(20));
  DrawLine(getx(12), gety(20), getx(14), gety(21));
  DrawLine(getx(14), gety(18), getx(14), gety(21));
  DrawLine(getx(14), gety(18), getx(13), gety(18));
  DrawLine(getx(11), gety(16), getx(13), gety(18));
  DrawLine(getx(11), gety(16), getx(12), gety(15));
  DrawLine(getx(16), gety(15), getx(12), gety(15));
  DrawLine(getx(16), gety(15), getx(12), gety(15));
  DrawLine(getx(16), gety(15), getx(18), gety(14));
  DrawLine(getx(18), gety(13), getx(18), gety(14));
  DrawLine(getx(18), gety(13), getx(19), gety(13));
  DrawLine(getx(21), gety(11), getx(19), gety(13));
  DrawLine(getx(21), gety(11), getx(22), gety(11));
  DrawLine(getx(24), gety(9), getx(22), gety(11));
  DrawLine(getx(24), gety(9), getx(22), gety(8));
  DrawLine(getx(22), gety(5), getx(22), gety(8));
  DrawLine(getx(22), gety(5), getx(21), gety(4));
  DrawLine(getx(21), gety(2), getx(21), gety(4));
  DrawLine(getx(21), gety(2), getx(20), gety(0));
}

//function for display
void Display(void) {

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0, 1, 0); //setting green color boundary of india_map
  glBegin(GL_POINTS);
  draw_Map();
  glEnd();
  colorPixel fill_color = {
    1.0 f,
    0.0 f,
    0.0 f
  }; // red color will be filled
  colorPixel boundary_color = {
    0.0 f,
    1.0 f,
    0.0 f
  }; // green- boundary

  point2D p = {
    300,
    300
  }; // a point inside the Map

  boundary_fill(p.x, p.y, fill_color, boundary_color); //call for fill the mAP
  glFlush();
}

int main(int argc, char ** argv) {
  glutInit( & argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(650, 450);
  glutInitWindowPosition(200, 200);
  glutCreateWindow("Open GL");
  window_Init();
  glutDisplayFunc(Display);

  glutMainLoop();
  return 0;
}
