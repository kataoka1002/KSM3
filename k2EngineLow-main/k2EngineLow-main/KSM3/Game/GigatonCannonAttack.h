#pragma once

class Player;
class Game;
class Boss;

class GigatonCannonAttack :public IGameObject
{
public:
	GigatonCannonAttack();
	~GigatonCannonAttack();
	bool Start();
	void Setup();
	void Update();
	void Move();
	void Damage();
	void DestroyWithImpactEffect();
	void Render(RenderContext& rc);

	Player* m_player = nullptr;
	Game* m_game = nullptr;
	Boss* m_boss = nullptr;
	EffectEmitter* m_tyakudanEffect = nullptr;
	SoundSource* m_cannonSE = nullptr;					//ギガトンキャノンSE


	ModelRender m_bulletModel;
	Vector3 m_position = Vector3::Zero;
	Vector3 m_bulletForward = Vector3::Zero;
	Vector3 m_moveSpeed = Vector3::Zero;
	Vector3 m_bulletLocalPosition = Vector3::Zero;	//弾のローカルポジション
	Quaternion m_rot;
	Quaternion originRotation;

	bool m_atackState = true;
	bool Landing_state_BB = false;
	float m_fallSpeed = 0.0f;
	float m_bulletDamage = 100.0f;

};

