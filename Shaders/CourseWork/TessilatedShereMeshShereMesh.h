#pragma once
#include "..\DXFramework\SphereMesh.h"
class TessilatedShereMesh :
	public BaseMesh
{
public:
	TessilatedShereMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, WCHAR* textureFilename, int resolution);
	~TessilatedShereMesh();


	void SendData(ID3D11DeviceContext* deviceContext);

	void MenuOptions(bool* is_open);
protected:
	void InitBuffers(ID3D11Device* device);

	int resolution;

};


 