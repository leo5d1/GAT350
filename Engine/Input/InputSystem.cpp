#include "InputSystem.h"
#include <SDL.h>
#include <iostream>

namespace c14
{
	const uint32_t key_space = SDL_SCANCODE_SPACE;
	const uint32_t key_up = SDL_SCANCODE_W;
	const uint32_t key_left = SDL_SCANCODE_A;
	const uint32_t key_down = SDL_SCANCODE_S;
	const uint32_t key_right = SDL_SCANCODE_D;
	const uint32_t key_escape = SDL_SCANCODE_ESCAPE;
	const uint32_t key_enter = SDL_SCANCODE_RETURN;
	const uint32_t key_q = SDL_SCANCODE_Q;
	const uint32_t key_e = SDL_SCANCODE_E;

	const uint32_t button_left = 0;
	const uint32_t button_middle = 1;
	const uint32_t button_right = 2;

	void InputSystem::Initialize()
	{
		const uint8_t* keyboardState = SDL_GetKeyboardState(&m_numKeys);

		m_keyboardState.resize(m_numKeys);
		std::copy(keyboardState, keyboardState + m_numKeys, m_keyboardState.begin());

		m_prevKeyboardState = m_keyboardState;
	}

	void InputSystem::Shutdown()
	{
		//
	}

	void InputSystem::Update()
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		//save previous keyboard state
		m_prevKeyboardState = m_keyboardState;

		//get current keyboard state
		const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardState, keyboardState + m_numKeys, m_keyboardState.begin());

		// save prev mouse state
		m_prevMouseButtonState = m_mouseButtonState;

		// get current mouse state
		m_prevMouseButtonState = m_mouseButtonState;
		int x, y;
		uint32_t buttons = SDL_GetMouseState(&x, &y);
		m_mousePosition = c14::Vector2{ x , y };
		m_mouseButtonState[0] = buttons & SDL_BUTTON_LMASK; // buttons [0001] & [0RML] 
		m_mouseButtonState[1] = buttons & SDL_BUTTON_MMASK; // buttons [0010] & [0RML] 
		m_mouseButtonState[2] = buttons & SDL_BUTTON_RMASK; // buttons [0100] & [0RML]

	}

	InputSystem::State InputSystem::GetKeyState(uint32_t key)
	{
		State keyState = State::Idle;

		bool keyDown = GetKeyDown(key);
		bool prevKeyDown = GetPreviousKeyDown(key);

		if (keyDown == true && prevKeyDown == true)
		{
			keyState = State::Held;
		}
		else if (keyDown == true && prevKeyDown == false)
		{
			keyState = State::Pressed;
		}
		else if (keyDown == false && prevKeyDown == true)
		{
			keyState = State::Released;
		}
		else if (keyDown == false && prevKeyDown == false) 
		{
			keyState = State::Idle;
		} 

		return keyState;
	}

	InputSystem::State InputSystem::GetButtonState(uint32_t button)
	{
		State keyState = State::Idle;

		bool keyDown = GetButtonDown(button);
		bool prevKeyDown = GetPreviousButtonDown(button);

		if (keyDown == true && prevKeyDown == true)
		{
			keyState = State::Held;
		}
		else if (keyDown == true && prevKeyDown == false)
		{
			keyState = State::Pressed;
		}
		else if (keyDown == false && prevKeyDown == true)
		{
			keyState = State::Released;
		}
		else if (keyDown == false && prevKeyDown == false)
		{
			keyState = State::Idle;
		}

		return keyState;
	}
}
