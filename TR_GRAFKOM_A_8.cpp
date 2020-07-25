#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sstream>

#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)


bool shouldChangeColor = false;

double redShade = 0;
double greenShade = 0;
double blueShade = 0;

double extraRedShade = 0;
double extraGreenShade = 0;
double extraBlueShade = 0;

double pageScaleX = 1;
double pageScaleY = 1;
double pageTranslationX = 0;
double pageTranslationY = 0;
double targetpageScaleX = 1;
double targetpageScaleY = 1;
double targetpageTranslationX = 0;
double targetpageTranslationY = 0;

float randomFloat()
{
	return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}


void resetColors()
{
	redShade = 0;
	greenShade = 0;
	blueShade = 0;
	extraRedShade = 0;
	extraGreenShade = 0;
	extraBlueShade = 0;
}

class Vector3f
{
	
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f const &v)
	{
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f &v)
	{
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n)
	{
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n)
	{
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit()
	{
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v)
	{
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

class Camera
{
public:
	Vector3f eye, center, up;

	Camera(float eyeX = 1.0f, float eyeY = 1.0f, float eyeZ = 1.0f, float centerX = 0.0f, float centerY = 0.0f, float centerZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f)
	{
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
		Vector3f view = (center - eye).unit();
		eye = eye + view * -0.7;
		center = center + view * -0.7;
	}

	void moveX(float d)
	{
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
	}

	void moveY(float d)
	{
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	void moveZ(float d)
	{
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void rotateX(float a)
	{
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void rotateY(float a)
	{
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void look()
	{
		gluLookAt(
				eye.x, eye.y, eye.z,
				center.x, center.y, center.z,
				up.x, up.y, up.z);
	}
};

Camera camera;

void setDefaultColor()
{
	glColor3f(0.5, 0.5, 0.5);
}

void setupLights()
{
	GLfloat ambient[] = {0.7f, 0.7f, 0.7, 1.0f};
	GLfloat diffuse[] = {0.6f, 0.6f, 0.6, 1.0f};
	GLfloat specular[] = {1.0f, 1.0f, 1.0, 1.0f};
	GLfloat shininess[] = {50};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	GLfloat lightIntensity[] = {0.7f, 0.7f, 1, 1.0f};
	// GLfloat lightPosition[] = { -7.0f, 6.0f,3.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}

void setupCamera()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 640 / 480, 0.001, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}

void tanah (double thickness)
{
	glPushMatrix();
	glTranslated(0.2, 0.2 * thickness, 0.2);
	glScaled(4.0, thickness, 4.0);
	glColor3f(0.0 + redShade, 0.9 + extraGreenShade, 0 - blueShade);
	glutSolidCube(1);
	glPopMatrix();
	setDefaultColor();
}

void parit (double thickness)
{
	glPushMatrix();
	glTranslated(0.22, 0.22 * thickness, 0.22);
	glScaled(2.3, thickness, 2.3);
	glColor3f(0.1 + redShade, 0.3 + extraGreenShade, 1 - blueShade);
	glutSolidCube(1);
	glPopMatrix();
	setDefaultColor();
}

void tanah2 (double thickness)
{
	glPushMatrix();
	glTranslated(0.24, 0.24 * thickness, 0.24);
	glScaled(2.0, 0.6, 2.0);
	glColor3f(0.0 + redShade, 0.9 + extraGreenShade, 0 - blueShade);
	glutSolidCube(1);
	glPopMatrix();
	setDefaultColor();
}



void tembokdepan(double thickness)
{
	
}

void Ruangan()
{

	glPushMatrix();
	glTranslated(pageTranslationX, pageTranslationY, 0);

	setDefaultColor();

	glPopMatrix();

	tanah(0.02);
	glPushMatrix();
	
	parit(0.02);
	glPushMatrix();
	
	tanah2(0.02);
	glPushMatrix();
	//tembok belakang
	glPushMatrix();
	glTranslated(-0.3, 0.4 , 0.33);
	glScaled(0.13, 0.4, 1.2);
	glColor3f(0.9 + redShade, 0.9 + extraGreenShade, 1 - blueShade);
	glutSolidCube(1);
	glPopMatrix();
	
	//tower kiri belakang
	glPushMatrix();
	glTranslated(-0.27, 0.4 , 1);
	glScaled(0.13, 0.8,-0.2);
	glColor3f(0.9 + redShade, 0.9 + extraGreenShade, 1 - blueShade);
	glutSolidCube(1);
	glPopMatrix();
	
	//tower kanan belakang
	glPushMatrix();
	glTranslated(-0.27, 0.4 , -0.3);
	glScaled(0.13, 0.8,-0.2);
	glColor3f(0.9 + redShade, 0.9 + extraGreenShade, 1 - blueShade);
	glutSolidCube(1);
	glPopMatrix();
	
	//tembok kiri
	glPushMatrix();
	glTranslated(0.2, 0.4 , 1.02);
	glScaled(1, 0.4, 0.13);
	glColor3f(0.9 + redShade, 0.9 + extraGreenShade, 1 - blueShade);
	glutSolidCube(1);
	glPopMatrix();

	//tembok kanan
	glPushMatrix();
	glTranslated(0.2, 0.4 , -0.35);
	glScaled(1, 0.4, 0.13);
	glColor3f(0.9 + redShade, 0.9 + extraGreenShade, 1 - blueShade);
	glutSolidCube(1);
	glPopMatrix();
	
	//tower kiri depan
	glPushMatrix();
	glTranslated(0.75, 0.4 , 1);
	glScaled(0.13, 0.8,-0.2);
	glColor3f(0.9 + redShade, 0.9 + extraGreenShade, 1 - blueShade);
	glutSolidCube(1);
	glPopMatrix();
	
	//tower kanan depan
	glPushMatrix();
	glTranslated(0.75, 0.4 , -0.3);
	glScaled(0.13, 0.8,-0.2);
	glColor3f(0.9 + redShade, 0.9 + extraGreenShade, 1 - blueShade);
	glutSolidCube(1);
	glPopMatrix();
	
	//tembok depan
	glPushMatrix();
	glTranslated(0.74, 0.4 , 0.33);
	glScaled(0.13, 0.4, 1.2);
	glColor3f(0.9 + redShade, 0.9 + extraGreenShade, 1 - blueShade);
	glutSolidCube(1);
	glPopMatrix();
	
	//bangunan 1
	glPushMatrix();
	glTranslated(0.2, 0.4 , 0.0);
	glScaled(0.5, 1.4 ,0.5);
	glColor3f(0.9 + redShade, 0.9 + extraGreenShade, 1 - blueShade);
	glutSolidCube(1);
	glPopMatrix();
	
	//bangunan 2
	glPushMatrix();
	glTranslated(0.2, 0.4 , 0.5);
	glScaled(0.5, 0.9 ,0.5);
	glColor3f(0.9 + redShade, 0.9 + extraGreenShade, 1 - blueShade);
	glutSolidCube(1);
	glPopMatrix();
	
	//gerbang depan 1
	glPushMatrix();
	glTranslated(0.8, 0.4 , 0.31);
	glScaled(0.3, 0.8 ,0.3);
	glColor3f(0.9 + redShade, 0.9 + extraGreenShade, 1 - blueShade);
	glutSolidCube(1);
	glPopMatrix();
	
	//gerbang depan 2
	glPushMatrix();
	glTranslated(0.95, 0.4 , 0.31);
	glScaled(0.15, 0.45 ,0.15);
	glColor3f(0.9 + redShade, 0.9 + extraGreenShade, 1 - blueShade);
	glutSolidCube(1);
	glPopMatrix();
	
	//tembok luar kiri
	glPushMatrix();
	glTranslated(0.3, 0.4 , 1.21);
	glScaled(1.75, 0.15, 0.05);
	glColor3f(0.9 + redShade, 0.9 + extraGreenShade, 1 - blueShade);
	glutSolidCube(1);
	glPopMatrix();
	
	//tembok luar kanan
	glPushMatrix();
	glTranslated(0.3, 0.4 , -0.6);
	glScaled(1.75, 0.15, 0.05);
	glColor3f(0.9 + redShade, 0.9 + extraGreenShade, 1 - blueShade);
	glutSolidCube(1);
	glPopMatrix();
	
	//tembok luar belakang
	glPushMatrix();
	glTranslated(-0.55, 0.4 , 0.32);
	glScaled(0.05, 0.15, 1.8);
	glColor3f(0.9 + redShade, 0.9 + extraGreenShade, 1 - blueShade);
	glutSolidCube(1);
	glPopMatrix();
	
	//tembok luar depan
	glPushMatrix();
	glTranslated(1.15, 0.4 , 0.32);
	glScaled(0.05, 0.15, 1.8);
	glColor3f(0.9 + redShade, 0.9 + extraGreenShade, 1 - blueShade);
	glutSolidCube(1);
	glPopMatrix();
}


void Tampilan()
{
	setupCamera();
	setupLights();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glScaled(pageScaleX, pageScaleY, 1);
	Ruangan();
	glPopMatrix();
	glFlush();
}

void setLeftView()
{
	camera.up.x = -0.00405836;
	camera.up.y = 0.999989;
	camera.up.z = 0.00230124;

	camera.center.x = -0.713009;
	camera.center.y = 0.448415;
	camera.center.z = 0.426624;

	camera.eye.x = -1.71246;
	camera.eye.y = 0.444435;
	camera.eye.z = 0.393797;
}

void setTopView()
{
	camera.up.x = 0.0226687;
	camera.up.y = -0.0143616;
	camera.up.z = -0.99964;

	camera.center.x = -0.00778855;
	camera.center.y = 1.79373;
	camera.center.z = 0.516674;

	camera.eye.x = -0.00758377;
	camera.eye.y = 2.79363;
	camera.eye.z = 0.502314;
}

void setRightView()
{
	camera.up.x = -0.108454;
	camera.up.y = 0.994058;
	camera.up.z = -0.00928754;

	camera.center.x = 0.952321;
	camera.center.y = 0.526236;
	camera.center.z = 0.454693;

	camera.eye.x = 1.94623;
	camera.eye.y = 0.634482;
	camera.eye.z = 0.434158;
}

void setFrontView()
{
	camera.up.x = -0.00171101;
	camera.up.y = 0.995962;
	camera.up.z = -0.0897583;

	camera.center.x = 0.0095462;
	camera.center.y = 0.491564;
	camera.center.z = 1.5339;

	camera.eye.x = 0.0304264;
	camera.eye.y = 0.590316;
	camera.eye.z = 2.62926;
}

void onKeyPress(unsigned char key, int x, int y)
{
	float d = 0.01 * 10;

	switch (key)
	{

	case 'c': //ganti warna lampu ruangan
		shouldChangeColor = !shouldChangeColor;
		if (!shouldChangeColor)
			resetColors();
		break;
	case 'w': //gerak ke atass
		camera.moveY(d);
		break;
	case 's': // gerak ke bawah
		camera.moveY(-d);
		break;
	case 'a'://gerak ke kiri
		camera.moveX(d);
		break;
	case 'd': // gerak ke kanan
		camera.moveX(-d);
		break;
	case 'q':// perbesar
		camera.moveZ(d);
		break;
	case 'e':// perkecil
		camera.moveZ(-d);
		break;
	case 'h': // tampilan dari kanan
		setRightView();
		break;
	case 'g': // tampilan dari kiri
		setLeftView();
		break;
	case 'y': //tampilan dari atas
		setTopView();
		break;
	case 'f': // tapilan dari depan
		setFrontView();
		break;
	case GLUT_KEY_ESCAPE:
		exit(EXIT_SUCCESS);
	}

	glutPostRedisplay();
}

void onSpecialKey(int key, int x, int y) //untuk menggerakan tampilan dengan key arrow
{
	float a = 3.0;

	switch (key)
	{
	case GLUT_KEY_UP:
		camera.rotateX(a);
		break;
	case GLUT_KEY_DOWN:
		camera.rotateX(-a);
		break;
	case GLUT_KEY_LEFT:
		camera.rotateY(a);
		break;
	case GLUT_KEY_RIGHT:
		camera.rotateY(-a);
		break;
	}

	glutPostRedisplay();
}

void colorDurationHandler(int x)
{
	if (shouldChangeColor)
	{
		redShade = randomFloat();
		greenShade = randomFloat();
		blueShade = randomFloat();

		extraRedShade = randomFloat();
		extraGreenShade = randomFloat();
		extraBlueShade = randomFloat();
	}
	glutPostRedisplay();
	glutTimerFunc(500, colorDurationHandler, 0);
}

int main(int argc, char **argv)
{
	
	glutInit(&argc, argv);

	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("TR GRAFKOM A - KELOMPOK 8");
	glutDisplayFunc(Tampilan);
	glutKeyboardFunc(onKeyPress);
	glutSpecialFunc(onSpecialKey);
	colorDurationHandler(0);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
	return 0;
}
