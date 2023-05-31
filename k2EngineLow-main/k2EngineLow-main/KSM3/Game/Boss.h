#pragma once
#define HP 2000.0f

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
	void Move();//移動処理
	void Damage();
	void SetHPScale();
	void PlayerSearch();//索敵


	Player* b_player = nullptr;
	Battle_ship_attack* b_battle_ship_attack;
	Drop_item* drop_item;
	Boss_Riser* b_boss_riser;
	Boss_Shovel* b_boss_shovel;
	Boss_Drill* b_boss_drill;
	Boss_Cannon* b_boss_cannon;
	Customize_UI_ver2* m_customizeUI = nullptr;
	Boss_Turbo* b_boss_turbo;
	Result* result;
	Game* boss_game;
	Left_arm_weapons* m_leftArm = nullptr;
	Left_leg_weapons* m_leftLeg = nullptr;
	Right_arm_weapons* m_rightArm = nullptr;
	Right_leg_weapons* m_rightLeg = nullptr;
	Shoulder_weapons* m_shoulder = nullptr;
	SoundSource* m_battleShipGunTyakutiSE;
	Boss_Saber* b_boss_saber;

	//std::vector<Boss_Riser*>m_riserObject;

	ModelRender boss_modelRender;//モデルレンダー
	SpriteRender m_bossHPSprite;
	SpriteRender m_bossHPWakuSprite;
	SpriteRender m_bossHPWakuSprite2;
	EffectEmitter* m_BossEffect = nullptr;
	EffectEmitter* Boss_Explosion;
	EffectEmitter* Explosion_Another;
	EffectEmitter* Boss_attack_efe;
	EffectEmitter* Boss_attack_Explosion_efe;
	Vector3 boss_position;//座標
	CharacterController boss_characterController;//キャラクターコントローラー
	Quaternion boss_rotation;//クォータニオン
	
	Vector3 boss_moveSpeed;//移動速度
	Vector3 boss_forward{ 0.0f,0.0f,-1.0f };//エネミーの正面ベクトル
	Vector3 riser_pos;

	int boss_weapons = 1;
	int boss_game_state = 0;   
	int attack_state = 0;		//攻撃中かどいうか。0が攻撃中じゃ無い。
	int time_score = 10000;
	float boss_HP = HP;
	float BOSS_HP_MAX = HP;
	float boss_time = 0.0f;
	float boss_time_score = 0.0f;
	bool defeat_state = false;

	bool Boss_attack = false;
	int Boss_Rotation_count = 0;

	int Boss_efecount = 0;
	Vector3 movespeed = { 0.0f,0.0f,0.0f };

	int Death_count = 0;
	float Scale = 15.0f;
	float Efect_scale = 70.0f;
	int boss_attack_count = 0;
	int Boss_attack_kind = 1;
	Vector3 attack_efe_LP = { 0.0f,1000.0f,0.0f };
};

