// tessellation shader.cpp
#include "WobblyShader.h"

WobblyShader::WobblyShader(ID3D11Device* device, HWND hwnd) : BaseShader(device, hwnd)
{
	InitShader(L"shaders/wobblyBox_vs.hlsl", L"shaders/wobblyBox_hs.hlsl", L"shaders/wobblyBox_ds.hlsl", L"shaders/wobblyBox_ps.hlsl");
	//InitShader(L"shaders/planet_vs.hlsl", L"shaders/planet_ps.hlsl");
}


WobblyShader::~WobblyShader()
{
	// Release the sampler state.
	if (m_sampleState)
	{
		m_sampleState->Release();
		m_sampleState = 0;
	}

	// Release the matrix constant buffer.
	if (m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
	}


	// Release the light constant buffer.
	if (m_tessellationBuffer)
	{
		m_tessellationBuffer->Release();
		m_tessellationBuffer = 0;
	}

	// Release the layout.
	if (m_layout)
	{
		m_layout->Release();
		m_layout = 0;
	}
	if (lightBuffer)
	{
		lightBuffer->Release();
		lightBuffer = 0;
	}
	// Release the light constant buffer.
	if (lightBuffer2)
	{
		lightBuffer2->Release();
		lightBuffer2 = 0;
	}
	//Release base shader components
	BaseShader::~BaseShader();
}

void WobblyShader::InitShader(WCHAR* vsFilename, WCHAR* psFilename)
{
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_SAMPLER_DESC samplerDesc;
	D3D11_BUFFER_DESC tesselationDesc;
	D3D11_BUFFER_DESC planetDesc;
	 
 
	D3D11_BUFFER_DESC lightBufferDesc;
	D3D11_BUFFER_DESC lightBufferDesc2;

	// Load (+ compile) shader files
	loadVertexShader(vsFilename);

	loadPixelShader(psFilename);

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader.
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;




	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	m_device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);

	// Create a texture sampler state description.
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Create the texture sampler state.
	m_device->CreateSamplerState(&samplerDesc, &m_sampleState);

	tesselationDesc.Usage = D3D11_USAGE_DYNAMIC;
	tesselationDesc.ByteWidth = sizeof(TessellationBufferType);
	tesselationDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	tesselationDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	tesselationDesc.MiscFlags = 0;
	tesselationDesc.StructureByteStride = 0;

	m_device->CreateBuffer(&tesselationDesc, NULL, &m_tessellationBuffer);


	planetDesc.Usage = D3D11_USAGE_DYNAMIC;
	planetDesc.ByteWidth = sizeof(WavetBufferType);
	planetDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	planetDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	planetDesc.MiscFlags = 0;
	planetDesc.StructureByteStride = 0;

	m_device->CreateBuffer(&planetDesc, NULL, &planetBuffer);


	// Create the texture sampler state. 

	 


	// Required a CLAMPED sampler for sampling the depth map
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	// Create the texture sampler state.
	m_device->CreateSamplerState(&samplerDesc, &sampleStateClamp);


	// Setup light buffer
	// Setup the description of the light dynamic constant buffer that is in the pixel shader.
	// Note that ByteWidth always needs to be a multiple of 16 if using D3D11_BIND_CONSTANT_BUFFER or CreateBuffer will fail.
	lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	lightBufferDesc.ByteWidth = sizeof(LightBufferType);
	lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightBufferDesc.MiscFlags = 0;
	lightBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	m_device->CreateBuffer(&lightBufferDesc, NULL, &lightBuffer);

	// Setup the description of the camera dynamic constant buffer that is in the vertex shader.
	lightBufferDesc2.Usage = D3D11_USAGE_DYNAMIC;
	lightBufferDesc2.ByteWidth = sizeof(LightBufferType2);
	lightBufferDesc2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferDesc2.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightBufferDesc2.MiscFlags = 0;
	lightBufferDesc2.StructureByteStride = 0;

	// Create the camera constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	m_device->CreateBuffer(&lightBufferDesc2, NULL, &lightBuffer2);

}

void WobblyShader::InitShader(WCHAR* vsFilename, WCHAR* hsFilename, WCHAR* dsFilename, WCHAR* psFilename)
{

	// InitShader must be overwritten and it will load both vertex and pixel shaders + setup buffers
	InitShader(vsFilename, psFilename);

	// Load other required shaders.
	loadHullShader(hsFilename);
	loadDomainShader(dsFilename);


}


void WobblyShader::SetShaderParameters(ID3D11DeviceContext * deviceContext, const XMMATRIX & worldMatrix, const XMMATRIX & viewMatrix, const XMMATRIX & projectionMatrix, ID3D11ShaderResourceView * texture, ID3D11ShaderResourceView * highMap, TessellationBufferType tesselationInfo, WavetBufferType plantinfo, ID3D11ShaderResourceView * depthMap[], Light * light[])
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	TessellationBufferType* tessPtr;
	WavetBufferType* plantPtr;
	unsigned int bufferNumber;
	XMMATRIX tworld, tview, tproj;

	LightBufferType2* lightPtr2;
	LightBufferType* lightPtr;
	XMMATRIX tLightViewMatrix[NUM_LIGHTS], tLightProjectionMatrix[NUM_LIGHTS];

	// Transpose the matrices to prepare them for the shader.
	tworld = XMMatrixTranspose(worldMatrix);
	tview = XMMatrixTranspose(viewMatrix);
	tproj = XMMatrixTranspose(projectionMatrix);
	for (int i = 0; i < NUM_LIGHTS; i++)
	{
		tLightViewMatrix[i] = XMMatrixTranspose(light[i]->GetViewMatrix());
		tLightProjectionMatrix[i] = XMMatrixTranspose(light[i]->GetProjectionMatrix());
	}

	// Lock the constant buffer so it can be written to.
	result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// Get a pointer to the data in the constant buffer.
	dataPtr = (MatrixBufferType*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	dataPtr->world = tworld;// worldMatrix;
	dataPtr->view = tview;
	dataPtr->projection = tproj;
	for (int i = 0; i < NUM_LIGHTS; i++)
	{
		dataPtr->lightView[i] = tLightViewMatrix[i];

		dataPtr->lightProjection[i] = tLightProjectionMatrix[i];

	}
	// Unlock the constant buffer.
	deviceContext->Unmap(m_matrixBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// Now set the constant buffer in the vertex shader with the updated values.
	deviceContext->DSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer); 
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);




	deviceContext->Map(m_tessellationBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	tessPtr = (TessellationBufferType*)mappedResource.pData;

	tessPtr->maxDistance = tesselationInfo.maxDistance;
	tessPtr->maxTesselationAmmount = tesselationInfo.maxTesselationAmmount;
	tessPtr->minDistance = tesselationInfo.minDistance;
	tessPtr->minTesselationAmmount = tesselationInfo.minTesselationAmmount;
	tessPtr->camPos = tesselationInfo.camPos;

	//	tessPtr->innerTesselastionValue = tesselationInfo.innerTesselastionValue;
	//tessPtr->outerTessellationValue = tesselationInfo.outerTessellationValue;
	//tessPtr->padding = XMINT2(0, 0);
	// Unlock the constant buffer.
	deviceContext->Unmap(m_tessellationBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// Now set the constant buffer in the vertex shader with the updated values.
	deviceContext->HSSetConstantBuffers(0, 1, &m_tessellationBuffer);
	deviceContext->HSSetConstantBuffers(1, 1, &m_matrixBuffer);




	deviceContext->Map(planetBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	plantPtr = (WavetBufferType*)mappedResource.pData;

	plantPtr->speed = plantinfo.speed;
	plantPtr->amplutude = plantinfo.amplutude;
	plantPtr->freqancy = plantinfo.freqancy;
	plantPtr->steepnesss = plantinfo.steepnesss;
	plantPtr->time = plantinfo.time;
	plantPtr->padding = 0;
	plantPtr->padding = float(0);

	//	 Unlock the constant buffer.
	deviceContext->Unmap(planetBuffer, 0);

	//	 Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	//	 Now set the constant buffer in the vertex shader with the updated values.
	deviceContext->VSSetConstantBuffers(1, 1, &planetBuffer);
	// Set shader texture resource in the pixel shader.
	deviceContext->PSSetShaderResources(0, 1, &texture);


	//deviceContext->VSSetShaderResources(0, 1, &highMap);


	// Send light data to vertex shader
	deviceContext->Map(lightBuffer2, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	lightPtr2 = (LightBufferType2*)mappedResource.pData;

	for (int i = 0; i < NUM_LIGHTS; i++)
	{
		lightPtr2->position[i] = XMFLOAT4(light[i]->GetPosition().x, light[i]->GetPosition().y, light[i]->GetPosition().z, 0);
	}
	deviceContext->Unmap(lightBuffer2, 0);
	bufferNumber = 2;
	deviceContext->VSSetConstantBuffers(3, 1, &lightBuffer2);


	for (int i = 0; i < NUM_LIGHTS; i++)
	{
		// send all the depth maps for each light 

		// Set shader depth map texture resource.

		deviceContext->PSSetShaderResources(1, 1, (&depthMap[0]));
		deviceContext->PSSetShaderResources(2, 1, (&depthMap[1]));
		deviceContext->PSSetShaderResources(3, 1, (&depthMap[2]));
		deviceContext->PSSetShaderResources(4, 1, (&depthMap[3]));
	}

	//Additional
	// Send light data to pixel shader
	deviceContext->Map(lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	lightPtr = (LightBufferType*)mappedResource.pData;

	for (int i = 0; i < NUM_LIGHTS; i++)
	{
		lightPtr->ambientColour[i] = light[i]->GetAmbientColour();
		lightPtr->diffuseColour[i] = light[i]->GetDiffuseColour();
		lightPtr->lightDirection[i] = XMFLOAT4(light[i]->GetDirection().x, light[i]->GetDirection().y, light[i]->GetDirection().z, 0);
		lightPtr->specularPower[i].x = light[i]->GetSpecularPower();
		lightPtr->specularColour[i] = light[i]->GetSpecularColour();
		lightPtr->position[i] = XMFLOAT4(light[i]->GetPosition().x, light[i]->GetPosition().y, light[i]->GetPosition().z, 0);
		lightPtr->willGenerateShadows[i] = (int)light[i]->GetWillGenerateShadows();

		switch (light[i]->GetLightType())
		{
		case Light::lightType::directional:
			lightPtr->lightType[i].x = true;
			lightPtr->lightType[i].y = false;
			lightPtr->lightType[i].z = false;
			break;


		case Light::lightType::point:
			lightPtr->lightType[i].x = false;
			lightPtr->lightType[i].y = true;
			lightPtr->lightType[i].z = false;
			break;


		case Light::lightType::spot:
			lightPtr->lightType[i].x = false;
			lightPtr->lightType[i].y = false;
			lightPtr->lightType[i].z = true;
			break;
		default:
			break;
		}


		lightPtr->attenuationValues[i] = XMFLOAT4(light[i]->GetAttenuationContantFactor(),
			light[i]->GetAttenuationLinearFactor(),
			light[i]->GetAttenuationQuadraticFactor(),
			light[i]->GetRange());
		lightPtr->isSpecular[i] = light[i]->GetMakesSpecular();

	}
	deviceContext->Unmap(lightBuffer, 0);
	bufferNumber = 0;
	deviceContext->PSSetConstantBuffers(bufferNumber, 1, &lightBuffer);

}

void WobblyShader::Render(ID3D11DeviceContext* deviceContext, int indexCount)
{
	// Set the sampler state in the pixel shader.
	deviceContext->PSSetSamplers(0, 1, &m_sampleState);
	deviceContext->PSSetSamplers(1, 1, &sampleStateClamp);

	// Base render function.

	BaseShader::Render(deviceContext, indexCount);
}

 