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
	//���ʂ̃i���o�[
	const int RIGHT_ARM_NUM = 1;
	const int RIGHT_LEG_NUM = 2;
	const int LEFT_ARM_NUM = 3;
	const int LEFT_LEG_NUM = 4;
	const int SHOULDER_NUM = 5;

	//����摜�̃T�C�Y
	const Vector3 WEAPON_SPRITE_SCALE = { 0.1f,0.1f,0.1f };
	const Vector3 WEAPON_REVERSAL_SPRITE_SCALE = { -0.1f,0.1f,0.1f };

	//�摜�̍ŏ��̐F
	const float UI_START_COLLAR_G = 1.0f;
	const float UI_START_COLLAR_R = 0.0f;

	//�L�����̘g�̃^�[�Q�b�g�|�W�V����
	const float KILL_SPRITE_TARGET = 600.0f;
	
	//HP�̃^�[�Q�b�g�|�W�V����
	const float HP_SPRITE_TARGET = 610.0f;
	
	//HP�̘g�̃^�[�Q�b�g�|�W�V����
	const float HP_FRAME_SPRITE_TARGET = 730.0f;

	//�{�^������UI�̃^�[�Q�b�g�|�W�V����
	const float L1_SPRITE_TARGET = -650.0f;
	const float R2_SPRITE_TARGET = -470.0f;

	//�L�����̃t�H���g�̃^�[�Q�b�g�|�W�V����
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

	//�T��
	m_player = FindGO<Player>("player");
	m_wave = FindGO<Wave>("wave");
	m_game = FindGO<Game>("game");


	//�X�v���C�g�̏�����---------------------------------------------------------------------

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
	
	//�ړ�����
	Move();


	//�̗͌v�Z
	CalcHP();


	//�Ԃ��t���[���̐���
	MakeRedFrame();


	//�G���E�������̕\��
	wchar_t text[256];
	swprintf_s(text, 256, L"%02d�@/%02d", m_game->GetDefeatedEnemyNum(), m_game->GetEnemyNum());
	m_killEnemyAmountFont.SetPivot({ 0.0f,0.5f });
	m_killEnemyAmountFont.SetText(text);
	m_killEnemyAmountFont.SetPosition(Vector3(m_killFontPos, 465.0f, 0.0f));
	m_killEnemyAmountFont.SetShadowParam(true, 1.0f, Vector4(0.0f, 0.0f, 0.0f, 1.0f));
	m_killEnemyAmountFont.SetScale(1.2f);
	m_killEnemyAmountFont.SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
	
}

void PlayerUI::Move()
{

	//UI���Z�b�g����Ă�Ȃ�
	if (m_setUI == true)
	{
		return;
	}


	//�X�v���C�g�̉��ړ��ʂ����߂�
	m_killSpritePosX -= (m_killSpritePosX - KILL_SPRITE_TARGET) / 10.0f;
	m_HPSpriteX -= (m_HPSpriteX - HP_SPRITE_TARGET) / 10.0f;
	m_HPwakuSpriteX -= (m_HPwakuSpriteX - HP_FRAME_SPRITE_TARGET) / 10.0f;
	m_L1SpritePosX -= (m_L1SpritePosX - L1_SPRITE_TARGET) / 10.0f;
	m_R2SpritePosX -= (m_R2SpritePosX - R2_SPRITE_TARGET) / 10.0f;
	m_killFontPos -= (m_killFontPos - KILL_FONT_TARGET) / 10.0f;


	//���ꂼ��ړI�̈ʒu�ɋ߂Â�����,�ړI�̈ʒu�ŌŒ�
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


	//�S�ẴX�v���C�g���Z�b�g�o������
	if (setA == true && setB == true && setC == true && setD == true && setE == true && setF == true)
	{
		m_setUI = true;
	}


	//�X�V
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

	//�̗͂������ȉ��̎�
	if (m_player->GetPlayerHP() <= m_player->GetPlayerHPMax() / 2.0f)
	{

		//�����x�̌v�Z
		m_redFrame_A = 1.0f - (m_player->GetPlayerHP() * (1.0f / m_player->GetPlayerHPMax()));

	}
	//�̗͂������ȏ�̎�
	else
	{

		//�����x��0�ɂ���(�����Ȃ�����)
		m_redFrame_A = 0.0f;

	}


	//�X�V
	m_redFrameSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_redFrame_A });
	m_redFrameSprite.Update();

}

void PlayerUI::CalcHP()
{

	//�v���C���[�̗̑͌v�Z
	m_HPSprite.SetMulColor(Damage(m_player->GetPlayerHP(), m_player->GetPlayerHPMax()));
	m_HPSprite.Update();


	//�e����̗̑͌v�Z
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

Vector4 PlayerUI::Damage(float nowHP, float maxHP)	//�������͍���HP�A�������͍ő�HP
{
	float m_collarG;	//�ΐF�̗�
	float m_collarR;	//�ԐF�̗�

	//�̗͂������ȏ�̎�
	if (nowHP >= maxHP * 0.5f)
	{
		m_collarR = (1.0f - (nowHP * (1.0f / maxHP))) * 2.0f;	//�̗͂�����قǐԐ����������Ă���
		m_collarG = 1.0f;	//�ΐ����͌Œ�
	}
	//�̗͂������ȉ��̎�
	else if (nowHP < maxHP * 0.5f)
	{
		m_collarG = (nowHP * (1.0f / maxHP)) * 2.0f;	//�̗͂�����قǗΐ����������Ă���
		m_collarR = 1.0f;	//�Ԑ����͌Œ�
	}

	Vector4 col;	//�ŏI�I�ȃJ���[

	return col = { m_collarR,m_collarG,0.0f,1.0f };
}

void PlayerUI::WeaponUISetUp(int num)
{
	switch (num)
	{
	case RIGHT_ARM_NUM:	//�E�r
		m_rightArmHPSprite.Init("Assets/sprite/player/weaponUI.dds", 700.0f, 700.0f);
		m_rightArmHPSprite.SetPosition({ 710.0f,-250.0f,0.0f });
		m_rightArmHPSprite.SetScale(WEAPON_SPRITE_SCALE);
		m_rightArmHPSprite.SetMulColor({ UI_START_COLLAR_R,UI_START_COLLAR_G,0.0f,1.0f });
		m_rightArmHPSprite.Update();
		break;
	case RIGHT_LEG_NUM:	//�E��
		m_rightLegHPSprite.Init("Assets/sprite/player/weaponUI.dds", 700.0f, 700.0f);
		m_rightLegHPSprite.SetPosition({ 730.0f,-330.0f,0.0f });
		m_rightLegHPSprite.SetScale(WEAPON_SPRITE_SCALE);
		m_rightLegHPSprite.SetMulColor({ UI_START_COLLAR_R,UI_START_COLLAR_G,0.0f,1.0f });
		m_rightLegHPSprite.Update();
		break;
	case LEFT_ARM_NUM:	//���r
		m_leftArmHPSprite.Init("Assets/sprite/player/weaponUI.dds", 700.0f, 700.0f);
		m_leftArmHPSprite.SetPosition({ 510.0f,-250.0f,0.0f });
		m_leftArmHPSprite.SetScale(WEAPON_REVERSAL_SPRITE_SCALE);
		m_leftArmHPSprite.SetMulColor({ UI_START_COLLAR_R,UI_START_COLLAR_G,0.0f,1.0f });
		m_leftArmHPSprite.Update();
		break;
	case LEFT_LEG_NUM:	//����
		m_leftLegHPSprite.Init("Assets/sprite/player/weaponUI.dds", 700.0f, 700.0f);
		m_leftLegHPSprite.SetPosition({ 490.0f,-330.0f,0.0f });
		m_leftLegHPSprite.SetScale(WEAPON_REVERSAL_SPRITE_SCALE);
		m_leftLegHPSprite.SetMulColor({ UI_START_COLLAR_R,UI_START_COLLAR_G,0.0f,1.0f });
		m_leftLegHPSprite.Update();
		break;
	case SHOULDER_NUM:	//��
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

	//���C���Q�[��������Ȃ� or �v���C���[������ł���Ȃ�
	if (m_player->GetGameState() != MAIN_GAME_NUM || m_player->GetPlayerDead() != false)
	{
		return;
	}


	//�Ԙg�̕`��
	m_redFrameSprite.Draw(rc);


	//�v���C���[��HP�̕`��
	m_HPBackSprite.Draw(rc);
	m_HPSprite.Draw(rc);


	//�{�^����UI�̕`��
	m_L1Sprite.Draw(rc);
	m_R2Sprite.Draw(rc);

	
	//�{�X�풆�ƃE�F�[�u�R�N���A���o���͕\�����Ȃ�
	if (m_player->GetBossState() != 1 && m_wave->GetWaveClear() == nullptr)
	{
		//�L�����̘g
		m_enemyKillSprite.Draw(rc);

		//�L�����̕\��
		m_killEnemyAmountFont.Draw(rc);
	}


	//����UI�̂��ꂼ�ꂪ�k������Ȃ��Ȃ�`��
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