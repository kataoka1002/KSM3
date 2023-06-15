#pragma once
#include "AttackBase.h"

class GigatonCannonAttack : public AttackBase
{
public:
	GigatonCannonAttack();
	~GigatonCannonAttack();

	void Update()					override;
	void DestroyWithImpactEffect()	override;
	void Render(RenderContext& rc)	override;
	void SetUp()					override;

private:

	SoundSource* m_cannonSE = nullptr;	//ƒMƒKƒgƒ“ƒLƒƒƒmƒ“SE

};

