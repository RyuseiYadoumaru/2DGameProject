#include "DxLib.h"
#include "SoundManager.h"
#include "../FileSystem/FileSystem.h"

#include <list>
#include <string>


namespace mySystem
{
	std::unordered_map<std::string, int> SoundManager::m_soundDataList;

	void SoundManager::SetUp()
	{
		// 初期化
		m_soundDataList.clear();
		InitSoundMem();

		// サウンドデータ取り込み
		std::list<std::vector<std::string>> filePathList;
		filePathList.push_back(FileSystem::GetAllFileFromFolder("Assets/BGM/", "mp3"));
		filePathList.push_back(FileSystem::GetAllFileFromFolder("Assets/SE/", "mp3"));
		for (auto& pathList : filePathList)
		{
			for (auto& path : pathList)
			{
				std::string name(FileSystem::GetFileName(path, false));
				m_soundDataList.insert(std::make_pair(name, LoadSoundMem(path.c_str())));
			}
		}
	}

	void SoundManager::ShutDown()
	{
		SoundManager::AllStop();
		InitSoundMem();
	}

	void SoundManager::Play(std::string name)
	{
		int mem = NULL;
		mem = m_soundDataList[name];
		if (mem == NULL)
		{
			printf("サウンドデータがありません\n");
			return;
		}
		PlaySoundMem(mem, DX_PLAYTYPE_BACK);
	}

	void SoundManager::PlayLoop(std::string name)
	{
		int mem = NULL;
		mem = m_soundDataList[name];
		if (mem == NULL)
		{
			printf("サウンドデータがありません\n");
			return;
		}

		PlaySoundMem(mem, DX_PLAYTYPE_LOOP);
	}

	void SoundManager::Stop(std::string name)
	{
		int mem = NULL;
		mem = m_soundDataList[name];
		if (mem == NULL)
		{
			printf("サウンドデータがありません\n");
			return;
		}

		StopSoundMem(mem);
	}

	void SoundManager::AllStop()
	{
		for (auto& handle : m_soundDataList)
		{
			StopSoundMem(handle.second);
		}
	}
}