// Colour shader.h
// Simple shader example.
#ifndef _DEPTHSHADER_H_
#define _DEPTHSHADER_H_

#include "../DXFramework/BaseShader.h"

using namespace std;
using namespace DirectX;


class DepthShader : public BaseShader
{

public: 

	struct DepthBufferType
	{
		/*
		if the shader will generate a shadow map for a given light
		*/
		int willGenerateShadowMap;
		XMFLOAT3 padding;
	};
	DepthShader(ID3D11Device* device, HWND hwnd);
	~DepthShader();

	void SetShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection);

private:
	void InitShader(WCHAR*, WCHAR*);

private:
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_depthBuffer;
};

#endif