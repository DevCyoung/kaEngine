#ifndef CONSTANT_BUFFER_FXH
#define CONSTANT_BUFFER_FXH

cbuffer Transform : register(b0)
{
	row_major matrix cbWorld;
	row_major matrix cbView;
	row_major matrix cbProjection;
}

cbuffer ColorInfo : register(b1)
{
	float4 cbColor;
}

#endif
