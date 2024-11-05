#pragma once
#include "../Include/ObjectInclude.h"

#include "Map2DDefinition.h"
namespace Downwell
{
	class Map2DSponer : public GameObject
	{
	protected:
		using CSVDataList = vector<vector<string>>;

	public:
		GAMEOBJECT_CLASS;

	public:
		void DestroyBlock(int indexX, int indexY);

	public:
		Map2DData* GetMap2DData() noexcept	{ return &_mapData; }
		BlockMap* GetBlockMap() noexcept	{ return &_blockMap; }

	protected:
		Map2DData _mapData;
		BlockMap _blockMap;

	protected:
		void CreateMap(const Map2DData& inMapData);

		void SponeCihpObject(MapChip inChip, int inChipX, int inChipY, float inSize);
		MapChipData CreateMapChipData(CSVDataList dataList);

		CSVDataList LoadMap(string dataName);
		CSVDataList LoadMapRand(vector<string> dataNameList, int loadNum = 1);

		MapChip GetChipObjetFromChipName(string chip);

	private:
		virtual void Setup() override;
		virtual void BeginPlay() override;
		virtual void EndPlay() override;
	};
}