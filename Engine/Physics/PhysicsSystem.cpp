#include "PhysicsSystem.h"
#include "Math/MathUtils.h"

namespace c14
{
	const float PhysicsSystem::pixelsPerUnit = 48.0f;

	void PhysicsSystem::Initialize()
	{
		b2Vec2 gravity{ 0, 10 };
		m_world = std::make_unique<b2World>(gravity);
		m_contactListener = std::make_unique<ContactListener>();
		m_world->SetContactListener(m_contactListener.get());
	}

	void PhysicsSystem::Shutdown()
	{
	}

	void PhysicsSystem::Update()
	{
		m_world->Step(1.0f / 60.0f, 8, 3);
	}

	b2Body* PhysicsSystem::CreateBody(const Vector2& position, float angle, const RigidBodyData& data)
	{
		Vector2 worldPosition = ScreenToWorld(position);

		b2BodyDef bodyDef;
		bodyDef.type = (data.is_dynamic) ? b2_dynamicBody : b2_staticBody;
		bodyDef.position = *((b2Vec2*)(&worldPosition));
		bodyDef.angle = math::DegToRad(angle);
		bodyDef.fixedRotation = data.constrain_angle;
		b2Body* body = m_world->CreateBody(&bodyDef);

		return body;
	}

	void PhysicsSystem::DestroyBody(b2Body* body)
	{
		m_world->DestroyBody(body);
	}

	void PhysicsSystem::SetCollisionBox(b2Body* body, const CollisionData& data, class Actor* actor)
	{
		b2PolygonShape shape;
		Vector2 worldSize = PhysicsSystem::ScreenToWorld(data.size * 0.5f);
		shape.SetAsBox(worldSize.x, worldSize.y);

		b2FixtureDef fixtureDef;
		fixtureDef.density = data.density;
		fixtureDef.friction = data.friction;
		fixtureDef.restitution = data.restitution;
		fixtureDef.isSensor = data.is_trigger;
		fixtureDef.shape = &shape;
		fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(actor);

		body->CreateFixture(&fixtureDef);
	}
	void PhysicsSystem::SetCollisionBoxStatic(b2Body* body, const CollisionData& data, Actor* actor)
	{
		Vector2 worldSize = PhysicsSystem::ScreenToWorld(data.size * 0.5f);

		b2Vec2 vs[4] =
		{
			{ -worldSize.x, -worldSize.y },
			{  worldSize.x, -worldSize.y },
			{  worldSize.x,  worldSize.y },
			{ -worldSize.x,  worldSize.y },
		};

		b2ChainShape shape;
		shape.CreateLoop(vs, 4);

		b2FixtureDef fixtureDef;
		fixtureDef.density = data.density;
		fixtureDef.friction = data.friction;
		fixtureDef.restitution = data.restitution;
		fixtureDef.isSensor = data.is_trigger;
		fixtureDef.shape = &shape;
		fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(actor);

		body->CreateFixture(&fixtureDef);
	}
}