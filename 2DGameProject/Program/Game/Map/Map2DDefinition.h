#pragma once
#include "../Include/ObjectInclude.h"

namespace Downwell
{
	class Block;

	enum class MapChip
	{
		NO,		// None
		NB,		// NormalBlock
		BB,		// BreakBlock
		FE,		// FloatingEnemy
		CE,		// CrawlEnemy
	};

	using MapChipData = vector<vector<MapChip>>;
	using BlockMap = map<int, map<int ,Block*>>;

	struct Map2DData
	{
		MapChipData mapChipDataList;

		float chipSize;
		int chipWidthNum;
		int chipHeightNum;
		int stageNum;
	};

	class Map2DUtility
	{
	public:
		static MapChip GetMapChipFromPosition(const Map2DData& inMapData, float posX, float posY)
		{
			float chipPosX = posX + (inMapData.chipSize / 2.0f);
			float chipPosY = posY + (inMapData.chipSize / 2.0f);
			int indexX = static_cast<int>(chipPosX / inMapData.chipSize);
			int indexY = static_cast<int>(chipPosY / inMapData.chipSize);

			// 例外範囲チェック
			bool isExceededWidthIndex = (indexX >= inMapData.chipWidthNum);
			bool isExceededHeightIndex = (indexY >= inMapData.chipHeightNum);
			if (isExceededWidthIndex || isExceededHeightIndex) return MapChip::NO;
			if (indexX < 0 || indexY < 0) return MapChip::NO;

			return inMapData.mapChipDataList[indexY][indexX];
		}

		static Block* GetMapChipObjectFromPosition(BlockMap& inBlockList, const Map2DData& inMapData, float posX, float posY)
		{
			float chipPosX = posX + (inMapData.chipSize / 2.0f);
			float chipPosY = posY + (inMapData.chipSize / 2.0f);
			int indexX = static_cast<int>(chipPosX / inMapData.chipSize);
			int indexY = static_cast<int>(chipPosY / inMapData.chipSize);

			// 例外範囲チェック
			bool isExceededWidthIndex = (indexX >= inMapData.chipWidthNum);
			bool isExceededHeightIndex = (indexY >= inMapData.chipHeightNum);
			if (isExceededWidthIndex || isExceededHeightIndex)	return nullptr;
			if (indexX < 0 || indexY < 0) return nullptr;

			// ブロックがないときはNULLを返す
			if (inBlockList.contains(indexY) == false)			return nullptr;
			if (inBlockList[indexY].contains(indexX) == false)  return nullptr;

			return inBlockList[indexY][indexX];
		}
	};
}