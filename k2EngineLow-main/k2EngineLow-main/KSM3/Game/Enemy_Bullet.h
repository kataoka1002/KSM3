#pragma once
#include "sound/SoundSource.h"

class Customize_UI_ver2;
class Core_weapons;
class Enemy;
class Enemy_Near;
class Enemy_Far;
class Player;
class Game;
class Left_arm_weapons;
class Left_leg_weapons;
class Right_arm_weapons;
class Right_leg_weapons;
class Shoulder_weapons;


class Enemy_Bullet : public IGameObject
{
public:
	Enemy_Bullet();
	~Enemy_Bullet();

	void Setup();
	void Update();
	void Move();
	void MoveNear();
	void MoveFar();
	bool Start();
	void Effect(int num);
	void Render(RenderContext& rc);
	void FindWeapon();
	void Damage(int weaponNum);
	void DestroyWithImpactEffect();
	void PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale);

	/// <summary>
	/// 弾の親を設定する
	/// </summary>
	/// <param name="enemy">エネミーのポインタ</param>
	void SetEnemyMama(Enemy* enemy)
	{
		m_enemyMama = enemy;
	}


	/// <summary>
	/// 弾の親を設定する
	/// </summary>
	/// <param name="enemy">エネミーのポインタ</param>
	void SetEnemyFarMama(Enemy_Far* enemy)
	{
		m_enemyFarMama = enemy;
	}


	/// <summary>
	/// 弾の親を設定する
	/// </summary>
	/// <param name="enemy">エネミーのポインタ</param>
	void SetEnemyNearMama(Enemy_Near* enemy)
	{
		m_enemyNearMama = enemy;
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
	/// 弾の回転を教える
	/// </summary>
	/// <param name="rot">回転量</param>
	void SetRotation(Quaternion rot)
	{
		originRotation = rot;
	}


	/// <summary>
	/// ローカルポジションの設定
	/// </summary>
	/// <param name="pos">ローカルポジション</param>
	void SetLocalPosition(Vector3 pos)
	{
		m_bulletLocalPosition = pos;
	}



private:
	Customize_UI_ver2* m_customizeUI = nullptr;
	Core_weapons* m_coreWeapons = nullptr;
	Enemy* m_enemyMama = nullptr;
	Enemy_Near* m_enemyNearMama = nullptr;
	Enemy_Far* m_enemyFarMama = nullptr;
	Player* m_player = nullptr; 
	Game* m_game = nullptr;
	Left_arm_weapons* m_leftArm = nullptr;
	Left_leg_weapons* m_leftLeg = nullptr;
	Right_arm_weapons* m_rightArm = nullptr;
	Right_leg_weapons* m_rightLeg = nullptr;
	Shoulder_weapons* m_shoulder = nullptr;
	SoundSource* m_battleShipGunTyakutiSE = nullptr;		//戦艦砲SE
	std::unique_ptr<ModelRender> m_bulletModel;				//スマートポインタ

	Quaternion m_aim;
	Quaternion m_rot;
	Quaternion originRotation;
	Vector3 m_position = Vector3::Zero;
	Vector3 m_bulletFowrad = Vector3::Zero;
	Vector3 m_toCoreWeapons = Vector3::Zero;
	Vector3 m_bulletSpeed = Vector3::Zero;
	Vector3 m_bulletLocalPosition = Vector3::Zero;	//弾のローカルポジション

	float m_fallSpeed = 0.0f;
	bool m_attuckState = true;
	bool Landing_state = false;

	
};

