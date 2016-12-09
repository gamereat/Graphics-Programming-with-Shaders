#pragma once
#include "..\DXFramework\SphereMesh.h"
class TessilatedShereMesh :
	public SphereMesh
{
public:
	TessilatedShereMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext, WCHAR* textureFilename, int resolution);
	~TessilatedShereMesh();


	void SendData(ID3D11DeviceContext* deviceContext);

	void MenuOptions(bool* is_open);
protected:
	virtual void InitBuffers(ID3D11Device * device);

};


