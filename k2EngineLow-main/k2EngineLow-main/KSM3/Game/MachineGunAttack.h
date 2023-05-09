#pragma once

class Player;
class Game;
class Boss;

class MachineGunAttack :public IGameObject
{
public:
	MachineGunAttack();
	~MachineGunAttack();
	bool Start();
	void Setup();
	void Update();
	void Move();
	void Damage();
	void Render(RenderContext& rc);

	Player* m_player = nullptr;
	Game* m_game = nullptr;
	Boss* m_boss = nullptr;

	ModelRender m_bulletModel;
	Vector3 m_position;
	Vector3 m_bulletForward;
	Quaternion m_rot;
	Vector3 m_moveSpeed;

	bool m_atackState = true;
	bool Landing_state_BB = false;
	float m_fallSpeed = 0.0f;
};

