#include "Header//Struct.fxh"
#include "Header//ConstantBuffer.fxh"
#include "Header//TestShaderHeader.fxh"


tVSOut main(tVSIn In)
{
	tVSOut Out = (tVSOut) 0.0f;
    
	float4 world = mul(float4(In.Pos, 1.0f), cbWorld);
	float4 view = mul(world, cbView);
	float4 proj = mul(view, cbProjection);
    
	Out.Pos = proj;
	Out.UV = In.UV;
	Out.Color = In.Color;
	
	
	return Out;
}