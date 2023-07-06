#include "Header//Struct.fxh"
#include "Header//Sampler.fxh"
#include "Header//Texture.fxh"
#include "Header//ConstantBuffer.fxh"

#define FILL_COLOR B2_Color_1
#define RECT_SCALE B2_Scale
#define XY_COUNT B2_XYCount
#define MOUSE_POSITION B2_MousePos

float4 main(tVSOut In) : SV_TARGET
{
	float4 color = float4(1.0f, 1.0f, 0.7f, 1.0f);
	
	const int2 NORMAL_XY = int2(In.UV * RECT_SCALE + 1);	
	const int2 WIDTH = int2(RECT_SCALE.xy / XY_COUNT.xy);
	const int2 MOUSE_IDX = int2((MOUSE_POSITION.xy - 1) / WIDTH.xy);
	const int2 GRID_IDX = int2((NORMAL_XY.xy - 1) / WIDTH.xy);

	if (MOUSE_IDX.y == GRID_IDX.y && MOUSE_IDX.x == GRID_IDX.x)
	{
		color = float4(1.0f, 0.0f, 0.f, 0.8f);
	}
	else if (NORMAL_XY.x % WIDTH.x >= 2 && NORMAL_XY.y % WIDTH.y >= 2)
	{
		discard;
	}

	return FILL_COLOR;
	
}
