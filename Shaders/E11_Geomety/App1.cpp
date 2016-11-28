// Lab1.cpp
// Lab 1 example, simple textured quad
#include "App1.h"
#include <string>

 
App1::App1()
{
	m_Quad_Mesh = nullptr;

	m_Vertex_Manipulation_Shader = nullptr;

 	m_Texture_Shader = nullptr;

	m_Render_Texture = nullptr;

 	
	m_Tessellation_Shader = nullptr;



	m_Ortho_Mesh_normalScaled = nullptr; 

	m_DepthShader = nullptr;

	m_ShadowShader = nullptr;

 
}

void App1::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in)
{
	// Call super init function (required!)
	BaseApplication::init(hinstance, hwnd, screenWidth, screenHeight, in);

	interTess = XMINT4(12, 12, 12,12);
	outerTess = XMINT2(2,2);

	// Create Mesh object
	m_Quad_Mesh = new PlaneMesh(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), L"../res/bunny.png");
	m_Sphere_Mesh = new SphereMesh(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), L"../res/bunny.png");
	m_Vertex_Manipulation_Shader = new VertexShader(m_Direct3D->GetDevice(), hwnd);

	m_Texture_Shader =  new TextureShader(m_Direct3D->GetDevice(), hwnd);

 


	for (int i = 0; i < NUM_LIGHTS; i++)
	{
		m_Lights[i] = new Light();

		m_Lights[i]->SetDirection(0, 0,0);
		m_Lights[i]->SetDiffuseColour(0, 0, 0,0);
		m_Lights[i]->SetLookAt(0, 0, 0);
		m_Lights[i]->SetPosition(0, 0, -4);
		m_Lights[i]->SetWillGenerateShadows(false);
		m_Lights[i]->SetRange(255);

		m_depth_Texture[i] = new RenderTexture(m_Direct3D->GetDevice(), SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_NEAR, SCREEN_DEPTH);
	}

	m_Lights[0]->SetWillGenerateShadows(true);



	m_Ortho_Mesh_normalScaled = new OrthoMesh(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

	m_Render_Texture = new  RenderTexture(m_Direct3D->GetDevice(), SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_NEAR, SCREEN_DEPTH);

	m_TerrainTexture = new  RenderTexture(m_Direct3D->GetDevice(), SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_NEAR, SCREEN_DEPTH);

	m_Shadow_Texture = new  RenderTexture(m_Direct3D->GetDevice(), SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_NEAR, SCREEN_DEPTH);
	m_Render_VextexMinulation = new RenderTexture(m_Direct3D->GetDevice(), SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_NEAR, SCREEN_DEPTH);

	postPro.Init(m_Direct3D, hwnd, m_Timer);
 

	m_Tessellation_Shader = new TessellationShader(m_Direct3D->GetDevice(), hwnd);

	m_Point_Mesh = new PointMesh(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), L"../res/bunny.png");

	m_Tessellation_mesh = new TessellationMesh(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), L"../res/bunny.png");

	quad  = new QuadMesh (m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), L"../res/bunny.png");

	m_DepthShader = new DepthShader(m_Direct3D->GetDevice(), hwnd);

	m_ShadowShader = new ShadowShader(m_Direct3D->GetDevice(), hwnd);

	m_Geomentry_Shader = new GeomentryShader(m_Direct3D->GetDevice(), hwnd);
	teaTop = new Model(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), L"../res/bunny.png", L"../res/teapot.obj");

}

App1::~App1()
{
	// Run base application deconstructor
	BaseApplication::~BaseApplication();


	if (m_TerrainTexture)
	{
		delete m_TerrainTexture;
		m_TerrainTexture = nullptr;
	}
	if (m_Geomentry_Shader)
	{
		delete m_Geomentry_Shader;
		m_Geomentry_Shader = nullptr;
	}

	if (m_DepthShader)
	{
		delete m_DepthShader;
		m_DepthShader = nullptr;
	}
	if (m_ShadowShader)
	{
		delete m_ShadowShader;
		m_ShadowShader = nullptr;
	}
		

	if (m_UpScaleTexture)
	{
		delete m_UpScaleTexture;
		m_UpScaleTexture = nullptr;
	}
	 
	if (m_Tessellation_Shader)
	{
		delete m_Tessellation_Shader;
		m_Tessellation_Shader = nullptr;
	}

 
	if (m_Render_Texture)
	{
		delete m_Render_Texture;
		m_Render_Texture = nullptr;
	}
	if (m_Render_VextexMinulation)
	{
		delete m_Render_VextexMinulation;
		m_Render_VextexMinulation = nullptr;
	}

	if (m_Texture_Shader)
	{
		delete m_Texture_Shader;
		m_Texture_Shader = nullptr;
	}
 
	// Release the Direct3D object.
	if (m_Quad_Mesh)
	{
		delete m_Quad_Mesh;
		m_Quad_Mesh = 0;
	}

	if (m_Sphere_Mesh)
	{
		delete m_Sphere_Mesh;
		m_Sphere_Mesh = 0;
	}

	if (m_Vertex_Manipulation_Shader)
	{
		delete m_Vertex_Manipulation_Shader;
		m_Vertex_Manipulation_Shader = 0;
	}
	for (int i = 0; i < 4; i++)
	{
		if (m_Lights[i])
		{
			delete m_Lights[i];
			m_Lights[i] = 0;
		}
	}
}

bool App1::Frame()
{
	bool result;

	result = BaseApplication::Frame();
	if (!result)
	{
		return false;
	}
  	// Render the graphics.
	result = Render();
	if (!result)
	{
		return false;
	}
	return true;
}

bool App1::Render()
{

	//RenderTessellation();

	// Render world with minulation
	//RenderVertexMinulation();
//
//  RenderDepth();

//  RenderShadow();

//
	RenderTerrain();
	//RenderGeometry();


	// disable wireframe mode for the post processing effects
	if (m_Direct3D->getWireFrameMode())
	{
 		m_Direct3D->TurnOffWireframe();
	}

	// Apply any post processing effecst 
	m_UpScaleTexture = postPro.ApplyPostProccessing(m_Ortho_Mesh_normalScaled, m_TerrainTexture, m_Direct3D, m_Camera);

	//// Render the second pass

	//// 
	RenderToScreen();


	// disable wireframe mode for the post processing effects
	if (m_Direct3D->getWireFrameMode())
	{
		m_Direct3D->TurnOnWireframe();
	}

	return true;
}

void App1::RenderTessellation()
{

	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, baseViewMatrixs;

	// Set the render target to be the render to texture.
	m_Render_Texture->SetRenderTarget(m_Direct3D->GetDeviceContext());

	// Clear the render to texture.
	m_Render_Texture->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f, 0.0f, 1.0f, 1.0f);


	m_Camera->Update();
	
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	m_Tessellation_mesh->SendData(m_Direct3D->GetDeviceContext());

	m_Tessellation_Shader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Tessellation_mesh->GetTexture(), outerTess, interTess);

	m_Tessellation_Shader->Render(m_Direct3D->GetDeviceContext(), m_Tessellation_mesh->GetIndexCount());


	// Present the rendered scene to the screen.
	m_Direct3D->SetBackBufferRenderTarget();
}

void App1::RenderDepth()
{
	// Loop though for each light to generate depth map for each
	for (int i = 0; i < NUM_LIGHTS; i++)
	{
		XMMATRIX worldMatrix;

		XMMATRIX lightViewMartix, lightProjectionMatrix;

		// Set the render target to be the render to texture.
		m_depth_Texture[i]->SetRenderTarget(m_Direct3D->GetDeviceContext());

		// Clear the render to texture.
		m_depth_Texture[i]->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f, 0.0f, 1.0f, 1.0f);

		// Generate the view matrix based on the camera's position.
		m_Camera->Update();

		// Get the world, view, and projection matrices from the camera and d3d objects.
		m_Direct3D->GetWorldMatrix(worldMatrix);
		
		m_Lights[i]->GenerateViewMatrix();
		lightViewMartix = m_Lights[i]->GetViewMatrix();

		m_Lights[i]->GenerateProjectionMatrix(SCREEN_NEAR, SCREEN_DEPTH);
		lightProjectionMatrix = m_Lights[i]->GetProjectionMatrix();
		worldMatrix = XMMatrixScaling(0.1, 0.1, 0.1);

		////// Send geometry data (from mesh)
		teaTop->SendData(m_Direct3D->GetDeviceContext());

		m_DepthShader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, lightViewMartix, lightProjectionMatrix );

		m_DepthShader->Render(m_Direct3D->GetDeviceContext(), teaTop->GetIndexCount());

		worldMatrix = XMMatrixTranslation(-50, -1, -50);

		////// Send geometry data (from mesh)
		m_Quad_Mesh->SendData(m_Direct3D->GetDeviceContext());

		m_DepthShader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, lightViewMartix, lightProjectionMatrix );

		m_DepthShader->Render(m_Direct3D->GetDeviceContext(), m_Quad_Mesh->GetIndexCount());


		// Reset the render target back to the original back buffer and not the render to texture anymore.
		m_Direct3D->SetBackBufferRenderTarget();
		m_Direct3D->ResetViewport();
	}
}


void App1::RenderShadow()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, baseViewMatrix, orthoMartix;

	//m_Direct3D->BeginScene(0.39f, 0.58f, 0.92f, 1.0f);
	m_Shadow_Texture->SetRenderTarget(m_Direct3D->GetDeviceContext());


	m_Shadow_Texture->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f, 0.0f, 1.0f, 1.0f);

	//// Generate the view matrix based on the camera's position.
	m_Camera->Update();

	//// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	worldMatrix = XMMatrixScaling(0.1, 0.1, 0.1);

	
	ID3D11ShaderResourceView* depthMaps[NUM_LIGHTS];

	for (int i = 0; i < NUM_LIGHTS; i++)
	{

		depthMaps[i] = m_depth_Texture[i]->GetShaderResourceView();

	}


	//// Send geometry data (from mesh)
	teaTop->SendData(m_Direct3D->GetDeviceContext());

	m_ShadowShader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, teaTop->GetTexture(), depthMaps, m_Lights);

	m_ShadowShader->Render(m_Direct3D->GetDeviceContext(), teaTop->GetIndexCount());


	worldMatrix = XMMatrixTranslation(-50, -1, -50);


	//// Send geometry data (from mesh)
	m_Quad_Mesh->SendData(m_Direct3D->GetDeviceContext());

	m_ShadowShader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Quad_Mesh->GetTexture(), depthMaps, m_Lights);

	m_ShadowShader->Render(m_Direct3D->GetDeviceContext(), m_Quad_Mesh->GetIndexCount());



	//// Present the rendered scene to the screen.
	//m_Direct3D->EndScene();
	m_Direct3D->SetBackBufferRenderTarget();

}

void App1::RenderGeometry()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, baseViewMatrixs;

	// Set the render target to be the render to texture.
	m_Render_Texture->SetRenderTarget(m_Direct3D->GetDeviceContext());

	// Clear the render to texture.
	m_Render_Texture->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f, 0.0f, 1.0f, 1.0f);


	m_Camera->Update();

	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	m_Point_Mesh->SendData(m_Direct3D->GetDeviceContext());

	m_Geomentry_Shader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Point_Mesh->GetTexture(),isTri, vertexScale);

	m_Geomentry_Shader->Render(m_Direct3D->GetDeviceContext(), m_Point_Mesh->GetIndexCount());


	// Present the rendered scene to the screen.
	m_Direct3D->SetBackBufferRenderTarget();
	
}

void App1::RenderVertexMinulation()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;

	// Set the render target to be the render to texture.
	m_Render_Texture->SetRenderTarget(m_Direct3D->GetDeviceContext());

	// Clear the render to texture.
	m_Render_Texture->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f, 0.0f, 1.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Update();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);


	//// Send geometry data (from mesh)
	m_Sphere_Mesh->SendData(m_Direct3D->GetDeviceContext());

	m_Vertex_Manipulation_Shader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Sphere_Mesh->GetTexture(), m_Lights, m_Camera->GetPosition(), m_Timer->GetTotalTimePast(), sphereFreqnacy, sphereHeight, sphereManipulation);

	m_Vertex_Manipulation_Shader->Render(m_Direct3D->GetDeviceContext(), m_Sphere_Mesh->GetIndexCount());

	worldMatrix = XMMatrixTranslation(-50, -10, -50);

	////// Send geometry data (from mesh)
	m_Quad_Mesh->SendData(m_Direct3D->GetDeviceContext());

	m_Vertex_Manipulation_Shader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Quad_Mesh->GetTexture(), m_Lights, m_Camera->GetPosition(), m_Timer->GetTotalTimePast(), planeFreqnacy, planeHeight, planesManipulation);

	m_Vertex_Manipulation_Shader->Render(m_Direct3D->GetDeviceContext(), m_Quad_Mesh->GetIndexCount());


	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_Direct3D->SetBackBufferRenderTarget();

}


 
void App1::RenderToScreen()
{

	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, baseViewMatrix, orthoMartix;

	//// Clear the scene. (default blue colour)
	m_Direct3D->BeginScene(0.39f, 0.58f, 0.92f, 1.0f);

	//// Generate the view matrix based on the camera's position.
	m_Camera->Update();

	// Reset the world martix back to starting point
	m_Direct3D->GetWorldMatrix(worldMatrix);


	// To render ortho mesh
	// Turn off the Z buffer to begin all 2D rendering.
	m_Direct3D->TurnZBufferOff();

	m_Direct3D->GetOrthoMatrix(orthoMartix);// ortho matrix for 2D rendering
	m_Camera->GetBaseViewMatrix(baseViewMatrix);

	m_Ortho_Mesh_normalScaled->SendData(m_Direct3D->GetDeviceContext());


	m_Texture_Shader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, baseViewMatrix, orthoMartix, m_UpScaleTexture->GetShaderResourceView());
	m_Texture_Shader->Render(m_Direct3D->GetDeviceContext(), m_Ortho_Mesh_normalScaled->GetIndexCount());



	m_Direct3D->TurnZBufferOn();

	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();


}

void App1::RenderTerrain()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;

	// Set the render target to be the render to texture.
	m_TerrainTexture->SetRenderTarget(m_Direct3D->GetDeviceContext());
	

	
	m_Direct3D->SetBackBufferRenderTarget();

}


void App1::CreateMainMenuBar()
{
	static bool show_light_option[4];
	static bool showVertex;
	static bool tessellationMenuOption;
	static bool gemeotryMenu;

	if (ImGui::BeginMenu("Application Settings"))
	{
		if (ImGui::MenuItem("Vertex Changes"))
		{
			showVertex = showVertex ? false : true;

		}
		if (ImGui::BeginMenu("Lights"))
		{
			for (int i = 0; i < 4; i++)
			{
				std::string name = "Light " + std::to_string(i +1);
				if (ImGui::MenuItem(name.data()))
				{
					show_light_option[i] = show_light_option[i] ? false : true;
				}
			}
			ImGui::EndMenu();

		}


		if (ImGui::MenuItem("Tessellation"))
		{

			tessellationMenuOption = tessellationMenuOption ? false : true;

		}
		if (ImGui::MenuItem("Geo"))
		{

			gemeotryMenu = gemeotryMenu ? false : true;

		}


		ImGui::EndMenu();

	}

	postPro.PostProccessingMenu(); 

	GeomentryMenu(&gemeotryMenu);
 	vertexChangesMenu(&showVertex);
	tessellationMenu(&tessellationMenuOption);

 	for (int i = 0; i < 4; i++)
	{
		
		m_Lights[i]->DisplayGUIEditor(std::to_string(i),&show_light_option[i]);
	}
	
}


void App1::vertexChangesMenu(bool* is_open)
{
	if (*is_open == true)
	{

		// Create the window
		if (!ImGui::Begin("Vertex manipulation", is_open, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::End();
			return;
		}
		const char* items[] = { "Plane", "Sphere"  };

		static int selectedMesh ;
		ImGui::Combo("Mesh", &selectedMesh, items,2);
  
		// Allow the colours of the light be changed


		int minimulationType = 0;
		switch (selectedMesh)
		{
		case 0:
			minimulationType = planesManipulation;
			ImGui::SliderFloat("Height", &planeHeight, 0.0f, 25.0f);
			ImGui::SliderFloat("Freqancy", &planeFreqnacy, 0.0f, 25.0f);
			break;

		case 1:
			minimulationType = sphereManipulation;
			ImGui::SliderFloat("Height", &sphereHeight, 0.0f, 25.0f);
			ImGui::SliderFloat("Freqancy", &sphereFreqnacy, 0.0f, 25.0f);
			break;
		default:
			minimulationType = planesManipulation;

			break;
		}
		// Setting the light Type 
 
 
		ImGui::Text("Type Of Vertex Minimulation");
		ImGui::RadioButton("Sin Wave", &minimulationType, 0); ImGui::SameLine();
		ImGui::RadioButton("Cos Wave", &minimulationType, 1); ImGui::SameLine();
		ImGui::RadioButton(" Third Wave", &minimulationType, 2);
		ImGui::RadioButton(" Forth Wave ", &minimulationType, 3); ImGui::SameLine();
		ImGui::RadioButton(" Fith Wave ", &minimulationType, 4);
		 


		switch (selectedMesh)
		{
		case 0:
			planesManipulation =  (VertexShader::typeOfVertexMinimulation)minimulationType;
			break;

		case 1:
			sphereManipulation = (VertexShader::typeOfVertexMinimulation)minimulationType;;

			break;
		default:
			planesManipulation = (VertexShader::typeOfVertexMinimulation)minimulationType;;

			break;
		}

		ImGui::End();
	}
}

void App1::tessellationMenu(bool * is_open)
{
	if (*is_open == true)
	{
		if(!ImGui::Begin("Tessellation Options", is_open , ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::End();
			return;
		}

 
		ImGui::SliderInt4("Outer Tessellation Factor", &interTess.x, 1, 64);
		ImGui::SliderInt2("Inner Tessellation Factor", &outerTess.x, 1, 64);

		ImGui::End();


	}
}

void App1::GeomentryMenu(bool * is_open)
{
	if (*is_open == true)
	{
		if (!ImGui::Begin("Geomentry Options", is_open, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::End();
			return;
		}


		ImGui::Checkbox("is using Tri", &isTri);
		if (isTri)
		{
			ImGui::SliderFloat3("Vertex Scaling", &vertexScale.x, 1, 64);

		}
		else
		{
			ImGui::SliderFloat4("Vertex Scaling", &vertexScale.x, 1, 64);

		}
		ImGui::End();


	}
}
