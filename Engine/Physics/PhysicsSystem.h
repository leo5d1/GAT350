#pragma once
#include "Math/Vector2.h"
#include "box2d/box2d.h"
#include "ContactListener.h"
#include <memory>

#define VECTOR2_TO_B2VEC2(vec) (*(b2Vec2*)(&vec))
#define B2VEC2_TO_VECTOR2(vec) (*(c14::Vector2*)(&vec))

namespace c14
{
	class PhysicsSystem
	{
	public:
		struct RigidBodyData
		{
			float gravity_scale = 1.0f;
			bool constrain_angle = false;
			bool is_dynamic = true;
		};
		struct CollisionData
		{
			Vector2 size;
			float density = 1;
			float friction = 1;
			float restitution = 0.3f;
			bool is_trigger = false;
		};

	public:
		PhysicsSystem() = default;
		~PhysicsSystem() = default;

		void Initialize();
		void Shutdown();

		void Update();

		b2Body* CreateBody(const Vector2& position, float angle, const RigidBodyData& data);
		void DestroyBody(b2Body* body);

		void SetCollisionBox(b2Body* body, const CollisionData& data, class Actor* actor = nullptr);
		void SetCollisionBoxStatic(b2Body* body, const CollisionData& data, class Actor* actor = nullptr);

		static Vector2 WorldToScreen(const Vector2& world) { return world * pixelsPerUnit; }
		static Vector2 ScreenToWorld(const Vector2& screen) { return screen * (1.0f / pixelsPerUnit); }

	private:
		static const float pixelsPerUnit;

		std::unique_ptr<b2World> m_world;
		std::unique_ptr<ContactListener> m_contactListener;
	};
}