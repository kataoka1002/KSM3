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
	void Render(RenderContext& rc);

	Player* m_player = nullptr;
	Game* m_game = nullptr;

	ModelRender m_bulletModel;
	Quaternion B_S_aiming;
	Vector3 firing_position;
	Vector3 m_bulletForward; 

	bool Landing_state_BB = false;
	float move_speed = 30.0f;
	float fall_speed = 0.0f;
	bool atack_state = true;
	
	
};

