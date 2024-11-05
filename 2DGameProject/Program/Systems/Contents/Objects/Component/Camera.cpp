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
			// ���C���J�������󂩗D��x�����݂̃��C���J������荂�����Ɏ������D�悳���
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

		// TODO:�����_�����O����E�B���h�E����E�B���h�E�T�C�Y���擾���āA�J�����̍��W�ɃZ�b�g����
		// �J�����̒����_�𒆐S�ɂ���
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