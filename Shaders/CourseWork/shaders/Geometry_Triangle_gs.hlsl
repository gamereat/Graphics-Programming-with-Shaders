 const  float PI = 3.14159265f;

cbuffer MatrixBuffer : register(cb0)
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer GeomentryBuffer : register(cb1)
{

	int isTri;
	int3 padding;
	float4 vertexScale;
};

cbuffer PositionBuffer
{
	static float3 quad_position[4] =
	{
		float3(-1,1,0),
		float3(-1,-1,0),
		float3(1,1,0),
		float3(1,-1,0)
	};

	static float3 tri_position[3] =
	{
		float3(0.0,1.0,0.0),
		float3(-1.0,0.0,0.0),
		float3(1.0,0.0,0.0)
	};
};

struct InputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;

};

// pixel input type
struct OutputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};


OutputType generateTriangle(point InputType input[1], inout TriangleStream< OutputType > triStream)
{
	OutputType output;

	for (int i = 0; i < 3; i++)
	{
		float3 vposition = tri_position[i] * vertexScale[i];;
		vposition = mul(vposition, (float3x3) worldMatrix) + input[0].position;
		output.position = mul(float4 (vposition, 1.0), viewMatrix);
		output.position = mul(output.position, projectionMatrix);

		output.tex = input[0].tex;
		output.normal = input[0].normal;

		triStream.Append(output);
	}
	return output;
}
OutputType generateQuad(point InputType input[1], inout TriangleStream< OutputType > triStream)
{
	OutputType output;

	for (int i = 0; i < 4; i++)
	{
		float3 vposition = quad_position[i] * vertexScale[i];
		vposition = mul(vposition, (float3x3) worldMatrix) + input[0].position;
		output.position = mul(float4 (vposition, 1.0), viewMatrix);
		output.position = mul(output.position, projectionMatrix);

		output.tex = input[0].tex;
		output.normal = input[0].normal;

		triStream.Append(output);
	}
	return output;
}
[maxvertexcount(4)]
void main(	point InputType input[1] ,inout TriangleStream< OutputType > triStream)
{
	OutputType output;

	input[0].position.w = 1.0f;

	if(isTri == 0)
	{ 
		generateQuad(input[0], triStream);

	}
	else
	{
		generateTriangle(input[0], triStream);

	}


	/*output.position = input[0].position + float4(0.0, 1.0, 0.0, 0.0);

	output.position = mul(output.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	output.tex = input[0].tex;

	output.normal = mul(input[0].normal, (float3x3)worldMatrix);
	output.normal = normalize(output.normal);

	triStream.Append(output);


	output.position = input[0].position + float4(-1.0, 0.0, 0.0, 0.0);

	output.position = mul(output.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	output.tex = input[0].tex;

	output.normal = mul(input[0].normal, (float3x3)worldMatrix);
	output.normal = normalize(output.normal);

	triStream.Append(output);



	output.position = input[0].position + float4(1.0, 0.0, 0.0, 0.0);

	output.position = mul(output.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	output.tex = input[0].tex;

	output.normal = mul(input[0].normal, (float3x3)worldMatrix);
	output.normal = normalize(output.normal);

	triStream.Append(output);


	triStream.RestartStrip();*/




}


