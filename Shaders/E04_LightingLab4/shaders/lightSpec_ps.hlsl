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
	float3 position;
	float padding;

	float constantAttenuationFactor;
	float linearAttenuationFactor;
	float quadraticAttenuationFactor;
	float range;
};

struct InputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
	float3 viewDirection : TEXCOORD1;
	float3 position3D : TEXCOORD2;

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
	float attenuation;
	float distance;

	// set colour to default ambient colour
	colour = ambientColour;

    // Sample the pixel color from the texture using the sampler at this texture coordinate location.
	textureColour = shaderTexture.Sample(SampleType, input.tex);


	distance = length(input.position3D - position);

		if (distance < range)
		{	

			// Invert the light direction for calculations.
			lightDir = normalize(input.position3D - position);

			// Calculate the amount of light on this pixel.
			lightIntensity = saturate(dot(input.normal, -lightDir));




			if (lightIntensity > 0.0f)
			{
				// Work out the attenation value
				attenuation = 1 / (constantAttenuationFactor +
					linearAttenuationFactor * distance + pow(quadraticAttenuationFactor, 2));


					
					colour += (diffuseColour * lightIntensity);

				colour = colour * attenuation;

				colour = saturate(colour);

				// Calculate reflection vector based on the light intensity, normal vector and light direction
				reflection = reflect(lightDir, input.normal);

				// Determine the amount of specular light based on the reflection vector, viewing direction, and specular power.
				specular = pow(saturate(dot(reflection, input.viewDirection)), specularPower);

				//sum up specular light
				finalSpec = specularColour * specular;

				// Add the specular component last to the output colour.
				colour = saturate(colour + finalSpec);
			}
		}
	// Multiply the texture pixel and the final diffuse color to get the final pixel color result.
	colour = colour * textureColour;



    return colour;
}

