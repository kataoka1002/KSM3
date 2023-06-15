#pragma once
#include "Game.h"

class Game;
class Player;

class AttackBase : public IGameObject
{
public:
	AttackBase(){};

	virtual ~AttackBase() {};


	bool Start();
	void Move(float deleteDir);


	//純粋仮想関数にして、派生クラスで実装する
	virtual void Update()					= 0;
	virtual void Render(RenderContext& rc)	= 0;
	virtual void DestroyWithImpactEffect()	= 0;
	virtual void SetUp()					= 0;


	/// <summary>
	/// エフェクトを再生する
	/// </summary>
	/// <param name="name">エフェクトの名前</param>
	/// <param name="pos">発生させる場所</param>
	/// <param name="rot">回転量</param>
	/// <param name="scale">スケール</param>
	void PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale);
	
	
	/// <summary>
	/// ダメージ処理
	/// </summary>
	/// <param name="damage">与えるダメージ量</param>
	void DamageEvent(float damage);


	/// <summary>
	/// 弾の初期化
	/// </summary>
	/// <param name="scale">スケール</param>
	void BulletSetUp(float scale);


	/// <summary>
	/// 回転量をセットする
	/// </summary>
	/// <param name="rot">回転量</param>
	void SetRotation(Quaternion rot)
	{
		m_originRotation = rot;
	}


	/// <summary>
	/// ポジションの設定
	/// </summary>
	/// <param name="pos">ポジション</param>
	void SetPosition(Vector3 pos)
	{
		m_position = pos;
	}


	/// <summary>
	/// ローカルポジションの設定
	/// </summary>
	/// <param name="pos">ローカルポジション</param>
	void SetLocalPosition(Vector3 pos)
	{
		m_bulletLocalPosition = pos;
	}


	//getter関数-----------------------------------------------------



	//---------------------------------------------------------------

protected:

	Game* m_game = nullptr;
	Player* m_player = nullptr;

	ModelRender m_bulletModel;						//弾のモデル
	Vector3 m_position = Vector3::Zero;				//ポジション
	Vector3 m_bulletForward = Vector3::Zero;		//前方向
	Vector3 m_bulletLocalPosition = Vector3::Zero;	//弾のローカルポジション
	Quaternion m_rot;
	Quaternion m_originRotation;

	float m_bulletDamage = 0.0f;
	float m_fallSpeed = 0.0f;
	float m_moveSpeed = 0.0f;
	float m_decreaseSpeed = 0.0f;
	float m_addFallSpeed = 0.0f;
};

