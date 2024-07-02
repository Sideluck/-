#pragma once

class BaseScene;

class SceneManager
{
public:
	enum SceneType
	{
		Title,
		Game,
		Result
	};

	void PreUpdate();
	void Update();
	void Draw();

	//次のシーンを設定する関数
	void SetNextScene(SceneType _sceneType) { m_nextSceneType = _sceneType; };

	//現在のシーンを取得する関数
	//ゲッターはvoidじゃない
	SceneType GetCurrentSceneType() {return m_currentSceneType;}


private:

	void Init();
	void Release();

	//シーンを切り替える関数
	void ChangeScene(SceneType _sceneType);

	//現在のシーンを管理しているポインタ
	std::shared_ptr<BaseScene>m_currentScene;

	//現在のシーンを管理している変数
	SceneType m_currentSceneType = SceneType::Title;

	//次のシーンを管理している変数
	SceneType m_nextSceneType = m_currentSceneType;

//シングルトンパターン
private:

	SceneManager() { Init(); }
	~SceneManager() { Release(); }

public:

	static SceneManager& Instance()
	{
		static SceneManager instance;//実体化
		return instance;
	}

};