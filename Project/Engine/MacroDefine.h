#pragma once

//MessageBox(hWnd, L"Failed to create device", L"Error", MB_OK);
#define ASSERT(expression, message) assert(expression && message)
#define MSANDASSERT(hWnd, expression, message) MessageBox(hWnd, message, L"Error", MB_OK); assert(false);