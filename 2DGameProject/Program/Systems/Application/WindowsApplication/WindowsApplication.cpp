#include "WindowsApplication.h"
#include "../../GameSystem/GameSystem.h"
#include "DxLib.h"

#include "../../Timer/Timer.h"
#include "../../Input/GamePad.h"
#include "../../Typedef/Typedef.h"

namespace mySystem
{
#pragma region  Main Function

	bool WindowsApplication::Setup()
	{
		// ウィンドウ生成
		WindowsWindowDefinition definition;
		definition.Width = 1280.0f;
		definition.Height = 720.0f;
		definition.canChangeWindowSize = false;
		definition.title = "Downwell";

		_window = make_shared<WindowsWindow>(definition);
		_window->Create();

		// コンソール表示
		// デバッグログに使うため標準出力のみ許可している
		CreateConsole();

		auto errorHandle = DxLib_Init();
		if (errorHandle == -1) return false;

		printf("アプリケーション開始\n");
		return true;
	}
	
	void WindowsApplication::Run()
	{
		auto gameSystem = unique_ptr<GameSystem>();
		gameSystem->Initialize();

		unsigned int frame = 0;
		while (IsEscape() == false)
		{
			cout << "\n" << frame << ":::Frame\n";
			gameSystem->MainLoop();
			frame++;
			if (frame >= 0xfffffff0)
			{
				frame = 0x00000000;
			}
		}

		gameSystem->Finalize();
		gameSystem.reset();
	}


	void WindowsApplication::Suhtdown()
	{
		DestryConsole();

		_window->Close();
		_window.reset();

		DxLib_End();
	}

#pragma endregion

#pragma region  Boolean Function

	bool WindowsApplication::IsEscape()
	{
		if (ProcessMessage() != 0 ||
			CheckHitKey(KEY_INPUT_ESCAPE))
		{
			return true;
		}
		return false;
	}
#pragma endregion

#pragma region  Console Function
	
	void WindowsApplication::CreateConsole()
	{
#if _DEBUG
		AllocConsole();
		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
#endif
	}

	void WindowsApplication::DestryConsole()
	{
#if _DEBUG
		FreeConsole();
#endif
	}

#pragma endregion

}