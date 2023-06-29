#pragma once


class Player;
class Battle_ship_attack;
class Drop_item;
class Boss_Riser;
class Boss_Shovel;
class Customize_UI_ver2;
class Boss_Drill;
class Boss_Cannon;
class Boss_Turbo;
class Result;
class Game;
class Boss_Saber;
class GameCamera;
class Left_arm_weapons;
class Left_leg_weapons;
class Right_arm_weapons;
class Right_leg_weapons;
class Shoulder_weapons;

class Boss :public IGameObject
{
public:
	Boss();
	~Boss();

	bool Start();
	void Player_Damage(int boss_damage_kind,bool Landing_state);
	void Update();//更新処理
	void Render(RenderContext& rc);//描画処理
	void Damage();
	void SetHPScale();
	void PlayerSearch();//索敵

	Quaternion GetRotation()
	{
		return m_rotation;
	}

	Vector3 GetPosition()
	{
		return m_position;
	}

	Vector3 GetForward()
	{
		return m_forward;
	}

	Boss_Saber* GetSaber()
	{
		return m_bossSaber;
	}

	Boss_Shovel* GetShovel()
	{
		return m_bossShovel;
	}

	Boss_Drill* GetDrill()
	{
		return m_bossDrill;
	}

	void ApplyDamage(float damage)
	{
		m_HP -= damage;

		m_HP = max(0.0f, m_HP);
	}

	void SetPosition(Vector3 pos)
	{
		m_position = pos;
	}

private:
	Player* m_player = nullptr;
	Drop_item* m_dropItem;
	Boss_Riser* m_bossRiser;
	Boss_Shovel* m_bossShovel;
	Boss_Drill* m_bossDrill;
	Boss_Cannon* m_bossCannon;
	Customize_UI_ver2* m_customizeUI = nullptr;
	Boss_Turbo* m_bossTurbo;
	Result* m_result;
	Game* m_game;
	Left_arm_weapons* m_leftArm = nullptr;
	Left_leg_weapons* m_leftLeg = nullptr;
	Right_arm_weapons* m_rightArm = nullptr;
	Right_leg_weapons* m_rightLeg = nullptr;
	Shoulder_weapons* m_shoulder = nullptr;
	SoundSource* m_battleShipGunTyakutiSE;
	Boss_Saber* m_bossSaber;
	EffectEmitter* m_BossEffect = nullptr;
	EffectEmitter* m_bossExplosion;
	EffectEmitter* m_explosionAnother;
	EffectEmitter* m_bossAttackEfe;
	EffectEmitter* m_bossAttackExplosionEfe;

	SpriteRender m_bossHPSprite;
	SpriteRender m_bossHPWakuSprite;
	SpriteRender m_bossHPWakuSprite2;
	ModelRender m_modelRender;//モデルレンダー
	CharacterController m_characterController;//キャラクターコントローラー
	Quaternion m_rotation;//クォータニオン
	
	Vector3 m_position;//座標
	Vector3 m_forward={ 0.0f,0.0f,-1.0f };//エネミーの正面ベクトル
	Vector3 m_moveSpeed = { 0.0f,0.0f,0.0f };
	Vector3 m_attackEfeLP = { 0.0f,1000.0f,0.0f };

	int m_attackState = 0;		//攻撃中かどいうか。0が攻撃中じゃ無い。
	int m_timeScore = 10000;
	int m_rotationCount = 0;
	int m_bossEfeCount = 0;
	int m_bossAttackCount = 0;
	int m_bossAttackKind = 1;
	int m_deathCount = 0;
	float BOSS_HP_MAX = 2000.0f;
	float m_HP = BOSS_HP_MAX;
	float m_bossTime = 0.0f;
	float m_bossTimeScore = 0.0f;
	float m_scale = 15.0f;
	float m_efectScale = 70.0f;
	bool m_attack = false;

};

