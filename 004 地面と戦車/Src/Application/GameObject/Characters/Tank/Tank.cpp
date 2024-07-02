#include "Tank.h"

void Tank::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Tank/Tank.gltf");
}

void Tank::Update()
{
	//押したキーの方向に戦車が回転する
	Math::Vector3 moveVec;
	bool moveFlg = false;

	//WASDキー
	if (GetAsyncKeyState('W')) 
	{ 
		moveVec += Math::Vector3(0, 0, 1);
		moveFlg = true;
	}
	if (GetAsyncKeyState('S')) 
	{ 
		moveVec += Math::Vector3(0, 0, -1); 
		moveFlg = true;
	}
	if (GetAsyncKeyState('A')) 
	{
		moveVec += Math::Vector3(-1, 0, 0); 
		moveFlg = true;
	}
	if (GetAsyncKeyState('D')) 
	{ 
		moveVec += Math::Vector3(1, 0, 0);
		moveFlg = true;
	}

	if (moveFlg == true)
	{
		//移動中(移動キーが押された時)

	}
}

void Tank::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model,m_mWorld);
}
