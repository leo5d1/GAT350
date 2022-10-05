#pragma once


namespace c14
{
	template<class T>
	class Singleton
	{
	public:
		// copy constructor
		Singleton(const Singleton&) = delete;
		// assignment operator
		Singleton& operator = (const Singleton&) = delete;

		static T& Instance()
		{
			static T instance;
			return instance;
		}
	protected:
		// prevent public constructor
		Singleton() = default;
	};
}