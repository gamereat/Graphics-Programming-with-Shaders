#pragma once
#include "../DXFramework/BaseMesh.h"
#include <vector>
class HeightMap : public BaseMesh
{
public:
	HeightMap();
	~HeightMap();
	

	void LoadHeightMap(ID3D11Device* device, ID3D11DeviceContext* deviceContext, WCHAR* filename);

	void GenerateHeighMap();

private:

	/*
	Values taken from heightmap
	*/
	std::vector<float> heightMapValues;


};

