#include "HeightMap.h"



HeightMap::HeightMap()
{
}


HeightMap::~HeightMap()
{
}

HeightMap::HeightMap(ID3D11Device * device, ID3D11DeviceContext * deviceContext, WCHAR * fileDirectory)
{
	LoadHeightMapTexture(device, deviceContext, fileDirectory);
}

void HeightMap::LoadHeightMapTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, WCHAR * fileDirectory)
{
	heightMapTexture = new Texture(device, deviceContext, fileDirectory);
}

void HeightMap::UnloadHeightMap()
{
	if (heightMapTexture)
	{
		delete heightMapTexture;
		heightMapTexture = nullptr;
	}
}

Texture * HeightMap::getHeightMapTexture()
{
	return heightMapTexture;
}

void HeightMap::setHeightMapTexture(Texture * heightMapTexture)
{
	this->heightMapTexture = heightMapTexture;
}

float HeightMap::getHeightScaling()
{
	return heightScaling;
}

void HeightMap::setHeightMapScaling(float heightScaling)
{
	this->heightScaling = heightScaling;
}
