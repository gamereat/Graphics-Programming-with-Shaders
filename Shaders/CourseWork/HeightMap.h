#pragma once
#include "../DXFramework/Texture.h"
class HeightMap
{
public:
	HeightMap();
 	~HeightMap();


	/*
	Overload contructor that will load in height map from file
	@param device			Directx 11 device used for current project
	@param deviceContext	Directx 11 device context used for current project
	@param fileDirectory	The directory file is located in
	*/
	 HeightMap(ID3D11Device* device, ID3D11DeviceContext* deviceContext, WCHAR* fileDirectory);

	/*
	Loads in height map from file

	 
	@param device			Directx 11 device used for current project
	@param deviceContext	Directx 11 device context used for current project
	@param fileDirectory	The directory file is located in
	*/
	void LoadHeightMapTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, WCHAR* fileDirectory);

	/*
	Used to unload height map from memory and clean up 
	*/
	void UnloadHeightMap();
	/*
	Gets the height map texture
	*/
	Texture* getHeightMapTexture();
	/*
	Used to save height map data
	*/
	void setHeightMapTexture(Texture* heightMapTexture);

	/*
	Will get a height map scaling value used to scale height map
	*/
	float getHeightScaling();

	/*
	Changes height map scallign value 
	*/
	void setHeightMapScaling(float heightScaling);
private:

	/*
	Scaling factor used for height map
	*/
	float heightScaling;

	/*
	Texture used to hold height map information
	*/
	Texture* heightMapTexture;


};

