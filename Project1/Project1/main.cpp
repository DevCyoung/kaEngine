#include <iostream>

int main()
{
	int x = 0;
	int* pX = &x;

	int** ppX = &pX;

	int* const const* ccppX = ppX;
	ccppX = ppX;

	int const* const* const cccppX = ccppX;

	return 0;
}