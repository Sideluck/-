#include "TPSCamera.h"

void TPSCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();

	// 注視点
	m_mLocalPos = Math::Matrix::CreateTranslation(0, 2.0f, -5.0f);

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);
}

void TPSCamera::Update()
{
	// ターゲットの行列(有効な場合利用する)
	Math::Matrix								_targetMat	= Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject>	_spTarget	= m_wpTarget.lock();
	if (_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
	}

	// カメラの回転

	//カーソル制御
	if (GetAsyncKeyState('H')&0x8000)
	{
		m_hold = true;
		ShowCursor(true);
	}
	if (GetAsyncKeyState('J')&0x8000)
	{
		m_hold = false;
		ShowCursor(false);
	}
	if (m_hold == false)
	{
		//UpdateRotateByMouse();
	}
	m_mRotation = GetRotationMatrix();
	m_mWorld	= m_mLocalPos * m_mRotation * _targetMat;

	CameraBase::Update();
}