
#include "egen/window/details/GlfwConverters.hpp"
#include <GLFW/glfw3.h>

namespace egen::details {

Keyboard::Key convert_key(int key)
{
	switch (key) {
		case GLFW_KEY_A: return Keyboard::A;
		case GLFW_KEY_B: return Keyboard::B;
		case GLFW_KEY_C: return Keyboard::C;
		case GLFW_KEY_D: return Keyboard::D;
		case GLFW_KEY_E: return Keyboard::E;
		case GLFW_KEY_F: return Keyboard::F;
		case GLFW_KEY_G: return Keyboard::G;
		case GLFW_KEY_H: return Keyboard::H;
		case GLFW_KEY_I: return Keyboard::I;
		case GLFW_KEY_J: return Keyboard::J;
		case GLFW_KEY_K: return Keyboard::K;
		case GLFW_KEY_L: return Keyboard::L;
		case GLFW_KEY_M: return Keyboard::M;
		case GLFW_KEY_N: return Keyboard::N;
		case GLFW_KEY_O: return Keyboard::O;
		case GLFW_KEY_P: return Keyboard::P;
		case GLFW_KEY_Q: return Keyboard::Q;
		case GLFW_KEY_R: return Keyboard::R;
		case GLFW_KEY_S: return Keyboard::S;
		case GLFW_KEY_T: return Keyboard::T;
		case GLFW_KEY_U: return Keyboard::U;
		case GLFW_KEY_V: return Keyboard::V;
		case GLFW_KEY_W: return Keyboard::W;
		case GLFW_KEY_X: return Keyboard::X;
		case GLFW_KEY_Y: return Keyboard::Y;
		case GLFW_KEY_Z: return Keyboard::Z;

		case GLFW_KEY_0: return Keyboard::Num0;
		case GLFW_KEY_1: return Keyboard::Num1;
		case GLFW_KEY_2: return Keyboard::Num2;
		case GLFW_KEY_3: return Keyboard::Num3;
		case GLFW_KEY_4: return Keyboard::Num4;
		case GLFW_KEY_5: return Keyboard::Num5;
		case GLFW_KEY_6: return Keyboard::Num6;
		case GLFW_KEY_7: return Keyboard::Num7;
		case GLFW_KEY_8: return Keyboard::Num8;
		case GLFW_KEY_9: return Keyboard::Num9;

		case GLFW_KEY_F1: return Keyboard::F1;
		case GLFW_KEY_F2: return Keyboard::F2;
		case GLFW_KEY_F3: return Keyboard::F3;
		case GLFW_KEY_F4: return Keyboard::F4;
		case GLFW_KEY_F5: return Keyboard::F5;
		case GLFW_KEY_F6: return Keyboard::F6;
		case GLFW_KEY_F7: return Keyboard::F7;
		case GLFW_KEY_F8: return Keyboard::F8;
		case GLFW_KEY_F9: return Keyboard::F9;
		case GLFW_KEY_F10: return Keyboard::F10;
		case GLFW_KEY_F11: return Keyboard::F11;
		case GLFW_KEY_F12: return Keyboard::F12;

		case GLFW_KEY_UP: return Keyboard::Up;
		case GLFW_KEY_DOWN: return Keyboard::Down;
		case GLFW_KEY_LEFT: return Keyboard::Left;
		case GLFW_KEY_RIGHT: return Keyboard::Right;

		case GLFW_KEY_LEFT_SHIFT:
		case GLFW_KEY_RIGHT_SHIFT: return Keyboard::Shift;
		case GLFW_KEY_LEFT_CONTROL:
		case GLFW_KEY_RIGHT_CONTROL: return Keyboard::Control;
		case GLFW_KEY_LEFT_ALT:
		case GLFW_KEY_RIGHT_ALT: return Keyboard::Alt;
		case GLFW_KEY_LEFT_SUPER:
		case GLFW_KEY_RIGHT_SUPER: return Keyboard::Super;

		case GLFW_KEY_SPACE: return Keyboard::Space;
		case GLFW_KEY_ENTER: return Keyboard::Enter;
		case GLFW_KEY_ESCAPE: return Keyboard::Escape;
		case GLFW_KEY_TAB: return Keyboard::Tab;
		case GLFW_KEY_BACKSPACE: return Keyboard::Backspace;
		case GLFW_KEY_DELETE: return Keyboard::Delete;
		case GLFW_KEY_INSERT: return Keyboard::Insert;
		case GLFW_KEY_HOME: return Keyboard::Home;
		case GLFW_KEY_END: return Keyboard::End;
		case GLFW_KEY_PAGE_UP: return Keyboard::PageUp;
		case GLFW_KEY_PAGE_DOWN: return Keyboard::PageDown;

		case GLFW_KEY_COMMA: return Keyboard::Comma;
		case GLFW_KEY_PERIOD: return Keyboard::Period;
		case GLFW_KEY_SLASH: return Keyboard::Slash;
		case GLFW_KEY_SEMICOLON: return Keyboard::Semicolon;
		case GLFW_KEY_APOSTROPHE: return Keyboard::Apostrophe;
		case GLFW_KEY_LEFT_BRACKET: return Keyboard::LeftBracket;
		case GLFW_KEY_RIGHT_BRACKET: return Keyboard::RightBracket;
		case GLFW_KEY_BACKSLASH: return Keyboard::Backslash;
		case GLFW_KEY_MINUS: return Keyboard::Minus;
		case GLFW_KEY_EQUAL: return Keyboard::Equal;

		case GLFW_KEY_KP_0: return Keyboard::NumPad0;
		case GLFW_KEY_KP_1: return Keyboard::NumPad1;
		case GLFW_KEY_KP_2: return Keyboard::NumPad2;
		case GLFW_KEY_KP_3: return Keyboard::NumPad3;
		case GLFW_KEY_KP_4: return Keyboard::NumPad4;
		case GLFW_KEY_KP_5: return Keyboard::NumPad5;
		case GLFW_KEY_KP_6: return Keyboard::NumPad6;
		case GLFW_KEY_KP_7: return Keyboard::NumPad7;
		case GLFW_KEY_KP_8: return Keyboard::NumPad8;
		case GLFW_KEY_KP_9: return Keyboard::NumPad9;
		case GLFW_KEY_KP_DECIMAL: return Keyboard::NumPadDecimal;
		case GLFW_KEY_KP_ENTER: return Keyboard::NumPadEnter;
		case GLFW_KEY_KP_ADD: return Keyboard::NumPadAdd;
		case GLFW_KEY_KP_SUBTRACT: return Keyboard::NumPadSubtract;
		case GLFW_KEY_KP_MULTIPLY: return Keyboard::NumPadMultiply;
		case GLFW_KEY_KP_DIVIDE: return Keyboard::NumPadDivide;

		case GLFW_KEY_CAPS_LOCK: return Keyboard::CapsLock;
		case GLFW_KEY_SCROLL_LOCK: return Keyboard::ScrollLock;
		case GLFW_KEY_PAUSE: return Keyboard::Pause;
		case GLFW_KEY_PRINT_SCREEN: return Keyboard::PrintScreen;

		default: return Keyboard::KeyUnknown;
	}
}

int convert_key(Keyboard::Key key)
{
	switch (key) {
		case Keyboard::A: return GLFW_KEY_A;
		case Keyboard::B: return GLFW_KEY_B;
		case Keyboard::C: return GLFW_KEY_C;
		case Keyboard::D: return GLFW_KEY_D;
		case Keyboard::E: return GLFW_KEY_E;
		case Keyboard::F: return GLFW_KEY_F;
		case Keyboard::G: return GLFW_KEY_G;
		case Keyboard::H: return GLFW_KEY_H;
		case Keyboard::I: return GLFW_KEY_I;
		case Keyboard::J: return GLFW_KEY_J;
		case Keyboard::K: return GLFW_KEY_K;
		case Keyboard::L: return GLFW_KEY_L;
		case Keyboard::M: return GLFW_KEY_M;
		case Keyboard::N: return GLFW_KEY_N;
		case Keyboard::O: return GLFW_KEY_O;
		case Keyboard::P: return GLFW_KEY_P;
		case Keyboard::Q: return GLFW_KEY_Q;
		case Keyboard::R: return GLFW_KEY_R;
		case Keyboard::S: return GLFW_KEY_S;
		case Keyboard::T: return GLFW_KEY_T;
		case Keyboard::U: return GLFW_KEY_U;
		case Keyboard::V: return GLFW_KEY_V;
		case Keyboard::W: return GLFW_KEY_W;
		case Keyboard::X: return GLFW_KEY_X;
		case Keyboard::Y: return GLFW_KEY_Y;
		case Keyboard::Z: return GLFW_KEY_Z;

		case Keyboard::Num0: return GLFW_KEY_0;
		case Keyboard::Num1: return GLFW_KEY_1;
		case Keyboard::Num2: return GLFW_KEY_2;
		case Keyboard::Num3: return GLFW_KEY_3;
		case Keyboard::Num4: return GLFW_KEY_4;
		case Keyboard::Num5: return GLFW_KEY_5;
		case Keyboard::Num6: return GLFW_KEY_6;
		case Keyboard::Num7: return GLFW_KEY_7;
		case Keyboard::Num8: return GLFW_KEY_8;
		case Keyboard::Num9: return GLFW_KEY_9;

		case Keyboard::F1: return GLFW_KEY_F1;
		case Keyboard::F2: return GLFW_KEY_F2;
		case Keyboard::F3: return GLFW_KEY_F3;
		case Keyboard::F4: return GLFW_KEY_F4;
		case Keyboard::F5: return GLFW_KEY_F5;
		case Keyboard::F6: return GLFW_KEY_F6;
		case Keyboard::F7: return GLFW_KEY_F7;
		case Keyboard::F8: return GLFW_KEY_F8;
		case Keyboard::F9: return GLFW_KEY_F9;
		case Keyboard::F10: return GLFW_KEY_F10;
		case Keyboard::F11: return GLFW_KEY_F11;
		case Keyboard::F12: return GLFW_KEY_F12;

		case Keyboard::Up: return GLFW_KEY_UP;
		case Keyboard::Down: return GLFW_KEY_DOWN;
		case Keyboard::Left: return GLFW_KEY_LEFT;
		case Keyboard::Right: return GLFW_KEY_RIGHT;

		case Keyboard::Shift: return GLFW_KEY_LEFT_SHIFT;
		case Keyboard::Control: return GLFW_KEY_LEFT_CONTROL;
		case Keyboard::Alt: return GLFW_KEY_LEFT_ALT;
		case Keyboard::Super: return GLFW_KEY_LEFT_SUPER;

		case Keyboard::Space: return GLFW_KEY_SPACE;
		case Keyboard::Enter: return GLFW_KEY_ENTER;
		case Keyboard::Escape: return GLFW_KEY_ESCAPE;
		case Keyboard::Tab: return GLFW_KEY_TAB;
		case Keyboard::Backspace: return GLFW_KEY_BACKSPACE;
		case Keyboard::Delete: return GLFW_KEY_DELETE;
		case Keyboard::Insert: return GLFW_KEY_INSERT;
		case Keyboard::Home: return GLFW_KEY_HOME;
		case Keyboard::End: return GLFW_KEY_END;
		case Keyboard::PageUp: return GLFW_KEY_PAGE_UP;
		case Keyboard::PageDown: return GLFW_KEY_PAGE_DOWN;

		case Keyboard::Comma: return GLFW_KEY_COMMA;
		case Keyboard::Period: return GLFW_KEY_PERIOD;
		case Keyboard::Slash: return GLFW_KEY_SLASH;
		case Keyboard::Semicolon: return GLFW_KEY_SEMICOLON;
		case Keyboard::Apostrophe: return GLFW_KEY_APOSTROPHE;
		case Keyboard::LeftBracket: return GLFW_KEY_LEFT_BRACKET;
		case Keyboard::RightBracket: return GLFW_KEY_RIGHT_BRACKET;
		case Keyboard::Backslash: return GLFW_KEY_BACKSLASH;
		case Keyboard::Minus: return GLFW_KEY_MINUS;
		case Keyboard::Equal: return GLFW_KEY_EQUAL;

		case Keyboard::NumPad0: return GLFW_KEY_KP_0;
		case Keyboard::NumPad1: return GLFW_KEY_KP_1;
		case Keyboard::NumPad2: return GLFW_KEY_KP_2;
		case Keyboard::NumPad3: return GLFW_KEY_KP_3;
		case Keyboard::NumPad4: return GLFW_KEY_KP_4;
		case Keyboard::NumPad5: return GLFW_KEY_KP_5;
		case Keyboard::NumPad6: return GLFW_KEY_KP_6;
		case Keyboard::NumPad7: return GLFW_KEY_KP_7;
		case Keyboard::NumPad8: return GLFW_KEY_KP_8;
		case Keyboard::NumPad9: return GLFW_KEY_KP_9;
		case Keyboard::NumPadDecimal: return GLFW_KEY_KP_DECIMAL;
		case Keyboard::NumPadEnter: return GLFW_KEY_KP_ENTER;
		case Keyboard::NumPadAdd: return GLFW_KEY_KP_ADD;
		case Keyboard::NumPadSubtract: return GLFW_KEY_KP_SUBTRACT;
		case Keyboard::NumPadMultiply: return GLFW_KEY_KP_MULTIPLY;
		case Keyboard::NumPadDivide: return GLFW_KEY_KP_DIVIDE;

		case Keyboard::CapsLock: return GLFW_KEY_CAPS_LOCK;
		case Keyboard::ScrollLock: return GLFW_KEY_SCROLL_LOCK;
		case Keyboard::Pause: return GLFW_KEY_PAUSE;
		case Keyboard::PrintScreen: return GLFW_KEY_PRINT_SCREEN;

		default: return GLFW_KEY_UNKNOWN;
	}
}

Keyboard::Action convert_action(int action)
{
	switch (action) {
		case GLFW_PRESS: return Keyboard::Press;
		case GLFW_RELEASE: return Keyboard::Relase;
		default: return Keyboard::Relase;
	}
}

Keyboard::Mods convert_mods(int mods)
{
	Keyboard::Mods result;
	if (mods & GLFW_MOD_SHIFT) result.set(Keyboard::Mods::Shift);
	if (mods & GLFW_MOD_CONTROL) result.set(Keyboard::Mods::Control);
	if (mods & GLFW_MOD_ALT) result.set(Keyboard::Mods::Alt);
	if (mods & GLFW_MOD_SUPER) result.set(Keyboard::Mods::Super);
	if (mods & GLFW_MOD_CAPS_LOCK) result.set(Keyboard::Mods::CapsLock);
	if (mods & GLFW_MOD_NUM_LOCK) result.set(Keyboard::Mods::NumLoc);
	return result;
}

} // namespace egen::details