
Texture2D shaderTexture : register(t0);
Texture2D depthMapTexture : register(t1);

SamplerState SampleTypeWrap  : register(s0);
SamplerState SampleTypeClamp : register(s1);

cbuffer LightBuffer : register(cb0)
{ 
	float4 diffuseColour[4];
	float4 lightDirection[4];
	float4 ambientColour[4];
	float4 specularColour[4];
	float4 position[4];

	float4 specularPower[4];

	// 0 is constant
	// 1 linear
	// 2 quadratic
	// 3 range
	float4 attenuationValues[4];

	//0 - directional
	//1- spot
	//2- point
	int4 lightType[4];

	int isSpecular[4];
};

struct InputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
    float4 lightViewPosition[4] : TEXCOORD1;
	float3 lightPos[4] : TEXCOORD5;
	float3 position3D : TEXCOORD10;
	float3 viewDirection : TEXCOORD11;


};


float4 main(InputType input) : SV_TARGET
{
	float bias;
    float4 color;
	float2 projectTexCoord[4];
	float depthValue;
	float lightDepthValue;
    float lightIntensity;
	float4 textureColor;
	float attenuation;
	float distance;
	float3 lightDir;
	float4 specular;
	float3 reflection;
	float4 finalSpec;

	// Set the bias value for fixing the floating point precision issues.
	bias = 0.0001f;

	// Set the default output color to the ambient light value for all pixels.
	color = ambientColour[0];


	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	textureColor = shaderTexture.Sample(SampleTypeWrap, input.tex);
	
	for (int i = 0; i < 4; i++)
	{
		// Calculate the projected texture coordinates.
		
		projectTexCoord[i].x =  input.lightViewPosition[i].x / input.lightViewPosition[i].w / 2.0f + 0.5f;
		projectTexCoord[i].y = -input.lightViewPosition[i].y / input.lightViewPosition[i].w / 2.0f + 0.5f;


	
		// Determine if the projected coordinates are in the 0 to 1 range.  If so then this pixel is in the view of the light.
		if ((saturate(projectTexCoord[i].x) == projectTexCoord[i].x) && (saturate(projectTexCoord[i].y) == projectTexCoord[i].y))
		{
			// Sample the shadow map depth value from the depth texture using the sampler at the projected texture coordinate location.
			depthValue = depthMapTexture.Sample(SampleTypeClamp, projectTexCoord[i]).r;

			// Calculate the depth of the light.
			lightDepthValue = input.lightViewPosition[i].z / input.lightViewPosition[i].w;

			// Subtract the bias from the lightDepthValue.
			lightDepthValue = lightDepthValue - bias;

			// Compare the depth of the shadow map value and the depth of the light to determine whether to shadow or to light this pixel.
			// If the light is in front of the object then light the pixel, if not then shadow this pixel since an object (occluder) is casting a shadow on it.
			if (lightDepthValue < depthValue)
			{
				// Calculate the amount of light on this pixel.
				lightIntensity = saturate(dot(input.normal, input.lightPos[i]));

				if (lightIntensity > 0.0f)
				{
					// Determine the final diffuse color based on the diffuse color and the amount of light intensity.
					color += (diffuseColour[i] * lightIntensity);

					// Saturate the final light color.
					color = saturate(color);
				}
			}
		}
		else
		{
			distance = length(input.position3D - position[i].xyz);

			if (distance < attenuationValues[i].w || lightType[i].x == 1)
			{
				if (lightType[i].y == 1)
				{
					// Invert the light direction for calculations.
					lightDir = normalize(input.position3D - position[i].xyz);

					// Calculate the amount of light on this pixel.
					lightIntensity = saturate(dot(input.normal, -lightDir));

				}
				else if (lightType[i].x == 1)
				{

					// Invert the light direction for calculations.
					lightDir = -lightDirection[i].xyz;

					// Calculate the amount of light on this pixel.
					lightIntensity = saturate(dot(input.normal, lightDir));
				}



				if (lightIntensity > 0.0f)
				{
					if (lightType[i].y == 1)
					{
						// Work out the attenation value
						attenuation = 1 / (attenuationValues[i].x +
							attenuationValues[i].y * distance + pow(attenuationValues[i].z, 2));
					}


					color += (diffuseColour[i] * lightIntensity);

					if (lightType[i].y == 1)
					{
						color = color * attenuation;
					}
					color = saturate(color);

					if (isSpecular[i] == 1)
					{
						// Calculate reflection vector based on the light intensity, normal vector and light direction
						reflection = reflect(lightDir, input.normal);

						// Determine the amount of specular light based on the reflection vector, viewing direction, and specular power.
						specular = pow(saturate(dot(reflection, input.viewDirection)), specularPower[i]);

						//sum up specular light
						finalSpec = specularColour[i] * specular;

						// Add the specular component last to the output colour.
						color = saturate(color + finalSpec);
					}
				}
			}
		}
	}

	// Combine the light and texture color.
	color = color * textureColor;

    return color;
}