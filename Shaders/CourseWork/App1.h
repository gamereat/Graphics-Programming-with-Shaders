// Application.h
#ifndef _APP1_H
#define _APP1_H

// Includes
#include "../DXFramework/baseapplication.h"
#include "D3D.h"
#include "../DXFramework/PointMesh.h"

#include "../DXFramework/PlaneMesh.h"
#include "../DXFramework/SphereMesh.h"
#include "VertexShader.h"
#include "../DXFramework/Light.h"
#include "TextureShader.h"
#include "../DXFramework/OrthoMesh.h"
#include "../DXFramework/RenderTexture.h"
#include "TessellationShader.h"
#include "../DXFramework/TessellationMesh.h"
#include "../DXFramework/QuadMesh.h"
#include "../DXFramework/Model.h"

#include "VerticalBlurShader.h"
#include "PostProcessing.h"
#include "DepthShader.h"
#include "ShadowShader.h"
#include "GeomentryShader.h"
#include "TerrainGenerator.h"
#include "HeightMap.h"
#include "wobblyBox.h"
#include "Scene.h"
#include "Terrain.h"
const int SHADOWMAP_WIDTH = 1024;
const int SHADOWMAP_HEIGHT = 1024;
class App1 : public BaseApplication
{
public:

	enum class SceneViewed
	{
		WobblySquare = 1,

	};
 
	App1();
	~App1();
	void init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input*);
	 
	bool Frame();

protected:
	bool Render();
	void CreateMainMenuBar();


private:

	/*
	The current Scene that is viewed the world 
	*/
	Scene* currentScene;
	
	WobblyBox* wobblyBox;


	Terrain* terrain;
	PostProcessing postPro;
	void RenderTessellation();
	
 
	void RenderToTexture();
	void RenderToScreen();
  
	void RenderDepth();

	void RenderGeometry();

	void RenderVertexMinulation();
  
	void RenderTerrain();

	void RenderShadow();

 
	

	void tessellationMenu(bool * is_open);

	void GeomentryMenu(bool * is_open);

	void vertexChangesMenu(bool * is_open);
	Model* teaTop;

	HeightMap* heightMap;

	DepthShader* m_DepthShader;
	ShadowShader* m_ShadowShader;
	TerrainGenerator* terrainShader;

 	Light* m_Lights[4];
	
	TessellationMesh* m_Tessellation_mesh;
	TessellationShader* m_Tessellation_Shader;
	VertexShader* m_Vertex_Manipulation_Shader;
	TextureShader* m_Texture_Shader;

 	RenderTexture* m_Render_Texture;

	GeomentryShader* m_Geomentry_Shader;


	RenderTexture* m_Shadow_Texture;

	/*
	holds all the depth textures from each light
	*/
	RenderTexture* m_depth_Texture[NUM_LIGHTS];

	RenderTexture* m_Render_VextexMinulation;
	RenderTexture* m_TerrainTexture;
	RenderTexture* m_UpScaleTexture;
	PlaneMesh* m_Quad_Mesh;

	/*
	Mesh used to make terrain
	*/
	PlaneMesh* terrainMesh;



	SphereMesh* m_Sphere_Mesh;
	OrthoMesh* m_Ortho_Mesh_normalScaled;

	PointMesh* m_Point_Mesh;


	XMFLOAT3 lightPos;
	XMFLOAT3 lightAttenation;
	float lightRange;
	float planeHeight;
	float planeFreqnacy;
 	float sphereHeight;
	float sphereFreqnacy;

	bool isTri;
	XMFLOAT4 vertexScale;

	XMINT4 interTess;

	XMINT2 outerTess;


	VertexShader::typeOfVertexMinimulation planesManipulation;
	VertexShader::typeOfVertexMinimulation sphereManipulation;


 };

#endif