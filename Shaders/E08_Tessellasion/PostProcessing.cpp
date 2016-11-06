#include "PostProcessing.h"



PostProcessing::PostProcessing()
{

}


PostProcessing::~PostProcessing()
{
}

void PostProcessing::Init(D3D* directX3D, HWND hwnd)
{
	horizontalBlurShader = new HorizontalBlurShader(directX3D->GetDevice(), hwnd);

	downScaleAmmount = 2;
	upScaleAmmount = 1;

	orthoMeshDownScaled = new OrthoMesh(directX3D->GetDevice(), directX3D->GetDeviceContext(), SCREEN_WIDTH / downScaleAmmount, SCREEN_HEIGHT / downScaleAmmount, 0, 0);

	downScale = new PostProccessingDownScale(directX3D, hwnd, downScaleAmmount);


	UpScale = new PostProccessingUpScale(directX3D, hwnd, upScaleAmmount);

	boxBlur = new PostProccessBoxBlur(directX3D, hwnd, downScaleAmmount);

	HorizontalBlur = new PostProcessingHorizontalBlur(directX3D, hwnd, downScaleAmmount);


	ff = new RenderTexture(directX3D->GetDevice(), SCREEN_WIDTH / downScaleAmmount, SCREEN_HEIGHT / downScaleAmmount, SCREEN_NEAR, SCREEN_DEPTH);
}

RenderTexture* PostProcessing::ApplyPostProccessing(OrthoMesh*& orthNormalSized, RenderTexture* lastRenderTexture, D3D* directX3D, Camera* camera)
{

	currentRenderTexture = nullptr;
	RenderTexture* downScaleTexture;
	downScaleTexture = currentRenderTexture = downScale->Render(directX3D, camera, orthoMeshDownScaled, lastRenderTexture);
	 

	
	currentRenderTexture = boxBlur->Render(directX3D, camera, orthoMeshDownScaled, downScaleTexture);
	currentRenderTexture = HorizontalBlur->Render(directX3D, camera, orthoMeshDownScaled, downScaleTexture);





	 return UpScale->Render(directX3D, camera, orthNormalSized, currentRenderTexture);

}


 

void PostProcessing::PostProccessingMenu()
{
	static bool isGeneralSetting;
 	if (ImGui::BeginMenu("Post Proccessing Settings"))
	{
		if (ImGui::MenuItem("General Settings"))
		{
			isGeneralSetting = isGeneralSetting ? false : true;
		}

		if (ImGui::MenuItem("Box Blur"))
		{
			boxBlur->ToggleMenu();
		}


		if (ImGui::MenuItem("Horizontal Blur"))
		{
			HorizontalBlur->ToggleMenu();
		}
		ImGui::EndMenu();

	}

	GeneralSettingMenu(&isGeneralSetting);
}


void PostProcessing::GeneralSettingMenu(bool* isOpen)
{
	if (*isOpen == true)
	{
		if (!ImGui::Begin("General PostProsessing effects", isOpen, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::End();
			return;
		}
			ImGui::Text("General Settting for the post processing effects");


			ImGui::End();

		
	}
}