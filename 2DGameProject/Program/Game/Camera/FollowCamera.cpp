#include "FollowCamera.h"

namespace Downwell
{
	void FollowCamera::OnEnableRangeY(float min, float max)
	{
		_maxRangeY = max;
		_minRangeY = min;
		enableRangeY = true;
	}

	void FollowCamera::OnDisableRangeY()
	{
		_maxRangeY = 0.0f;
		_minRangeY = 0.0f;
		enableRangeY = false;
	}

	void FollowCamera::Following()
	{
		// ‰¡‚ÍŒÅ’è
		_transform->position.x = 247.5f;
		// c’Ç]
		float targetPos = (_followTrans->position.y + _followOffset.y);
		_transform->position.y = targetPos;
	}

	void FollowCamera::DelayFollowing()
	{
		// ‰¡‚ÍŒÅ’è
		_transform->position.x = 247.5f;
	
		// c’Ç]
		// –ˆƒtƒŒ[ƒ€À•WŽæ“¾
		float targetPos = (_followTrans->position.y + _followOffset.y);
		if (isDistant == false)
		{
			float distance = fabsf(_transform->position.y - targetPos);
			if (distance >= _followingDistance)
			{
				// ‹——£‚ª—£‚ê‚½‚ç’Ç]‚·‚é
				isDistant = true;
			}
		}
		else
		{
			if (_prePosY == _followTrans->position.y)
			{
				_frame++;
				if (_frame >= _delayFrame) isDistant = false;
			}
			else
			{
				_frame = 3;
			}
			_transform->position.y = Easing::Liner(static_cast<float>(_frame), static_cast<float>(_delayFrame), _transform->position.y, targetPos);

		}
		_prePosY = _followTrans->position.y;
	}

#pragma region  System Callback Functions

	void FollowCamera::Setup()
	{
		SetOrder(800);

		if (_followTrans == nullptr) return;

		// ƒJƒƒ‰‚Íc‚Ì‚Ý’Ç]‚µ‚Ü‚·
		//_transform->position.x = 247.5f * 2;
		_transform->position.y = _followTrans->position.y + _followOffset.y;
		isDistant = false;
	}

	void FollowCamera::LateUpdate()
	{
		if (_followTrans == nullptr) return;
		
		// ’Ç]ˆ—
		if (isDelay == true)
		{
			DelayFollowing();
		}
		else
		{
			Following();
		}
	
		// ”ÍˆÍ‚ð’´‚¦‚é‚ÆƒJƒƒ‰‚Í’Ç]‚ð‚â‚ß‚é
		if (enableRangeY == true)
		{
			if		(_transform->position.y <= _minRangeY) _transform->position.y = _minRangeY;
			else if (_transform->position.y >= _maxRangeY) _transform->position.y = _maxRangeY;
		}
	}

	void FollowCamera::End()
	{
		_followTrans = nullptr;
	}
#pragma endregion

}