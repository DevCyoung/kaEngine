#include "Header//Struct.fx"
#include "Header//Sampler.fx"
#include "Header//Texture.fx"

float4 main(tVSOut In) : SV_TARGET
{    
	float4 color = (float) 0.0f;
	color = MeshRenderer00.Sample(pointSampler, In.UV);

	return color;
}


