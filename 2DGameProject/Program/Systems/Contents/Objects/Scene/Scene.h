#pragma once
#include "SceneHeader.h"

#define  SCENE_CLASS using myGame::Object::Scene::Scene; 

namespace myGame::Object
{
	class Scene : 
		public mySystem::IScene, public mySystem::Object
	{
	public:
		Scene(string name) : Object(name, true) {};
		~Scene() = default;

	private:
		virtual void SetupObject();
		virtual void BeginPlay();
		virtual void Tick();
		virtual void EndPlay();
		
	private:
		void OnEnter() override final;
		void OnUpdate() override final;
		void OnExit() override final;

	private:
		

	};
}