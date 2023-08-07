#include <GL/glut.h>
#include <math.h>

//Khỏi tạo vị trí của camera
GLfloat eyeX = 0.0f, eyeY = 0.0f, eyeZ = 1.0f, upX = 0.0f, upY = 1.0f, upZ = 0.0f;

//Hàm vẽ 3 trục X, Y, Z
void drawCoordinates()
{
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(-200, 0.0, 0.0);
    glVertex3f(200, 0.0, 0.0);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0, -200.0, 0.0);
    glVertex3f(0, 200.0, 0.0);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(0, 0.0, -200.0);
    glVertex3f(0, 0.0, 200.0);
    glEnd();
}

//Vẽ hình tứ giác ở phía sau
void drawSquare1(float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex3f(-0.2, -1, -0.2);
    glVertex3f(0.2, -1, -0.2);
    glVertex3f(0.2, 1, -0.2);
    glVertex3f(-0.2, 1, -0.2);
    glEnd();
}

//Vẽ hình  tứ giác phía trước bên trái
void drawSquare2(float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex3f(-0.2, -1, -0.2);
    glVertex3f(0, -1, 0.4);
    glVertex3f(0, 1, 0.4);
    glVertex3f(-0.2, 1, -0.2);
    glEnd();
}

//Vẽ hình tứ giác phía trước bên phải
void drawSquare3(float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex3f(0, -1, 0.4);
    glVertex3f(0.2, -1, -0.2);
    glVertex3f(0.2, 1, -0.2);
    glVertex3f(0, 1, 0.4);
    glEnd();
}

//Vẽ tam giác nằm ở đỉnh hình lăng trụ
void drawTriangle(float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    glVertex3f(0, 1, 0.4);
    glVertex3f(0.2, 1, -0.2);
    glVertex3f(-0.2, 1, -0.2);
    glEnd();
}

//Hàm vẽ hình lăng trụ tam giác
void drawTriangularPrism(float size) {
    //Phóng đại hình lăng trụ theo kích thước người dùng mong muốn
    glScalef(size, size, size);
    //Vẽ và tô màu 3 hình tứ giác
    drawSquare1(0, 0, 1);
    drawSquare2(0, 1, 0);
    drawSquare3(1, 0, 0);
    drawTriangle(1, 1, 0);
    //Vẽ 1 tam giác mới và di chuyển xuống đáy hình lăng trụ
    glPushMatrix();
    glTranslatef(0, -2, 0);
    drawTriangle(0, 1, 1);
    glPopMatrix();
}

//Tạo hàm bắt sự kiện phím của người dùng
void specialKeys(int key, int x, int y)
{
    switch (key)
    {
        //Nhấn phím mũi tên lên để nhìn từ phía trên
    case GLUT_KEY_UP:
        eyeY += 1.0f;
        upZ = -1.0f;
        break;
        //Nhấn phím mũi tên xuống để nhìn từ phía dưới
    case GLUT_KEY_DOWN:
        eyeY -= 1.0f;
        upZ = 1.0f;
        break;
        //Nhấn phím mũi tên trái để nhìn bên trái
    case GLUT_KEY_LEFT:
        eyeX -= 1.0f;
        upY = 1.0f;
        break;
        //Nhấn phím mũi tên phải để nhìn bên phải
    case GLUT_KEY_RIGHT:
        eyeX += 1.0f;
        upY = 1.0f;
        break;
        //Nhấn phím f5 để đặt lại camera ở vị trí mặc định
    case GLUT_KEY_F5:
        eyeX = 0.0f;
        eyeY = 0.0f;
        eyeZ = 1.0f;
        upX = 0.0f;
        upY = 1.0f;
        upZ = 0.0f;
        break;
        //Nhấn phím PG DN để nhìn hình từ phía sau
    case GLUT_KEY_PAGE_DOWN:
        eyeZ -= 1.0f;
        upY = 1.0f;
        break;
    }
    //Reset khung hình mỗi lần bấm phím
    glutPostRedisplay();
}

void display()
{
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawCoordinates();
    glPushMatrix();
    gluLookAt(eyeX, eyeY, eyeZ, 0, 0, 0, 0, upY, upZ);
    //glEnable(GL_CULL_FACE);
    drawTriangularPrism(100.0f);
    glPopMatrix();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("De tai nhom 5");
    glutInitWindowSize(800, 700);
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-200.0, 200.0, -200.0, 200.0, -200.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutInitDisplayMode(GLUT_DEPTH);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
