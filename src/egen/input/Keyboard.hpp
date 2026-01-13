#pragma once

#include <cstdint>

namespace egen
{

namespace Keyboard
{
    enum Key
    {
        // Letters
        A, B, C, D, E, F, G, H, I, J, K, L, M,
        N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

        // Numbers
        Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,

        // Function keys
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,

        // Arrow keys
        Up, Down, Left, Right,

        // Modifiers
        Shift, Control, Alt, Super,

        // Other common keys
        Space, Enter, Escape, Tab, Backspace, Delete, Insert,
        Home, End, PageUp, PageDown,

        // Punctuation
        Comma, Period, Slash, Semicolon, Apostrophe, LeftBracket, RightBracket, Backslash, Minus, Equal,

        // Numpad
        NumPad0, NumPad1, NumPad2, NumPad3, NumPad4, NumPad5, NumPad6, NumPad7, NumPad8, NumPad9,
        NumPadDecimal, NumPadEnter, NumPadAdd, NumPadSubtract, NumPadMultiply, NumPadDivide,

        // Misc
        CapsLock, ScrollLock, Pause, PrintScreen,

        // Unknown
        KeyUnknown
    };

    enum Action
    {
        Press,
        Relase
    };

    class Mods
    {
    public:
        enum Mod
        {
            Shift = 0,
            Control,
            Alt,
            Super,
            CapsLock,
            NumLoc,
        };

        void set(Mod mod)
        {
            mods[mod] = 0x1;
        }

        void clear(Mod mod)
        {
            mods[mod] = 0x0;
        }

        bool is_set(Mod mod)
        {
            return static_cast<bool>(mods[mod]);
        }

    private:
        uint8_t mods[6];
    };


};

}