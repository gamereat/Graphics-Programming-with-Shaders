#pragma once
#include "PostProcessingBase.h"
#include "HorizontalBlurShader.h"

class PostProcessingGaussianBlur :
	public PostProcessingBase
{
public:
	RenderTexture* Render(D3D* directX3D, Camera* camera, OrthoMesh* orthoMesh, RenderTexture* currentRenderTexture);
	void MenuOptions(bool * isOpen);

	PostProcessingGaussianBlur(D3D * directX3D, HWND hwnd, float downscaleValue);
	~PostProcessingGaussianBlur();



private:
	HorizontalBlurShader* horizontalBlurShader;

	float downScaleAmmount;

	int neighboursToUse;
};

