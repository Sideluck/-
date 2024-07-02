#pragma once

class Cannon:public KdGameObject
{
public:
	Cannon() { Init(); }
	~Cannon(){}

	void Init()override;
	void Update()override;
	void DrawLit()override;
	void DrawBright()override;

private:
	Math::Matrix m_scaleMat;
	Math::Matrix m_transMat;
	Math::Matrix m_rotMat;

	float p = 0;

	std::shared_ptr<KdModelData> m_model;
};