#pragma once
#include "Singleton.h"

class Camera;

enum class eKeyCode
{
	F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
	NUM0, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9,
		
	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, H, J, K, L,
	Z, X, C, V, B, N, M,

	LSHIFT, LCONTROL,

	UP, DOWN, LEFT, RIGHT, SPACE,

	NUMPAD0, NUMPAD1, NUMPAD2, NUMPAD3, NUMPAD4, NUMPAD5, NUMPAD6, NUMPAD7, NUMPAD8, NUMPAD9,

	LBTN, RBTN,

	END
};

class InputManager
{
	friend class Engine;
	SINGLETON_DECLARE(InputManager);
private:
	enum class eKeyState
	{
		Down,
		Pressed,
		Up,
		None,
	};
private:
	struct tKeyInfo
	{
		eKeyCode key;
		eKeyState state;
		bool bPressed;
	};

public:
	eKeyState GetKeyState(const eKeyCode KEY)
	{
		return mKeyInfos[static_cast<UINT>(KEY)].state;
	};

	bool GetKey(const eKeyCode KEY)
	{
		return mKeyInfos[static_cast<UINT>(KEY)].state == eKeyState::Pressed;
	}

	bool GetKeyDown(const eKeyCode KEY)
	{
		return mKeyInfos[static_cast<UINT>(KEY)].state == eKeyState::Down;
	};

	bool GetKeyUp(const eKeyCode KEY)
	{
		return mKeyInfos[static_cast<UINT>(KEY)].state == eKeyState::Up;
	};

	const Vector2& GetWindowMousePos() const
	{
		return mMousePos;
	}

	const Vector2& GetMouseDir() const
	{
		return mMouseDir;
	}

	bool IsWindowMouseHoverd();

private:
	void update(const HWND H_WND);
private:
	std::vector<tKeyInfo> mKeyInfos;
	Vector2 mMousePos;
	Vector2 mPrevMousePos;
	Vector2 mMouseDir;
};

#define gInput InputManager::GetInstance()