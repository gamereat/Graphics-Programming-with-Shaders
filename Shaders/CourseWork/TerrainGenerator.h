#pragma once
#include "..\DXFramework\BaseShader.h"
#include "HeightMap.h"
using namespace std;
using namespace DirectX;

class TerrainGenerator :	public BaseShader
{
public:
 
	struct TerrainBufferType {
		XMFLOAT3 CammeraPos;

	};

	TerrainGenerator(ID3D11Device* device, HWND hwnd);
	~TerrainGenerator();

	void SetShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &worldMatrix, const XMMATRIX &viewMatrix, const XMMATRIX &projectionMatrix, ID3D11ShaderResourceView* texture);
	void Render(ID3D11DeviceContext * deviceContext, int indexCount);

 
private:
	void InitShader(WCHAR* vsFilename, WCHAR* psFilename);
	void InitShader(WCHAR* vsFilename, WCHAR* psFilename, WCHAR* gsFilename, WCHAR* hsFilename, WCHAR* dsFilename);

	void InitShader(WCHAR* vsFilename, WCHAR* psFilename, HeightMap* heightMap);
	void InitShader(WCHAR * vsFilename, WCHAR * psFilename, WCHAR * gsFilename , WCHAR * hsFilename, WCHAR * dsFilename, HeightMap * heightMap);
 private:
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* terrainBuffer;

	HeightMap* heightMap;

};

