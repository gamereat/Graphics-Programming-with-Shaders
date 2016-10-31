// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "../DXFramework/baseapplication.h"
#include "D3D.h"
#include "../DXFramework/PlaneMesh.h"
#include "../DXFramework/SphereMesh.h"
#include "VertexShader.h"
#include "BoxBlurShader.h"
#include "../DXFramework/Light.h"
#include "TextureShader.h"
#include "../DXFramework/OrthoMesh.h"
#include "../DXFramework/RenderTexture.h"
#include "TessellationShader.h"
#include "../DXFramework/TessellationMesh.h"

class App1 : public BaseApplication
{
public:

	App1();
	~App1();
	void init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input*);

	bool Frame();

protected:
	bool Render();
	void CreateMainMenuBar();


private:

	void RenderTessellation();

	void RenderToTexture();
	void RenderToScreen();
	void RenderBoxBlur();
 	void RenderVertexMinulation();

	void vertexChangesMenu(bool * is_open);

	void tessellationMenu(bool * is_open);

	void boxBlurChangesMenu(bool * is_open);

 	Light* m_Lights[4];
	
	TessellationMesh* m_Tessellation_mesh;

	TessellationShader* m_Tessellation_Shader;

	VertexShader* m_Vertex_Manipulation_Shader;
	TextureShader* m_Texture_Shader;
	BoxBlurShader* m_BoxBur_Shader;

	RenderTexture* m_Render_Texture;

	RenderTexture* m_Render_VextexMinulation;

	PlaneMesh* m_Quad_Mesh;
	SphereMesh* m_Sphere_Mesh;
	OrthoMesh* m_Ortho_Mesh;

	XMFLOAT3 lightPos;
	XMFLOAT3 lightAttenation;
	float lightRange;
	float planeHeight;
	float planeFreqnacy;
 	float sphereHeight;
	float sphereFreqnacy;

	bool isUsingBoxBlur;

	XMINT3 outerTesselation;

	int innerTesselation;

	VertexShader::typeOfVertexMinimulation planesManipulation;
	VertexShader::typeOfVertexMinimulation sphereManipulation;
 };

#endif