#pragma once
#include "Map2DSponer.h"

namespace Downwell
{
	class Map2DTitleSponer : public Map2DSponer
	{
	public:
		Map2DSponer::Map2DSponer;

	private:
		void Setup() override;
		void BeginPlay() override;

	};
}