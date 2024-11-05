#include "WindowsWindow.h"

namespace mySystem
{
	class WindowsApplication
	{
	public:
		WindowsApplication() = default;
		~WindowsApplication() = default;

	public:
		bool Setup();
		void Run();
		void Suhtdown();

	private:
		shared_ptr<WindowsWindow> _window;

	private:
		bool IsEscape();

	private:
		void CreateConsole();
		void DestryConsole();

	};
}