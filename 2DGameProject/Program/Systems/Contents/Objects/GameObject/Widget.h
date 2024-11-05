#pragma once
#include "../Generic/GameObject.h"
#include "../Component/WidgetRenderer.h"

#define  WIDGET_CLASS myGame::Object::Widget::Widget;

namespace myGame::Object
{
	class Widget : public GameObject
	{
	public:
		GAMEOBJECT_CLASS;

	protected:
		TComponentPtr<WidgetRenderer> _widget = nullptr;

	private:
		void Initialize() override final
		{
			_widget = AddComponent<WidgetRenderer>();
			Setup();
		}

		void Finalize() override final
		{
			_widget = nullptr;
		}
	};
}