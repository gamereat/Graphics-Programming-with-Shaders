#pragma once
#include "PostProcessingBase.h"
#include "HorizontalBlurShader.h"

class PostProcessingHorizontalBlur :
	public PostProcessingBase
{
public:
	RenderTexture* Render(D3D* directX3D, Camera* camera, OrthoMesh* orthoMesh, RenderTexture* currentRenderTexture);
	void MenuOptions(bool * isOpen);

	PostProcessingHorizontalBlur(D3D * directX3D, HWND hwnd, float downscaleValue);
	~PostProcessingHorizontalBlur();



private:
	HorizontalBlurShader* horizontalBlurShader;

	float downScaleAmmount;

	int neighboursToUse;
};

