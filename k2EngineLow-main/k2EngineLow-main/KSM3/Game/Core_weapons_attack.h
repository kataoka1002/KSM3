#pragma once
#include "AttackBase.h"

class Core_weapons_attack : public AttackBase
{
public:
	Core_weapons_attack();
	~Core_weapons_attack();

	void Update()					override;
	void DestroyWithImpactEffect()	override;
	void Render(RenderContext& rc)	override;
	void SetUp()					override;

private:

	Core_weapons* m_coreWeapon = nullptr;

};

