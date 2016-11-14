#pragma once
#include "VerticalBlurShader.h"
#include "PostProcessingBase.h"
class PostProcessingVerticalBlur :
	public PostProcessingBase
{
 
public:
	RenderTexture* Render(D3D* directX3D, Camera* camera, OrthoMesh* orthoMesh, RenderTexture* currentRenderTexture);
	void MenuOptions(bool * isOpen);

	PostProcessingVerticalBlur(D3D * directX3D, HWND hwnd, float downscaleValue);
	~PostProcessingVerticalBlur();



private:
	VerticalBlurShader* verticalBlurShader;

	float downScaleAmmount;

	int neighboursToUse;
};

