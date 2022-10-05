#pragma once
#include "RenderComponent.h"
#include "Math/Rect.h"
#include "Math/Vector2.h"
#include <vector>

namespace c14
{
	class TilemapComponent : public Component
	{
	public:
		CLASS_DECLARATION(TilemapComponent)

		virtual void Initialize() override;
		virtual void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;


	private:
		int num_columns = 0;
		int num_rows = 0;
		Vector2 size;

		std::vector<std::string> tile_names;
		std::vector<int> tiles;
	};
}