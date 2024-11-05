#pragma once
#include <unordered_map>

namespace mySystem
{
	class SoundManager
	{
	public:
		static void SetUp();
		static void ShutDown();

	public:
		static void Play(std::string name);
		static void PlayLoop(std::string name);
		static void Stop(std::string name);
		static void AllStop();

	private:
		static std::unordered_map<std::string, int> m_soundDataList;
	};

}