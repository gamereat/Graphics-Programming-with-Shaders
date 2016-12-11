#pragma once
#include "../DXFramework/SphereMesh.h"
#include "../DXFramework/CubeMesh.h"
#include "../DXFramework/QuadMesh.h"
#include "TessilatedShereMeshShereMesh.h"
#include "../DXFramework/RenderTexture.h"
#include "../DXFramework/Camera.h"
#include "../DXFramework/D3D.h"
#include "PlanetShader.h"
#include "../DXFramework/CubeMesh.h"
#include "HeightMap.h"
#include "TesselatedQuadMess.h"
#include "../DXFramework/Light.h"
#include "VertexShader.h"
#include "DepthShader.h"
 class Planet
{
public:
	Planet();
	~Planet();




	void Init(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	void Update(float deltaTime);
	void Render(RenderTexture* renderTexture, D3D* device, Camera* camera, RenderTexture *depthMap[], Light* light[]);
	void MenuOptions();
private:

	void GenerateDepthPass(D3D* device, Camera* camera, RenderTexture*depthMap[], Light* light[]);

	bool isWaterMenuOpen;
	bool isTessMenuOpen;
	void waterOptions(bool* is_open);
	void tesselationOptions(bool* is_open);
	CubeMesh* PlanetShpere;
	Texture* heightMapTexture;

	PlanetShader* planetShader;



	PlanetShader::PlanetBufferType plantinfo;
	PlanetShader::TessellationBufferType tesselationInfo;


	DepthShader* depthShader;
	RenderTexture* m_depth_Textur;

	float t = 0;
};

