#include "StdAfx.h"
#include "GLRender.h"
#include <gl\GL.h>
#include <gl\GLU.h>
#include "glut.h"
GLRender::GLRender(void)
{
	x = y = 0;
	z = -10;
	
	ugaoX = 30;
	ugaoY = -30;

	LampaX = 0;
	LampaZ = 0;

	gornjiDeoX = -60;

	glavaX = glavaY = 0;
}

GLRender::~GLRender(void)
{
}

void SetWoodMaterial()
{
	float diffuse[] = {.6014, .2973, .1019};
	float specular[] = {1.0, 1.0, 1.0, 1.0};
	float shinines[] = {50.0};

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

	glShadeModel(GL_SMOOTH);
}

void SetRedMetal()
{
	float reddiffuse[] = {1.0, .0, .0};
	float redspecular[] = { 1.0, 1.0, 1.0, 1.0 };
	float shinines[] = { 50.0 };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, reddiffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, shinines);
	glMaterialfv(GL_FRONT, GL_SPECULAR, redspecular);

	glShadeModel(GL_SMOOTH);
}

void SetWallMaterial()
{
	float ambient[] = { .2, .2, .2, 1.0 };
	float diffuse[] = { .3891, .3346, .2763, 1.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
}

void SetBulbMaterial()
{
	float diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	float specular[] = { 1.0, 1.0, 1.0, 1.0 };
	float emission[] = { 50.0 };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, emission);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	glShadeModel(GL_SMOOTH);
}

bool GLRender::CreateGLContext(CDC* pDC)
{
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd,0,sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize=sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion=1;
	pfd.dwFlags=PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType=PFD_TYPE_RGBA;
	pfd.cColorBits=32;
	pfd.cDepthBits=32;
	pfd.iLayerType=PFD_MAIN_PLANE;

	int nPixelFormat=ChoosePixelFormat(pDC->m_hDC,&pfd);
	
	if(nPixelFormat==0)
		return false;

	BOOL bResult=SetPixelFormat(pDC->m_hDC,nPixelFormat,&pfd);

	if(!bResult)
		return false;

	m_hrc=wglCreateContext(pDC->m_hDC);

	if(!m_hrc)
		return false;

	return true;
}
void GLRender::PrepareScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC,m_hrc);
	glClearColor(1.0,1.0,1.0,0.0);
	glEnable(GL_DEPTH_TEST);

	SetLightModel();
	
	wglMakeCurrent(NULL,NULL);
}

void GLRender::DestroyScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC,m_hrc);
	wglMakeCurrent(NULL,NULL);
	if(m_hrc)
	{
		wglDeleteContext(m_hrc);
		m_hrc=NULL;
	}

}

void GLRender::Reshape(CDC* pDC,int w, int h)
{
	wglMakeCurrent(pDC->m_hDC,m_hrc);
	glViewport(0,0,(GLsizei) w,(GLsizei) h);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective(40,(double)w/(double)h,1,100);
	
	glMatrixMode(GL_MODELVIEW);
	wglMakeCurrent(NULL,NULL);
}

void GLRender::DrawScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC,m_hrc);
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(0,0,0,0,0,-10,0,1,0);
	glTranslatef(x, y, z);
	glRotatef(ugaoX, 1, 0, 0);
	glRotatef(ugaoY, 0, 1, 0);

	DrawWalls(10);
	DrawTable();

	SetRedMetal();
	DrawLamp();
	
	glFlush();
	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(NULL,NULL);

}

//SetRedMetal();
//
//float diffuse[] = { .3, .3, .3, 1.0 };
//float specular[] = { 1.0, 1.0, 1.0, .3 };
//float ambient[] = { .3, .3, .3, 1.0 };
//
//glMaterialfv(GL_BACK, GL_AMBIENT, ambient);
//glMaterialfv(GL_BACK, GL_DIFFUSE, diffuse);
//glMaterialfv(GL_BACK, GL_SPECULAR, specular);

void GLRender::DrawBox(double a, double b, double c)
{
	GLfloat vertices[]= { -a/2, -b/2 ,c/2, 
		a/2, -b/2 ,c/2, 
		a/2, b/2 ,c/2, 
		-a/2, b/2 ,c/2, 
		-a/2, -b/2 ,-c/2, 
		a/2, -b/2 ,-c/2,
		a/2, b/2 ,-c/2,
		-a/2, b/2 ,-c/2	};

	GLushort indices[]= { 0,1,2,3, 1,5,6,2, 7,6,5,4, 0,3,7,4, 7,3,2,6, 0,4,5,1	};
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, indices);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void GLRender::DrawBox2(double a, double b, double c)
{
	SetRedMetal();
	GLfloat vertices[] = { 0, 0, c,	
		a, 0, c, a, b, c, 
		0, b, c, 0, 0, 0, 
		a, 0, 0, a, b, 0, 
		0, b, 0 };
	GLushort indices[]=	{ 0,1,2,3, 1,5,6,2, 7,6,5,4, 0,3,7,4, 7,3,2,6, 0,4,5,1 };
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_SHORT, indices);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void GLRender::DrawTable()
{
	//nogare
	SetWoodMaterial();
	glPushMatrix();
	glColor3f(0,1,0);

	glTranslatef(1,1,1);

	DrawBox(0.1,2,0.1);

	glTranslatef(2.2,0,0);
	DrawBox(0.1,2,0.1);

	glTranslatef(-2.2,0,1.8);
	DrawBox(0.1,2,0.1);

	glTranslatef(2.2,0,0);
	DrawBox(0.1,2,0.1);

	glPopMatrix();
	//ispod table
	glPushMatrix();
	glColor3f(0.64,0,0);
	glTranslatef(1+1+0.1,0.2+1.6,0.8+1+0.1);
	DrawBox(2.1,0.4,1.7);
	glPopMatrix();
	//tabla
	glPushMatrix();
	glColor3f(0.9,0.62,0.58);
	glTranslatef(1.3+1-0.2,0.05+2,1.05+1-0.2);
	DrawBox(2.6,0.1,2.1);
	glPopMatrix();
}

void GLRender::DrawWall(int a)
{
	glBegin(GL_QUADS);
		glNormal3f(0.0, 0.0, 1.0);
		glVertex3f(0, 0, 0);
		glVertex3f(a, 0, 0);
		glVertex3f(a, a, 0);
		glVertex3f(0, a, 0);
	glEnd();
}

void GLRender::DrawWalls(int a)
{
	glPushMatrix();		
	glColor3f(0.7,0.7,0.7);
	
	glNormal3f(0.0, 0.0, -1.0);
	SetMaterial();
	DrawWall(a);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8,0.8,0.8);
	glRotatef(90,0,1,0);
	glTranslatef(-a, 0, 0);
	glNormal3f(0.0, -1.0, 0.0);
	
	DrawWall(a);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.3, 0.3, 0.3);
	glRotatef(270,1,0,0);
	glTranslatef(0, -a, 0);
	glNormal3f(-1.0, 0.0, 0.0);
	DrawWall(a);
	glPopMatrix();
}

void GLRender::DrawLamp()
{
	GLUquadricObj *obj;
	obj = gluNewQuadric();

	gluQuadricDrawStyle(obj, GLU_FILL);
	glColor3f(.9, .9, .2);
	glPushMatrix(); // sacuvamo stanje analogno pDC->GetWorldTransform(XFORM* xformStruct);
	glTranslatef(1.3, 2, 2);

	glRotatef(LampaX, 1, 0, 0);
	glRotatef(LampaZ, 0, 1, 0);
	SetRedMetal();
	gluSphere(obj, .2, 50, 8);

	glColor3f(.0, .0, .5);
	glRotatef(30, 1, 0, 0);
	SetRedMetal();
	DrawBox(0.05, 1.5, 0.05);

	glColor3f(.0, .5, .0);
	glTranslatef(.0, .71, 0);
	SetRedMetal();
	gluSphere(obj, .05, 50, 8);

	glPushMatrix(); //sve transformacije koje smo odradili ostaju "globalno"

	glColor3f(1, .0, .0);
	glRotatef(gornjiDeoX, 1, 0, 0);
	glRotatef(-45, 1, 0, 0);
	SetRedMetal();
	DrawBox2(0.05, 0.7, 0.05);


	glPushMatrix();
	glTranslatef(0.025, 0.5, 0.25);
	glRotatef(-45, 1, 0, 0);
	DrawLampTop();
	glPopMatrix();
	glPopMatrix();
	gluDeleteQuadric(obj);
	glPopMatrix();
}

void GLRender::DrawLampTop()
{
	glColor3f(.0, .0, .9);
	glPushMatrix();
	glTranslatef(0, 0.28, 0);
	glRotatef(glavaX, 1, 0, 0);
	glRotatef(glavaY, 0, 1, 0);

	DrawBox(0.12, 0.25, 0.15);
	// sfera
	GLUquadricObj *ob;
	ob = gluNewQuadric();

	glPushMatrix();
	glRotatef(-90, 0, 0, 1);
	GLdouble eqn[4] = { 0, -1, 0, 0 }; // Data for clipping plane 0.
	glClipPlane(GL_CLIP_PLANE0, eqn); // Specify clipping plane 0.
	glPopMatrix();

	glTranslatef(0, 0.25, 0);
	glClipPlane(GL_CLIP_PLANE0, eqn); // Specify clipping plane 0.
	glEnable(GL_CLIP_PLANE0);

	gluSphere(ob, 0.15, 30, 30);

	gluDeleteQuadric(ob);
	glDisable(GL_CLIP_PLANE0);

	glPopMatrix();

	GLUquadricObj *sijalica;
	sijalica = gluNewQuadric();

	glPushMatrix();

	glRotatef(glavaX, 1, 0, 0);
	glRotatef(glavaY, 0, 1, 0);
	SetBulbMaterial();
	glTranslatef(0, .50, 0);
	gluSphere(sijalica, .10, 30, 30);
	glPopMatrix();
}

void GLRender::SetLightModel() 
{
	float global_ambient[]  = { .2, .2, .2, 1.0 };
	float global_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
	float global_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	//globalno svetlo

	glLightfv(GL_LIGHT1, GL_AMBIENT, global_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, global_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, global_specular);

	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 40.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 7.0);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);

	// svetlo bele boje

	float local_ambient[]  = {.2, .2, .2, 1.0};
	float local_diffuse[] = {1.0, 1.0, 1.0, 1.0};
	float local_specular[] = {1.0, 1.0, 1.0, 1.0};
	float local_position[] = {.0, .0, 1.5, 2.5};

	glLightfv(GL_LIGHT2, GL_AMBIENT, local_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, local_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, local_specular);

	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0);

	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 20.0);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 2.0);

	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, .5);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0);

	glLightfv(GL_LIGHT2, GL_POSITION, local_position);

	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHTING);
}

void GLRender::SetMaterial()
{
	SetWallMaterial();
}