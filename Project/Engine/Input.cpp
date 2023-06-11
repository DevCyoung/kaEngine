#include "Input.h"
#include "Engine.h"

namespace engine
{    

    using namespace engine::math;

    int ASCII[(UINT)eKeyCode::END] =
    {
        'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
        'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
        'Z', 'X', 'C', 'V', 'B', 'N', 'M',

        VK_UP, VK_DOWN, VK_LEFT ,VK_RIGHT, VK_SPACE,
        VK_LBUTTON, VK_RBUTTON,
    };

    std::vector<Input::Key> Input::mKeys;
    Vector2 Input::mMousePos = Vector2::Zero;

    Input::Input()
    {
    }

    Input::~Input()
    {
    }

    void Input::initialize()
    {
        mKeys.reserve(static_cast<size_t>(eKeyCode::END));

        for (UINT i = 0; i < static_cast<UINT>(eKeyCode::END); i++)
        {
            Key keyInfo = {};

            keyInfo.key = static_cast<eKeyCode>(i);
            keyInfo.state = eKeyState::None;
            keyInfo.bPressed = false;

            mKeys.push_back(keyInfo);
        }
    }

    void Input::update()
    {
        const engine::Engine* const application = engine::Engine::GetInst();        

        if (GetFocus())
        {
            for (UINT i = 0; i < static_cast<UINT>(eKeyCode::END); i++)
            {
                Key& keyInfo = mKeys[i];

                if (GetAsyncKeyState(ASCII[i]) & 0x8000)
                {                  
                    if (keyInfo.bPressed == false)
                    {
                        keyInfo.state = eKeyState::Down;
                        keyInfo.bPressed = true;
                    }
                    else
                    {
                        keyInfo.state = eKeyState::Pressed;
                    }
                }
                else
                {
                    if (keyInfo.bPressed == true)
                    {
                        keyInfo.state = eKeyState::Up;
                        keyInfo.bPressed = false;
                    }
                    else
                    {
                        keyInfo.state = eKeyState::None;
                    }
                }

            }

            POINT mousePos = {};
            GetCursorPos(&mousePos);

            ScreenToClient(application->GetHwnd(), &mousePos);

            mMousePos.x = static_cast<float>(mousePos.x);
            mMousePos.y = static_cast<float>(mousePos.y);
        }
        else
        {
            for (UINT i = 0; i < static_cast<UINT>(eKeyCode::END); i++)
            {
                if (eKeyState::Down == mKeys[i].state || eKeyState::Pressed == mKeys[i].state)
                {
                    mKeys[i].state = eKeyState::Up;
                }
                else if (eKeyState::Up == mKeys[i].state)
                {
                    mKeys[i].state = eKeyState::None;
                }

                mKeys[i].bPressed = false;
            }
        }
    }

    void Input::render()
    {
    }


}