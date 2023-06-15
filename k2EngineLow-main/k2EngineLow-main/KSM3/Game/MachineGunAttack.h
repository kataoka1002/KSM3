#pragma once
#include "AttackBase.h"

class MachineGunAttack : public AttackBase
{
public:
	MachineGunAttack();
	~MachineGunAttack();

	void Update()					override;
	void DestroyWithImpactEffect()	override;
	void Render(RenderContext& rc)	override;
	void SetUp()					override;

private:

};

