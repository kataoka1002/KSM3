#pragma once
#include "WeaponBase.h"

class Left_arm_weapons : public WeaponBase
{
public:
	Left_arm_weapons();
	~Left_arm_weapons();

	void Update()					override;
	void Render(RenderContext& rc)	override;
	void SetUp()					override;
	void InitWeapon()				override;
	void DestroyEvent()				override;
	void SetBulletLocalPosition()	override;

};

