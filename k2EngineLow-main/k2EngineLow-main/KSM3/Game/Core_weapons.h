#pragma once

class Core_weapons_attack;
class Player;
class Core_weapons:public IGameObject, Noncopyable
{
public:
	Core_weapons();
	~Core_weapons();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void WeaponSet();
	void MakeBullet();

	Vector3 GetPosition()
	{
		return m_position;
	}

	Quaternion GetRotation()
	{
		return m_rotation;
	}

	int GetSetWeapon()
	{
		return m_setWeapon;
	}

private:
	Player* m_player = nullptr;
	Core_weapons_attack* m_coreWeaponAttack;


	Quaternion m_rotation;
	ModelRender m_coreWeaponModel;

	Vector3 m_position = Vector3::Zero;
	Vector3 m_localPosition = { 0.0f,80.0f,10.0f };
	Vector3 m_scale = { 1.0f,1.0f,1.5f };
	int m_setWeapon = 2;	//0:空オブジェクト 1:ギガプラズマ  2:Versatile_Perforator
	int m_firingCount = 0;
};

