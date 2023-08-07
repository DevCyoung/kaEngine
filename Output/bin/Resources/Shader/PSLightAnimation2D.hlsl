#include "Header//Struct.fxh"
#include "Header//Sampler.fxh"
#include "Header//Texture.fxh"
#include "Header//ConstantBuffer.fxh"
#include "Light2D.hlsl"

float4 main(tVSLightOut In) : SV_TARGET
{
	float4 outColor = In.Color;
	
	float2 UV = B3_UVBackLeftTop + In.vUV * B3_UVBackSIze;
	
	UV.x -= B3_UVOffset.x;
	UV.y += B3_UVOffset.y;
	
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
	
	//outColor.r = 0.f;
	//outColor.b = 0.f;
	//outColor.g = 0.f;
	
	if (B1_bUseColor == 1)
	{
		float src = 0.7f;
		float dst = 1.f - src;
		
		outColor.r = 0.0f;
		outColor.g = outColor.g + outColor.g * src + 1.f * dst;		
		outColor.b = outColor.b + outColor.b * src + 1.f * dst;
		outColor.a = B1_cbColor.a;		
	}
	
	
	//outColor.rgb *= (float3(1.f, 1.f, 1.f) * 5.f);
	
	// Lighting Ã³¸®
	tLightColor LightColor = (tLightColor) 0.f;
    
	CalcLight2D(In.vWorldPos, LightColor);
        
	outColor.rgb *= (LightColor.vDiffuse.rgb + LightColor.vAmbient.rgb);
	return outColor;
}