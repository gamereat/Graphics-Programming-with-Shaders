struct InputType
{
    float4 position : SV_POSITION;
    float4 depthPosition[4] : TEXCOORD5;
};

float4 main(InputType input) : SV_TARGET
{
	float depthValue;
	float4 color[4];

	for (int i = 0; i < 4; i++)
	{
		// Get the depth value of the pixel by dividing the Z pixel depth by the homogeneous W coordinate.
		depthValue = input.depthPosition[i].z / input.depthPosition[i].w;

		color[i] = float4(depthValue, depthValue, depthValue, 1.0f);
	}
	float4 outputColour = float4(0,0,0,0);
	for (int i = 0; i < 4; i++)
	{
		outputColour = color[i];
	}
	outputColour /= 4;

	outputColour = float4(outputColour.x, outputColour.y, outputColour.z, 1.0f);
	return outputColour;
}