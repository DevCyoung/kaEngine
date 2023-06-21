#ifndef CONSTANT_BUFFER_FX
#define CONSTANT_BUFFER_FX

cbuffer Transform : register(b0)
{
	row_major matrix cbWorld;
	row_major matrix cbView;
	row_major matrix cbProjection;
}

#endif
