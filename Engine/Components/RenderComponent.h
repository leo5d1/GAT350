#pragma once
#include "Framework/Component.h"
#include "Math/Rect.h"
#include "Math//Vector2.h"

namespace c14
{
	class Renderer;

	class RenderComponent : public Component
	{
	public:
		virtual void Draw(Renderer& renderer) = 0;

		virtual Rect& GetSource() { return source; }
		void SetFlipHorizontal(bool flip = true) { flipHorizontal = flip; }
		bool GetFlipHorizontal() { return flipHorizontal; }

	protected:
		Rect source;
		Vector2 registration = Vector2{ 0.5f, 0.5f };
		bool flipHorizontal = false;
	};
}
