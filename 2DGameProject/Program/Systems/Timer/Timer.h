#pragma once

namespace mySystem
{
	class Timer
	{
	public:
		static Timer& Get()
		{
			static Timer instance;
			return instance;
		}
	public:
		void Initialize();
		void Update();
		void Finalize();

		const float DeltaTime() const noexcept { return _deltaTime; }
		const unsigned int GetFrameCount() const noexcept { return _totalFrameCount; }

	private:
		void Wait();
		void PrintFPS();

	private:
		float _deltaTime = 0.0f;
		float _currentTime = 0.0f;
		float _lastTime = 0.0f;
		float _currentFps = 0.0f;
		unsigned int _totalFrameCount = 0;
		float _saveTime = 0.0f;

		constexpr static float FPS = 60.0f;
	};
}