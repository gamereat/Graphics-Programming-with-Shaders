#pragma once

#include "BoxBlurShader.h"
#include "HorizontalBlurShader.h"
#include "VerticalBlurShader.h"
#include "../DXFramework/OrthoMesh.h"

#include "../DXFramework/baseapplication.h"
#include "../DXFramework/RenderTexture.h"
#include "TextureShader.h"
#include "BoxBlurShader.h"

#include "../DXFramework/D3D.h"
#include "PostProccessBoxBlur.h"
#include "PostProccessingDownScale.h"
#include "PostProccessingUpScale.h"
#include "PostProcessingHorizontalBlur.h"

class PostProcessing
{
public:
	 
	PostProcessing();
	~PostProcessing();
	void Init(D3D* directX3D, HWND hwnd);



	RenderTexture* ApplyPostProccessing(OrthoMesh*& orthNormalSized, RenderTexture* lastRenderTexture ,D3D* directX3D, Camera* camera);

	void PostProccessingMenu();
	HorizontalBlurShader* horizontalBlurShader;

private:

	void GeneralSettingMenu(bool* isOpen);
	 
	//RenderTexture* UpScale(OrthoMesh*& orthNormalSized, D3D* directX3D, Camera* camera);
	PostProcessingHorizontalBlur* HorizontalBlur;
	PostProccessingDownScale* downScale;
	PostProccessingUpScale* UpScale;
	/*
	Box Blur post prosseing
	*/
	PostProccessBoxBlur* boxBlur;

	/*
	The current Render texture being used. Used to work out which render texture to set with shader Paramters
	*/
	RenderTexture* currentRenderTexture;


	RenderTexture* ff;



	OrthoMesh* orthoMeshDownScaled;
	/*
	How much the image will be downscalled by when doing post proccessing effects
	*/
	float downScaleAmmount;
	/*
	How much the image will be upscade back after the post proccesssing effects
	*/
	float upScaleAmmount;
	
};

