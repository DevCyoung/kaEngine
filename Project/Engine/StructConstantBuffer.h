#pragma once

struct alignas(16) tTransform // c0
{
	Matrix mWorld;
	Matrix mView;
	Matrix mProj;
}; // 48 bytes