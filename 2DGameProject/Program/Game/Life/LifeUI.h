#pragma once
#include "../Include/ObjectInclude.h"

namespace Downwell
{
	class Life;

	class LifeUI : public Widget
	{
	public:
		WIDGET_CLASS;

	private:
		virtual void Setup() override;

	};

	class LifeUIManager : public Script
	{
		using LifeUIContainer = vector<LifeUI*>;

	public:
		SCRIPT_CLASS;

	private:
		LifeUIContainer _lifeUIList;

		float _uiDistance = 41;

	public:
		void Create(int lifeNum);
		void DamageUI(int index);

	private:
		void Setup() override;
	};
}