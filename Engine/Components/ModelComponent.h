#pragma once 
#include "RenderComponent.h" 

namespace c14
{
	class Renderer;
	class Model;
	class Material;

	class ModelComponent : public RenderComponent
	{
	public:
		CLASS_DECLARATION(ModelComponent)

		virtual void Update() override {}
		virtual void Draw(Renderer& renderer) override;


		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		std::shared_ptr<Model> model;
		std::shared_ptr<Material> material;
		bool depth_test = true;
	};
}