#include "GeomertyShaderScene.h"
#include "VertexShader.h"


#include "../DXFramework/BaseApplication.h"

 
GeomertyShaderScene::GeomertyShaderScene(std::string sceneName)
	: Scene(sceneName)

{
	firstTimeExplotion = false;
}

GeomertyShaderScene::~GeomertyShaderScene()
{
}

void GeomertyShaderScene::Init(HWND hwnd, ID3D11Device * device, ID3D11DeviceContext * deviceContext)
{
	Scene::Init(hwnd, device, deviceContext);

	geomentryShader = new GeomentryShader(device, hwnd);

 
	floor = new PlaneMesh(device, deviceContext, L"../res/cloud.png");
	teaTop = new Model(device, deviceContext, L"../reasdas/bunny.png", L"../res/teapot.obj");

 
}

void GeomertyShaderScene::Update(Timer* timer)
{
	if (firstTimeExplotion)
	{
		geoSettings.time += timer->GetTime();
	}
}

void GeomertyShaderScene::Render(RenderTexture * renderTexture, D3D * device, Camera * camera, RenderTexture * depthMap[], Light * light[])
{
	GenerateDepthPass(device, camera, depthMap, light);

	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, baseViewMatrix, orthoMartix;

	//m_Direct3D->BeginScene(0.39f, 0.58f, 0.92f, 1.0f);
	renderTexture->SetRenderTarget(device->GetDeviceContext());

	renderTexture->ClearRenderTarget(device->GetDeviceContext(), 0.0f, 0.0f, 1.0f, 1.0f);

	//// Generate the view matrix based on the camera's position.
	camera->Update();

	//// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	device->GetWorldMatrix(worldMatrix);
	camera->GetViewMatrix(viewMatrix);
	device->GetProjectionMatrix(projectionMatrix);

	worldMatrix = XMMatrixScaling(0.1, 0.1, 0.1);


	ID3D11ShaderResourceView* depthMaps[NUM_LIGHTS];

	for (int i = 0; i < NUM_LIGHTS; i++)
	{

		depthMaps[i] = depthMap[i]->GetShaderResourceView();

	}


	// Send geometry data (from mesh)
		teaTop->SendData(device->GetDeviceContext());

	geomentryShader->SetShaderParameters(device->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, teaTop->GetTexture(), geoSettings);

	geomentryShader->Render(device->GetDeviceContext(), teaTop->GetIndexCount());


	worldMatrix = XMMatrixTranslation(-50, -10, -50);


	//// Send geometry data (from mesh)
	floor->SendData(device->GetDeviceContext());

	//geomentryShader->SetShaderParameters(device->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, floor->GetTexture(), heightMap->GetTexture(), tesselationInfo, depthMaps, light, terrainInfo);

	//geomentryShader->Render(device->GetDeviceContext(), floor->GetIndexCount());




	//// Present the rendered scene to the screen.
	//m_Direct3D->EndScene();
	device->SetBackBufferRenderTarget();
}

void GeomertyShaderScene::ResetLights(Light * lights[])
{
	//Setting light 1 
	lights[0]->SetDiffuseColour(1, 1, 1, 1);
	lights[0]->SetPosition(0, 60, -25);
	lights[0]->SetRange(100);
	lights[0]->SetAttenuationContantFactor(1);
}

void GeomertyShaderScene::MenuOptions()
{
	std::string menuName;
	menuName.append(sceneName);
	menuName.append(" Settings");
	if (ImGui::BeginMenu(menuName.c_str()))
	{
		if (ImGui::MenuItem("Scene Information "))
		{
			isInformationPopupOpen = isInformationPopupOpen ? false : true;
		}
		if (ImGui::MenuItem("Explosion effects "))
		{
			isExplotionMenuOpen = isExplotionMenuOpen ? false : true;
		}
 



		ImGui::EndMenu();
	}


	SceneInformationPopUp(&isInformationPopupOpen);
	explotionMenu(&isExplotionMenuOpen);


}

void GeomertyShaderScene::GenerateDepthPass(D3D * device, Camera * camera, RenderTexture * depthMap[], Light * lights[])
{
	// Loop though for each light to generate depth map for each
	for (int i = 0; i < NUM_LIGHTS; i++)
	{
		XMMATRIX worldMatrix;

		XMMATRIX lightViewMartix, lightProjectionMatrix;

		// Set the render target to be the render to texture.
		depthMap[i]->SetRenderTarget(device->GetDeviceContext());

		// Clear the render to texture.
		depthMap[i]->ClearRenderTarget(device->GetDeviceContext(), 0.0f, 0.0f, 1.0f, 1.0f);

		// Generate the view matrix based on the camera's position.
		camera->Update();

		// Get the world, view, and projection matrices from the camera and d3d objects.
		device->GetWorldMatrix(worldMatrix);

		lights[i]->GenerateViewMatrix();
		lightViewMartix = lights[i]->GetViewMatrix();

		lights[i]->GenerateProjectionMatrix(SCREEN_NEAR, SCREEN_DEPTH);
		lightProjectionMatrix = lights[i]->GetProjectionMatrix();
		worldMatrix = XMMatrixScaling(0.1, 0.1, 0.1);


		////// Send geometry data (from mesh)
			teaTop->SendData(device->GetDeviceContext());

		depthShader->SetShaderParameters(device->GetDeviceContext(), worldMatrix, lightViewMartix, lightProjectionMatrix);

			depthShader->Render(device->GetDeviceContext(), teaTop->GetIndexCount());

		worldMatrix = XMMatrixTranslation(-50, -10, -50);

		////// Send geometry data (from mesh)
	//	floor->SendData(device->GetDeviceContext());

	//	depthShader->SetShaderParameters(device->GetDeviceContext(), worldMatrix, lightViewMartix, lightProjectionMatrix);
//
	//	depthShader->Render(device->GetDeviceContext(), floor->GetIndexCount());


		// Reset the render target back to the original back buffer and not the render to texture anymore.
		device->SetBackBufferRenderTarget();
		device->ResetViewport();
	}
}

void GeomertyShaderScene::explotionMenu(bool * is_open)
{
	if (*is_open == true)
	{
		if (!ImGui::Begin("Explosion ", is_open, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::End();
			return;
		}

		//ImGui::SliderInt4("InnerTess", &tesselationInfo.innerTesselastionValue.x, 1.0f, 64);
		//	ImGui::SliderInt2("OiterTess", &tesselationInfo.outerTessellationValue.x, 1.0f, 64);

		ImGui::DragFloat("Explosion Velocity", &geoSettings.explosiveAmmount);
		ImGui::DragFloat("Maximum explosion time", &geoSettings.maxTime);
		ImGui::DragFloat("Gravity scale", &geoSettings.gravity);
		ImGui::DragFloat("Explosive acceleration", &geoSettings.explosiveAcceleration);
 
		if (ImGui::Button("Explode Teapot"))
		{
			firstTimeExplotion = true;
			geoSettings.time = 0;
		}
		ImGui::End();
	}
}

void GeomertyShaderScene::SceneInformationPopUp(bool * is_open)
{
}
