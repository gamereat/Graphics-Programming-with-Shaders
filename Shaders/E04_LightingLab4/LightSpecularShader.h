// Light shader.h
// Basic single light shader setup
#ifndef _LIGHTSHADER_H_
#define _LIGHTSHADER_H_

#include "../DXFramework/BaseShader.h"
#include "../DXFramework/Light.h"

using namespace std;
using namespace DirectX;


class LightSpecularShader : public BaseShader
{
private:
	struct LightBufferType
	{
		XMFLOAT4 diffuse;
		XMFLOAT3 direction;
		float specularPower;
		XMFLOAT4 ambient; 
		XMFLOAT4 specularColour;
		XMFLOAT3 position;
		float padding;

		float constantAttenuationFactor;
		float linearAttenuationFactor;
		float quadraticAttenuationFactor;
		float range;

	};
	struct CammeraBufferType  
	{
		XMFLOAT3 cammeraPostion;
		float padding;
	};
public:

	LightSpecularShader(ID3D11Device* device, HWND hwnd);
	~LightSpecularShader();

	void SetShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection, ID3D11ShaderResourceView* texture, Light* light, XMFLOAT3 cammeraPostion);
	void Render(ID3D11DeviceContext* deviceContext, int vertexCount);

private:
	void InitShader(WCHAR*, WCHAR*);

private:
	ID3D11Buffer* m_matrixBuffer;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_lightBuffer;
	ID3D11Buffer* m_camBuffer;
};

#endif