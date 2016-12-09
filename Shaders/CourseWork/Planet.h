#pragma once
#include "../DXFramework/SphereMesh.h"
#include "../DXFramework/CubeMesh.h"
#include "TessilatedShereMeshShereMesh.h"
#include "../DXFramework/RenderTexture.h"
#include "../DXFramework/Camera.h"
#include "../DXFramework/D3D.h"
#include "PlanetShader.h"

class Planet
{
public:
	Planet();
	~Planet();

	void Init(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	void Update(float deltaTime);
	void Render(RenderTexture* RenderTexture, D3D* device, Camera* camera);
	void MenuOptions(bool* is_open);
private:

	TessilatedShereMesh* PlanetShpere;

	PlanetShader* planetShader;


	XMINT4 planetInnerTessAmmount;
	XMINT2 planetOuterTessAmmount;
};

