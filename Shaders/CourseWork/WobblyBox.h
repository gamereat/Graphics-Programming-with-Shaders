#pragma once
#include "../DXFramework/SphereMesh.h"
#include "../DXFramework/CubeMesh.h"
#include "../DXFramework/QuadMesh.h"
#include "TessilatedShereMeshShereMesh.h"
#include "WobblyShader.h"
#include "../DXFramework/CubeMesh.h"
#include "TesselatedQuadMess.h"
#include "VertexShader.h"
#include "Scene.h"
/*
Wobbly box scene used to inseminate waves and distance based tessellation 
*/
 class WobblyBox : public Scene
{
public:
	/*
	@param sceneName		Name for the given scene
	*/
	WobblyBox(std::string sceneName);
	~WobblyBox();



	/*
	Initializes the given Scene

	@param hwnd		A handle to the window
	@param device	The directx11 device
	@param deviceContext	The directx11 device Context

	*/
	void Init(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* deviceContext);

	/*
	Updates the current scene

	@param timer	 application timer that can be used to get total time and delta time for application
	*/
	void Update(Timer* timer);
	/*
	Renders the given scene

	@param renderTexture	The given render texture that should be used for this scene
	@param device			The directx11 device
	@paran camera			the camera for the scene
	@param depthmap			The Render textures to be used for depths maps from the given lights
	@param lights			The lights within the scene
	*/
	void Render(RenderTexture* renderTexture, D3D* device, Camera* camera, RenderTexture *depthMap[], Light* light[]);
	
	/*
	The given menu options for the scene
	*/
	void MenuOptions();


	/*
	Will set lights back to correct position in the world
	Used when changing scene so lights so the scene in the best light :D and are light correctly

	@param lights The lights from within the world
	*/
	virtual void ResetLights(Light* lights[]);
private:



	/*
	Does a depth pass on the given scene

	@param device	The directx11 device
	@param camera	The camera within the scene
	@param DepthMap	The depth maps to be created on to
	@param lights   The lights within the scene
	*/
	void GenerateDepthPass(D3D* device, Camera* camera, RenderTexture*depthMap[], Light* light[]);

	/*
	Scene information pop up will tell the user about the current scene
	*/
	virtual void SceneInformationPopUp(bool* is_open);

	/*
	If the water effect menu is open 
	*/
	bool isWaterMenuOpen;
 
	/*
	If the tessellation effect menu is open
	*/
	bool isTessMenuOpen;

	/*
	Water menu 
	allows used to change water effects in real time

	@param is_open if the menu option is open
	*/
	void waterOptions(bool* is_open);

	/*
	tessellation menu
	allows used to change tessellation effects in real time

	@param is_open if the menu option is open
	*/
	void tesselationOptions(bool* is_open);

	/*
	Box shape used to add wave effect to
	*/
	CubeMesh* boxShape;
	
	/*
	Shader used to create wave effects
	*/
	WobblyShader* wobblyShader;
	
	/*
	Holds variables that can effect the wave effects
	*/
	WobblyShader::WavetBufferType waveInfo;

	/*
	Holds Tessellation effect information for changing in real time
	*/
	WobblyShader::TessellationBufferType tesselationInfo;

	 
	/*
	Texture used to create hight map from
	*/
	Texture* heightMapTexture;
 };

