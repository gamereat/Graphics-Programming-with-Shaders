// Lab1.cpp
// Lab 1 example, simple textured quad
#include "App1.h"

App1::App1()
{
	m_Quad_Mesh = nullptr;
	m_Light_Shader = nullptr;
}

void App1::init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, Input *in)
{
	// Call super init function (required!)
	BaseApplication::init(hinstance, hwnd, screenWidth, screenHeight, in);

	// Create Mesh object
	m_Quad_Mesh = new PlaneMesh(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), L"../res/DefaultDiffuse.png");
	m_Sphere_Mesh = new SphereMesh(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), L"../res/DefaultDiffuse.png");
	m_Light_Shader = new LightSpecularShader(m_Direct3D->GetDevice(), hwnd);

	for (int i = 0; i < 4; i++)
	{
		m_Lights[i] = new Light();
	}

}


App1::~App1()
{
	// Run base application deconstructor
	BaseApplication::~BaseApplication();

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

	if (m_Light_Shader)
	{
		delete m_Light_Shader;
		m_Light_Shader = 0;
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
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;

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

	m_Light_Shader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Sphere_Mesh->GetTexture(), m_Lights, m_Camera->GetPosition());

	m_Light_Shader->Render(m_Direct3D->GetDeviceContext(), m_Sphere_Mesh->GetIndexCount());

	worldMatrix = XMMatrixTranslation(-50, -10, -50);
  
	//// Send geometry data (from mesh)
	m_Quad_Mesh->SendData(m_Direct3D->GetDeviceContext());
   
	m_Light_Shader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Quad_Mesh->GetTexture(), m_Lights, m_Camera->GetPosition());

	m_Light_Shader->Render(m_Direct3D->GetDeviceContext(), m_Quad_Mesh->GetIndexCount());








 

	//// Present the rendered scene to the screen.
	m_Direct3D->EndScene();

	return true;
}

void App1::CreateMainMenuBar()
{
	static bool show_light_option[4];
 	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Lights"))
		{ 
			for (int i = 0; i < 4; i++)
			{
				if (ImGui::MenuItem("Light "))
				{
					show_light_option[i] = show_light_option[i] ? false : true;
				}
			}
 
			ImGui::EndMenu();

		}
 
		ImGui::EndMainMenuBar();
	}
	for (int i = 0; i < 4; i++)
	{
		m_Lights[i]->DisplayGUIEditor(i,&show_light_option[i]);
	}

}

