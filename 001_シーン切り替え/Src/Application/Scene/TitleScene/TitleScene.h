#pragma once

class TitleScene
{
public:
	TitleScene() { Init(); };
	~TitleScene() { Release(); };

	/*TitleScene() {};
	~TitleScene() {};*/

	/*void Init();*/
	void Update();
	void Draw();
	/*void Release();*/

private:

	void Init();
	void Release();

	//変数
	KdTexture m_titleTex;
	KdTexture m_startTex;

	float m_alpha = 0.0f;
	float m_alphaAdd = 0.01f;
};