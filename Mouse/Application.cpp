//////////////////////////////////////////////////////////////////////          
// mouse.cpp
// 
// This program illustrates interaction using the mouse.
// 
// Interaction:
// Left mouse click to draw a square point, right mouse click to exit.
// 
// Sumanta Guha.
////////////////////////////////////////////////////////////////////// 

#include <cstdlib>
#include <glut.h>
#include <vector>
#include <iostream>

//////////////////////////////////////////////////////////////////////          
// mouse.cpp
// 
// This program illustrates interaction using the mouse.
// 
// Interaction:
// Left mouse click to draw a square point, right mouse click to exit.
// 
// Sumanta Guha.
////////////////////////////////////////////////////////////////////// 



// Use the STL extension of C++.
using namespace std;
// whateva!


// Globals.
static GLsizei width, height; // OpenGL window size.
static float pointSize = 3.0; // Size of point

// Point class.
class Point
{
public:
	Point() :xVal(0), yVal(0) {}
	Point(int x, int y)
	{
		xVal = x; yVal = y;
	}
	void drawPoint(void); // Function to draw a point.
	int GetX() {
		return xVal;
	}
	int GetY() {
		return yVal;
	}
private:
	int xVal, yVal; // x and y co-ordinates of point.
	static float size; // Size of point.
};

float Point::size = pointSize; // Set point size.

// Function to draw a point.
void Point::drawPoint(void)
{
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex3f(xVal, yVal, 0.0);
	glEnd();

	if (1)
	{
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_LINES);
		glVertex3f(0, yVal, 0.0);
		glVertex3f(width, yVal, 0.0);
		glEnd();

		glBegin(GL_LINES);
		glVertex3f(xVal, 0, 0.0);
		glVertex3f(xVal, height, 0.0);
		glEnd();
	}
	//  glBegin(GL_POLYGON);
	//glVertex3f(20.0, 20.0, 0.0);
	//glVertex3f(80.0, 20.0, 0.0);
	//glVertex3f(80.0, 80.0, 0.0);
	//glVertex3f(20.0, 80.0, 0.0);
	//glEnd();


}

// Vector of points.
vector<Point> points;

// Iterator to traverse a Point array.
vector<Point>::iterator pointsIterator;

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	// Loop through the points array drawing each point.
	pointsIterator = points.begin();
	while (pointsIterator != points.end())
	{
		pointsIterator->drawPoint();
		pointsIterator++;
	}

	glFlush();
}





// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set viewing box dimensions equal to window dimensions.
	glOrtho(0.0, (float)w, 0.0, (float)h, -1.0, 1.0);

	// Pass the size of the OpenGL window to globals.
	width = w;
	height = h;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	cout << "Interaction:" << endl;
	cout << "Left mouse click to draw a square point, right mouse click to exit." << endl;
}


struct Node {
	Point pos;
	int data;
	Node(Point pt, int dat) :pos(pt), data(dat) {}
	Node() {
		data = 0;

	}
	int GetX() {
		return pos.GetX();
	}
	int GetY() {
		return pos.GetY();
	}

};

class Quad {
private:
	Point topLeft;
	Point botRight;
	Node * n;
	Quad * topLeftTree;
	Quad * topRightTree;
	Quad * botLeftTree;
	Quad * botRightTree;
public:
	Quad() {
		topLeftTree = NULL;
		topRightTree = NULL;
		botLeftTree = NULL;
		botRightTree = NULL;
		n = NULL;
	}
	Quad(Point tl, Point br) {
		topLeft = tl;
		botRight = br;
		topLeftTree = NULL;
		topRightTree = NULL;
		botLeftTree = NULL;
		botRightTree = NULL;
		n = NULL;

	}
	void insert(Node *);
	Node * search(Point);
	bool inBoundary(Point);
	void Draw();
	void PrintBounds();
};

void Quad::PrintBounds() {

	std::cout << "Hello!" << std::endl;
	std::cout << topLeft.GetX() << " ," << topLeft.GetY() << "      " << botRight.GetX() << "," << botRight.GetY() << std::endl;
}

bool Quad::inBoundary(Point p)
{
	return (p.GetX() >= topLeft.GetX() && p.GetX() <= botRight.GetX() && p.GetY() >= topLeft.GetY() && p.GetY() <= botRight.GetY());
}

void Quad::insert(Node * node) {
	std::cout << "------------------------------" << std::endl;
	std::cout << node->pos.GetX() << " " << node->GetY() << std::endl;
	this->PrintBounds();
	if (node == NULL) {
		return;
	}

	if (!inBoundary(node->pos)) {
		
		std::cout << "not in this quad !" << std::endl;
		return;
	}

	if (abs(topLeft.GetX() - botRight.GetX()) <= 1 && abs(topLeft.GetY() - botRight.GetY()) <= 1) {
		if (n == NULL) {
			n = node;
			std::cout << "Inserted NODE - " << node->GetX() << " " << node->GetY() << "----------------------------------------" << std::endl;
		}
		return;
	}

	int xc = (topLeft.GetX() + botRight.GetX()) / 2;
	int yc = (topLeft.GetY() + botRight.GetY()) / 2;
	if (xc >= node->pos.GetX()) {
		if (yc >= node->pos.GetY()) {
			//ADD top left
			std::cout << "Inserting top left" << std::endl;
			if (topLeftTree == NULL) {
				topLeftTree = new Quad(Point(topLeft.GetX(),topLeft.GetY()), Point(xc,yc));
			}
			topLeftTree->insert(node);
		}
		else {
			//ADD bottom left
			std::cout << "Inserting botom left" << std::endl;
			if (botLeftTree == NULL) {
				botLeftTree = new Quad(Point(topLeft.GetX(), yc), Point(xc, botRight.GetY()));
			}
			botLeftTree->insert(node);
			
		}
	}
	else if (yc >= node->pos.GetY()) {
		//ADD top right
		std::cout << "Inserting top right" << std::endl;
		if (topRightTree == NULL) {
			topRightTree = new Quad(Point(xc, topLeft.GetY()), Point(botRight.GetX(), yc));
		}
			topRightTree->insert(node);
		}
		else {
		// ADD bottom right
		std::cout << "Inserting bottom right" << std::endl;
		if (botRightTree == NULL) {
			botRightTree = new Quad(Point(xc, yc), Point(botRight.GetX(), botRight.GetY()));
		}
		botRightTree->insert(node);
		}


}

Quad root;

// Find a node in a quadtree 
Node* Quad::search(Point p)
{
	std::cout << "POINT SEARCH CALLED!!! " << std::endl;

	// Current quad cannot contain it 
	if (!inBoundary(p))
	{
		std::cout << "Point not found boundary" << std::endl;
		return NULL;
	}
	std::cout << "Here 0 " << std::endl;
	// We are at a quad of unit length - we know that because n is not NULL - that only happens at 1 pixel level
	// We cannot subdivide this quad further 
	if (n != NULL)
	{
		std::cout << "Point found!!!" << std::endl;
		return n;
	}
	

	if ((topLeft.GetX() + botRight.GetX()) / 2 >= p.GetX())
	{
		std::cout << "HERE 1" << std::endl;
		// Indicates topLeftTree 
		if ((topLeft.GetY() + botRight.GetY()) / 2 >= p.GetY())
		{
			if (topLeftTree == NULL)
			{
				std::cout << "TopLeft exit" << std::endl;
				std::cout << "Point not found TL END" << std::endl;
				return NULL;
			}
			std::cout << "Search deeper topLeft " << std::endl;
			return topLeftTree->search(p);
		}

		// Indicates botLeftTree 
		else
		{
			if (botLeftTree == NULL)
			{
				std::cout << "BotLeft exit" << std::endl;
				std::cout << "Point not found BL END" << std::endl;
				return NULL;
			}
			std::cout << "Search deeper botLeft " << std::endl;
			return botLeftTree->search(p);
		}
	}
	else
	{
		std::cout << "HERE 2" << std::endl;
		// Indicates topRightTree 
		if ((topLeft.GetY() + botRight.GetY()) / 2 >= p.GetY())
		{
			if (topRightTree == NULL)
			{
				std::cout << "TopRight exit" << std::endl;
				std::cout << "Point not found TR END" << std::endl;
				return NULL;
			}
			std::cout << "Search deeper topRight " << std::endl;
			return topRightTree->search(p);
		}

		// Indicates botRightTree 
		else
		{
			if (botRightTree == NULL)
			{
				std::cout << "BotRight exit" << std::endl;
				std::cout << "Point not found BR END" << std::endl;
				return NULL;
			}
			std::cout << "Search deeper botRight " << std::endl;
			return botRightTree->search(p);
		}
	}
	std::cout << "Point not found END!";
};


void Quad::Draw() {
	
	if (n == NULL)
	{
		int x1 = topLeft.GetX();
		int y1 = topLeft.GetY();
		int x2 = botRight.GetX();
		int y2 = botRight.GetY();
		int xc = (x1 + x2) / 2;
		int yc = (y1 + y2) / 2;
		//std::cout << "Drawing lines" << std::endl;
		
		glColor3f(0.0, 0.0, 0.0);

		glBegin(GL_LINES);
		glVertex3f(x1, yc, 0.0);
		glVertex3f(x2, yc, 0.0);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(xc, y1, 0.0);
		glVertex3f(xc, y2, 0.0);
		glEnd();

		if (topLeftTree != NULL) {
			topLeftTree->Draw();
		}
		if (topRightTree != NULL) {
			topRightTree->Draw();
		}
		if (botRightTree != NULL) {
			botRightTree->Draw();
		}
		if (botLeftTree != NULL) {
			botLeftTree->Draw();
		}
	}
	else {
		std::cout << "Drawing point " << std::endl;
		glColor3f(1.0, 0.0, 0.0);
		glPointSize(1.5);
		glBegin(GL_POINTS);
		int xVal = n->GetX();
		int yVal = n->GetY();
		glVertex3f(xVal, yVal, 0.0);
		glEnd();
	}
	

}
void drawQuad(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	root.Draw();
	glFlush();
}


// Mouse callback routine.
void mouseControl(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)

		// Store the clicked point in the points array after correcting
		// from event to OpenGL co-ordinates.
		points.push_back(Point(x, height - y));
	std::cout << "trying to insert " << x << "  " << height - y << std::endl;
	root.PrintBounds();
	//root.insert(new Node(Point(x, height - y), 5));
	std::cout << "coordinates " << x << "  " << y << std::endl;
	root.insert(new Node(Point(x, height - y), 5));


	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) exit(0);

	glutPostRedisplay();
}


// Main routine.
int main(int argc, char **argv)
{
	
	printInteraction();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	int xsize = 512*2;
	int ysize = 512*2;
	glutInitWindowSize(xsize, ysize);
	root = Quad(Point(0, 0), Point(xsize, ysize));
	root.PrintBounds();
	Node n1(Point(10, ysize - 20), 1);
	root.insert(&n1);
	root.search(Point(100, 104));

	glutInitWindowPosition(100, 100);
	glutCreateWindow("mouse.cpp");
	setup();
	//glutDisplayFunc(drawScene);
	glutDisplayFunc(drawQuad);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	// Register the mouse callback function. 
	glutMouseFunc(mouseControl);

	glutMainLoop();

	

	std::cin.get();
	return 0;
}
