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

		const Vector2& GetMousePos() const
		{
			return mMousePos;
		}


		void update(const HWND hWnd);

	private:
		std::vector<tKeyInfo> mKeyInfos;
		Vector2 mMousePos;
    };
};

#define gInput engine::InputManager::GetInstance()
