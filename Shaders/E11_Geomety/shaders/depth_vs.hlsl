cbuffer MatrixBuffer : register(cb0)
{
    matrix worldMatrix;
    matrix viewMatrix[4];
    matrix projectionMatrix[4];
};

struct InputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};

struct OutputType
{
    float4 position : SV_POSITION;
    float4 depthPosition[4] : TEXCOORD0;
};

OutputType main(InputType input)
{
    OutputType output;
        
    // Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;
 	for (int i = 0; i < 4; i++)
	{
		// Calculate the position of the vertex against the world, view, and projection matrices.
		output.position = mul(input.position, worldMatrix[i]);
		output.position = mul(output.position, viewMatrix[i]);
		output.position = mul(output.position, projectionMatrix[i]);

		// Store the position value in a second input value for depth value calculations.
		output.depthPosition[i] = output.position;
	}
    return output;
}