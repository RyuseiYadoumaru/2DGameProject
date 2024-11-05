#pragma once

namespace Downwell
{
	struct PlayerActionData
	{
		// ���s
		float walkMaxSpeed;
		float walkMinSpeed;

		// �W�����v
		float jumpPower;
		int risingFrame;
		int jumpFloatingFrame;

		// ����
		float fallMaxSpeed;
		int fallMaxSpeedFrame;

		// �e����
		int fireIntervalFrame;

		// ���݂�
		float startStepPower;
		int stepFrame;


	};
}