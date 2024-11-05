#include "Camera.h"

#include "../Generic/GameObject.h"
#include "../../Maths/Vector2.h"

namespace myGame::Object
{
	Camera* Camera::_mainCamera = nullptr;
	bool Camera::enableMainCamera = false;

	void Camera::Initialize()
	{
		SetOrder(900);
	}

	void Camera::Finalize()
	{
	}

	void Camera::Start()
	{
		_transform = &GetContext().GetTrans();

		bool isEmptyMainCamera = (_mainCamera == nullptr);
		if (isEmptyMainCamera ||
			_priority >= _mainCamera->GetPriority())
		{
			// メインカメラが空か優先度が現在のメインカメラより高い時に自分が優先される
			_mainCamera = this;
			enableMainCamera = true;
		}

		_renderScopeLeft	= ScreenWidth;
		_renderScopeRight	= ScreenWidth;
		_renderScopeTop		= ScreenHeight;
		_renderScopeButtom	= ScreenHeight;
	}

	void Camera::Update()
	{
	}

	void Camera::LateUpdate()
	{
		if (_mainCamera == nullptr ||_priority >= _mainCamera->GetPriority())
		{
			_mainCamera = this;
		}

		// TODO:レンダリングするウィンドウからウィンドウサイズを取得して、カメラの座標にセットする
		// カメラの注視点を中心にする
		_cameraPos.x = _transform->position.x - (ScreenWidth / 2.0f);
		_cameraPos.y = _transform->position.y - (ScreenHeight / 2.0f);
	}

	void Camera::End()
	{
		_transform = nullptr;
		if (_mainCamera->GetID() == this->GetID())
		{
			_mainCamera = nullptr;
		}
	}

}