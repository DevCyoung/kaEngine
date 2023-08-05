#ifndef CONSTANT_BUFFER_FXH
#define CONSTANT_BUFFER_FXH

cbuffer Transform : register(b0)
{
	row_major matrix B0_World;
	row_major matrix B0_View;
	row_major matrix B0_Projection;
}

cbuffer ColorInfo : register(b1)
{
	int B1_bUseColor;
	int B1_ColorType;
	float2 B1_dummy;	
	float4 B1_cbColor;
}

cbuffer DebugInfo : register(b2)
{
	float3 B2_MousePos;
	float B2_GridDummy;
	float2 B2_Scale;
	int2 B2_XYCount;
	
	float4 B2_Color_0;
	float4 B2_Color_1;
	float4 B2_Color_2;
	float4 B2_Color_3;
	
	float4 B2_Vector4_0;
	float4 B2_Vector4_1;
	float4 B2_Vector4_2;
	float4 B2_Vector4_3;
}

cbuffer Animation2DInfo : register(b3)
{
	float2 B3_UVBackLeftTop;
	float2 B3_UVBackSIze;

	float2 B3_UVLeftTop;
	float2 B3_UVSize;

	float2 B3_UVOffset;
	float2 B3_Dummy;
}

cbuffer GLOBAL : register(b4)
{
	float2 B4_Resolution;
	float B4_DT;
	float B4_GlobalTime;
	float B4_AccTime;
	uint B4_Light2DCount;
	uint B4_Light3DCount;
	int B4_globalpadding;
}

#endif
