#include "stdafx.h"
#include "PlayerUI.h"
#include "Player.h"
#include "Right_arm_weapons.h"
#include "Right_leg_weapons.h"
#include "Left_arm_weapons.h";
#include "Left_leg_weapons.h";
#include "Shoulder_weapons.h";
#include "Wave.h"
#include "Game.h"

namespace
{
	//部位のナンバー
	const int RIGHT_ARM_NUM = 1;
	const int RIGHT_LEG_NUM = 2;
	const int LEFT_ARM_NUM = 3;
	const int LEFT_LEG_NUM = 4;
	const int SHOULDER_NUM = 5;

	//武器画像のサイズ
	const Vector3 WEAPON_SPRITE_SCALE = { 0.1f,0.1f,0.1f };
	const Vector3 WEAPON_REVERSAL_SPRITE_SCALE = { -0.1f,0.1f,0.1f };

	//画像の最初の色
	const float UI_START_COLLAR_G = 1.0f;
	const float UI_START_COLLAR_R = 0.0f;

	//キル数の枠のターゲットポジション
	const float KILL_SPRITE_TARGET = 600.0f;
	
	//HPのターゲットポジション
	const float HP_SPRITE_TARGET = 610.0f;
	
	//HPの枠のターゲットポジション
	const float HP_FRAME_SPRITE_TARGET = 730.0f;

	//ボタン説明UIのターゲットポジション
	const float L1_SPRITE_TARGET = -650.0f;
	const float R2_SPRITE_TARGET = -470.0f;

	//キル数のフォントのターゲットポジション
	const float KILL_FONT_TARGET = 580.0f;


	const float HP_SPRITE_POS_Y = -300.0f;
	const float HP_WAKU_SPRITE_POS_Y = -340.0f;
	const float KILL_SPRITE_POS_Y = 350.0f;
	const float L1_SPRITE_POS_Y = -330.0f;
	const float R2_SPRITE_POS_Y = -330.0f;
}

PlayerUI::PlayerUI()
{

}

PlayerUI::~PlayerUI()
{

}

bool PlayerUI::Start()
{

	//探す
	m_player = FindGO<Player>("player");
	m_wave = FindGO<Wave>("wave");
	m_game = FindGO<Game>("game");


	//スプライトの初期化---------------------------------------------------------------------

	m_HPSprite.Init("Assets/sprite/player/playerUI.dds", 691.0f, 597.0f);
	m_HPSprite.SetPosition({ m_HPSpriteX,HP_SPRITE_POS_Y,0.0f });
	m_HPSprite.SetScale({ 0.4f,0.4f,0.4f });
	m_HPSprite.SetMulColor({ UI_START_COLLAR_R,UI_START_COLLAR_G,0.0f,1.0f });
	m_HPSprite.Update();

	m_HPBackSprite.Init("Assets/sprite/player/PlayerUIWaku.dds", 2220.0f, 1080.0f);
	m_HPBackSprite.SetPosition({ m_HPwakuSpriteX,HP_WAKU_SPRITE_POS_Y,0.0f });
	m_HPBackSprite.SetScale({ 0.6f,0.6f,0.6f });
	m_HPBackSprite.Update();

	m_enemyKillSprite.Init("Assets/sprite/player/enemyKillAmount.dds", 1980.0f, 1020.0f);
	m_enemyKillSprite.SetPosition({ m_killSpritePosX,KILL_SPRITE_POS_Y,0.0f });
	m_enemyKillSprite.SetScale({ 0.7f,0.6f,0.6f });
	m_enemyKillSprite.Update();

	m_redFrameSprite.Init("Assets/sprite/player/RedFrame.dds", 1600.0f, 900.0f);
	m_redFrameSprite.SetPosition(Vector3::Zero);
	m_redFrameSprite.SetScale({ 1.0f,1.0f,1.0f });
	m_redFrameSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_redFrame_A });
	m_redFrameSprite.Update();

	m_L1Sprite.Init("Assets/sprite/player/buttonL1.dds", 1600.0f, 900.0f);
	m_L1Sprite.SetPosition({ m_L1SpritePosX,L1_SPRITE_POS_Y,0.0f });
	m_L1Sprite.SetScale(0.2f);
	m_L1Sprite.Update();

	m_R2Sprite.Init("Assets/sprite/player/buttonR2.dds", 1600.0f, 900.0f);
	m_R2Sprite.SetPosition({ m_R2SpritePosX,R2_SPRITE_POS_Y,0.0f });
	m_R2Sprite.SetScale(0.2f);
	m_R2Sprite.Update();

	//-----------------------------------------------------------------------------------------------

	return true;
}

void PlayerUI::Update()
{
	
	//移動処理
	Move();


	//体力計算
	CalcHP();


	//赤いフレームの生成
	MakeRedFrame();


	//敵を殺した数の表示
	wchar_t text[256];
	swprintf_s(text, 256, L"%02d　/%02d", m_game->GetDefeatedEnemyNum(), m_game->GetEnemyNum());
	m_killEnemyAmountFont.SetPivot({ 0.0f,0.5f });
	m_killEnemyAmountFont.SetText(text);
	m_killEnemyAmountFont.SetPosition(Vector3(m_killFontPos, 465.0f, 0.0f));
	m_killEnemyAmountFont.SetShadowParam(true, 1.0f, Vector4(0.0f, 0.0f, 0.0f, 1.0f));
	m_killEnemyAmountFont.SetScale(1.2f);
	m_killEnemyAmountFont.SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	
}

void PlayerUI::Move()
{

	//UIがセットされてるなら
	if (m_setUI == true)
	{
		return;
	}


	//スプライトの横移動量を求める
	m_killSpritePosX -= (m_killSpritePosX - KILL_SPRITE_TARGET) / 10.0f;
	m_HPSpriteX -= (m_HPSpriteX - HP_SPRITE_TARGET) / 10.0f;
	m_HPwakuSpriteX -= (m_HPwakuSpriteX - HP_FRAME_SPRITE_TARGET) / 10.0f;
	m_L1SpritePosX -= (m_L1SpritePosX - L1_SPRITE_TARGET) / 10.0f;
	m_R2SpritePosX -= (m_R2SpritePosX - R2_SPRITE_TARGET) / 10.0f;
	m_killFontPos -= (m_killFontPos - KILL_FONT_TARGET) / 10.0f;


	//それぞれ目的の位置に近づいたら,目的の位置で固定
	if (m_killSpritePosX - 0.05f <= KILL_SPRITE_TARGET)
	{
		m_killSpritePosX = KILL_SPRITE_TARGET;
		setA = true;
	}
	if (m_HPSpriteX - 0.05f <= HP_SPRITE_TARGET)
	{
		m_HPSpriteX = HP_SPRITE_TARGET;
		setB = true;
	}
	if (m_HPwakuSpriteX - 0.05f <= HP_FRAME_SPRITE_TARGET)
	{
		m_HPwakuSpriteX = HP_FRAME_SPRITE_TARGET;
		setC = true;
	}
	if (m_L1SpritePosX + 0.05f >= L1_SPRITE_TARGET)
	{
		m_L1SpritePosX = L1_SPRITE_TARGET;
		setD = true;
	}
	if (m_R2SpritePosX + 0.05f >= R2_SPRITE_TARGET)
	{
		m_R2SpritePosX = R2_SPRITE_TARGET;
		setE = true;
	}
	if (m_killFontPos - 0.05f <= KILL_FONT_TARGET)
	{
		m_killFontPos = KILL_FONT_TARGET;
		setF = true;
	}


	//全てのスプライトがセット出来たら
	if (setA == true && setB == true && setC == true && setD == true && setE == true && setF == true)
	{
		m_setUI = true;
	}


	//更新
	m_enemyKillSprite.SetPosition({ m_killSpritePosX,KILL_SPRITE_POS_Y,0.0f });
	m_enemyKillSprite.Update();

	m_HPSprite.SetPosition({ m_HPSpriteX,HP_SPRITE_POS_Y,0.0f });
	m_HPSprite.Update();

	m_HPBackSprite.SetPosition({ m_HPwakuSpriteX,HP_WAKU_SPRITE_POS_Y,0.0f });
	m_HPBackSprite.Update();

	m_L1Sprite.SetPosition({ m_L1SpritePosX,L1_SPRITE_POS_Y,0.0f });
	m_L1Sprite.Update();

	m_R2Sprite.SetPosition({ m_R2SpritePosX,R2_SPRITE_POS_Y,0.0f });
	m_R2Sprite.Update();

}

void PlayerUI::MakeRedFrame()
{

	//体力が半分以下の時
	if (m_player->GetPlayerHP() <= m_player->GetPlayerHPMax() / 2.0f)
	{

		//透明度の計算
		m_redFrame_A = 1.0f - (m_player->GetPlayerHP() * (1.0f / m_player->GetPlayerHPMax()));

	}
	//体力が半分以上の時
	else
	{

		//透明度を0にする(見えなくする)
		m_redFrame_A = 0.0f;

	}


	//更新
	m_redFrameSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_redFrame_A });
	m_redFrameSprite.Update();

}

void PlayerUI::CalcHP()
{

	//プレイヤーの体力計算
	m_HPSprite.SetMulColor(Damage(m_player->GetPlayerHP(), m_player->GetPlayerHPMax()));
	m_HPSprite.Update();


	//各武器の体力計算
	if (m_rightArm != nullptr)
	{
		m_rightArmHPSprite.SetMulColor(Damage(m_rightArm->GetHP(), m_rightArm->GetHPMax()));
		m_rightArmHPSprite.Update();
	}

	if (m_rightLeg != nullptr)
	{
		m_rightLegHPSprite.SetMulColor(Damage(m_rightLeg->GetHP(), m_rightLeg->GetHPMax()));
		m_rightLegHPSprite.Update();
	}

	if (m_leftArm != nullptr)
	{
		m_leftArmHPSprite.SetMulColor(Damage(m_leftArm->GetHP(), m_leftArm->GetHPMax()));
		m_leftArmHPSprite.Update();
	}

	if (m_leftLeg != nullptr)
	{
		m_leftLegHPSprite.SetMulColor(Damage(m_leftLeg->GetHP(), m_leftLeg->GetHPMax()));
		m_leftLegHPSprite.Update();
	}

	if (m_shoulder != nullptr)
	{
		m_shoulderHPSprite.SetMulColor(Damage(m_shoulder->GetHP(), m_shoulder->GetHPMax()));
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
	case RIGHT_ARM_NUM:	//右腕
		m_rightArmHPSprite.Init("Assets/sprite/player/weaponUI.dds", 700.0f, 700.0f);
		m_rightArmHPSprite.SetPosition({ 710.0f,-250.0f,0.0f });
		m_rightArmHPSprite.SetScale(WEAPON_SPRITE_SCALE);
		m_rightArmHPSprite.SetMulColor({ UI_START_COLLAR_R,UI_START_COLLAR_G,0.0f,1.0f });
		m_rightArmHPSprite.Update();
		break;
	case RIGHT_LEG_NUM:	//右足
		m_rightLegHPSprite.Init("Assets/sprite/player/weaponUI.dds", 700.0f, 700.0f);
		m_rightLegHPSprite.SetPosition({ 730.0f,-330.0f,0.0f });
		m_rightLegHPSprite.SetScale(WEAPON_SPRITE_SCALE);
		m_rightLegHPSprite.SetMulColor({ UI_START_COLLAR_R,UI_START_COLLAR_G,0.0f,1.0f });
		m_rightLegHPSprite.Update();
		break;
	case LEFT_ARM_NUM:	//左腕
		m_leftArmHPSprite.Init("Assets/sprite/player/weaponUI.dds", 700.0f, 700.0f);
		m_leftArmHPSprite.SetPosition({ 510.0f,-250.0f,0.0f });
		m_leftArmHPSprite.SetScale(WEAPON_REVERSAL_SPRITE_SCALE);
		m_leftArmHPSprite.SetMulColor({ UI_START_COLLAR_R,UI_START_COLLAR_G,0.0f,1.0f });
		m_leftArmHPSprite.Update();
		break;
	case LEFT_LEG_NUM:	//左足
		m_leftLegHPSprite.Init("Assets/sprite/player/weaponUI.dds", 700.0f, 700.0f);
		m_leftLegHPSprite.SetPosition({ 490.0f,-330.0f,0.0f });
		m_leftLegHPSprite.SetScale(WEAPON_REVERSAL_SPRITE_SCALE);
		m_leftLegHPSprite.SetMulColor({ UI_START_COLLAR_R,UI_START_COLLAR_G,0.0f,1.0f });
		m_leftLegHPSprite.Update();
		break;
	case SHOULDER_NUM:	//肩
		m_shoulderHPSprite.Init("Assets/sprite/player/weaponUI.dds", 700.0f, 700.0f);
		m_shoulderHPSprite.SetPosition({ 615.0f,-150.0f,0.0f });
		m_shoulderHPSprite.SetScale(WEAPON_SPRITE_SCALE);
		m_shoulderHPSprite.SetMulColor({ UI_START_COLLAR_R,UI_START_COLLAR_G,0.0f,1.0f });
		m_shoulderHPSprite.Update();
		break;
	default:
		break;
	}
}

void PlayerUI::Render(RenderContext& rc)
{

	//メインゲーム中じゃない or プレイヤーが死んでいるなら
	if (m_player->GetGameState() != MAIN_GAME_NUM || m_player->GetPlayerDead() != false)
	{
		return;
	}


	//赤枠の描画
	m_redFrameSprite.Draw(rc);


	//プレイヤーのHPの描画
	m_HPBackSprite.Draw(rc);
	m_HPSprite.Draw(rc);


	//ボタンのUIの描画
	m_L1Sprite.Draw(rc);
	m_R2Sprite.Draw(rc);

	
	//ボス戦中とウェーブ３クリア演出中は表示しない
	if (m_player->GetBossState() != 1 && m_wave->GetWaveClear() == nullptr)
	{
		//キル数の枠
		m_enemyKillSprite.Draw(rc);

		//キル数の表示
		m_killEnemyAmountFont.Draw(rc);
	}


	//武器UIのそれぞれがヌルじゃないなら描画
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