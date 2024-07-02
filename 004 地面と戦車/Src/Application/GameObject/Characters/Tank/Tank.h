#pragma once

class Tank :public KdGameObject
{
public:
	Tank() { Init(); }
	~Tank(){}

	void Init()override;
	void Update()override;
	void DrawLit()override;

private:
	std::shared_ptr<KdModelData> m_model;
};