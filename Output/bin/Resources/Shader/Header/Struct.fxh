#ifndef STRUCT_FXH
#define STRUCT_FXH

struct tVSIn
{
	float3 Pos : POSITION;
	float4 Color : COLOR;
	float2 UV : TEXCOORD;	
};

struct tVSOut
{
	float4 Pos : SV_Position;
	float4 Color : COLOR;
	float2 UV : TEXCOORD;	
};

#endif