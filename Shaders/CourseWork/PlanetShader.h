#pragma once
#include "..\DXFramework\BaseShader.h"
class PlanetShader :public BaseShader
{

	struct TessellationBufferType
	{
		XMINT4 outerTessellationValue;
		XMINT2 innerTesselastionValue;
		XMINT2 padding;
	};
public:

	PlanetShader(ID3D11Device* device, HWND hwnd);
	~PlanetShader();

	void SetShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX &world, const XMMATRIX &view, const XMMATRIX &projection, ID3D11ShaderResourceView* texture, XMINT2 innerTess, XMINT4 outerTess);
	void Render(ID3D11DeviceContext* deviceContext, int vertexCount);

private:
	void InitShader(WCHAR* vsFilename, WCHAR* psFilename);
	void InitShader(WCHAR* vsFilename, WCHAR* hsFilename, WCHAR* dsFilename, WCHAR* psFilename);

private:
	ID3D11Buffer* m_matrixBuffer;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_tessellationBuffer;
};

