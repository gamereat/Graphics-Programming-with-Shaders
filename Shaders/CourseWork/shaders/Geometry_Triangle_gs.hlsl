cbuffer MatrixBuffer : register(cb0)
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
};

cbuffer GeomentryBuffer : register(cb1)
{

    float time;
    float gravity;
    float explosiveAmmount;
    float padding;

    float4 vertexScale;
};

cbuffer PositionBuffer
{
    static float3 quad_position[4] =
    {
        float3(-1, 1, 0),
		float3(-1, -1, 0),
		float3(1, 1, 0),
		float3(1, -1, 0)
    };

    static float3 tri_position[3] =
    {
        float3(0.0, 1.0, 0.0),
		float3(-1.0, 0.0, 0.0),
		float3(1.0, 0.0, 0.0)
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


OutputType generateTriangle(triangle InputType input[3], inout TriangleStream<OutputType> triStream)
{
    OutputType output;

    return output;
}
OutputType generateQuad(triangle InputType input[3], inout TriangleStream<OutputType> triStream)
{
    OutputType output;

    for (int i = 0; i < 4; i++)
    {
        float3 vposition = quad_position[i] * vertexScale[i];
        vposition = mul(vposition, (float3x3) worldMatrix) + input[0].position;
        output.position = mul(float4(vposition, 1.0), viewMatrix);
        output.position = mul(output.position, projectionMatrix);

        output.tex = input[0].tex;
        output.normal = input[0].normal;

        triStream.Append(output);
    }
    return output;
}
[maxvertexcount(4)]
void main(triangle InputType input[3], inout TriangleStream<OutputType> triStream)
{
    OutputType output;

 
    for (int i = 0; i < 3; i++)
    {
        float4 normal = float4(((input[0].normal + input[1].normal + input[2].normal) / 3),0);

        float3 vposition = input[i].position;;

         
        float length = sqrt(vposition.x * vposition.x + vposition.z * vposition.z + vposition.y * vposition.y);
   
        float scalex = 2.0 + 1.0 * cos(time * 2.0 + length);
         float scaley = 2.0 + 1.0 * sin(time * 2.0 + length);
  

        input[i].position += normal * explosiveAmmount;
        vposition = mul(input[i].position.xyz, (float3x3) worldMatrix);
        output.position = mul(float4(vposition, 1.0), viewMatrix);
        output.position = mul(output.position, projectionMatrix);

        output.tex = input[i].tex;
        output.normal = input[i].normal;

        triStream.Append(output);
    }
     




}


