#include "input.h"

void SetKeyDown(Keyboard* keyboard, uint32_t scancode)
{
    keyboard->keystates[scancode].keyDown = true;
    keyboard->keystates[scancode].keyUp   = false;
}

void SetKeyUp(Keyboard* keyboard, uint32_t scancode)
{
    keyboard->keystates[scancode].keyDown = false;
    keyboard->keystates[scancode].keyUp   = true;
}

bool KeyDown(Keyboard* keyboard, uint32_t scancode)
{
    if(keyboard->keystates[scancode].keyDown)
    {
        return true;
    }
    return false;
}

bool KeyUp(Keyboard* keyboard, uint32_t scancode)
{
    if(keyboard->keystates[scancode].keyUp)
    {
        keyboard->keystates[scancode].keyUp = false;
        return true; 
    }
    return false;
}

bool CheckForConectedControllers()
{
    DWORD dwResult;
    for(DWORD i = 0; i < XUSER_MAX_COUNT; i++)
    {
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));
        dwResult = XInputGetState(i, &state);
        if(dwResult == ERROR_SUCCESS)
        {
            return true;
        }
    }
    return false;
}


void ProcessXinput(Controller* controller)
{
    DWORD dwResult;
    for(DWORD i = 0; i < XUSER_MAX_COUNT; i++)
    {
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));
        dwResult = XInputGetState(i, &state);
        if(dwResult == ERROR_SUCCESS)
        {
            XINPUT_GAMEPAD* pad = &state.Gamepad;
            controller->up = (pad->wButtons & XINPUT_GAMEPAD_DPAD_UP);
            controller->down = (pad->wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
            controller->left = (pad->wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
            controller->right = (pad->wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
            controller->A = (pad->wButtons & XINPUT_GAMEPAD_A);
            controller->B = (pad->wButtons & XINPUT_GAMEPAD_B);
            controller->X = (pad->wButtons & XINPUT_GAMEPAD_X);
            controller->Y = (pad->wButtons & XINPUT_GAMEPAD_Y);
            controller->thumbLX = pad->sThumbLX;
            controller->thumbLY = pad->sThumbLY;
            controller->thumbRX = pad->sThumbRX;
            controller->thumbRY = pad->sThumbRY; 
        }
    }
}
