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
	/// 攻撃処理 (弾の生成)
	/// </summary>
	/// <param name="customPoint">取り付けている武器の種類</param>
	void MakeBullet(int customPoint);


	/// <summary>
	/// 武器の初期化を行う
	/// </summary>
	/// <param name="customPoint">取り付けている武器の種類</param>
	void SetWeapon(int customPoint);


	/// <summary>
	/// 取り付ける武器の種類を教える
	/// </summary>
	/// <param name="weaponKind">武器の種類</param>
	void SetWeaponKind(int weaponKind)
	{
		m_setWeapon = weaponKind;
	}


	/// <summary>
	/// ダメージ処理
	/// </summary>
	/// <param name="Damage">与えるダメージ</param>
	void ApplyDamage(float Damage)
	{
		m_HP -= Damage;

		m_HP = max(m_HP, 0.0f);
	}


	//getter----------------------------------------------------------------------

	/// <summary>
	/// セットしている武器の種類を返す
	/// </summary>
	/// <returns>セットしている武器の種類</returns>
	int GetWeaponKind()
	{
		return m_setWeapon;
	}


	/// <summary>
	/// 現在の体力を返す
	/// </summary>
	/// <returns>現在の体力</returns>
	float GetHP()
	{
		return m_HP;
	}


	/// <summary>
	/// HPの最大値を返す
	/// </summary>
	/// <returns>HPの最大値</returns>
	float GetHPMax()
	{
		return m_HPMax;
	}


	/// <summary>
	/// 今いるポジションを返す
	/// </summary>
	/// <returns>今いるポジション</returns>
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


	const float MACHINEGUN_HP_MAX	= 700.0f;	//マシンガンのHPの最大値
	const float GIGATON_HP_MAX		= 500.0f;	//ギガトンキャノンのHPの最大値
	const float BATTLESHIP_HP_MAX	= 400.0f;	//戦艦砲のHPの最大値

	const float MACHINEGUN_SCALE	= 2.0f;		//マシンガンの大きさ
	const float GIGATON_SCALE		= 0.8f;		//ギガトンキャノンの大きさ
	const float BATTLESHIP_SCALE	= 2.0f;		//戦艦砲の大きさ

};

