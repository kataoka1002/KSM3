#pragma once
#include "WeaponBase.h"

class Right_leg_weapons : public WeaponBase
{
public:
	Right_leg_weapons();
	~Right_leg_weapons();

	void Update()					override;
	void Render(RenderContext& rc)	override;
	void SetUp()					override;
	void InitWeapon()				override;
	void DestroyEvent()				override;
	void SetBulletLocalPosition()	override;

};

