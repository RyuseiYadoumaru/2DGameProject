#pragma once
#include "WindowsWindowDefinition.h"

namespace mySystem
{
	class WindowsWindow
	{
		PROHIBIT_COPY_AND_ASSIN(WindowsWindow);

	public:
		void Create();
		void Close();

	public:
		WindowsWindow(const WindowsWindowDefinition& inDefinition);
		~WindowsWindow() = default;

	private:
		WindowsWindowDefinition definition;

	};
}