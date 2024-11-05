#include "GamePad.h"
#include "DxLib.h"

int GamePad::_nowBuffer = NULL;
int GamePad::_oldBuffer = NULL;
bool GamePad::isActive  = true;

void GamePad::GetBuffer()
{
	_oldBuffer = _nowBuffer;
	_nowBuffer = GetJoypadInputState(DX_INPUT_PAD1);
}

bool GamePad::Press(int xinput)
{
	if (isActive == false) return false;
	return (_nowBuffer & xinput) != 0;
}

bool GamePad::Trigger(int xinput)
{
	if (isActive == false) return false;
	bool condition1 = (_nowBuffer & xinput) != 0;
	bool condition2 = (_oldBuffer & xinput) == 0;
	return (condition1 && condition2);
}

DirectX::XMFLOAT2 GamePad::LStick()
{
	if (isActive == false) return DirectX::XMFLOAT2(0.0f, 0.0f);

	DirectX::XMFLOAT2 ret;
	int x,y;

	GetJoypadAnalogInput(&x, &y, DX_INPUT_PAD1);
	ret.x = static_cast<float>(x) / 1000.0f;
	ret.y = static_cast<float>(y) / 1000.0f;
	return ret;
}

void GamePad::StartVibration(int power, int time)
{
	StartJoypadVibration(DX_INPUT_PAD1, power, time, -1);
}

void GamePad::StopVibration()
{
	StopJoypadVibration(DX_INPUT_PAD1, -1);
}
