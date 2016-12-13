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
    float explosiveAcceleration;

    float maxTime;

    //@DEPECATED
    //just used as padding now 
    float3 explotionMaximums;
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


 
[maxvertexcount(4)]
void main(triangle InputType input[3], inout TriangleStream<OutputType> triStream)
{
    OutputType output;

    float t = time;
    if (time >= maxTime)
    {
        t = maxTime;
    }
    for (int i = 0; i < 3; i++)
    {
        input[i].position.w = 0;
        float4 normal = float4(((input[0].normal + input[1].normal + input[2].normal) / 3), 0);
 
        float3 vposition = input[i].position;;

        float3 explotionForce = normal.xyz *( (0.5 * explosiveAcceleration * t * t) + (explosiveAmmount * t));
        float3 gravityForce = float3(0, 1, 0) * 0.5 * gravity * t ;

        float3 explotionEffect = explotionForce + gravityForce;

      //  input[i].position.xyz += explotionEffect;


          
        input[i].position.xyz += explotionEffect;
      
 
        vposition = mul(input[i].position.xyz, (float3x3) worldMatrix);
        output.position = mul(float4(vposition, 1.0), viewMatrix);
        output.position = mul(output.position, projectionMatrix);

        output.tex = input[i].tex;
        output.normal = input[i].normal;

        triStream.Append(output);
    }
     


}

// x = 1/2 *a * (t*t )+ v*t + x
 


