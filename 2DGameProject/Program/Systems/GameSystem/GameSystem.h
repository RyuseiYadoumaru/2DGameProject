#pragma once
#include "../Typedef/Typedef.h"

namespace mySystem
{
	class GameSystem final
	{
	public:
		GameSystem() = default;
		~GameSystem() = default;

	public:
		void Initialize();
		void MainLoop();
		void Finalize();

	};
}