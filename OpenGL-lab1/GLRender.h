#pragma once


class GLRender
{
public:
	HGLRC m_hrc;

	//za rotaciju
	int ugaoZ, ugaoX, ugaoY,
		LampaX, LampaZ, gornjiDeoX,
		gornjideoY, glavaX, glavaY;

	//za translaciju
	int x, y, z;

	//materijali
	int parts;
public:

	GLRender(void);
	~GLRender(void);
	virtual bool CreateGLContext(CDC* pDC);
	virtual void PrepareScene(CDC* pDC);
	virtual void DestroyScene(CDC* pDC);
	virtual void Reshape(CDC* pDC,int w, int h);
	virtual void DrawScene(CDC* pDC);
	virtual void DrawBox(double a, double b, double c);
	virtual void DrawTable();
	virtual void DrawWalls(int a);
	virtual void DrawWall(int a);
	virtual void DrawLamp();
	virtual void DrawLampTop();
	virtual void DrawBox2(double a, double b, double c);
	
	
	
	
	virtual void SetLightModel();
	virtual void SetMaterial();

};

