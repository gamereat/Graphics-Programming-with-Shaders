// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "../DXFramework/baseapplication.h"
#include "D3D.h"
#include "../DXFramework/PlaneMesh.h"
#include "../DXFramework/SphereMesh.h"
#include "LightSpecularShader.h"

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
	LightSpecularShader* m_Light_Shader;
	PlaneMesh* m_Quad_Mesh;
	SphereMesh* m_Sphere_Mesh;
	XMFLOAT3 lightPos;
	XMFLOAT3 lightAttenation;
	float lightRange;
 };

#endif