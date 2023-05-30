#include "stdafx.h"
#include "PlayerUI.h"
#include "Player.h"
#include "Right_arm_weapons.h"
#include "Right_leg_weapons.h"
#include "Left_arm_weapons.h";
#include "Left_leg_weapons.h";
#include "Shoulder_weapons.h";
#include "Wave.h"

PlayerUI::PlayerUI()
{

}

PlayerUI::~PlayerUI()
{

}

bool PlayerUI::Start()
{
	m_player = FindGO<Player>("player");
	m_wave = FindGO<Wave>("wave");

	m_HPSprite.Init("Assets/sprite/player/playerUI.dds", 691.0f, 597.0f);
	m_HPSprite.SetPosition({ 610.0f,-300.0f,0.0f });
	m_HPSprite.SetScale({ 0.4f,0.4f,0.4f });
	m_HPSprite.SetMulColor({ UI_START_COLLAR_R,UI_START_COLLAR_G,0.0f,1.0f });
	m_HPSprite.Update();

	m_HPBackSprite.Init("Assets/sprite/player/PlayerUIWaku.dds", 2220.0f, 1080.0f);
	m_HPBackSprite.SetPosition({ 730.0f,-340.0f,0.0f });
	m_HPBackSprite.SetScale({ 0.6f,0.6f,0.6f });
	m_HPBackSprite.Update();

	m_enemyKillSprite.Init("Assets/sprite/player/enemyKillAmount.dds", 1980.0f, 1020.0f);
	m_enemyKillSprite.SetPosition({ 1000.0f,350.0f,0.0f });
	m_enemyKillSprite.SetScale({ 0.7f,0.6f,0.6f });
	m_enemyKillSprite.Update();

	m_redFrameSprite.Init("Assets/sprite/player/RedFrame.dds", 1600.0f, 900.0f);
	m_redFrameSprite.SetPosition(Vector3::Zero);
	m_redFrameSprite.SetScale({ 1.0f,1.0f,1.0f });
	m_redFrameSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_redFrame_A });
	m_redFrameSprite.Update();

	m_L1Sprite.Init("Assets/sprite/player/buttonL1.dds", 1600.0f, 900.0f);
	m_L1Sprite.SetPosition({ m_L1SpritePosX,-330.0f,0.0f });
	m_L1Sprite.SetScale(0.2f);
	m_L1Sprite.Update();

	m_R2Sprite.Init("Assets/sprite/player/buttonR2.dds", 1600.0f, 900.0f);
	m_R2Sprite.SetPosition({ m_R2SpritePosX,-330.0f,0.0f });
	m_R2Sprite.SetScale(0.2f);
	m_R2Sprite.Update();

	return true;
}

void PlayerUI::Update()
{
	if (m_setUI == false)
	{
		//スプライトの横移動を求める
		m_killSpritePosX -= (m_killSpritePosX - m_killSpriteTargetPos  ) / 10.0f;
		m_HPSpriteX		 -= (m_HPSpriteX      - m_HPSpriteTargetPos    ) / 10.0f;
		m_HPwakuSpriteX	 -= (m_HPwakuSpriteX  - m_HPwakuSpriteTargetPos) / 10.0f;
		m_L1SpritePosX	 -= (m_L1SpritePosX   - m_L1SpriteTargetPos    ) / 10.0f;
		m_R2SpritePosX	 -= (m_R2SpritePosX   - m_R2SpriteTargetPos    ) / 10.0f;
		m_killFontPos    -= (m_killFontPos    - m_killFontTargetPos    ) / 10.0f;

		//それぞれ目的の位置にたどり着いたらそこで固定
		if (m_killSpritePosX - 0.05f <= m_killSpriteTargetPos)
		{
			m_killSpritePosX = m_killSpriteTargetPos;
			setA = true;
		}
		if (m_HPSpriteX - 0.05f <= m_HPSpriteTargetPos)
		{
			m_HPSpriteX = m_HPSpriteTargetPos;
			setB = true;
		}
		if (m_HPwakuSpriteX - 0.05f <= m_HPwakuSpriteTargetPos)
		{
			m_HPwakuSpriteX = m_HPwakuSpriteTargetPos;
			setC = true;
		}
		if (m_L1SpritePosX + 0.05f >= m_L1SpriteTargetPos)
		{
			m_L1SpritePosX = m_L1SpriteTargetPos;
			setD = true;
		}
		if (m_R2SpritePosX + 0.05f >= m_R2SpriteTargetPos)
		{
			m_R2SpritePosX = m_R2SpriteTargetPos;
			setE = true;
		}
		if (m_killFontPos - 0.05f <= m_killFontTargetPos)
		{
			m_killFontPos = m_killFontTargetPos;
			setF = true;
		}

		//全てのスプライトがセット出来たら
		if (setA == true && setB == true && setC == true && setD == true && setE == true && setF == true)
		{
			m_setUI = true;
		}

		//更新
		m_enemyKillSprite.SetPosition({ m_killSpritePosX,350.0f,0.0f });
		m_enemyKillSprite.Update();
		m_HPSprite.SetPosition({ m_HPSpriteX,-300.0f,0.0f });
		m_HPSprite.Update();
		m_HPBackSprite.SetPosition({ m_HPwakuSpriteX,-340.0f,0.0f });
		m_HPBackSprite.Update();
		m_L1Sprite.SetPosition({ m_L1SpritePosX,-330.0f,0.0f });
		m_L1Sprite.Update();
		m_R2Sprite.SetPosition({ m_R2SpritePosX,-330.0f,0.0f });
		m_R2Sprite.Update();
	}

	//プレイヤーの体力計算
	m_HPSprite.SetMulColor(Damage(m_player->m_playerHP, m_player->m_playerHPMax));
	m_HPSprite.Update();

	//赤いフレームの生成
	if (m_player->m_playerHP <= m_player->m_playerHPMax / 2.0f)
	{
		m_redFrame_A = 1.0f - (m_player->m_playerHP * (1.0f / m_player->m_playerHPMax));
		m_redFrameSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_redFrame_A });
		m_redFrameSprite.Update();
	}

	//敵を殺した数の表示
	wchar_t text[256];
	swprintf_s(text, 256, L"%02d　/10",m_player->killEnemy);
	m_killEnemyAmount.SetPivot({ 0.0f,0.5f });
	m_killEnemyAmount.SetText(text);
	m_killEnemyAmount.SetPosition(Vector3(m_killFontPos, 465, 0.0f));
	m_killEnemyAmount.SetShadowParam(true, 1.0f, Vector4(0.0f, 0.0f, 0.0f, 1.0f));
	m_killEnemyAmount.SetScale(1.2f);
	m_killEnemyAmount.SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));

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
		m_rightArmHPSprite.SetPosition({ 710.0f,-250.0f,0.0f });
		m_rightArmHPSprite.SetScale({ 0.1f,0.1f,0.1f });
		m_rightArmHPSprite.SetMulColor({ UI_START_COLLAR_R,UI_START_COLLAR_G,0.0f,1.0f });
		m_rightArmHPSprite.Update();
		break;
	case 2:	//右足
		m_rightLegHPSprite.Init("Assets/sprite/player/weaponUI.dds", 700.0f, 700.0f);
		m_rightLegHPSprite.SetPosition({ 730.0f,-330.0f,0.0f });
		m_rightLegHPSprite.SetScale({ 0.1f,0.1f,0.1f });
		m_rightLegHPSprite.SetMulColor({ UI_START_COLLAR_R,UI_START_COLLAR_G,0.0f,1.0f });
		m_rightLegHPSprite.Update();
		break;
	case 3:	//左腕
		m_leftArmHPSprite.Init("Assets/sprite/player/weaponUI.dds", 700.0f, 700.0f);
		m_leftArmHPSprite.SetPosition({ 510.0f,-250.0f,0.0f });
		m_leftArmHPSprite.SetScale({ -0.1f,0.1f,0.1f });
		m_leftArmHPSprite.SetMulColor({ UI_START_COLLAR_R,UI_START_COLLAR_G,0.0f,1.0f });
		m_leftArmHPSprite.Update();
		break;
	case 4:	//左足
		m_leftLegHPSprite.Init("Assets/sprite/player/weaponUI.dds", 700.0f, 700.0f);
		m_leftLegHPSprite.SetPosition({ 490.0f,-330.0f,0.0f });
		m_leftLegHPSprite.SetScale({ -0.1f,0.1f,0.1f });
		m_leftLegHPSprite.SetMulColor({ UI_START_COLLAR_R,UI_START_COLLAR_G,0.0f,1.0f });
		m_leftLegHPSprite.Update();
		break;
	case 5:	//肩
		m_shoulderHPSprite.Init("Assets/sprite/player/weaponUI.dds", 700.0f, 700.0f);
		m_shoulderHPSprite.SetPosition({ 615.0f,-150.0f,0.0f });
		m_shoulderHPSprite.SetScale({ 0.1f,0.1f,0.1f });
		m_shoulderHPSprite.SetMulColor({ UI_START_COLLAR_R,UI_START_COLLAR_G,0.0f,1.0f });
		m_shoulderHPSprite.Update();
		break;
	default:
		break;
	}
}

void PlayerUI::Render(RenderContext& rc)
{
	if (m_player->game_state == 0 && m_player->m_playerDead == false)
	{
		m_redFrameSprite.Draw(rc);

		m_HPBackSprite.Draw(rc);
		m_HPSprite.Draw(rc);

		m_L1Sprite.Draw(rc);
		m_R2Sprite.Draw(rc);

		if (m_player->bossState != 1 && m_wave->m_waveClear == nullptr)	//ウェーブ３クリア演出中は表示しない
		{
			//キル数の枠
			m_enemyKillSprite.Draw(rc);

			//キル数の表示
			m_killEnemyAmount.Draw(rc);
		}

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