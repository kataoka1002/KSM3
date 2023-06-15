#pragma once
#include "AttackBase.h"

class Battle_ship_attack : public AttackBase
{
public:
	Battle_ship_attack();
	~Battle_ship_attack();

	void SmokeEfect();

	void Update()					override;
	void DestroyWithImpactEffect()	override;
	void Render(RenderContext& rc)	override;
	void SetUp()					override;

private:

	SoundSource* m_battleShipGunTyakudanSE = nullptr;	//’…’eSE
	SoundSource* m_battleShipGunSE = nullptr;			//”­ŽËSE

	Vector3 m_kemuriEfePos = Vector3::Zero;

	int m_smokeCount = 0;
};

