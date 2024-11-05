#include "DxLib.h"
#include "WindowsWindow.h"

namespace mySystem 
{
	void WindowsWindow::Create()
	{
		ChangeWindowMode(TRUE);

		SetWindowSizeChangeEnableFlag(definition.canChangeWindowSize, definition.canChangeWindowSize);

		SetGraphMode(definition.Width, definition.Height, 32);
		SetWindowSize(definition.Width, definition.Height);

		SetWindowText(definition.title.c_str());

		// ダブルバッファの裏面に描画
		SetDrawScreen(DX_SCREEN_BACK);
	}

	void WindowsWindow::Close()
	{

	}


	WindowsWindow::WindowsWindow(const WindowsWindowDefinition& inDefinition)
	{
		definition.Width = inDefinition.Width;
		definition.Height = inDefinition.Height;

		definition.canChangeWindowSize = inDefinition.canChangeWindowSize;

		definition.title = inDefinition.title;
	}
}