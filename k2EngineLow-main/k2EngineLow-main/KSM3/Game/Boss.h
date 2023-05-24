#pragma once
#define HP 2000.0f

class Player;
class Battle_ship_attack;
class Drop_item;
class Boss_Riser;
class Boss_Shovel;
class Boss_Drill;
class Boss_Cannon;
class Boss_Turbo;
class Result;
class Game;

class Boss :public IGameObject
{
public:
	Boss();
	~Boss();

	bool Start();
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
	Boss_Turbo* b_boss_turbo;
	Result* result;
	Game* boss_game;

	//std::vector<Boss_Riser*>m_riserObject;

	ModelRender boss_modelRender;//モデルレンダー
	SpriteRender m_bossHPSprite;
	SpriteRender m_bossHPWakuSprite;
	SpriteRender m_bossHPWakuSprite2;
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

	Vector3 movespeed = { 0.0f,0.0f,0.0f };
};

