#pragma once

#include "../../../../Systems/BaseClasses/Component.h"
#include "Transform.h"

namespace myMath
{
	class Vector2;
}

namespace myGame::Object
{
	class Camera : public mySystem::IComponent
	{
	public:
		static constexpr float ScreenWidth  = 1280.0f;
		static constexpr float ScreenHeight = 720.0f;

	public:
		static Camera& GetMainCamera() noexcept { return *_mainCamera; }
		static const bool EnableMainCaera() noexcept { return enableMainCamera; }

		static bool CheckAppearCamera(const Transform& inTrans, float expandX = 0.0f, float expandY = 0.0f)
		{
			if (_mainCamera == nullptr) return false;
			const Transform& cameraTrans = _mainCamera->GetOwnerTrans();
			float cameraLeft	= cameraTrans.position.x - (ScreenWidth  / 2.0f  + expandX);
			float cameraRight	= cameraTrans.position.x + (ScreenWidth  / 2.0f  + expandX);
			float cameraTop		= cameraTrans.position.y - (ScreenHeight / 2.0f  + expandY);
			float cameraButtom  = cameraTrans.position.y + (ScreenHeight / 2.0f  + expandY);
			if (inTrans.position.x > cameraLeft && inTrans.position.x < cameraRight &&
				inTrans.position.y > cameraTop && inTrans.position.y < cameraButtom)
			{
				return true;
			}
			return false;
		}

	private:
		static Camera* _mainCamera;
		static bool enableMainCamera;

	public:
		COMPONENT_CLASS;

	public:
		const int GetPriority() const noexcept { return _priority; }

		const Transform& GetOwnerTrans() const noexcept { return *_transform; }
		const myMath::Vector2& GetCameraPosition() const noexcept { return _cameraPos; }

		float GetRenderScopeLeft	() const noexcept { return _renderScopeLeft; }
		float GetRenderScopeRight	() const noexcept { return _renderScopeRight; }
		float GetRenderScopeTop		() const noexcept { return _renderScopeTop; }
		float GetRenderScopeButtom	() const noexcept { return _renderScopeButtom; }

		void SetRenderScopeLeft		(float scope) noexcept { _renderScopeLeft	= scope; }
		void SetRenderScopeRight	(float scope) noexcept { _renderScopeRight	= scope; }
		void SetRenderScopeTop		(float scope) noexcept { _renderScopeTop	= scope; }
		void SetRenderScopeButtom	(float scope) noexcept { _renderScopeButtom = scope; }

	private:
		int _priority = 0;
		Transform* _transform = nullptr;
		myMath::Vector2 _cameraPos;

		float _renderScopeLeft		= 0.0f;
		float _renderScopeRight		= 0.0f;
		float _renderScopeTop		= 0.0f;
		float _renderScopeButtom	= 0.0f;

	public:
		virtual void Initialize() override;
		virtual void Finalize() override;

		virtual void Start() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void End() override;

	};
}