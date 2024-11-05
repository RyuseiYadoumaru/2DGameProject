#pragma once
#include "../Include/ObjectInclude.h"


namespace Downwell
{
	class Gun;

	class BulletUI : public Widget
	{
	public:
		WIDGET_CLASS;

	private:
		virtual void Setup() override;

		virtual void BeginPlay() override;

		virtual void Tick() override;

		virtual void EndPlay() override;

	};

	class GunUIManager : public Script
	{
		using BulletUIContainer = vector<BulletUI*>;

	public:
		SCRIPT_CLASS;

	private:
		BulletUIContainer _bulletUIList;

		float _bulletUIDistance = 57.0f;

	public:
		void Create(const Gun& inGun);
		void ReloadUI(const Gun& inGun);
		void DecreaseUI(const int index);

	private:
		void Setup() override;

	};

}