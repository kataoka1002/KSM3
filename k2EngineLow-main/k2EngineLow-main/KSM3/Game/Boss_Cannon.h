#pragma once
#define HP 500.0f

class Player;
class Boss;
class Boss_Cannon_attack;
class Drop_item;
class Game;
class Boss_Saber;

class Boss_Cannon :public IGameObject
{
public:
	Boss_Cannon();
	~Boss_Cannon();

	void Setup();
	void Update();
	void Move();
	void PlayerSearch();
	void Render(RenderContext& rc);
	void Rotation();

	Player* b_w_player;
	Boss* b_w_boss;
	Boss_Saber* m_bossSaber;
	Boss_Cannon_attack* b_boss_weapons;
	Drop_item* m_dropItem;
	Game* m_game;
	EffectEmitter* m_weaponEffect = nullptr;
	SoundSource* m_Cannon_ChargeSE = nullptr;
	//CharacterController boss_riser_characterContller;
	CharacterController m_enemyCharacterController;	//エネミーキャラコン
	Quaternion b_w_rotation;
	Vector3 b_w_position;
	Vector3 b_w_moveSpeed;
	Vector3 b_w_Fowrad = { 0.0f,0.0f,1.0f };
	int game_state = 0;
	ModelRender boss_Cannon_Render;

	//いる。絶対。
	Vector3 b_w_localposition = { 00.0f,00.0f,-0.0f };
	Vector3 efeLP = { 0.0f,680.0f,-00.0f };
	bool m_attackState = false;
	bool attack_ok = false;
	bool defeatState = false;//死んだかどうかのフラグ。
	int set_weapons = 0;

	int firing_cound = 0;
	int fast = 0;

	float connon_HP = HP;
	float scale = 15.0f;
};