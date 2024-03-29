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
#include "wobblyBox.h"
#include "Scene.h"
#include "GeomertyShaderScene.h"
#include "Terrain.h"
const int SHADOWMAP_WIDTH = 1024;
const int SHADOWMAP_HEIGHT = 1024;

/*
Base application used to interact with any of my scenes 
*/
class App1 : public BaseApplication
{
public:

 
	App1();
	~App1();
	
	/*
	Initializes application 

 	*/
	void init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input*);
	
	/*
	Update function used to update given scene

	@return is it was successful 
	*/
	bool Frame();

protected:
	/*
	Renders the given scene 
	@return is it was successful
	*/
	bool Render();
	
	/*
	Adds menu bar option to top of application to expose function to the user 
	*/
	void CreateMainMenuBar();


private:


	/*
	Shows off Geomerty Shader explotion
	*/
	GeomertyShaderScene* geomertyShaderScene;
	/*
	The current Scene that is viewed the world 

	*/
	Scene* currentScene;
	
	/*
	Wobbly box scene which demonstrates wave functions
	*/
	WobblyBox* wobblyBoxScene;

	/*
	Terrain scene demonstrates terrain generation and hight maps 
	*/
	Terrain* terrainScence;

	/*
	Post processing object which creates and adds in post processing effects to scene
	*/
	PostProcessing postPro;

	/*
	Render 
	*/
	void RenderToScreen();
  

	/*
	Lights used within the world all usable at any point 
	*/
 	Light* lights[4];
	

	/*
	holds all the depth textures from each light
	*/
	RenderTexture* depthTextures[NUM_LIGHTS];

	/*
	Render texture used to send to a scene
	*/
 	RenderTexture* sceneTexture;
	
	/*
	Texture that has been up scaled to correct size after post processing
	*/
	RenderTexture* upScaleTexture;
 

	/*
	OrthorMesh that is scaled to correct size
	*/
 	OrthoMesh* orthoMeshNormalScaled;
	  
	/*
	Texture shader that will add a texture to a object
	*/
	TextureShader* textureShader;


 };

#endif