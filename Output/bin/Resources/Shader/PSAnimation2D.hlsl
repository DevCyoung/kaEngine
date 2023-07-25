#include "Header//Struct.fxh"
#include "Header//Sampler.fxh"
#include "Header//Texture.fxh"
#include "Header//ConstantBuffer.fxh"

float4 main(tVSOut In) : SV_TARGET
{
	float4 outColor = In.Color;	
	
	float2 UV = B3_UVBackLeftTop + In.UV * B3_UVBackSIze;	
	
	if (B3_UVLeftTop.x <= UV.x && UV.x <= B3_UVLeftTop.x + B3_UVSize.x && 
		B3_UVLeftTop.y <= UV.y && UV.y <= B3_UVLeftTop.y + B3_UVSize.y)
	{
		outColor = AtlasAnimation2D.Sample(pointSampler, UV);
								
		if (outColor.a == 0.f)
		{
			discard;
		}						
		else if (outColor.r == 1.f && outColor.g == 0.f && outColor.b == 1.f)
		{
			discard;
		}			
	}
	else
	{
		discard;
	}

	//To Cyan		
	float src = 0.35f;
	float dst = 1.f - src;	
	
	outColor.r  = 0.f;
	outColor.g += outColor.g * src + 1.f * dst;
	outColor.b += outColor.b * src + 1.f * dst;	
	
	return outColor;
}