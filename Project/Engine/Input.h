#pragma once
#include "Engine.h"

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

	class Input
	{
	private:
		Input();
        virtual ~Input();

	public:
		struct Key
		{
			eKeyCode key;
			eKeyState state;
			bool bPressed;
		};

		static void Initialize();
		static void Update();
		static void Render();

		static eKeyState GetKeyState(const eKeyCode key)
		{
			return mKeys[static_cast<UINT>(key)].state;
		};

		static bool GetKey(const eKeyCode key)
		{
			return mKeys[static_cast<UINT>(key)].state == eKeyState::Pressed;
		}

		static bool GetKeyDown(const eKeyCode key)
		{
            return mKeys[static_cast<UINT>(key)].state == eKeyState::Down;
        };

		static bool GetKeyUp(const eKeyCode key)
		{
			return mKeys[static_cast<UINT>(key)].state == eKeyState::Up;
		};

	private:
		static std::vector<Key> mKeys;
		static ya::math::Vector2 mMousePos;
    };
};
