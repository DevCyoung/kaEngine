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
	
	int B1_bSetColorR;
	float B1_R;
	int B1_bSetColorG;
	float B1_G;
	int B1_bSetColorB;
	float B1_B;
	int B1_bSetColorA;
	float B1_A;
	
	
	int B1_bMulColorR;
	float B1_MulR;
	int B1_bMulColorG;
	float B1_MulG;
	int B1_bMulColorB;
	float B1_MulB;
	int B1_bMulColorA;
	float B1_MulA;
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

cbuffer Sprite2D : register(b5)
{
	float2 B5_Dummy;	
	float2 B5_SpriteUV;
	
	int B5_bSetColorR;
	float B5_R;
	int B5_bSetColorG;
	float B5_G;
	int B5_bSetColorB;
	float B5_B;
	int B5_bSetColorA;
	float B5_A;
	
	
	int B5_bMulColorR;
	float B5_MulR;
	int B5_bMulColorG;
	float B5_MulG;
	int B5_bMulColorB;
	float B5_MulB;
	int B5_bMulColorA;
	float B5_MulA;
}

cbuffer Wave : register(b6)
{
	float B6_WaveXPower;	
	float B6_WaveYPower;
	float B6_WaveSpeed;
	float B6_dummy1;
}

#endif
