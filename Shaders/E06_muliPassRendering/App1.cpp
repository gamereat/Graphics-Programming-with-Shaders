// Lab1.cpp
// Lab 1 example, simple textured quad
#include "App1.h"
#include <string>
App1::App1()
{
	m_Quad_Mesh = nullptr;
	m_Vertex_Manipulation_Shader = nullptr;

	m_Ortho_Mesh = nullptr;
	m_Texture_Shader = nullptr;

	m_Render_Texture = nullptr;
}

void App1::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in)
{
	// Call super init function (required!)
	BaseApplication::init(hinstance, hwnd, screenWidth, screenHeight, in);

	// Create Mesh object
	m_Quad_Mesh = new PlaneMesh(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), L"../res/DefaultDiffuse.png");
	m_Sphere_Mesh = new SphereMesh(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), L"../res/DefaultDiffuse.png");
	m_Vertex_Manipulation_Shader = new VertexShader(m_Direct3D->GetDevice(), hwnd);

	m_Texture_Shader =  new TextureShader(m_Direct3D->GetDevice(), hwnd);

	for (int i = 0; i < 4; i++)
	{
		m_Lights[i] = new Light();
	}

	m_Lights[0]->SetDirection(-1, 0, 0);
	m_Lights[0]->SetDiffuseColour(1, 1, 1, 1);

	m_Ortho_Mesh = new OrthoMesh(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), SCREEN_WIDTH/4, SCREEN_HEIGHT /4, -((SCREEN_WIDTH / 4) + (SCREEN_WIDTH / 8)), ((SCREEN_HEIGHT / 4) + (SCREEN_HEIGHT / 8)));

	m_Render_Texture = new  RenderTexture(m_Direct3D->GetDevice(), SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_NEAR, SCREEN_DEPTH);

}


App1::~App1()
{
	// Run base application deconstructor
	BaseApplication::~BaseApplication();

	if (m_Render_Texture)
	{
		delete m_Render_Texture;
		m_Render_Texture = nullptr;
	}

	if (m_Texture_Shader)
	{
		delete m_Texture_Shader;
		m_Texture_Shader = nullptr;
	}

	if (m_Ortho_Mesh)
	{
		delete m_Ortho_Mesh;
		m_Ortho_Mesh = nullptr;
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


	// Render the first pass
	RenderToTexture();

	// Render the second pass
	RenderToScreen();
	return true;
}

void App1::RenderToTexture()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;

	// Set the render target to be the render to texture.
	m_Render_Texture->SetRenderTarget(m_Direct3D->GetDeviceContext());

	// Clear the render to texture.
	m_Render_Texture->ClearRenderTarget(m_Direct3D->GetDeviceContext(),0.0f, 0.0f, 1.0f, 1.0f);

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
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, baseViewMatrix, orthoMatrix;

	//// Clear the scene. (default blue colour)
	m_Direct3D->BeginScene(0.39f, 0.58f, 0.92f, 1.0f);

	//// Generate the view matrix based on the camera's position.
	m_Camera->Update();

	//// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);


	//// Send geometry data (from mesh)
	m_Sphere_Mesh->SendData(m_Direct3D->GetDeviceContext());

	m_Vertex_Manipulation_Shader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Sphere_Mesh->GetTexture(), m_Lights, m_Camera->GetPosition(), m_Timer->GetTotalTimePast(), sphereFreqnacy, sphereHeight, sphereManipulation);

	m_Vertex_Manipulation_Shader->Render(m_Direct3D->GetDeviceContext(), m_Sphere_Mesh->GetIndexCount());

	worldMatrix = XMMatrixTranslation(-50, -10, -50);

	//// Send geometry data (from mesh)
	m_Quad_Mesh->SendData(m_Direct3D->GetDeviceContext());

	m_Vertex_Manipulation_Shader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Quad_Mesh->GetTexture(), m_Lights, m_Camera->GetPosition(), m_Timer->GetTotalTimePast(), planeFreqnacy, planeHeight, planesManipulation);

	m_Vertex_Manipulation_Shader->Render(m_Direct3D->GetDeviceContext(), m_Quad_Mesh->GetIndexCount());
	

	// Reset the world martix back to starting point
	m_Direct3D->GetWorldMatrix(worldMatrix);


	// To render ortho mesh
	// Turn off the Z buffer to begin all 2D rendering.
	m_Direct3D->TurnZBufferOff();

	m_Direct3D->GetOrthoMatrix(orthoMatrix);// ortho matrix for 2D rendering
	m_Camera->GetBaseViewMatrix(baseViewMatrix);

	m_Ortho_Mesh->SendData(m_Direct3D->GetDeviceContext());
	m_Texture_Shader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, baseViewMatrix, orthoMatrix, m_Render_Texture->GetShaderResourceView());
	m_Texture_Shader->Render(m_Direct3D->GetDeviceContext(), m_Ortho_Mesh->GetIndexCount());

	m_Direct3D->TurnZBufferOn();

	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();


}

void App1::CreateMainMenuBar()
{
	static bool show_light_option[4];
	static bool showVertex;

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

	
		ImGui::EndMenu();

	}





	vertexChangesMenu(&showVertex);
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

