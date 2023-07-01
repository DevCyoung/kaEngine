#include "Header//Struct.fxh"
#include "Header//Sampler.fxh"
#include "Header//Texture.fxh"
#include "Header//ConstantBuffer.fxh"

float4 main(tVSOut In) : SV_TARGET
{
	float4 color = (float) 0.0f;
	color = MeshRenderer00.Sample(pointSampler, In.UV);	
	
	if (color.r == 1.0f && color.g == 0.0f && color.b == 1.0f)
	{
		discard;
	}
	
	//if (color.r == 0.0f && color.g == 0.0f && color.b == 0.0f && color.a == 1.0f)
	//{
	//	discard;		
	//}
	
	return color;
}
