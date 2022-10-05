#pragma once
#include "RenderComponent.h"
#include "Math/Color.h"
#include "Math/Vector2.h"
#include <memory>

namespace c14
{
	class Font;
	class Texture;

	class TextComponent : public RenderComponent
	{
	public:
		CLASS_DECLARATION(TextComponent)

		virtual void Update() override;
		virtual void Draw(Renderer& renderer) override;

		void SetText(const std::string& text);

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		std::string text;
		std::string font_name;
		int font_size;
		Vector2 registration;
		Color color;

		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture> m_texture;
	};
}