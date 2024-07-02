#include "Player.h"
#include "../../Scene/SceneManager.h"

void Player::Update()
{
	//移動処理
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pos.x -= 0.1f;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pos.x += 0.1f;
	}
	
	//ジャンプ
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		m_gravity = -0.1f;
	}

	//重力をキャラに反映
	m_pos.y -= m_gravity;
	m_gravity += 0.005f;

	//アニメーション処理
	/*int Run[4] = { 24,25,24,26 };
	m_polygon.SetUVRect(Run[(int)m_anim]);
	m_anim += 0.1f;
	if (m_anim >= 4)
	{
		m_anim = 0;
	}*/
	m_polygon.SetUVRect(24);

	//座標更新
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = transMat;
}

void Player::PostUpdate()
{
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
		obj->Intersects(ray,&retRayList);
	}

	//デバッグ用(レイを可視化)
	m_pDebugWire->AddDebugLine(ray.m_pos,ray.m_dir,ray.m_range);

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
		jumpCount = 0;
	}

	//☆☆☆
	//球判定
	//☆☆☆

	//球判定用の変数を作成
	KdCollider::SphereInfo sphere;
	//球の中心位置を設定
	sphere.m_sphere.Center = m_pos + Math::Vector3(0, 0.5f,0);
	//球の半径を設定
	sphere.m_sphere.Radius = 0.3f;
	//当たり判定をしたいタイプを設定
	sphere.m_type = KdCollider::TypeGround|KdCollider::TypeBump;
	//デバッグ用
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center,sphere.m_sphere.Radius);

	//球が当たったオブジェクト情報を作成
	std::list<KdCollider::CollisionResult> retSphereList;

	//☆☆☆☆☆☆☆☆☆
	//球と当たり判定☆
	//☆☆☆☆☆☆☆☆☆
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		if (obj->Intersects(sphere, &retSphereList))
		{
			//このif文に入ったら当たっている
			if (obj->GetObjectType() == KdGameObject::Enemy)
			{
				//このif文に入ったら敵確定
				obj->OnHit();
			}
		}
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

void Player::Init()
{
	m_polygon.SetMaterial("Asset/Textures/chara.png");
	m_pos = { -25,0,0 };

	//画像分割
	m_polygon.SetSplit(6, 6);

	//原点変更
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	//デバッグ用
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

	keyFlg = false;

}

void Player::DrawLit()
{
	//ディゾルブ
	static float d = 1;
	d -= 0.01f;
	if (d < 0)
	{
		d = 1;
	}
	KdShaderManager::Instance().m_StandardShader.SetDissolve(d);

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon,m_mWorld);
}

void Player::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}
