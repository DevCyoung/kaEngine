#include "Header//Struct.fxh"
#include "Header//Sampler.fxh"
#include "Header//Texture.fxh"

float4 main(tVSOut In) : SV_TARGET
{    
	float4 color = (float) 0.0f;
	color = MeshRenderer00.Sample(samplerState, In.UV);
	return color;
}
