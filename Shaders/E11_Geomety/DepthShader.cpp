// depth shader.cpp
#include "depthshader.h"


DepthShader::DepthShader(ID3D11Device* device, HWND hwnd) : BaseShader(device, hwnd)
{
	InitShader(L"shaders/depth_vs.hlsl", L"shaders/depth_ps.hlsl");
}


DepthShader::~DepthShader()
{
	// Release the matrix constant buffer.
	if (m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
	}

	// Release the layout.
	if (m_layout)
	{
		m_layout->Release();
		m_layout = 0;
	}

	//Release base shader components
	BaseShader::~BaseShader();
}


void DepthShader::InitShader(WCHAR* vsFilename, WCHAR* psFilename)
{
	D3D11_BUFFER_DESC matrixBufferDesc;

	// Load (+ compile) shader files
	loadVertexShader(vsFilename);
	loadPixelShader(psFilename);

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixDepthBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	m_device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);

}


void DepthShader::SetShaderParameters(ID3D11DeviceContext * deviceContext, const XMMATRIX & world, const XMMATRIX  (&view)[4], const XMMATRIX  (&projection)[4])
{

	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixDepthBufferType* dataPtr;
	unsigned int bufferNumber;
	XMMATRIX tworld, tview[4], tproj[4];


	// Transpose the matrices to prepare them for the shader.
	tworld = XMMatrixTranspose(world);

	for (int i = 0; i < 4; i++)
	{
		tview[i] = XMMatrixTranspose(view[i]);
		tproj[i] = XMMatrixTranspose(projection[i]);
	}
	// Lock the constant buffer so it can be written to.
	result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// Get a pointer to the data in the constant buffer.
	dataPtr = (MatrixDepthBufferType*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	for (int i = 0; i < 4; i++)
	{	
		dataPtr->world = tworld;// worldMatrix;

		dataPtr->view[i] = tview[i];
		dataPtr->projection[i] = tproj[i];
	}
	// Unlock the constant buffer.
	deviceContext->Unmap(m_matrixBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// Now set the constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);
}



