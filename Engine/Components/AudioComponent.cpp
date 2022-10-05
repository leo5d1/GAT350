#include "AudioComponent.h"
#include "Engine.h"

namespace c14
{
	AudioComponent::~AudioComponent()
	{
		m_channel.Stop();
	}
	
	void AudioComponent::Initialize()
	{
		if (play_on_start)
		{
			Play();
		}
	}

	void AudioComponent::Update()
	{

	}

	bool AudioComponent::Write(const rapidjson::Value& value) const
	{
		//
		return true;
	}

	bool AudioComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, sound_name);
		READ_DATA(value, play_on_start);
		READ_DATA(value, volume);
		READ_DATA(value, pitch);
		READ_DATA(value, loop);

		g_audio.AddAudio(sound_name, sound_name);

		return true;
	}

	void AudioComponent::Play()
	{
		Stop();
		m_channel = g_audio.PlayAudio(sound_name, volume, pitch, loop);
	}
	
	void AudioComponent::Stop()
	{
		m_channel.Stop();
	}
}
