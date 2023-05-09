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

	//std::vector<Boss_Riser*>m_riserObject;

	ModelRender boss_modelRender;//モデルレンダー
	Vector3 boss_position;//座標
	CharacterController boss_characterController;//キャラクターコントローラー
	Quaternion boss_rotation;//クォータニオン
	Vector3 boss_moveSpeed;//移動速度
	Vector3 boss_forward{ 0.0f,0.0f,-1.0f };//エネミーの正面ベクトル
	Vector3 riser_pos;

	bool defeat_state = false;

	int boss_weapons = 1;
	int boss_game_state = 0;
	int attack_state = 0;		//攻撃中かどいうか。0が攻撃中じゃ無い。

	float boss_HP = HP;
};

