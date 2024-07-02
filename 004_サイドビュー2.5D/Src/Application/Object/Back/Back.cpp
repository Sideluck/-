#include "Back.h"

void Back::Init()
{
	m_polygon.SetMaterial("Asset/Textures/Back.png");
	m_scaleMat = Math::Matrix::CreateScale(300, 100, 1);
	m_transMat = Math::Matrix::CreateTranslation(0, 0, 50);

	m_mWorld = m_scaleMat * m_transMat;

}

void Back::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}
