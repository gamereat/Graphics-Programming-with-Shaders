// Light class
// Holds data that represents a light source

#include "light.h"
#include "../imgui/imgui.h"
#include <string>
void Light::GenerateViewMatrix()
{
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);

	//up = XMVectorSetX(up, 0.0f);
	//up = XMVectorSetY(up, 1.0f);
	//up = XMVectorSetZ(up, 0.0f);

	// Create the view matrix from the three vectors.
	m_viewMatrix = XMMatrixLookAtLH(m_position, m_lookAt, up);
}

void Light::GenerateProjectionMatrix(float screenNear, float screenFar)
{
	float fieldOfView, screenAspect;

	// Setup field of view and screen aspect for a square light source.
	fieldOfView = (float)XM_PI / 2.0f;
	screenAspect = 1.0f;

	// Create the projection matrix for the light.
	m_projectionMatrix = XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, screenNear, screenFar);
}

void Light::DisplayGUIEditor(std::string  lightNum,bool* is_open)
{
	std::string name = "Lights " ;
	name += "Settings ";
	name+= lightNum;
 	if (*is_open == true)
	{

		// Create the window
		if (!ImGui::Begin(name.data(), is_open, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::End();
			return;
		}
		// Setting the light Type 
		int lightType = (int)m_lightType;
		ImGui::Text("Light Type"); ImGui::SameLine();
		ImGui::RadioButton("Directional", &lightType, 0); ImGui::SameLine();
		ImGui::RadioButton("Point", &lightType, 1); ImGui::SameLine();
		ImGui::RadioButton("Spot", &lightType, 2);
		m_lightType = (Light::lightType)lightType;

		ImGui::Text("Colour of light");
		// Allow the colours of the light be changed
		ImGui::ColorEdit4("Diffuse Colour", &m_diffuseColour.x, true);
		ImGui::ColorEdit4("Ambient Colour", &m_ambientColour.x, true);

		ImGui::Text("Specular Settings");


		// Change based off the specular colour
		ImGui::Checkbox("Make specular ", &m_makeSpecular);

		if (m_makeSpecular)
		{
			ImGui::ColorEdit4("Specular Colour", &m_specularColour.x, true);
			ImGui::DragFloat("Specular Power", &m_specularPower, 0.5f, 1.0f, 75.0f);
		}

		XMFLOAT3 lightPos(0, 0, 0);
		// Give the correct setting depending on the diffrent light type
		switch (m_lightType)
		{
		case Light::lightType::directional:
			ImGui::Text("Directional light settings");

			ImGui::DragFloat3("Direction", &m_direction.x, 0.005f, 0.0f, 1.0);

			break;
		case Light::lightType::point:

			// Allow the position of the light be changed
			ImGui::Text("Point light settings");

			lightPos = XMFLOAT3(XMVectorGetX(m_position), XMVectorGetY(m_position), XMVectorGetZ(m_position));
			ImGui::DragFloat3("Set Light Pos", &lightPos.x);
			m_position = XMVectorSet(lightPos.x, lightPos.y, lightPos.z, 1.0f);

			ImGui::Text("Attenuation settings");

			ImGui::DragFloat("Range", &m_range, 0.5f, 0.0f, 100.0f);
			ImGui::DragFloat("Attenuation Constant Factor", &m_attenuationConstantFactor, 0.1f, 0.1f, 10.0f);
			ImGui::DragFloat("Attenuation Linear Factor", &m_attenuationLinearFactor, 0.1f, 0.0f, 10.0f);
			ImGui::DragFloat("Attenuation Quadratic Factor", &m_attenuationQuadraticFactor, 0.1f, 0.0f, 10.0f);
			break;
		case Light::lightType::spot:
			ImGui::Text("SPOT LIGHT NOT IMPLMENTED YET");
			break;
		default:
			break;
		}


		ImGui::End();
	}
}

void Light::SetAmbientColour(float red, float green, float blue, float alpha)
{
	m_ambientColour = XMFLOAT4(red, green, blue, alpha);
}

void Light::SetDiffuseColour(float red, float green, float blue, float alpha)
{
	m_diffuseColour = XMFLOAT4(red, green, blue, alpha);
}


void Light::SetDirection(float x, float y, float z)
{
	m_direction = XMFLOAT3(x, y, z);
}

void Light::SetSpecularColour(float red, float green, float blue, float alpha)
{
	m_specularColour = XMFLOAT4(red, green, blue, alpha);
}


void Light::SetSpecularPower(float power)
{
	m_specularPower = power;
}

void Light::SetPosition(float x, float y, float z)
{
	m_position = XMVectorSet(x, y, z, 1.0f);
}

XMFLOAT4 Light::GetAmbientColour()
{
	return m_ambientColour;
}

XMFLOAT4 Light::GetDiffuseColour()
{
	return m_diffuseColour;
}


XMFLOAT3 Light::GetDirection()
{
	return m_direction;
}

XMFLOAT4 Light::GetSpecularColour()
{
	return m_specularColour;
}


float Light::GetSpecularPower()
{
	return m_specularPower;
}

XMFLOAT3 Light::GetPosition()
{
	XMFLOAT3 temp(XMVectorGetX(m_position), XMVectorGetY(m_position), XMVectorGetZ(m_position));
	return temp;
}

void Light::SetLookAt(float x, float y, float z)
{
	m_lookAt = XMVectorSet(x, y, z, 1.0f);
}

void Light::SetRange(float newRange)
{
	m_range = newRange;

}

void Light::SetAttenuationContantFactor(float newValue)
{

	m_attenuationConstantFactor = newValue;
}

void Light::SetAttenuationLinearFactor(float newValue)
{
	m_attenuationLinearFactor = newValue;
}

void Light::SetAttenuationQuadraticFactor(float newValue)
{
	m_attenuationQuadraticFactor = newValue;
}

XMMATRIX Light::GetViewMatrix()
{
	return m_viewMatrix;
}

XMMATRIX Light::GetProjectionMatrix()
{
	return m_projectionMatrix;
}

float Light::GetRange()
{
	return m_range;
}

float Light::GetAttenuationContantFactor()
{
	return m_attenuationConstantFactor;
}

float Light::GetAttenuationLinearFactor()
{
	return m_attenuationLinearFactor;
}

float Light::GetAttenuationQuadraticFactor()
{
	return m_attenuationQuadraticFactor;
}

Light::lightType Light::GetLightType()
{
	return m_lightType;
}
bool Light::GetMakesSpecular()
{
	return m_makeSpecular;
}
