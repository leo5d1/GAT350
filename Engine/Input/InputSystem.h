#pragma once
#include "Math/MathUtils.h"
#include <cstdint>
#include <array>
#include <vector>

namespace c14
{
	class InputSystem
	{
	public:
		enum State
		{
			Idle,
			Pressed,
			Held,
			Released
		};

	public:
		InputSystem() = default;
		~InputSystem() = default;

		void Initialize();
		void Shutdown();

		void Update();

		State GetKeyState(uint32_t key);
		bool GetKeyDown(int key) { return m_keyboardState[key]; }
		bool GetPreviousKeyDown(uint32_t key) { return m_prevKeyboardState[key]; }

		const glm::vec2& GetMousePosition() const { return m_mousePosition; }
		const glm::vec2& GetMouseRelative() const { return m_mouseRelative; }

		State GetButtonState(uint32_t button);
		bool GetButtonDown(uint32_t button) { return m_mouseButtonState[button]; }
		bool GetPreviousButtonDown(uint32_t button) { return m_prevMouseButtonState[button]; }

	private:
		int m_numKeys;

		std::vector<uint8_t> m_keyboardState;
		std::vector<uint8_t> m_prevKeyboardState;

		glm::vec2 m_mousePosition;
		glm::vec2 m_prevMousePosition;
		glm::vec2 m_mouseRelative;

		std::array<uint8_t, 3> m_mouseButtonState;
		std::array<uint8_t, 3> m_prevMouseButtonState;
	};

	extern const uint32_t button_left;
	extern const uint32_t button_middle;
	extern const uint32_t button_right;

	extern const uint32_t key_space;
	extern const uint32_t key_escape;
	extern const uint32_t key_enter;
	extern const uint32_t key_up;
	extern const uint32_t key_down;
	extern const uint32_t key_left;
	extern const uint32_t key_right;

	extern const uint32_t key_w;
	extern const uint32_t key_a;
	extern const uint32_t key_s;
	extern const uint32_t key_d;
	extern const uint32_t key_q;
	extern const uint32_t key_e;
	extern const uint32_t key_LShift;
	extern const uint32_t key_LCtrl;
}
