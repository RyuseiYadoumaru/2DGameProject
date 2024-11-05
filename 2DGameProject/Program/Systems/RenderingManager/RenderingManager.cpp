#include "DxLib.h"
#include "RenderingManager.h"

#include "../BaseClasses/Renderer.h"

namespace mySystem
{
	map<int, map<unsigned int, Renderer*>> RenderingManager::_rendererMap;
	unordered_map<string, int> RenderingManager::_spriteHandleMap;

	int RenderingManager::LoadSprite(string fileName)
	{
		if (_spriteHandleMap.contains(fileName) == false)
		{
			string path = "Assets/Sprites/" + fileName;
			int spriteHandle = LoadGraph(path.c_str());
			_spriteHandleMap[fileName] = (spriteHandle != -1) ? spriteHandle : NULL;
		}
		return _spriteHandleMap[fileName];
	}

	void RenderingManager::Initialize()
	{
		_rendererMap.clear();
	}

	void RenderingManager::Rendering()
	{
		ObjectDrawCall();
		SwapChain();
	}

	void RenderingManager::Finalize()
	{
		_rendererMap.clear();

		for (auto& handle : _spriteHandleMap)
		{
			// ƒƒ‚ƒŠ‚É“o˜^‚³‚ê‚Ä‚¢‚éƒXƒvƒ‰ƒCƒg‚ðíœ
			DeleteGraph(handle.second);
		}

		_spriteHandleMap.clear();
	}

	void RenderingManager::SceneFinalize()
	{
		_rendererMap.clear();
	}

	void RenderingManager::Register(Renderer& renderer)
	{
		_rendererMap[renderer.GetLayer()][renderer.GetID()] = &renderer;
	}

	void RenderingManager::Remove(Renderer& renderer)
	{
		const int layer = renderer.GetLayer();
		const unsigned int rendererID = renderer.GetID();
		if (_rendererMap[layer].contains(rendererID))
		{
			_rendererMap[layer][rendererID] = nullptr;
			_rendererMap[layer].erase(rendererID);
		}
	}

	void RenderingManager::ObjectDrawCall()
	{
		for (auto& rendererList : _rendererMap)
		{
			for (auto& rendererID : rendererList.second)
			{
				bool active =rendererID.second->IsActive();
				if (active)
				{
					rendererID.second->Draw();
				}
			}
		}
	}

	void RenderingManager::SwapChain()
	{
		ScreenFlip();
	}

	void RenderingManager::ClearBuffer()
	{
		ClearDrawScreen();
	}
}