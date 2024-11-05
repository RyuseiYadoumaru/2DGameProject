#include "DxLib.h"
#include "Map2DSponer.h"

#include "../Block/NormalBlock.h"
#include "../Block/BreakBlock.h"
#include "../Enemy/FloatingEnemy.h"
#include "../Enemy/CrawlEnemy.h"
#include "../Enemy/EnemyManager.h"

#include "../Include/SystemInclude.h"

namespace Downwell
{
	void Map2DSponer::DestroyBlock(int indexX, int indexY)
	{
		bool hasIndexY = _blockMap.contains(indexY);
		if (hasIndexY == false) return;

		bool hasIndexX = _blockMap[indexY].contains(indexX);
		if (hasIndexX == false) return;

		GameObject::Destoy(_blockMap[indexY][indexX]);

		_blockMap[indexY].erase(indexX);
		_mapData.mapChipDataList[indexY][indexX] = MapChip::NO;

	}

	void Map2DSponer::CreateMap(const Map2DData& inMapData)
	{
		if (inMapData.mapChipDataList.empty()) return;

		// マップ生成
		int chipY = 0;
		for (auto& chipLineList : inMapData.mapChipDataList)
		{
			int chipX = 0;
			for (auto& chipData : chipLineList)
			{
				SponeCihpObject(chipData, chipX, chipY, _mapData.chipSize);
				chipX++;
			}
			chipY++;
		}
	}

	void Map2DSponer::SponeCihpObject(MapChip inChip, int inChipX, int inChipY, float inSize)
	{
		float setPositionX = inChipX * inSize;
		float setPositionY = inChipY * inSize;

		switch (inChip)
		{
			case Downwell::MapChip::NO:
			{
				break;
			}

			case Downwell::MapChip::NB:
			{
				Block* block = GameObject::Instance<NormalBlock>("NormalBlock");
				block->SetBlockSize(inSize);
				block->SetIndex(inChipX, inChipY);
				block->SetOwnerSponer(this);
				block->GetTrans().position.Set(setPositionX, setPositionY);
				_blockMap[inChipY][inChipX] = block;
				break;
			}

			case Downwell::MapChip::BB:
			{
				Block* block = GameObject::Instance<BreakBlock>("BreakBlock");
				block->SetBlockSize(inSize);
				block->SetIndex(inChipX, inChipY);
				block->SetOwnerSponer(this);
				block->GetTrans().position.Set(setPositionX, setPositionY);
				_blockMap[inChipY][inChipX] = block;
				break;
			}

			case Downwell::MapChip::FE:
			{
				Enemy* enemy = GameObject::Instance<FloatingEnemy>("FloatingEnemy", Tag::FloatingEnemy);
				enemy->GetTrans().position.Set(setPositionX, setPositionY);
				EnemyManager::Register(enemy);
				break;
			}

			case Downwell::MapChip::CE:
			{
				Enemy* enemy = GameObject::Instance<CrawlEnemy>("CrawlEnemy", Tag::CrawlEnemy);
				enemy->GetTrans().position.Set(setPositionX, setPositionY);
				EnemyManager::Register(enemy);
				break;
			}
		}
	}

	MapChipData Map2DSponer::CreateMapChipData(CSVDataList dataList)
	{
		MapChipData mapChipData;
		for (auto& lineData : dataList)
		{
			vector<MapChip> onelineChipList;
			for (auto& chipName : lineData)
			{
				MapChip chip = GetChipObjetFromChipName(chipName);
				onelineChipList.push_back(chip);
			}
			mapChipData.push_back(onelineChipList);
		}

		return mapChipData;
	}

	Map2DSponer::CSVDataList Map2DSponer::LoadMap(string dataName)
	{
		string filePath = "Assets/MapData/" + dataName + ".csv";
		string line, one;
		one.clear();
		line.clear();

		ifstream inputMapDataStream(filePath);

		if (!inputMapDataStream)
		{
			cout << filePath + ":::マップデータが存在しません\n";
		}

		// 行読み込み
		Map2DSponer::CSVDataList chipData;
		while (getline(inputMapDataStream, line, '\n'))
		{
			vector<string> oneLineChipList;

			istringstream inputLineDataStream(line);
			while (getline(inputLineDataStream, one, ','))
			{
				// 1行分を確保する
				oneLineChipList.push_back(one);
			}

			// 行ごとに格納
			chipData.push_back(oneLineChipList);
		}
		return chipData;
	}

	Map2DSponer::CSVDataList Map2DSponer::LoadMapRand(vector<string> dataNameList, int loadNum)
	{
		CSVDataList dataList;

		unordered_map<string, CSVDataList> loadedData;
		for (int num = 0; num < loadNum; num++)
		{
			CSVDataList loadData;

			int index = GetRand(static_cast<int>(dataNameList.size()) - 1);
			string loadDataName = dataNameList[index];
			if (loadedData.contains(loadDataName))
			{
				// すでにロードされているデータ
				loadData = loadedData[loadDataName];
			}
			else
			{
				loadData = LoadMap(loadDataName);
				loadedData[loadDataName] = loadData;
			}

			for (auto& lineData : loadData)
			{
				// データを追加する
				dataList.push_back(lineData);
			}
		}

		return dataList;
	}

	MapChip Map2DSponer::GetChipObjetFromChipName(string chip)
	{
		if (chip == "NB" || chip == "LL" || chip == "RL")
		{
			// NormalBlock
			return MapChip::NB;
		}
		else if (chip == "FE")
		{
			return MapChip::FE;
		}
		else if (chip == "CE")
		{
			return MapChip::CE;
		}
		else if (chip == "BB")
		{
			return MapChip::BB;
		}
		else
		{
			// 何もない
			return MapChip::NO;
		}		
	}

#pragma region System Callback Functions

	void Map2DSponer::Setup()
	{
		// マップチップ読み込み
		// マップデータ
		_mapData.stageNum = 8;
		_mapData.chipSize = 45.0f;

		vector<string> mapDataList
		{
			"MapData_1",
			"MapData_2",
			"MapData_3",
			"MapData_4",
			"MapData_5",
			"MapData_6",
			"MapData_7",
			"MapData_8",
			"MapData_9",
			"MapData_10",
		};
		vector<vector<string>> dataList = LoadMapRand(mapDataList, _mapData.stageNum);
		

		string startMapDataName = "MapData_Start";
		vector<vector<string>> _startMapData = LoadMap(startMapDataName);
		
		for (int mapY = _startMapData.size() - 1; mapY >= 0; mapY--)
		{
			// スタートマップを先頭に挿入するため
			// データの後ろから参照している
			vector<string> data = _startMapData[mapY];
			dataList.insert(dataList.begin(), data);
		}

		// ゴール直前のマップを生成する
		string endMapDataName = "MapData_End";
		vector<vector<string>> _endMapData = LoadMap(endMapDataName);
		for (int mapY = 0; mapY < _endMapData.size(); mapY++)
		{
			vector<string> data = _endMapData[mapY];
			dataList.insert(dataList.end(), data);
		}

		_mapData.mapChipDataList = CreateMapChipData(dataList);
		_mapData.chipHeightNum = _mapData.mapChipDataList.size();
		_mapData.chipWidthNum = _mapData.mapChipDataList[0].size();
	}

	void Map2DSponer::BeginPlay()
	{
		// マップ生成
		CreateMap(_mapData);
	}

	void Map2DSponer::EndPlay()
	{
		EnemyManager::AllEnemyClear();
	}

#pragma endregion
}