#pragma once

#include "egen/input/Keyboard.hpp"

namespace egen::details
{
    Keyboard::Key convert_key(int key);
    int convert_key(Keyboard::Key);

    Keyboard::Action convert_action(int action);

    Keyboard::Mods convert_mods(int mods);
}
