#pragma once
#include "../Typedef/Typedef.h"


namespace mySystem
{
	class Renderer;

	class RenderingManager final
	{
	public:
		static int LoadSprite(string fileName);

#pragma region System Callback Function 
	public:
		static void Initialize();
		static void ClearBuffer();
		static void Rendering();
		static void Finalize();

		static void SceneFinalize();
#pragma endregion

	public:
		static void Register(Renderer& renderer);
		static void Remove(Renderer& renderer);

	private:
		static map<int, map<unsigned int, Renderer*>> _rendererMap;

		static unordered_map<string, int> _spriteHandleMap;

	private:
		static void ObjectDrawCall();
		static void SwapChain();
	};
}