#pragma once

class Boss;
class Boss_Shovel;
class Core_weapons;
class Player;

class Boss_Shovel_attack :public IGameObject
{
public:
	Boss_Shovel_attack();
	~Boss_Shovel_attack();

	void SetUp();
	void Update();
	void Move();
	void Render(RenderContext& rc);

private:
	Boss_Shovel* m_weapon = nullptr;
	Boss* m_boss = nullptr;
	Core_weapons* m_coreWeapon = nullptr;
	Player* m_player = nullptr;
	SoundSource* m_attackSE = nullptr;

	ModelRender m_bulletModel;
	Quaternion m_aim;
	Vector3 m_firePosition = Vector3::Zero;
	Vector3 m_bulletForward = Vector3::Zero;

	float m_moveSpeed = 30.0f;
	float m_fallSpeed = 0.0f;
	bool m_fastFlag = true;
};