#pragma once
class Player;
class PlayerUI;
class Customize_UI_ver2;
class MachineGunAttack;
class GigatonCannonAttack;
class Battle_ship_attack;

class WeaponBase : public IGameObject
{
public:
	WeaponBase(){};

	virtual ~WeaponBase() {};

	bool Start();
	void Move();

	/// <summary>
	/// �U������ (�e�̐���)
	/// </summary>
	/// <param name="customPoint">���t���Ă��镐��̎��</param>
	void MakeBullet(int customPoint);


	/// <summary>
	/// ����̏��������s��
	/// </summary>
	/// <param name="customPoint">���t���Ă��镐��̎��</param>
	void SetWeapon(int customPoint);


	/// <summary>
	/// ���t���镐��̎�ނ�������
	/// </summary>
	/// <param name="weaponKind">����̎��</param>
	void SetWeaponKind(int weaponKind)
	{
		m_setWeapon = weaponKind;
	}


	/// <summary>
	/// �_���[�W����
	/// </summary>
	/// <param name="Damage">�^����_���[�W</param>
	void ApplyDamage(float Damage)
	{
		m_HP -= Damage;

		m_HP = max(m_HP, 0.0f);
	}


	//getter----------------------------------------------------------------------

	/// <summary>
	/// �Z�b�g���Ă��镐��̎�ނ�Ԃ�
	/// </summary>
	/// <returns>�Z�b�g���Ă��镐��̎��</returns>
	int GetWeaponKind()
	{
		return m_setWeapon;
	}


	/// <summary>
	/// ���݂̗̑͂�Ԃ�
	/// </summary>
	/// <returns>���݂̗̑�</returns>
	float GetHP()
	{
		return m_HP;
	}


	/// <summary>
	/// HP�̍ő�l��Ԃ�
	/// </summary>
	/// <returns>HP�̍ő�l</returns>
	float GetHPMax()
	{
		return m_HPMax;
	}


	/// <summary>
	/// ������|�W�V������Ԃ�
	/// </summary>
	/// <returns>������|�W�V����</returns>
	Vector3 GetPosition()
	{
		return m_position;
	}

	//----------------------------------------------------------------------------

	virtual void Update()					= 0;
	virtual void Render(RenderContext& rc)	= 0;
	virtual void SetUp()					= 0;
	virtual void InitWeapon()				= 0;
	virtual void DestroyEvent()				= 0;
	virtual void SetBulletLocalPosition()	= 0;

protected:

	Player* m_player = nullptr;
	PlayerUI* m_playerUI = nullptr;
	Customize_UI_ver2* m_customizeUI = nullptr;
	MachineGunAttack* m_machineGunAttack = nullptr;
	GigatonCannonAttack* m_gigatonAttack = nullptr;
	Battle_ship_attack* m_battleShipAttack = nullptr;

	ModelRender m_weaponModel;
	Quaternion m_rotation;
	Vector3 m_position = Vector3::Zero;
	Vector3 m_moveSpeed = Vector3::Zero;
	Vector3 m_localPosition = Vector3::Zero;
	Vector3 m_forward = { 0.0f, 0.0f, 1.0f };

	int m_setWeapon = 0;
	int m_firingCount = 0;
	float m_HP = 0.0f;
	float m_HPMax = 0.0f;


	const float MACHINEGUN_HP_MAX	= 700.0f;	//�}�V���K����HP�̍ő�l
	const float GIGATON_HP_MAX		= 500.0f;	//�M�K�g���L���m����HP�̍ő�l
	const float BATTLESHIP_HP_MAX	= 400.0f;	//��͖C��HP�̍ő�l

	const float MACHINEGUN_SCALE	= 2.0f;		//�}�V���K���̑傫��
	const float GIGATON_SCALE		= 0.8f;		//�M�K�g���L���m���̑傫��
	const float BATTLESHIP_SCALE	= 2.0f;		//��͖C�̑傫��

};

