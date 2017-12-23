#include "System.h"
#include <cassert>
#include <string>

System system_instance;

/*show string on the screen*/
void drawString(std::string str){
	static const int MAX_CHAR = 128;
	static int isFirstCall = 1;
	static GLuint lists;
	if (isFirstCall) {
		isFirstCall = 0;
		lists = glGenLists(MAX_CHAR);
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}

	for (std::string::iterator it = str.begin(); it != str.end(); it++) {
		glCallList(lists + *it);
	}
}

void onDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(2.0f);
	glColor3f(0.0, 0.0, 0.0);

	glBegin(GL_POINTS);
	/*draw points*/
	system_instance.draw();
	glEnd();

	glRasterPos2i(0, system_instance.getWindowSizeY() - 15);  //��ʼλ�� 
	drawString("[DEBUG INFO]");

	glRasterPos2i(0, system_instance.getWindowSizeY() - 30);  //��ʼλ�� 
	drawString(std::string("state:") + system_instance.getStateString());

	glRasterPos2i(0, system_instance.getWindowSizeY() - 45);  //��ʼλ�� 
	drawString(std::string("inputType:") + system_instance.getInputTypeString());
	
	glRasterPos2i(0, system_instance.getWindowSizeY() - 60);  //��ʼλ�� 
	drawString(std::string("mousePos:")
		+ std::to_string(system_instance.getMouseX()) + ','
		+ std::to_string(system_instance.getMouseY()));

	glutSwapBuffers();
}

static float angle = 0.0f;

void onDisplay2() {
	glEnable(GL_DEPTH_TEST);   //��Ȳ���
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	glOrtho(-30, 30, -30, 30, -50, 50);   //�����任
	
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity(); 
	gluLookAt(15, 12, 10, 0, 0, 0, 0, 0, 1);   //����ӽ�

	glRotatef(angle, 0, 0, 1);
	const static int size = 15;

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_QUADS);
	glVertex3i(size, size, size);
	glVertex3i(size, -size, size);
	glVertex3i(size, -size, -size);
	glVertex3i(size, size, -size);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3i(-size, size, size);
	glVertex3i(-size, -size, size);
	glVertex3i(-size, -size, -size);
	glVertex3i(-size, size, -size);
	glEnd();
	
	glBegin(GL_QUADS);
	glVertex3i(size, size, size);
	glVertex3i(-size, size, size);
	glVertex3i(-size, size, -size);
	glVertex3i(size, size, -size);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3i(size, -size, size);
	glVertex3i(-size, -size, size);
	glVertex3i(-size, -size, -size);
	glVertex3i(size, -size, -size);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3i(size, size, size);
	glVertex3i(-size, size, size);
	glVertex3i(-size, -size, size);
	glVertex3i(size, -size, size);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3i(size, size, -size);
	glVertex3i(-size, size, -size);
	glVertex3i(-size, -size, -size);
	glVertex3i(size, -size, -size);
	glEnd();
	
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex3i(size, size, size);
	glVertex3i(size, size, -size);
	glVertex3i(size, -size, size);
	glVertex3i(size, -size, -size);
	glVertex3i(-size, -size, size);
	glVertex3i(-size, -size, -size);
	glVertex3i(-size, size, size);
	glVertex3i(-size, size, -size);

	glVertex3i(size, size, size);
	glVertex3i(size, -size, size);
	glVertex3i(size, -size, size);
	glVertex3i(-size, -size, size);
	glVertex3i(-size, -size, size);
	glVertex3i(-size, size, size);
	glVertex3i(-size, size, size);
	glVertex3i(size, size, size);

	glVertex3i(size, size, -size);
	glVertex3i(size, -size, -size);
	glVertex3i(size, -size, -size);
	glVertex3i(-size, -size, -size);
	glVertex3i(-size, -size, -size);
	glVertex3i(-size, size, -size);
	glVertex3i(-size, size, -size);
	glVertex3i(size, size, -size);
	glEnd();

	glutSwapBuffers();
	glutPostRedisplay();
}

void idle2() {
	angle += 0.01;
}

void onChangeSize(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)width, 0.0, (GLdouble)height, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, width, height);

	system_instance.setWindowSize(width, height);
}

void onMouse(int button, int state, int x, int y) {
	y = system_instance.getWindowSizeY() - y;
	system_instance.setMousePos(x, y);

	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			system_instance.down(x, y);
		}
		else if (state == GLUT_UP) {
			system_instance.up(x, y);
		}
	}

	glutPostRedisplay();
}

void onMotion(int x, int y) {
	y = system_instance.getWindowSizeY() - y;
	system_instance.setMousePos(x, y);

	if (system_instance.getIsEditable() == true)
		system_instance.moveFocusPointTo(x, y);

	glutPostRedisplay();
}

void onPassiveMontion(int x, int y) {
	y = system_instance.getWindowSizeY() - y;
	system_instance.setMousePos(x, y);
	glutPostRedisplay();
}

void onKeyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 127: //`delete` key
		system_instance.clearCurrent();
		break;
	case 'w':
		system_instance.translate(0, 5);
		break;
	case 'a':
		system_instance.translate(-5, 0);
		break;
	case 's':
		system_instance.translate(0, -5);
		break;
	case 'd':
		system_instance.translate(5, 0);
		break;
	case 'e':
		system_instance.rotate(- 3.14 / 2);
		break;
	case 'q':
		system_instance.rotate(3.14 / 2);
		break;
	case '+':
		system_instance.scale(1.1f,1.1f);
		break;
	case '-':
		system_instance.scale(0.9f, 0.9f);
		break;
	case 'f':
		system_instance.fillOrNot();
		break;
	case 'c':
		system_instance.cutOrNot();
		break;
	case 'v':
		system_instance.cut();
		break;
	case 'r':
		system_instance.save(".\\save.bmp");
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void mainMenu(int id) {
	switch(id) {
	case 1:
		system_instance.setInputType(System::InputType::LINE);
		break;
	case 2:
		system_instance.setInputType(System::InputType::BEZIER);
		break;
	case 3:
		system_instance.setInputType(System::InputType::POLYGON);
		break;
	case 4:
		system_instance.setInputType(System::InputType::CIRCLE);
		break;
	case 5:
		system_instance.setInputType(System::InputType::ELLIPISE);
		break;
	case 6:
		system_instance.setInputType(System::InputType::CHOOSE);
		break;
	default:
		assert(0);
		break;
	}
}

void init() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	system_instance.setDrawPointFunc(glVertex2i);
}

void init2() {
	glClearColor(0.9, 0.9, 0.9, 0.0);      //ָ����Ļ����Ϊ��ɫ
	glColor3f(1.0, 1.0, 1.0);             //���û�����ɫΪ��ɫ
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(200,200);
	glutInitWindowSize(800, 600);
	int mainWindow = glutCreateWindow("Painting");
	glutDisplayFunc(onDisplay);
	glutReshapeFunc(onChangeSize);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);
	glutPassiveMotionFunc(onPassiveMontion);
	glutKeyboardFunc(onKeyboard);
	{
		glutCreateMenu(mainMenu);
		glutAddMenuEntry("ֱ��", 1);
		glutAddMenuEntry("����", 2);
		glutAddMenuEntry("�����", 3);
		glutAddMenuEntry("Բ", 4);
		glutAddMenuEntry("��Բ", 5);
		glutAddMenuEntry("ѡȡ", 6);
		glutAttachMenu(GLUT_RIGHT_BUTTON);
	}
	init();

	int subWindow = glutCreateSubWindow(mainWindow, 500, 400, 300, 200);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutDisplayFunc(onDisplay2);
	glutIdleFunc(idle2);
	init2();

	glutMainLoop();
	return 0;
}