#include "CameraController.h" 
#include "Engine.h" 

namespace c14
{
	void CameraController::Update()
	{
		// update transform 

		if (g_inputSystem.GetKeyState(key_left) == InputSystem::State::Held)
			m_owner->m_transform.position.x -= speed * g_time.deltaTime;

		if (g_inputSystem.GetKeyState(key_right) == InputSystem::State::Held)
			m_owner->m_transform.position.x += speed * g_time.deltaTime;
		if (g_inputSystem.GetKeyState(key_up) == InputSystem::State::Held)
			m_owner->m_transform.position.y += speed * g_time.deltaTime;

		if (g_inputSystem.GetKeyState(key_down) == InputSystem::State::Held)
			m_owner->m_transform.position.y -= speed * g_time.deltaTime;
	}

	bool CameraController::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool CameraController::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, speed);

		return true;
	}

}

