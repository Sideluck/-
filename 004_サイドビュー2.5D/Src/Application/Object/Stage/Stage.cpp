#include "Stage.h"

void Stage::Init()
{

	//データ読みこみ
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/SideViewMap/SideViewMap.gltf");

	m_transMat = Math::Matrix::CreateTranslation(0, -2.0f, 0);
	m_scaleMat = Math::Matrix::CreateScale(5, 1, 1);

	//ワールド行列は絶対使う!(自分で作った行列は使わない)
	m_mWorld = m_scaleMat * m_transMat;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("StageCollison",m_model,KdCollider::TypeGround);
}

void Stage::DrawLit()
{
	//表示
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model,m_mWorld);
}
