// Lab1.cpp
// Lab 1 example, simple textured quad
#include "App1.h"
#include <string>
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
	m_Light_Shader = new VertexShader(m_Direct3D->GetDevice(), hwnd);

	for (int i = 0; i < 4; i++)
	{
		m_Lights[i] = new Light();
	}

	m_Lights[0]->SetDirection(-1, 0, 0);
	m_Lights[0]->SetDiffuseColour(1, 1, 1, 1);

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

	m_Light_Shader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Sphere_Mesh->GetTexture(), m_Lights, m_Camera->GetPosition(),m_Timer->GetTotalTimePast(), sphereFreqnacy ,sphereHeight , sphereManipulation);

	m_Light_Shader->Render(m_Direct3D->GetDeviceContext(), m_Sphere_Mesh->GetIndexCount());

	worldMatrix = XMMatrixTranslation(-50, -10, -50);
  
	//// Send geometry data (from mesh)
	m_Quad_Mesh->SendData(m_Direct3D->GetDeviceContext());
   
	m_Light_Shader->SetShaderParameters(m_Direct3D->GetDeviceContext(), worldMatrix, viewMatrix, projectionMatrix, m_Quad_Mesh->GetTexture(), m_Lights, m_Camera->GetPosition(), m_Timer->GetTotalTimePast(), planeFreqnacy, planeHeight, planesManipulation);

	m_Light_Shader->Render(m_Direct3D->GetDeviceContext(), m_Quad_Mesh->GetIndexCount());








 

	//// Present the rendered scene to the screen.
	m_Direct3D->EndScene();

	return true;
}

void App1::CreateMainMenuBar()
{
	static bool show_light_option[4];
	static bool showVertex;
	static bool directxSetting ;
	
	if (ImGui::BeginMenu("Window Settings"))
	{
		if (ImGui::MenuItem("DirectX Options"))
		{
			directxSetting = directxSetting ? false : true;

		}
		ImGui::EndMenu();

	}
	if (ImGui::BeginMenu("Application Settings"))
	{
		if (ImGui::MenuItem("Vertex Changes"))
		{
			showVertex = showVertex ? false : true;
		//	ImGui::EndMenu();

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





	m_Direct3D->DirectXSettingsMenu(&directxSetting);
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

