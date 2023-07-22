#include "stdafx.h"
#include "GuideLight.h"
#include "Game.h"
#include "Player.h"

GuideLight::GuideLight()
{

}

GuideLight::~GuideLight()
{

}

bool GuideLight::Start()
{

	//メモリの確保
	m_modelRender = std::make_unique<ModelRender>();


	//モデルの初期化
	m_modelRender->Init("Assets/modelData/V_P_Bullet.tkm");
	m_modelRender->SetPosition(m_position);
	m_modelRender->SetScale(SCALE);
	m_modelRender->Update();
	
	return true;
}

void GuideLight::Update()
{
	//モデルの移動系の処理
	const float BULLET_SPPED = 20.0f;
	const float CURVATURE_RADIUS = 30.0f;
	const float DAMPING = 0.1f;

	CalcVelocity(BULLET_SPPED, CURVATURE_RADIUS, DAMPING);
	m_position += m_velocity;
	m_modelRender->SetPosition(m_position);
	m_modelRender->Update();

	//2フレーム毎に光発生
	if (count % 2 == 0)
	{
		m_guideLightEffect = NewGO<EffectEmitter>(0);
		m_guideLightEffect->Init(enGuide);
		m_guideLightEffect->SetScale({ 0.5f,0.5f,0.5f });
		m_guideLightEffect->SetPosition(m_position);
		m_guideLightEffect->Play();
	}

	//ある程度時間がたつと消える
	if (count >= 120)
	{
		DeleteGO(this);
	}
	count++;
}

void GuideLight::CalcVelocity(const float speed, const float curvatureRadius,const float damping)
{
	//遠心力を求める
	float maxCentripetalAccel = speed * speed / curvatureRadius;

	//スピードに減衰率をかけて逆方向への力を求める
	float propulsion = speed * damping;

	//目標の地点
	Vector3 targetPosition = m_targetPosition;

	//目標までのベクトル
	Vector3 toTarget = targetPosition - m_position;

	//速度を設定し、正規化して打ち出された方向を取得
	Vector3 vn = m_velocity;
	vn.Normalize();

	//目標までのベクトルと打ち出された方向の内積を求める(敵へ向かうベクトルをvnに射影し T'の大きさが求まる)
	float dot = toTarget.Dot(vn);

	//T'から目標までのベクトル(曲げるために加える加速度)を求める
	Vector3 centripetalAccel = toTarget - (vn * dot);

	//その長さを求める
	float centripetalAccelMagnitude = centripetalAccel.Length();

	//1以上なら長さを1に正規化し,1未満ならそのまま
	if (centripetalAccelMagnitude > 1.0f)
	{
		//ベクトルの正規化を行う
		centripetalAccel /= centripetalAccelMagnitude;
	}

	//長さがmaxCentripetalAccel以下ならそのまま、以上なら長さをmaxCentripetalAccelにする
	Vector3 force = centripetalAccel * maxCentripetalAccel;

	//推進力
	force += vn * propulsion;

	//空気抵抗
	force -= m_velocity * damping;

	//速度積分
	m_velocity += force * g_gameTime->GetFrameDeltaTime();
}

void GuideLight::Render(RenderContext& rc)
{
	//弾は見えなくてよい
	//m_modelRender->Draw(rc);
}