#include <vector>
#include<iostream>
#include <array>
#include<Gl/glut.h>


int vp_width = 640;
int vp_height = 480;

std::array<int, 2> currentPt;
std::vector<std::array<int, 2>> pts;
bool closed = false;

void draw_polygon(int button, int state, int x, int y)
{
	currentPt = std::array<int, 2>{x, vp_height - y};

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (closed)
			pts.clear(); // restart if last action was close
		closed = false;
		pts.push_back(currentPt);
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		closed = true;
}

//In a mouse move event function you can track the current mouse position :
void mouse_move(int x, int y)
{
	currentPt = std::array<int, 2>{x, vp_height - y};
	glutPostRedisplay();
}

//In your main loop you can continuously draw the lines between the current points.The fllowing function draw lines betwwen a list of points.If the "cloesd" flag is set, then the polygon is closed.Else a line from the last point in the list to the current mouse position is drawn.
void display(void)
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	if (!pts.empty())
	{
		glBegin(GL_LINE_STRIP);
		for (auto& pt : pts)
			glVertex2f((float)pt[0], (float)pt[1]);
		auto& endPt = closed ? pts.front() : currentPt;
		glVertex2f((float)endPt[0], (float)endPt[1]);
		glEnd();
	}

	glFlush();
	glutSwapBuffers();
}


int main()
{
	
		glutDisplayFunc(display);
	glutPassiveMotionFunc(mouse_move);
	glutMouseFunc(draw_polygon);

	glMatrixMode(GL_PROJECTION);
	glOrtho(0.0f, (float)vp_width, 0.0f, (float)vp_height, -1.0, 1.0);
	
}