#ifndef INPUT_H
#define INPUT_H

#include "utility.h"
#include "stdint.h"
#include "xinput.h"

struct KeyState
{
    bool keyDown;
    bool keyUp;
};

struct Keyboard
{
    KeyState keystates[256];
};

struct Mouse
{
    Vec2 mouseDPos;
    Vec2 mouseRPos;
};

struct Controller
{
    bool up;
    bool down;
    bool left;
    bool right;
    bool A;
    bool B;
    bool X;
    bool Y; 
    int16_t thumbLX;
    int16_t thumbRX;
    int16_t thumbLY;
    int16_t thumbRY;
};

void SetKeyDown(Keyboard* keyboard, uint32_t scancode);
void SetKeyUp(Keyboard* keyboard, uint32_t scancode);
bool KeyDown(Keyboard* keyboard, uint32_t scancode);
bool KeyUp(Keyboard* keyboard, uint32_t scancode);
bool CheckForConectedControllers();
void ProcessXinput(Controller* controller);


#endif
