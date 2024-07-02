#pragma once

class Back:public KdGameObject
{
public:
	Back() { Init(); }
	~Back(){}

	void Init()override;
	void DrawUnLit()override;

private:
	Math::Matrix m_scaleMat;
	Math::Matrix m_transMat;

	KdSquarePolygon m_polygon;
};