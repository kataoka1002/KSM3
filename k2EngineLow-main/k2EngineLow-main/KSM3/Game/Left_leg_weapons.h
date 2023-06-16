#pragma once
#include "WeaponBase.h"

class Left_leg_weapons : public WeaponBase
{
public:
	Left_leg_weapons();
	~Left_leg_weapons();

	void Update()					override;
	void Render(RenderContext& rc)	override;
	void SetUp()					override;
	void InitWeapon()				override;
	void DestroyEvent()				override;
	void SetBulletLocalPosition()	override;

};

