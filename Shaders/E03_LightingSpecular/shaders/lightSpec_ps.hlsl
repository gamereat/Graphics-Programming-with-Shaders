// Light pixel shader
// Calculate diffuse lighting for a single directional light (also texturing)

Texture2D shaderTexture : register(t0);
SamplerState SampleType : register(s0);

cbuffer LightBuffer : register(b0)
{
    float4 diffuseColour;
    float3 lightDirection;
	float specularPower;
	float4  ambientColour;
	float4 specularColour;

};

struct InputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
	float3 viewDirection : TEXCOORD1;

};

float4 main(InputType input) : SV_TARGET
{
	float4 textureColour;
	float3 lightDir;
	float lightIntensity;
	float4 colour;
	float3 reflection;
	float4 specular;
	float4 finalSpec;

	colour = ambientColour;

    // Sample the pixel color from the texture using the sampler at this texture coordinate location.
	textureColour = shaderTexture.Sample(SampleType, input.tex);
	

	// Invert the light direction for calculations.
    lightDir = -lightDirection;

    // Calculate the amount of light on this pixel.
    lightIntensity = saturate(dot(input.normal, lightDir));

	if (specularPower > 0)
	{
		if (lightIntensity > 0)
		{

			colour += (diffuseColour * lightIntensity);
			colour = saturate(colour);


			// Calculate reflection vector based on the light intensity, normal vector and light direction
			reflection = reflect(lightDir, input.normal);

			// Determine the amount of specular light based on the reflection vector, viewing direction, and specular power.
			specular = pow(saturate(dot(reflection, input.viewDirection)), specularPower);

			//sum up specular light
			finalSpec = specularColour * specular;


		}
		// Multiply the texture pixel and the final diffuse color to get the final pixel color result.
		colour = colour * textureColour;

		// Add the specular component last to the output colour.
		colour = saturate(colour + finalSpec);
	}
	else
	{
		// Multiply the texture pixel and the final diffuse color to get the final pixel color result.
		colour = colour * textureColour;

	}
    return colour;
}

