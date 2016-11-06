#pragma once
#include "PostProcessingBase.h"
#include "BoxBlurShader.h"

class PostProccessBoxBlur :
	public PostProcessingBase
{
public:
	// void Init();

	RenderTexture* Render(D3D* directX3D, Camera* camera, OrthoMesh* orthoMesh, RenderTexture* currentRenderTexture);
	 void MenuOptions(bool * isOpen);

	PostProccessBoxBlur(D3D * directX3D, HWND hwnd, float downscaleValue);
	~PostProccessBoxBlur();

private:
	BoxBlurShader* boxBurShader;

};

