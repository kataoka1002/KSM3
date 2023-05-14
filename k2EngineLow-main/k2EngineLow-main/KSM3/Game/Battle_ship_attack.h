#pragma once

class Player;
class Enemy;
class Game;
class Boss;

class Battle_ship_attack :public IGameObject
{
public:
	Battle_ship_attack();
	~Battle_ship_attack();
	bool Start();
	void Setup();
	void Update();
	void Move();
	void Damage();
	void EfeEfe();
	void Render(RenderContext& rc);


	Player* m_player = nullptr;
	Game* m_game = nullptr;
	Boss* m_boss = nullptr;
	EffectEmitter* m_kemuriEffect = nullptr;
	EffectEmitter* m_tyakudanEffect = nullptr;
	SoundSource* m_battleShipGunTyakudanSE = nullptr;	//戦艦砲SE
	SoundSource* m_battleShipGunSE = nullptr;			//戦艦砲SE


	ModelRender m_bulletModel;
	Quaternion B_S_aiming;
	Quaternion originRotation;
	Vector3 firing_position = Vector3::Zero;
	Vector3 m_bulletForward = Vector3::Zero;
	Vector3 m_kemuriEfePos = Vector3::Zero;
	Vector3 m_bulletLocalPosition = Vector3::Zero;	//弾のローカルポジション


	bool Landing_state_BB = false;
	float move_speed = 30.0f;
	float fall_speed = 0.0f;
	float m_bulletDamage = 50.0f;
	bool atack_state = true;
	int m_kemuriCount = 0;
	
};

