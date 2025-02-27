#pragma once

namespace Downwell
{
	struct PlayerActionData
	{
		// 歩行
		float walkMaxSpeed;
		float walkMinSpeed;

		// ジャンプ
		float jumpPower;
		int risingFrame;
		int jumpFloatingFrame;

		// 落下
		float fallMaxSpeed;
		int fallMaxSpeedFrame;

		// 弾発射
		int fireIntervalFrame;

		// 踏みつけ
		float startStepPower;
		int stepFrame;


	};
}