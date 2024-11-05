#pragma once
#include <DirectXMath.h>

enum Xinput 
{
	A = (0x00000010),
	B = (0x00000020),
	X = (0x00000040),
	Y = (0x00000080)
};

class GamePad
{
public:
	static void GetBuffer();

public:
	static void SetActive(bool active) noexcept { isActive = active; }

	static bool Press(int xinput);
	static bool Trigger(int xinput);
	static DirectX::XMFLOAT2 LStick();

	static void StartVibration(int power, int time);
	static void StopVibration();

private:
	static bool isActive;
	static int _nowBuffer;
	static int _oldBuffer;

};
