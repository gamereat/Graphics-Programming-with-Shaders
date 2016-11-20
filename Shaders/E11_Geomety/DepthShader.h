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
	struct MatrixDepthBufferType
	{
		XMMATRIX world;
		XMMATRIX view[4];
		XMMATRIX projection[4];
	};

	DepthShader(ID3D11Device* device, HWND hwnd);
	~DepthShader();

	void SetShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX (&view)[4], const XMMATRIX (&projection)[4]);

private:
	void InitShader(WCHAR*, WCHAR*);

private:
	ID3D11Buffer* m_matrixBuffer;
};

#endif