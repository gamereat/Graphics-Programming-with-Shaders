#include "Planet.h"



Planet::Planet()
{
}


Planet::~Planet()
{
	// clean up my memories
	if (PlanetShpere)
	{
		delete PlanetShpere;
		PlanetShpere = nullptr;
	}

	if (planetShader)
	{
		delete planetShader;
		planetShader = nullptr;
	}
}
 

void Planet::Init(HWND hwnd, ID3D11Device * device, ID3D11DeviceContext * deviceContext)
{
	PlanetShpere = new TessilatedShereMesh(device, deviceContext, L"../res/bunny.png", 19);
	planetShader = new PlanetShader(device, hwnd);

	planetInnerTessAmmount = XMINT4(1,1,1,1);
	planetOuterTessAmmount = XMINT2(1,1);
}

void Planet::Update(float deltaTime)
{

}

void Planet::Render(RenderTexture * renderTexture, D3D * device, Camera * camera)
{
	bool f = true;
	MenuOptions(&f);
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, baseViewMatrixs;

	// Set the render target to be the render to texture.
	renderTexture->SetRenderTarget(device->GetDeviceContext());

	// Clear the render to texture.
	renderTexture->ClearRenderTarget(device->GetDeviceContext(), 0.0f, 0.0f, 1.0f, 1.0f);
	 

	camera->Update();

	device->GetWorldMatrix(worldMatrix);
	camera->GetViewMatrix(viewMatrix);
	device->GetProjectionMatrix(projectionMatrix);

	PlanetShpere->SendData(device->GetDeviceContext());

	planetShader->SetShaderParameters(device->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, PlanetShpere->GetTexture(), planetOuterTessAmmount, planetInnerTessAmmount);

	planetShader->Render(device->GetDeviceContext(), PlanetShpere->GetIndexCount());


	// Present the rendered scene to the screen.
	device->SetBackBufferRenderTarget();
}

void Planet::MenuOptions(bool * is_open)
{

	if (*is_open == true)
	{

		// Create the window
		if (!ImGui::Begin("Vertex manipulation", is_open, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::End();
			return;
		}
	

		ImGui::SliderInt4("InnerTess", &planetInnerTessAmmount.x, 1.0f, 64);
		ImGui::SliderInt2("OiterTess", &planetOuterTessAmmount.x, 1.0f, 64);

		ImGui::End();
	}

}


