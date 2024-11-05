#include "Map2DTitleSponer.h"

namespace Downwell
{
	void Map2DTitleSponer::Setup()
	{
		// マップチップ読み込み
		// マップデータ
		vector<string> mapDataList
		{
			"MapData_Title",
		};
		_mapData.stageNum = mapDataList.size();
		_mapData.chipSize = 45.0f;

		vector<vector<string>> dataList;
		for (int i = 0; i < _mapData.stageNum; i++)
		{
			CSVDataList loadData;
			loadData = LoadMap(mapDataList[i]);
			
			for (auto& lineData : loadData)
			{
				dataList.push_back(lineData);
			}
		}

		_mapData.mapChipDataList = CreateMapChipData(dataList);
		_mapData.chipHeightNum = _mapData.mapChipDataList.size();
		_mapData.chipWidthNum = _mapData.mapChipDataList[0].size();

	}

	void Map2DTitleSponer::BeginPlay()
	{
		CreateMap(_mapData);
	}
}