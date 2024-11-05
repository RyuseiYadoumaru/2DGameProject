#pragma once
#include "../../Typedef/Typedef.h"

namespace mySystem
{
	struct WindowsWindowDefinition
	{
		float Width = 0.0f;
		float Height = 0.0f;

		bool canChangeWindowSize = false;;

		string title = "";
	};
}