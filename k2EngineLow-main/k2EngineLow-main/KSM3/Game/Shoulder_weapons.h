#pragma once
#include "WeaponBase.h"
class Battle_ship_attack;
class MachineGunAttack;
class GigatonCannonAttack;

class Shoulder_weapons : public WeaponBase
{
public:
	Shoulder_weapons();
	~Shoulder_weapons();

	void Update()					override;
	void Render(RenderContext& rc)	override;
	void SetUp()					override;
	void InitWeapon()				override;
	void DestroyEvent()				override;
	void SetBulletLocalPosition()	override;

	void Move2();	//マシンガン用
	void MakeBullet2(int customPoint);

private:

	Battle_ship_attack* m_battleShipAttack2 = nullptr;
	MachineGunAttack* m_machineGunAttack2 = nullptr;
	GigatonCannonAttack* m_gigatonAttack2 = nullptr;

	std::unique_ptr<ModelRender> m_machineGunWeapon2;	//マシンガンの2個目
	Quaternion m_rotation2;
	Vector3 m_position2 = Vector3::Zero;
	Vector3 m_localPosition2 = Vector3::Zero;
	int m_firingCount2 = 0;

};

