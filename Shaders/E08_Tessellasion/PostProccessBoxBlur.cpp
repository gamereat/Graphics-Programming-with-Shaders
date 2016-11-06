#include "PostProccessBoxBlur.h"



PostProccessBoxBlur::PostProccessBoxBlur(D3D * directX3D, HWND hwnd, float downscaleValue)
	: PostProcessingBase(directX3D, hwnd, downscaleValue)
{
	boxBurShader = new BoxBlurShader(directX3D->GetDevice(), hwnd);

}


PostProccessBoxBlur::~PostProccessBoxBlur()
{
}

 

RenderTexture* PostProccessBoxBlur::Render(D3D* directX3D, Camera* camera, OrthoMesh* orthoMesh, RenderTexture* currentRenderTextureh)
{
	if (isEnabled)
	{
		XMMATRIX worldMatrix, baseViewMatrix, orthoMartix;

		PreRender(directX3D, camera, worldMatrix, baseViewMatrix, orthoMartix, orthoMesh);

		boxBurShader->SetShaderParameters(directX3D->GetDeviceContext(), worldMatrix, baseViewMatrix, orthoMartix, currentRenderTextureh->GetShaderResourceView());
		boxBurShader->Render(directX3D->GetDeviceContext(), orthoMesh->GetIndexCount());

	}		
	
	PostRender(directX3D);

	if(isEnabled)
	{
		return renderTexture;
	}
	else
	{
		return currentRenderTextureh;

	}
}

void PostProccessBoxBlur::MenuOptions(bool * isOpen)
{
	if (*isOpen == true)
	{
		
		// Create the window
		if (!ImGui::Begin("Box Blur Settings", isOpen, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::End();
			return;
		}
		ImGui::Checkbox("Enable box blur", &isEnabled);


		ImGui::End();
	}
}
