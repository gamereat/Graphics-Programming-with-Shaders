#include "Planet.h"

#include "../DXFramework/BaseApplication.h"

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
	PlanetShpere = new CubeMesh(device, deviceContext, L"../res/bunny.png", 10);
	planetShader = new PlanetShader(device, hwnd);

	heightMapTexture = new Texture(device, deviceContext, L"../res/cloud.png");

	//tesselationInfo.outerTessellationValue = XMINT4(1, 1, 1, 1);
	//tesselationInfo.innerTesselastionValue = XMINT2(1, 1);
	depthShader = new DepthShader(device, hwnd);

	plantinfo.amplutude = 0.2;
	plantinfo.speed = 0.2;
	plantinfo.steepnesss = 0.2;
	plantinfo.freqancy = XMFLOAT3(1.75, 1.75, 1.75);

	tesselationInfo.maxDistance = 100;
	tesselationInfo.maxTesselationAmmount = 6;
	tesselationInfo.minDistance = 10;
	tesselationInfo.minTesselationAmmount = 1;

 		
	m_depth_Textur = new RenderTexture(device, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_NEAR, SCREEN_DEPTH);

}

void Planet::Update(float deltaTime)
{

	if (t < 100)
	{
		t++;
	}
	else
	{
		t = 0;
	}

	plantinfo.time = deltaTime;
}

void Planet::Render(RenderTexture * renderTexture, D3D * device, Camera * camera, RenderTexture * depthMap[], Light * light[])
{
 
 

	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, baseViewMatrixs;

	// Set the render target to be the render to texture.
	renderTexture->SetRenderTarget(device->GetDeviceContext());

	// Clear the render to texture.
	renderTexture->ClearRenderTarget(device->GetDeviceContext(), 0.0f, 0.0f, 1.0f, 1.0f);


	camera->Update();

	device->GetWorldMatrix(worldMatrix);
	camera->GetViewMatrix(viewMatrix);
	device->GetProjectionMatrix(projectionMatrix);
	ID3D11ShaderResourceView* depthMaps[NUM_LIGHTS];

	for (int i = 0; i < NUM_LIGHTS; i++)
	{

		depthMaps[i] = depthMap[i]->GetShaderResourceView();

	}

	tesselationInfo.camPos = XMFLOAT4(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z, 0);
	PlanetShpere->SendData(device->GetDeviceContext());

	planetShader->SetShaderParameters(device->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, PlanetShpere->GetTexture(), heightMapTexture->GetTexture(), tesselationInfo, plantinfo, depthMaps,light);

	planetShader->Render(device->GetDeviceContext(), PlanetShpere->GetIndexCount());


	// Present the rendered scene to the screen.
	device->SetBackBufferRenderTarget();




}

void Planet::MenuOptions()
{
	if (ImGui::BeginMenu("Planet Settings"))
	{
		isTessMenuOpen = ImGui::MenuItem("Water Settings");
		isWaterMenuOpen = ImGui::MenuItem("Tess Settings");
		ImGui::EndMenu();
	}






	waterOptions(&isWaterMenuOpen);
	tesselationOptions(&isTessMenuOpen);

}

void Planet::GenerateDepthPass(D3D* device, Camera* camera, RenderTexture * depthMap[], Light * light[])
{
	// Loop though for each light to generate depth map for each
//	for (int i = 0; i < NUM_LIGHTS; i++)
	{
		XMMATRIX worldMatrix;

		XMMATRIX lightViewMartix, lightProjectionMatrix;

		// Set the render target to be the render to texture.
		m_depth_Textur->SetRenderTarget(device->GetDeviceContext());

		// Clear the render to texture.
		m_depth_Textur->ClearRenderTarget(device->GetDeviceContext(), 0.0f, 0.0f, 1.0f, 1.0f);

		// Generate the view matrix based on the camera's position.
		camera->Update();

		// Get the world, view, and projection matrices from the camera and d3d objects.
		device->GetWorldMatrix(worldMatrix);

		light[0]->GenerateViewMatrix();
		lightViewMartix = light[0]->GetViewMatrix();

		light[0]->GenerateProjectionMatrix(SCREEN_NEAR, SCREEN_DEPTH);
		lightProjectionMatrix = light[0]->GetProjectionMatrix();
		worldMatrix = XMMatrixScaling(0.1, 0.1, 0.1);

		////// Send geometry data (from mesh)

		PlanetShpere->SendData(device->GetDeviceContext());

		depthShader->SetShaderParameters(device->GetDeviceContext(), worldMatrix, lightViewMartix, lightProjectionMatrix);

		depthShader->Render(device->GetDeviceContext(), PlanetShpere->GetIndexCount());

		 
		// Reset the render target back to the original back buffer and not the render to texture anymore.
		device->SetBackBufferRenderTarget();
		device->ResetViewport();
	}
}

void Planet::waterOptions(bool * is_open)
{
	if (!ImGui::Begin("Water manipulation", is_open, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
		return;
	}
	ImGui::DragFloat("Speed", &plantinfo.speed);


	ImGui::DragFloat("Amp", &plantinfo.amplutude);
	ImGui::DragFloat3("freq", &plantinfo.freqancy.x);
	ImGui::DragFloat("time", &plantinfo.time);
	ImGui::DragFloat("steepnees", &plantinfo.steepnesss);
	ImGui::End();

}

void Planet::tesselationOptions(bool * is_open)
{
	if (!ImGui::Begin("Tesselation ", is_open, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
		return;
	}

	//ImGui::SliderInt4("InnerTess", &tesselationInfo.innerTesselastionValue.x, 1.0f, 64);
	//	ImGui::SliderInt2("OiterTess", &tesselationInfo.outerTessellationValue.x, 1.0f, 64);

	ImGui::DragFloat("Max distance", &tesselationInfo.maxDistance);
	ImGui::DragFloat("Min Distance", &tesselationInfo.minDistance);
	ImGui::DragFloat("Max Tesseleation Ammount", &tesselationInfo.maxTesselationAmmount);
	ImGui::DragFloat("Min Tesselation Ammount", &tesselationInfo.minTesselationAmmount);


	ImGui::End();
}


