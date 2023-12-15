walk.c
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define _USE_MATH_DEFINES

GLdouble CameraAngle[2] = { 0.0, 0.0 };//�J�����̌���
GLdouble CameraPosition[3] = { 0.0, 0.0, 4.0 };//�J�����̈ʒu
GLint WindowSize[2] = { 0.0,0.0 };//�E�C���h�E�T�C�Y

void scene(void)
{
    /* ���̂̐F */
    static GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };
    static GLfloat green[] = { 0.2, 0.8, 0.2, 1.0 };
    static GLfloat blue[] = { 0.2, 0.2, 0.8, 1.0 };
    static GLfloat yellow[] = { 0.8, 0.8, 0.2, 1.0 };
    static GLfloat ground[][4] = {
      { 0.6, 0.6, 0.6, 1.0 },
      { 0.3, 0.3, 0.3, 1.0 }
    };

    int i, j;

    /* �Ԃ��� */
    glPushMatrix();
    glTranslated(0.0, 0.0, -3.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
    glutSolidCube(1.0);
    glPopMatrix();

    /* �΂̔� */
    glPushMatrix();
    glTranslated(0.0, 0.0, 3.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, green);
    glutSolidCube(1.0);
    glPopMatrix();

    /* ���� */
    glPushMatrix();
    glTranslated(-3.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
    glutSolidCube(1.0);
    glPopMatrix();

    /* ���F���� */
    glPushMatrix();
    glTranslated(3.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
    glutSolidCube(1.0);
    glPopMatrix();

    /* �n�� */
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
    static GLfloat lightpos[] = { 3.0, 4.0, 5.0, 1.0 }; /* �����̈ʒu */

    static double ex = 0.0, ez = 0.0; /* ���_�̈ʒu */
    static double r = 0.0;            /* ���_�̌��� */

    /* ��ʃN���A */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* ���f���r���[�ϊ��s��̏����� */
    glLoadIdentity();

    /* ���_�̈ړ� */
    glRotatef(-CameraAngle[1] / M_PI * 180, 1.0, 0.0, 0.0);
    glRotatef(CameraAngle[0] / M_PI * 180, 0.0, 1.0, 0.0);
    glTranslatef(-CameraPosition[0], -CameraPosition[1], -CameraPosition[2]);

    /* �����̈ʒu��ݒ� */
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    /* �V�[���̕`�� */
    scene();
    glFlush();
}

void resize(int w, int h)
{
    /* �E�B���h�E�S�̂��r���[�|�[�g�ɂ��� */
    glViewport(0, 0, w, h);

    WindowSize[0] = w;
    WindowSize[1] = h;

    /* �����ϊ��s��̎w�� */
    glMatrixMode(GL_PROJECTION);

    /* �����ϊ��s��̏����� */
    glLoadIdentity();
    gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);

    /* ���f���r���[�ϊ��s��̎w�� */
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    /* ESC �� q ���^�C�v������I�� */
    if (key == '\033' || key == 'q') {
        exit(0);
    }

    const double vel = 0.1;

    /* �L�[�{�[�h����WASD�ɂ��ړ����� */
    switch (key) {
    case 'w':
        //�O�i z+
        CameraPosition[0] += vel * cos(CameraAngle[0] - M_PI / 2.0);
        CameraPosition[2] += vel * sin(CameraAngle[0] - M_PI / 2.0);
        break;
    case 's':
        //��� z-
        CameraPosition[0] += vel * cos(CameraAngle[0] + M_PI / 2.0);
        CameraPosition[2] += vel * sin(CameraAngle[0] + M_PI / 2.0);
        break;
    case 'a':
        //���ɕ��s�ړ� x-
        CameraPosition[0] += vel * cos(CameraAngle[0] + M_PI);
        CameraPosition[2] += vel * sin(CameraAngle[0] + M_PI);
        break;
    case 'd':
        //�E�ɕ��s�ړ� x+
        CameraPosition[0] += vel * cos(CameraAngle[0]);
        CameraPosition[2] += vel * sin(CameraAngle[0]);
        break;
    case 'j':
        //����]
        CameraAngle[0] += vel * (-1);
        CameraAngle[1];
        break;
    case 'l':
        //�E��]
        CameraAngle[0] += vel * (1);
        CameraAngle[1];
        break;
    case 'i':
        //����]
        CameraAngle[0];
        CameraAngle[1] += vel;
        break;
    case 'k':
        //�E��]
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
    //�J�����̌�����ύX����
    CameraAngle[0] = (GLdouble)x / WindowSize[0] * M_PI * 2 - M_PI;
    CameraAngle[1] = (GLdouble)y / -WindowSize[1] * M_PI + M_PI / 2.0;
}

void init(void)
{
    /* �����ݒ� */
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