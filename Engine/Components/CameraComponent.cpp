#include "CameraComponent.h" 
#include "Framework/Actor.h" 
#include "Engine.h" 

namespace c14
{
	void CameraComponent::Update()
	{
		m_view = glm::lookAt(m_owner->m_transform.position, m_owner -> m_transform.position + m_owner->m_transform.getForward(), glm::vec3{ 0, 1, 0 });
	}

	void CameraComponent::SetProgram(std::shared_ptr<Program> program)
	{
		program->Use();
		program->SetUniform("view", m_view);
		program->SetUniform("projection", m_projection);
	}

	void CameraComponent::SetPerspective(float fov, float aspectRatio, float near,
		float far)
	{

		m_projection = glm::perspective(glm::radians(fov), aspectRatio, near, far);
	}

	bool CameraComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool CameraComponent::Read(const rapidjson::Value& value)
	{
		float fov;
		READ_DATA(value, fov);
		float aspect_ratio;
		if (!READ_DATA(value, aspect_ratio))
		{

			aspect_ratio = g_renderer.GetWidth() / (float(g_renderer.GetHeight()));

		}
		float near;
		READ_DATA(value, near);
		float far;
		READ_DATA(value, far);

		SetPerspective(fov, aspect_ratio, near, far);

		return true;
	}
}