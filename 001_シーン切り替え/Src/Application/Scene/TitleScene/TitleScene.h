#pragma once

//継承に限り、include おけぇい↑

//class BaseScene;
#include "../BaseScene/BaseScene.h" 

class TitleScene:public BaseScene
{
public:
	TitleScene() { Init(); };
	~TitleScene() { Release(); };

	/*TitleScene() {};
	~TitleScene() {};*/

	/*void Init();*/
	void Update()override;
	void Draw()override;
	/*void Release();*/

private:

	void Init()override;
	void Release()override;

	//変数
	KdTexture m_titleTex;
	KdTexture m_startTex;

	float m_alpha = 0.0f;
	float m_alphaAdd = 0.01f;
};