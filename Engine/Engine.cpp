#include "Engine.h"

namespace c14
{
	Renderer g_renderer;
	InputSystem g_inputSystem;
	AudioSystem g_audio;
	Time g_time;
	ResourceManager g_resources;
	PhysicsSystem g_physicsSystem;
	EventManager g_eventManager;

	void Engine::Initialize()
	{
		g_renderer.Initialize();
		g_inputSystem.Initialize();
		g_audio.Initialize();
		g_resources.Initialize();
		g_physicsSystem.Initialize();
		g_eventManager.Initialize();
	}

	void Engine::Update()
	{
		g_time.Tick();
		g_eventManager.Update();
		g_physicsSystem.Update();
		g_inputSystem.Update();
		g_audio.Update();
	}

	void Engine::Shutdown()
	{
		Factory::Instance().Shutdown();

		g_eventManager.Shutdown();
		g_physicsSystem.Shutdown();
		g_resources.Shutdown();
		g_inputSystem.Shutdown();
		g_audio.Shutdown();
		g_renderer.Shutdown();
	}

	void Engine::Register()
	{
		REGISTER_CLASS(Actor);
		REGISTER_CLASS(AudioComponent);
		REGISTER_CLASS(ModelComponent);
		REGISTER_CLASS(PhysicsComponent);
		REGISTER_CLASS(RBPhysicsComponent);
		REGISTER_CLASS(CollisionComponent);
		REGISTER_CLASS(PlayerComponent);
		REGISTER_CLASS(SpriteComponent);
		REGISTER_CLASS(SpriteAnimComponent);
		REGISTER_CLASS(TextComponent);
		REGISTER_CLASS(TilemapComponent);
		REGISTER_CLASS(CameraComponent);
		REGISTER_CLASS(CameraController);
	}
}