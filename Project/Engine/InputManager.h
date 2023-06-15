#pragma once
#include "Singleton.h"

namespace engine
{	
	enum class eKeyCode
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,

		UP, DOWN, LEFT, RIGHT, SPACE,
		LBUTTON, RBUTTON,
		END,
	};

	enum class eKeyState
	{
		Down,
		Pressed,
		Up,
		None,
	};

	class InputManager
	{	
		friend class Engine;
		SINGLETON_DECLARE(InputManager);
	public:
		eKeyState GetKeyState(const eKeyCode key)
		{
			return mKeyInfos[static_cast<UINT>(key)].state;
		};

		bool GetKey(const eKeyCode key)
		{
			return mKeyInfos[static_cast<UINT>(key)].state == eKeyState::Pressed;
		}

		bool GetKeyDown(const eKeyCode key)
		{
            return mKeyInfos[static_cast<UINT>(key)].state == eKeyState::Down;
        };

		bool GetKeyUp(const eKeyCode key)
		{
			return mKeyInfos[static_cast<UINT>(key)].state == eKeyState::Up;
		};

		Vector2 GetMousePos()
		{
			return mMousePos;
		}

	private:
		struct tKeyInfo
		{
			eKeyCode key;
			eKeyState state;
			bool bPressed;
		};
		void update(const HWND hWnd);

	private:
		std::vector<tKeyInfo> mKeyInfos;
		Vector2 mMousePos;
    };
};

#define gInput engine::InputManager::GetInstance()
