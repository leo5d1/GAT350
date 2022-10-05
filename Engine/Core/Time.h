#pragma once
#include <chrono>

namespace c14
{
	class Time
	{
	private:
		using clock = std::chrono::high_resolution_clock;
		using clock_duration = clock::duration;
		using clock_rep = clock::rep;

	public:
		Time() :
			m_startTimePoint{ clock::now() },
			m_frameTimePoint{ clock::now() }
		{}

		void Tick();
		void Reset() { m_startTimePoint = clock::now(); }

	public:
		float deltaTime = 0;
		float time = 0;

	private:
		clock::time_point m_startTimePoint; // time point at start of application
		clock::time_point m_frameTimePoint; // time point at start of frame
	};
}