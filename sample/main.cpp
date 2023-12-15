#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define M_PI 3.1415926535
//#define _USE_MATH_DEFINES

GLdouble CameraAngle[2] = { -0.9, -0.5 };//カメラの向き
GLdouble CameraPosition[3] = { 15.0, 8.0, 11.5 };//カメラの位置

GLint WindowSize[2] = { 0.0,0.0 };//ウインドウサイズ

GLfloat wood[] = { 0.427, 0.33, 0.239, 0.5 };
GLfloat leaf[] = { 0.2, 0.8, 0.2, 1.0 };
GLfloat snowman[] = { 0.8,0.9,1.0,1.0 };
GLfloat hat[][4] = {
  { 0.8, 0.2, 0.2, 1.0 },
  { 0.2, 0.8, 0.2, 1.0 }
};

GLUquadricObj* cone;

static GLfloat lightpos1[] = { 20.0, 0.0, 5.0, 1.0 }; /* 光源の位置 */
static GLfloat lightpos0[] = { 5.0, 3.0, 0.0, 1.0 };

/* 物体の色 */
static GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };
static GLfloat green[] = { 0.2, 0.8, 0.2, 1.0 };
static GLfloat blue[] = { 0.2, 0.2, 0.8, 1.0 };
static GLfloat yellow[] = { 0.8, 0.8, 0.2, 1.0 };
static GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
static GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };



static GLfloat ground[][4] = {
  { 0.8, 0.7, 0.8, 1.0 },
  { 0.1, 0.3, 0.3, 1.0 }
};

static GLfloat checkers[][4] = {
  { 0.8, 0.2, 0.2, 1.0 },
  { 0.9, 0.9, 0.9, 1.0 }
};

int i, j;

GLUquadricObj* quadratic;

float pos_x = 0.0, pos_y = 0.0, pos_z = 0.0;

void draw_snowman(float x, float z, int hatcolor)
{
    glPushMatrix();

    glScaled(0.5, 0.5, 0.5);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, snowman);
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos0);
    glTranslatef(pos_x, pos_y, pos_z);
    glTranslated(x, 0.5, z);

    glutSolidSphere(0.5, 50, 50);
    glTranslated(0, 0.85, 0);
    glutSolidSphere(0.4, 50, 50);
    glTranslated(0.2, 0.6, 0);

    glRotatef(90, 0.5, -0.15, 0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, hat[hatcolor]);
    gluCylinder(cone, 0.05, 0.25, 0.3, 30, 30);
    glRotatef(90, -0.5, 0, 0);
    glNormal3f(1, 0.5, 0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
    glutSolidSphere(0.07, 50, 50);

   glPopMatrix();
}

void draw_tree(float x, float z)
{
    cone = gluNewQuadric();
    glPushMatrix();
    glScaled(0.5, 0.5, 0.5);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, wood);
    glTranslated(x, 1.75, z);
    glRotatef(90, 1, 0, 0);
    gluCylinder(cone, 0.4, 0.4, 1.0, 30, 30);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, leaf);
    glTranslated(0, 0, -1.2);
    gluCylinder(cone, 0.0, 1.0, 1.4, 30, 30);
    glTranslated(0, 0, -0.2);
    gluCylinder(cone, 0.0, 0.8, 1.1, 30, 30);
    glTranslated(0, 0, -0.1);
    gluCylinder(cone, 0.0, 0.6, 0.7, 30, 30);
    glPopMatrix();
}

void scene(void)
{
    quadratic = gluNewQuadric();
    int hatcolor = 0;
//left right -- x
//up down --- y
//forward backward --- z

    /* ボード */
   glNormal3d(0, 1.0, 1.0);
    for (j = -6; j < 6; ++j) {
        for (i = -6; i < 6; ++i) {
            glPushMatrix();
            glMaterialfv(GL_FRONT, GL_DIFFUSE, ground[(i + j) & 1]);
            glTranslated((GLdouble)i + 0.5, -1.25, (GLdouble)j + 0.5);
            if (i == -6 || i == 5 || j == -6 || j == 5) { draw_tree(0, 0); glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
            }
            glutSolidCube(1.0);
            glPopMatrix();
        }
    }
    /* snowmen */
    for (j = -5; j < 5; j++) {
        for (i = -5; i < 5; i++) {
            glPushMatrix();
            if (i > 0) {      
                hatcolor = 0;
           }
            else {
                hatcolor = 1;
            }
            glTranslated((GLdouble)i + 0.5, -0.7, (GLdouble)j + 0.5);
            if (((i + j) & 1) == 1 && i != -1 && i != 0) {
                draw_snowman(0, 0, hatcolor);
            }
            glPopMatrix();
        }
    }

    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
    glTranslated(0, 2, 0);
    glutSolidSphere(0.5, 100, 100);
    glPopMatrix();
}

void display(void)
{

    /* background */
    glClearColor(0.8, 0.2, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    /* 視点の移動 */
    glRotatef(-CameraAngle[1] / M_PI * 180, 1.0, 0.0, 0.0);
    glRotatef(CameraAngle[0] / M_PI * 180, 0.0, 1.0, 0.0);
    glTranslatef(-CameraPosition[0], -CameraPosition[1], -CameraPosition[2]);

    /* 光源の位置を設定 */
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos0);
    glLightfv(GL_LIGHT1, GL_POSITION, lightpos1);


    /* シーンの描画 */
    scene();
    glFlush();
}

void resize(int w, int h)
{
    /* ウィンドウ全体をビューポートにする */
    glViewport(0, 0, w, h);

    WindowSize[0] = w;
    WindowSize[1] = h;

    /* 透視変換行列の指定 */
    glMatrixMode(GL_PROJECTION);

    /* 透視変換行列の初期化 */
    glLoadIdentity();
    gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    // ESC か q で終了 
    if (key == '\033' || key == 'q') {
        exit(0);
    }

    const double vel = 0.1;

    // WASD & IJKLによる移動処理 */
    switch (key) {
    case 'w':
        //前進 z+
        CameraPosition[0] += vel * cos(CameraAngle[0] - M_PI / 2.0);
        CameraPosition[2] += vel * sin(CameraAngle[0] - M_PI / 2.0);
        break;
    case 's':
        //後退 z-
        CameraPosition[0] += vel * cos(CameraAngle[0] + M_PI / 2.0);
        CameraPosition[2] += vel * sin(CameraAngle[0] + M_PI / 2.0);
        break;
    case 'a':
        //左に平行移動 x-
        CameraPosition[0] += vel * cos(CameraAngle[0] + M_PI);
        CameraPosition[2] += vel * sin(CameraAngle[0] + M_PI);
        break;
    case 'd':
        //右に平行移動 x+
        CameraPosition[0] += vel * cos(CameraAngle[0]);
        CameraPosition[2] += vel * sin(CameraAngle[0]);
        break;
    case 'j':
        //左回転
        CameraAngle[0] += vel * (-1);
        CameraAngle[1];
        break;
    case 'l':
        //右回転
        CameraAngle[0] += vel * (1);
        CameraAngle[1];
        break;
    case 'i':
        //左回転
        CameraAngle[0];
        CameraAngle[1] += vel;
        break;
    case 'k':
        //右回転
        CameraAngle[0];
        CameraAngle[1] -= vel;
        break;
    case 'u':
        //カメラの位置が一段上がる
        CameraPosition[1] += 4;
        break;
    case 'o':
        //カメラの位置が一段下がる
        CameraPosition[1] -= 4;
        break;
    case ' ':
    default:
        break;
    }
    glutPostRedisplay();
}

void init(void)
{
    /* 初期設定 */
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyboard);

    init();
    glutMainLoop();
    return 0;
}