#include "Enemy.h"
#include "../../Scene/SceneManager.h"

void Enemy::Update()
{
	if (m_goal >= 5)
	{
		m_goal = 0;
		m_dir *= -1;
		m_scale.x *= -1;
	}
	m_pos.x += m_speed * m_dir;
	m_goal += m_speed;

	//重力をキャラに反映
	m_pos.y -= m_gravity;
	m_gravity += 0.005f;

	//アニメーション処理
	int Walk[4] = { 3,4,3,5 };
	m_polygon.SetUVRect(Walk[(int)m_anim]);
	m_anim += 0.1f;
	if (m_anim >= 4)
	{
		m_anim = 0;
	}

	//座標更新
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix scaleMat;
	scaleMat = Math::Matrix::CreateScale(m_scale);
	m_mWorld = scaleMat * transMat;
}

void Enemy::PostUpdate()
{
	//ポイントライト(点光源)
	Math::Vector3 tmpPos = { 0,0.5,0 };
	//最大100個まで
	//毎フレーム追加する必要がある(毎フレームリセットされるため)
	KdShaderManager::Instance().WorkAmbientController().AddPointLight({ 3,0,0 }, 5, m_pos + tmpPos, true);

	//自分自身の当たり判定エリア
	m_pDebugWire->AddDebugSphere(m_pos + Math::Vector3(0, 0.5f, 0), 0.2f, kGreenColor);

	//☆☆☆☆☆☆☆☆☆☆☆☆
	//☆当たり判定(レイ判定)☆
	//☆☆☆☆☆☆☆☆☆☆☆☆

	//レイ判定用の変数を作成
	KdCollider::RayInfo ray;
	//レイの発射位置(座標)を設定
	ray.m_pos = m_pos;
	//レイの発射方向を設定
	ray.m_dir = Math::Vector3::Down;//真下

	//少し高いところから飛ばす
	ray.m_pos.y += 0.1f;

	//段差の許容範囲を設定
	float enableStepHigh = 0.2f;
	ray.m_pos.y += enableStepHigh;

	//レイの長さを設定
	ray.m_range = m_gravity + enableStepHigh;

	//当たり判定をしたい対応を設定
	ray.m_type = KdCollider::TypeGround;

	//レイに当たったオブジェクト情報を作成
	std::list<KdCollider::CollisionResult> retRayList;

	//☆☆☆☆☆☆☆☆☆
	//レイと当たり判定☆
	//☆☆☆☆☆☆☆☆☆
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(ray, &retRayList);
	}

	//デバッグ用(レイを可視化)
	//m_pDebugWire->AddDebugLine(ray.m_pos, ray.m_dir, ray.m_range);

	//レイリストから一番近いオブジェクトを検出
	float maxOverLap = 0;   //はみ出たレイの長さ
	Math::Vector3 hitPos;   //当たっていたらtrue
	bool ishit = false;

	for (auto& ret : retRayList)
	{
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitPos = ret.m_hitPos;
			ishit = true;
		}
	}
	if (ishit)
	{
		//当たっている
		m_pos = hitPos + Math::Vector3(0, -0.1f, 0);
		m_gravity = 0;
	}

	//☆☆☆
	//球判定
	//☆☆☆

	//球判定用の変数を作成
	KdCollider::SphereInfo sphere;
	//球の中心位置を設定
	sphere.m_sphere.Center = m_pos + Math::Vector3(0, 0.5f, 0);
	//球の半径を設定
	sphere.m_sphere.Radius = 0.3f;
	//当たり判定をしたいタイプを設定
	sphere.m_type = KdCollider::TypeGround|KdCollider::TypeBump;
	//デバッグ用
	//m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius);

	//球が当たったオブジェクト情報を作成
	std::list<KdCollider::CollisionResult> retSphereList;

	//☆☆☆☆☆☆☆☆
	//球と当たり判定☆
	//☆☆☆☆☆☆☆☆
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		//自分とは当たり判定をしない
		if (obj.get() == this)
		{
			continue;
		}

		obj->Intersects(sphere, &retSphereList);
	}

	//球リストから一番近いオブジェクトを検出
	maxOverLap = 0;   //はみ出た球の長さ
	ishit = false;
	Math::Vector3 hitDir; //当たった方向

	for (auto& ret : retSphereList)
	{
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitDir = ret.m_hitDir;
			ishit = true;
		}
	}
	if (ishit)
	{
		//Z方向無効
		hitDir.z = 0;
		//方向ベクトルは長さ1にする必要がある
		hitDir.Normalize();

		//押し戻し
		m_pos += hitDir * maxOverLap;
	}
}

void Enemy::Init()
{
	m_objectType = KdGameObject::Enemy;

	m_polygon.SetMaterial("Asset/Textures/chara.png");
	m_pos = { -20,0,0 };
	m_scale = { 1,1,1 };
	m_speed = 0.01;

	m_hp = 10;

	//画像分割
	m_polygon.SetSplit(6, 6);

	//原点変更
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	//デバッグ用
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	//当たり判定を設定
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("EnemyCollison",{0,0.5f,0},0.2f,KdCollider::TypeBump);
}

void Enemy::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void Enemy::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void Enemy::OnHit()
{
	//当たった時(攻撃された時)に処理してほしいプログラム

	//m_isExpired...生存フラグみたいなもの
	m_hp--;
	if (m_hp < 0)
	{
		m_isExpired = true;
	}

}
