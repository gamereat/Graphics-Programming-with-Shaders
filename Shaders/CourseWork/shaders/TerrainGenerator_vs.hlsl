Texture2D hightMap : register(t0);
SamplerState Sampl
{
    Filter = MIN_MAG_LINEAR_MIP_POINT;
    addressU = clamp;
    addressV = clamp;
};



cbuffer MatrixBuffer : register(cb0)
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
    matrix lightViewMatrix[4];
    matrix lightProjectionMatrix[4];
};


cbuffer CammeraBuffer : register(cb2)
{
    float3 cammeraPostion;
    float padding1;
}
cbuffer LightBuffer2 : register(cb3)
{
    float4 lightPosition[4];
};
struct InputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    uint id : SV_VertexID;

};

struct OutputType
{
    float4 position : POSITION;

    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    float4 lightViewPosition[4] : TEXCOORD1;
    float3 lightPos[4] : TEXCOORD5;
    float3 position3D : TEXCOORD10;
    float3 viewDirection : TEXCOORD11;
};
 
OutputType main(InputType input)
{
 //   OutputType output;
 //   input.position.w = 1.0f;

 // //  input.position.y = amplutude * sin(speed * (input.position.x + time));

	//// Store the texture coordinates for the pixel shader.
 //   output.tex = input.tex;

 
 //   input.position.y += hightMap.SampleLevel(Sampl, input.tex, 0).x ;
 
 //   output.position = mul(input.position, worldMatrix);
 //   output.position = mul(output.position, viewMatrix);
 //   output.position = mul(output.position, projectionMatrix);



    
	//// Calculate the normal vector against the world matrix only.
 //   output.normal = mul(input.normal, (float3x3) worldMatrix);
	
 //   // Normalize the normal vector.
 //   output.normal = normalize(output.normal);


 //   for (int i = 0; i < 4; i++)
 //   {
	//	// Calculate the position of the vertice as viewed by the light source.
 //       output.lightViewPosition[i] = mul(input.position, worldMatrix);
 //       output.lightViewPosition[i] = mul(output.lightViewPosition[i], lightViewMatrix[i]);
 //       output.lightViewPosition[i] = mul(output.lightViewPosition[i], lightProjectionMatrix[i]);
 //   }
 //   // Calculate the position of the vertex in the world.
 //   float4 worldPosition = mul(input.position, worldMatrix);

	//// Determine the viewing direction based on the position of the camera and the position of the vertex in the world.
 //   output.viewDirection = cammeraPostion.xyz - worldPosition.xyz;

	//// Normalize the viewing direction vector.
 //   output.viewDirection = normalize(output.viewDirection);

	//// world position of vertex
 //   output.position3D = mul(input.position, worldMatrix);

 //   for (int i = 0; i < 4; i++)
 //   {
	//	// Determine the light position based on the position of the light and the position of the vertex in the world.
 //       output.lightPos[i] = lightPosition[i].xyz - worldPosition.xyz;

	//	// Normalize the light position vector.
 //       output.lightPos[i] = normalize(output.lightPos[i]);
 //   }
    OutputType output;
    

    // Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;

	// Move the texture to half way along the screen

    // Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);

	// Store the texture coordinates for the pixel shader.
    output.tex = input.tex;

	// Calculate the normal vector against the world matrix only.
    output.normal = mul(input.normal, (float3x3) worldMatrix);
	
    // Normalize the normal vector.
    output.normal = normalize(output.normal);
    
    return output;
 }