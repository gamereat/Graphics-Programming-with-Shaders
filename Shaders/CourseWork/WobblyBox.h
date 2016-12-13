#pragma once
#include "../DXFramework/SphereMesh.h"
#include "../DXFramework/CubeMesh.h"
#include "../DXFramework/QuadMesh.h"
#include "TessilatedShereMeshShereMesh.h"
#include "PlanetShader.h"
#include "../DXFramework/CubeMesh.h"
#include "HeightMap.h"
#include "TesselatedQuadMess.h"
#include "VertexShader.h"
#include "Scene.h"
 class WobblyBox : public Scene
{
public:
	WobblyBox(std::string sceneName);
	~WobblyBox();




	void Init(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	void Update(Timer* timer);
	void Render(RenderTexture* renderTexture, D3D* device, Camera* camera, RenderTexture *depthMap[], Light* light[]);
	void MenuOptions();
private:

	void GenerateDepthPass(D3D* device, Camera* camera, RenderTexture*depthMap[], Light* light[]);

	virtual void SceneInformationPopUp(bool* is_open);


	static bool isWaterMenuOpen;
	static bool isTessMenuOpen;
	void waterOptions(bool* is_open);
	void tesselationOptions(bool* is_open);
	CubeMesh* PlanetShpere;
	Texture* heightMapTexture;

	PlanetShader* planetShader;



	PlanetShader::PlanetBufferType plantinfo;
	PlanetShader::TessellationBufferType tesselationInfo;

	 

 };

