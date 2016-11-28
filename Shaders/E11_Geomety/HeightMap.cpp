#include "HeightMap.h"



HeightMap::HeightMap()
{
}


HeightMap::~HeightMap()
{
}

void HeightMap::LoadHeightMap(ID3D11Device* device, ID3D11DeviceContext* deviceContext, WCHAR* filename)
{
	LoadTexture(device, deviceContext, filename);

  }

void HeightMap::GenerateHeighMap()
{
}
