#include "PostProcessing.h"



PostProcessing::PostProcessing()
{

}


PostProcessing::~PostProcessing()
{
	// Tidy up memory 
	if (horizontalBlur)
	{
		delete horizontalBlur;
		horizontalBlur = nullptr;
	}
	if (downScale)
	{
		delete downScale;
		downScale = nullptr;
	}
	if (UpScale)
	{
		delete UpScale;
		UpScale = nullptr;
	}

	if (boxBlur)
	{
		delete boxBlur;
		boxBlur = nullptr;
	}

 
	if (orthoMeshDownScaled)
	{
		delete orthoMeshDownScaled;
		orthoMeshDownScaled = nullptr;
	}
 
}

void PostProcessing::Init(D3D* directX3D, HWND hwnd)
{

	// Init var 
	// Set the down scale ammount to half the size of the screen
	downScaleAmmount = 2;
	// Set the upscale back the full size of the screen
	upScaleAmmount = 1;


	// Create a downscaled OrthoMesh to be used for each post prcoessing effect
	orthoMeshDownScaled = new OrthoMesh(directX3D->GetDevice(), directX3D->GetDeviceContext(), SCREEN_WIDTH / downScaleAmmount, SCREEN_HEIGHT / downScaleAmmount, 0, 0);

	// Init all the post proccessing effects 

	downScale = new PostProccessingDownScale(directX3D, hwnd, downScaleAmmount);
	
	UpScale = new PostProccessingUpScale(directX3D, hwnd, upScaleAmmount);

	boxBlur = new PostProccessBoxBlur(directX3D, hwnd, downScaleAmmount);

	horizontalBlur = new PostProcessingGaussianBlur(directX3D, hwnd, downScaleAmmount);

	verticalBlur = new PostProcessingVerticalBlur(directX3D, hwnd, downScaleAmmount);


}

RenderTexture* PostProcessing::ApplyPostProccessing(OrthoMesh*& orthNormalSized, RenderTexture* lastRenderTexture, D3D* directX3D, Camera* camera)
{
	//bool isWireFrameOn = false;
	//if (directX3D->getWireFrameMode())
	//{
	//	isWireFrameOn = true;
	//}	
	//directX3D->TurnOffWireframe();

	// Create a pointer to the current render texture being used for post processing 
	RenderTexture*  currentRenderTexture = nullptr;
	// Used to keep track of the down scale render texture 
	RenderTexture* downScaleTexture = nullptr;

	// Down scale the scene and keep track of the downscaled texture what is returned 
	downScaleTexture = currentRenderTexture = downScale->Render(directX3D, camera, orthoMeshDownScaled, lastRenderTexture);
	 
	// Add any post proccessing effects the use has enabled 
	
	currentRenderTexture = boxBlur->Render(directX3D, camera, orthoMeshDownScaled, downScaleTexture);

	// Guassian blur effect
	
	currentRenderTexture = verticalBlur->Render(directX3D, camera, orthoMeshDownScaled, downScaleTexture);
	currentRenderTexture = horizontalBlur->Render(directX3D, camera, orthoMeshDownScaled, currentRenderTexture);

	/*if (isWireFrameOn)
	{
		directX3D->TurnOnWireframe();
	}*/


 	// Upscale the scene again 
	// Return the render texture so i can be rendered to the scene 
	 return UpScale->Render(directX3D, camera, orthNormalSized, currentRenderTexture);

}


void PostProcessing::PostProccessingMenu()
{

	// Create a menu bar option 
	// each effect will have it own pop out menu which will allow the user to change settings for that effect  
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
			horizontalBlur->ToggleMenu();
		}

		if (ImGui::MenuItem("Vertical Blur"))
		{
			verticalBlur->ToggleMenu();
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