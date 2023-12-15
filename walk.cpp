walk.c
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define _USE_MATH_DEFINES

GLdouble CameraAngle[2] = { 0.0, 0.0 };//カメラの向き
GLdouble CameraPosition[3] = { 0.0, 0.0, 4.0 };//カメラの位置
GLint WindowSize[2] = { 0.0,0.0 };//ウインドウサイズ

void scene(void)
{
    /* 物体の色 */
    static GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };
    static GLfloat green[] = { 0.2, 0.8, 0.2, 1.0 };
    static GLfloat blue[] = { 0.2, 0.2, 0.8, 1.0 };
    static GLfloat yellow[] = { 0.8, 0.8, 0.2, 1.0 };
    static GLfloat ground[][4] = {
      { 0.6, 0.6, 0.6, 1.0 },
      { 0.3, 0.3, 0.3, 1.0 }
    };

    int i, j;

    /* 赤い箱 */
    glPushMatrix();
    glTranslated(0.0, 0.0, -3.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
    glutSolidCube(1.0);
    glPopMatrix();

    /* 緑の箱 */
    glPushMatrix();
    glTranslated(0.0, 0.0, 3.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, green);
    glutSolidCube(1.0);
    glPopMatrix();

    /* 青い箱 */
    glPushMatrix();
    glTranslated(-3.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
    glutSolidCube(1.0);
    glPopMatrix();

    /* 黄色い箱 */
    glPushMatrix();
    glTranslated(3.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
    glutSolidCube(1.0);
    glPopMatrix();

    /* 地面 */
    glBegin(GL_QUADS);
    glNormal3d(0.0, 1.0, 1.0);
    for (j = -4; j < 4; ++j) {
        for (i = -4; i < 4; ++i) {
            glMaterialfv(GL_FRONT, GL_DIFFUSE, ground[(i + j) & 1]);
            glVertex3d((GLdouble)i, -0.5, (GLdouble)j);
            glVertex3d((GLdouble)i, -0.5, (GLdouble)(j + 1));
            glVertex3d((GLdouble)(i + 1), -0.5, (GLdouble)(j + 1));
            glVertex3d((GLdouble)(i + 1), -0.5, (GLdouble)j);
        }
    }
    glEnd();
}

void display(void)
{
    static GLfloat lightpos[] = { 3.0, 4.0, 5.0, 1.0 }; /* 光源の位置 */

    static double ex = 0.0, ez = 0.0; /* 視点の位置 */
    static double r = 0.0;            /* 視点の向き */

    /* 画面クリア */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* モデルビュー変換行列の初期化 */
    glLoadIdentity();

    /* 視点の移動 */
    glRotatef(-CameraAngle[1] / M_PI * 180, 1.0, 0.0, 0.0);
    glRotatef(CameraAngle[0] / M_PI * 180, 0.0, 1.0, 0.0);
    glTranslatef(-CameraPosition[0], -CameraPosition[1], -CameraPosition[2]);

    /* 光源の位置を設定 */
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

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

    /* モデルビュー変換行列の指定 */
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    /* ESC か q をタイプしたら終了 */
    if (key == '\033' || key == 'q') {
        exit(0);
    }

    const double vel = 0.1;

    /* キーボード入力WASDによる移動処理 */
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
    case ' ':
    default:
        break;
    }
    glutPostRedisplay();
}

void motion(int x, int y)
{
    //カメラの向きを変更する
    CameraAngle[0] = (GLdouble)x / WindowSize[0] * M_PI * 2 - M_PI;
    CameraAngle[1] = (GLdouble)y / -WindowSize[1] * M_PI + M_PI / 2.0;
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
    glutMotionFunc(motion);
    //glutPassiveMotionFunc(motion);
    init();
    glutMainLoop();
    return 0;
}