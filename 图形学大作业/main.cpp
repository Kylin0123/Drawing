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

	glRasterPos2i(0, system_instance.getWindowSizeY() - 15);  //起始位置 

	drawString(std::string("state:")
		+ system_instance.getStateString() + "    "
		+ std::string("inputType:")
		+ system_instance.getInputTypeString() + "    "
		+ std::string("mousePos:")
		+ std::to_string(system_instance.getMouseX()) + ','
		+ std::to_string(system_instance.getMouseY())
	);

	glutSwapBuffers();
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

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(200,200);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Painting");
	glutDisplayFunc(onDisplay);
	glutReshapeFunc(onChangeSize);
	glutMouseFunc(onMouse);
	glutMotionFunc(onMotion);
	glutPassiveMotionFunc(onPassiveMontion);
	glutKeyboardFunc(onKeyboard);
	{
		glutCreateMenu(mainMenu);
		glutAddMenuEntry("直线", 1);
		glutAddMenuEntry("曲线", 2);
		glutAddMenuEntry("多边形", 3);
		glutAddMenuEntry("圆", 4);
		glutAddMenuEntry("椭圆", 5);
		glutAttachMenu(GLUT_RIGHT_BUTTON);
	}
	init();
	glutMainLoop();
	return 0;
}