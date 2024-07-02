#include "Cannon.h"

void Cannon::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Cannon2/Cannon.gltf");

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("CannonCollison", m_model, KdCollider::TypeGround);
}

void Cannon::Update()
{
	p++;
	m_transMat = Math::Matrix::CreateTranslation(-0.5f, 0, 0);
	m_scaleMat = Math::Matrix::CreateScale(1, 1, 1);
	m_rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(p));

	m_mWorld = m_scaleMat * m_rotMat * m_transMat;
}

void Cannon::DrawLit()
{
	//KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Cannon::DrawBright()
{
	//ライトブルーム
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}
