#pragma once
#define HP 200.0f

class Player;
class Battle_ship_attack;
class Drop_item;
class Enemy_weapons;

class Enemy_type2 :public IGameObject
{
public:
	Enemy_type2();
	~Enemy_type2();

	bool Start();
	void Update();//更新処理
	void Render(RenderContext& rc);//描画処理
	void Move();//移動処理
	void PlayerSearch();//索敵

	Player* e_player = nullptr;
	Battle_ship_attack* e_battle_ship_attack;
	Drop_item* drop_item;
	Enemy_weapons* e_enemy_weapons;

	ModelRender enemy_modelRender;//モデルレンダー
	Vector3 enemy_position;//座標
	CharacterController enemy_characterController;//キャラクターコントローラー
	Quaternion enemy_rotation;//クォータニオン
	Vector3 enemy_moveSpeed;//移動速度
	Vector3 enemy_forward{ 0.0f,0.0f,-1.0f };//エネミーの正面ベクトル

	bool defeat_state = false;

	int enemy_weapons = 1;
	int enemy_game_state = 0;

	float enemy_HP = HP;
};

