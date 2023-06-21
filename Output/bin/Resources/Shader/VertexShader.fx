#include "Header//Struct.fx"
#include "Header//ConstantBuffer.fx"

tVSOut main(tVSIn In)
{
	tVSOut Out = (tVSOut) 0.0f;
    
	float4 world = mul(float4(In.Pos, 1.0f), cbWorld);	
    //float4 view = mul(world, mView);
    //float4 proj = mul(view, mProjection);
    
	Out.Pos = world;
	Out.UV = In.UV;
	Out.Color = In.Color;
    
	return Out;
}
