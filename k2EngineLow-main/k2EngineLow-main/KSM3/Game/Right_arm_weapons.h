#pragma once
#include "WeaponBase.h"

class Right_arm_weapons : public WeaponBase
{
public:
	Right_arm_weapons();
	~Right_arm_weapons();

	void Update()					override;
	void Render(RenderContext& rc)	override;
	void SetUp()					override;
	void InitWeapon()				override;
	void DestroyEvent()				override;
	void SetBulletLocalPosition()	override;

};

