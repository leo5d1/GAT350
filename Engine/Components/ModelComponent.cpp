#include "ModelComponent.h"
#include "Renderer/Model.h"
#include "Framework/Actor.h"
#include "Engine.h"

namespace c14
{
	void ModelComponent::Update()
	{

	}

	bool ModelComponent::Write(const rapidjson::Value& value) const
	{
		//
		return true;
	}

	bool ModelComponent::Read(const rapidjson::Value& value)
	{
		std::string model_name;
		READ_DATA(value, model_name);

		m_model = g_resources.Get<Model>(model_name);

		return true;
	}

	void ModelComponent::Draw(Renderer& renderer)
	{
		//renderer.Draw(m_texture, m_owner->m_transform);
		m_model->Draw(renderer, m_owner->m_transform);
	}
}
