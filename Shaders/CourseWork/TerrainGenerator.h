#pragma once
#include "..\DXFramework\BaseShader.h"
#include "VertexShader.h"

using namespace std;
using namespace DirectX;

class TerrainGenerator :	public BaseShader
{
public:
	struct TessellationBufferType
	{
 
		float maxDistance;

		float minDistance;

		float minTesselationAmmount;
		float maxTesselationAmmount;
		XMFLOAT4 camPos;

	};



	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
		XMMATRIX lightView[NUM_LIGHTS];
		XMMATRIX lightProjection[NUM_LIGHTS];
	};
	struct CammeraBufferType
	{
		XMFLOAT3 cammeraPostion;
		float padding;
	};
	struct LightBufferType
	{
		//XMFLOAT4 ambient;
		//XMFLOAT4 diffuse; 

		XMFLOAT4 diffuseColour[NUM_LIGHTS];
		XMFLOAT4 lightDirection[NUM_LIGHTS];
		XMFLOAT4 ambientColour[NUM_LIGHTS];
		XMFLOAT4 specularColour[NUM_LIGHTS];
		XMFLOAT4 position[NUM_LIGHTS];

		XMFLOAT4 specularPower[NUM_LIGHTS];

		// 0 is constant
		// 1 linear
		// 2 quadratic
		// 3 range
		XMFLOAT4 attenuationValues[NUM_LIGHTS];

		//0 - directional
		//1- spot
		//2- point
		XMINT4 lightType[NUM_LIGHTS];

		int isSpecular[NUM_LIGHTS];

		int willGenerateShadows[NUM_LIGHTS];

	};

	struct LightBufferType2
	{
		XMFLOAT4 position[NUM_LIGHTS];
		//float padding;
	};
	struct TerrainBufferType {
	
		float scaler;
		XMFLOAT3 padding;

	};

	TerrainGenerator(ID3D11Device* device, HWND hwnd );
	~TerrainGenerator();

	void SetShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &worldMatrix, 
		const XMMATRIX &viewMatrix, const XMMATRIX &projectionMatrix, 
		ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView * highMap, TessellationBufferType tesselationInfo, 
		ID3D11ShaderResourceView*depthMap[], Light* light[], TerrainBufferType terrainInfo);
	void Render(ID3D11DeviceContext * deviceContext, int indexCount);

 
private:
	void InitShader(WCHAR* vsFilename, WCHAR* psFilename);
	void InitShader(WCHAR* vsFilename, WCHAR* hsFilename, WCHAR* dsFilename, WCHAR* psFilename);



private:
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* terrainBuffer;
	ID3D11SamplerState* m_sampleState;
	ID3D11SamplerState* sampleStateClamp;
	ID3D11Buffer* m_tessellationBuffer;
	ID3D11Buffer* planetBuffer;;
	ID3D11Buffer* lightBuffer;
	ID3D11Buffer* lightBuffer2;

};

