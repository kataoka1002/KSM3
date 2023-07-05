#pragma once

class Player;
class Boss;
class Boss_Cannon_attack;
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
	void Render(RenderContext& rc);
	void Rotation();

	/// <summary>
	/// �L���m���̑傫������
	/// </summary>
	/// <param name="amount">������</param>
	void DecreaseScale(float amount)
	{
		m_cannonScale -= amount;
	}

	/// <summary>
	/// �L���m���̑傫����ݒ�
	/// </summary>
	void SetCannonScale()
	{
		m_cannonModel.SetScale(m_cannonScale);
	}

	/// <summary>
	/// �U���ł��邩�ǂ�����ݒ�
	/// </summary>
	/// <param name="attack"></param>
	void SetAttackOK(bool attack)
	{
		m_attackOK = attack;
	}

	/// <summary>
	/// �t���O���Z�b�g
	/// </summary>
	/// <param name="flag"></param>
	void SetAttackFlag(bool flag)
	{
		m_attackFlag = flag;
	}

private:
	Player* m_player = nullptr;
	Boss* m_boss = nullptr;
	Boss_Saber* m_bossSaber = nullptr;
	Boss_Cannon_attack* m_cannonAttack = nullptr;
	Game* m_game = nullptr;
	EffectEmitter* m_weaponEffect = nullptr;
	SoundSource* m_cannonChargeSE = nullptr;

	CharacterController m_enemyCharacterController;	//�G�l�~�[�L�����R��
	Quaternion m_rotation;
	ModelRender m_cannonModel;

	Vector3 m_position = Vector3::Zero;
	Vector3 m_forward = { 0.0f,0.0f,1.0f };
	Vector3 m_localPosition = { 0.0f,0.0f,0.0f };
	Vector3 m_effectLocalPos = { 0.0f,680.0f,0.0f };
	bool m_attackFlag = false;
	bool m_attackOK = false;
	int m_fireCount = 0;
	int m_fast = 0;
	float m_HP = 500.0f;
	float m_cannonScale = 15.0f;
};