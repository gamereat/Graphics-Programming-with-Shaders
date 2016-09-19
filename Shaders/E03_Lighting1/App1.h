// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "../DXFramework/baseapplication.h"
#include "D3D.h"
#include "../DXFramework/SphereMesh.h"
#include "LightShader.h"

class App1 : public BaseApplication
{
public:

	App1();
	~App1();
	void init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input*);

	bool Frame();

protected:
	bool Render();

private:
	Light* m_Light;
	LightShader* m_Light_Shader;
 	SphereMesh* m_Sphere_Mesh;

	float secondQuadRotation;
};

#endif