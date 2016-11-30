#pragma once


#include "../DXFramework/BaseShader.h"

using namespace std;
using namespace DirectX;

class GeomentryShader : public BaseShader
{
 
public:

	struct GeomentryBufferType
	{
		// set if it is a tri or a quad.
		// 1 is tri 
		// 0 is quad
		int isTri;

		XMINT3 padding;
		XMFLOAT4 vertexScale;

	};

	GeomentryShader(ID3D11Device* device, HWND hwnd);
	~GeomentryShader();

	void SetShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &worldMatrix, const XMMATRIX &viewMatrix, const XMMATRIX &projectionMatrix, ID3D11ShaderResourceView* texture, bool isTri, XMFLOAT4 vertexScale);
	void Render(ID3D11DeviceContext * deviceContext, int indexCount);


private:
	void InitShader(WCHAR* vsFilename, WCHAR* psFilename);
	void InitShader(WCHAR* vsFilename, WCHAR* psFilename, WCHAR* gsFilename);

private:
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_GeomentryBuffer;

	ID3D11SamplerState* m_sampleState;

};


