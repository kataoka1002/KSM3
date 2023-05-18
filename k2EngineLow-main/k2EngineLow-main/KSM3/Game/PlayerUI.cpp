#include "stdafx.h"
#include "PlayerUI.h"
#include "Player.h"
#include "Right_arm_weapons.h"
#include "Right_leg_weapons.h"
#include "Left_arm_weapons.h";
#include "Left_leg_weapons.h";
#include "Shoulder_weapons.h";


PlayerUI::PlayerUI()
{

}

PlayerUI::~PlayerUI()
{

}

bool PlayerUI::Start()
{
	m_player = FindGO<Player>("player");

	m_HPSprite.Init("Assets/sprite/player/playerUI.dds", 691.0f, 597.0f);
	m_HPSprite.SetPosition({ 600.0f,-300.0f,0.0f });
	m_HPSprite.SetScale({ 0.4f,0.4f,0.4f });
	m_HPSprite.SetMulColor({ UI_START_COLLAR_R,UI_START_COLLAR_G,0.0f,1.0f });
	m_HPSprite.Update();

	return true;
}

void PlayerUI::Update()
{
	//プレイヤーの体力計算
	m_HPSprite.SetMulColor(Damage(m_player->m_playerHP, m_player->m_playerHPMax));
	m_HPSprite.Update();

	//各武器の体力計算
	if (m_rightArm != nullptr)
	{
		m_rightArmHPSprite.SetMulColor(Damage(m_rightArm->m_rightArmHP, m_rightArm->m_rightArmHPMax));
		m_rightArmHPSprite.Update();
	}
	if (m_rightLeg != nullptr)
	{
		m_rightLegHPSprite.SetMulColor(Damage(m_rightLeg->R_l_w_HP, m_rightLeg->R_l_w_HPMax));
		m_rightLegHPSprite.Update();
	}
	if (m_leftArm != nullptr)
	{
		m_leftArmHPSprite.SetMulColor(Damage(m_leftArm->L_a_w_HP, m_leftArm->L_a_w_HPMax));
		m_leftArmHPSprite.Update();
	}
	if (m_leftLeg != nullptr)
	{
		m_leftLegHPSprite.SetMulColor(Damage(m_leftLeg->L_l_w_HP, m_leftLeg->L_l_w_HPMax));
		m_leftLegHPSprite.Update();
	}
	if (m_shoulder != nullptr)
	{
		m_shoulderHPSprite.SetMulColor(Damage(m_shoulder->S_w_HP, m_shoulder->S_w_HPMax));
		m_shoulderHPSprite.Update();
	}
}

Vector4 PlayerUI::Damage(float nowHP, float maxHP)	//第一引数は今のHP、第二引数は最大HP
{
	float m_collarG;	//緑色の量
	float m_collarR;	//赤色の量

	//体力が半分以上の時
	if (nowHP >= maxHP * 0.5f)
	{
		m_collarR = (1.0f - (nowHP * (1.0f / maxHP))) * 2.0f;	//体力が減るほど赤成分が増えていく
		m_collarG = 1.0f;	//緑成分は固定
	}
	//体力が半分以下の時
	else if (nowHP < maxHP * 0.5f)
	{
		m_collarG = (nowHP * (1.0f / maxHP)) * 2.0f;	//体力が減るほど緑成分が減っていく
		m_collarR = 1.0f;	//赤成分は固定
	}

	Vector4 col;	//最終的なカラー
	return col = { m_collarR,m_collarG,0.0f,1.0f };
}

void PlayerUI::WeaponUISetUp(int num)
{
	switch (num)
	{
	case 1:	//右腕
		m_rightArmHPSprite.Init("Assets/sprite/player/weaponUI.dds", 700.0f, 700.0f);
		m_rightArmHPSprite.SetPosition({ 0.0f,0.0f,0.0f });
		m_rightArmHPSprite.SetScale({ 0.4f,0.4f,0.4f });
		m_rightArmHPSprite.SetMulColor({ UI_START_COLLAR_R,UI_START_COLLAR_G,0.0f,1.0f });
		m_rightArmHPSprite.Update();
		break;
	case 2:	//右足
		m_rightLegHPSprite.Init("Assets/sprite/player/weaponUI.dds", 700.0f, 700.0f);
		m_rightLegHPSprite.SetPosition({ 200.0f,0.0f,0.0f });
		m_rightLegHPSprite.SetScale({ 0.4f,0.4f,0.4f });
		m_rightLegHPSprite.SetMulColor({ UI_START_COLLAR_R,UI_START_COLLAR_G,0.0f,1.0f });
		m_rightLegHPSprite.Update();
		break;
	case 3:	//左腕
		m_leftArmHPSprite.Init("Assets/sprite/player/weaponUI.dds", 700.0f, 700.0f);
		m_leftArmHPSprite.SetPosition({ 300.0f,0.0f,0.0f });
		m_leftArmHPSprite.SetScale({ 0.4f,0.4f,0.4f });
		m_leftArmHPSprite.SetMulColor({ UI_START_COLLAR_R,UI_START_COLLAR_G,0.0f,1.0f });
		m_leftArmHPSprite.Update();
		break;
	case 4:	//左足
		m_leftLegHPSprite.Init("Assets/sprite/player/weaponUI.dds", 700.0f, 700.0f);
		m_leftLegHPSprite.SetPosition({ 400.0f,0.0f,0.0f });
		m_leftLegHPSprite.SetScale({ 0.4f,0.4f,0.4f });
		m_leftLegHPSprite.SetMulColor({ UI_START_COLLAR_R,UI_START_COLLAR_G,0.0f,1.0f });
		m_leftLegHPSprite.Update();
		break;
	case 5:	//肩
		m_shoulderHPSprite.Init("Assets/sprite/player/weaponUI.dds", 700.0f, 700.0f);
		m_shoulderHPSprite.SetPosition({ 500.0f,0.0f,0.0f });
		m_shoulderHPSprite.SetScale({ 0.4f,0.4f,0.4f });
		m_shoulderHPSprite.SetMulColor({ UI_START_COLLAR_R,UI_START_COLLAR_G,0.0f,1.0f });
		m_shoulderHPSprite.Update();
		break;
	default:
		break;
	}
}

void PlayerUI::Render(RenderContext& rc)
{
	if (m_player->game_state == 0)
	{
		m_HPSprite.Draw(rc);

		//それぞれがヌルじゃないなら描画
		if (m_rightArm != nullptr) 
		{
			m_rightArmHPSprite.Draw(rc);
		}
		if (m_rightLeg != nullptr) 
		{
			m_rightLegHPSprite.Draw(rc);
		}
		if (m_leftArm != nullptr) 
		{
			m_leftArmHPSprite.Draw(rc);
		}
		if (m_leftLeg != nullptr) 
		{
			m_leftLegHPSprite.Draw(rc);
		}
		if (m_shoulder != nullptr) 
		{
			m_shoulderHPSprite.Draw(rc);
		}
	}
}