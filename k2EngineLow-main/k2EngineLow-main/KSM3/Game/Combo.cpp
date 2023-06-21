#include "stdafx.h"
#include "Combo.h"
#include "Player.h"

Combo::Combo()
{

}

Combo::~Combo()
{

}

bool Combo::Start()
{
	m_player = FindGO<Player>("player");

	m_comboSprite.Init("Assets/sprite/player/1_kill.dds", 1600.0f, 900.0f);
	m_comboSprite.SetPosition(Vector3::Zero);
	m_comboSprite.SetScale(COMBO_NUM_SCALE);
	m_comboSprite.Update();

	m_combo10Sprite.Init("Assets/sprite/player/1_kill.dds", 1600.0f, 900.0f);
	m_combo10Sprite.SetPosition(Vector3::Zero);
	m_combo10Sprite.SetScale({ 1.0f,1.0f,1.0f });
	m_combo10Sprite.Update();

	m_killSprite.Init("Assets/sprite/player/KILL.dds", 1600.0f, 900.0f);
	m_killSprite.SetPosition({ -600.0f,150.0f,0.0f });
	m_killSprite.SetScale({ 0.8f,0.8f,0.8f });
	m_killSprite.Update();

	return true;
}

void Combo::Update()
{
	if (m_player->GetGameState() != MAIN_GAME_NUM)
	{
		return;
	}

	if (m_combo != 0)	//�R���{�����Z�b�g����鎞�Ԃ̏���
	{
		m_comboResetCount--;

		if (m_comboResetCount <= 0)
		{
			m_combo = COMBO_ZERO;					//�R���{�̃��Z�b�g
			m_comboResetCount = COMBO_RESET_COUNT;	//�J�E���g�̃��Z�b�g
		}
	}

	if (m_combo >= 1)	//�R���{�������Ă���Ƃ�
	{
		m_numScale += Vector3{ 0.05f,0.05f,0.05f };	//�g��

		if (m_numScale.x >= 0.8f)	
		{
			m_numScale = Vector3{ 0.8f,0.8f,0.8f };	//������x�̑傫���ŃX�g�b�v
		}

		m_comboSprite.SetScale(m_numScale);
		m_combo10Sprite.SetScale(m_numScale);
	}
	else if(m_combo == 0)	//�R���{�������ĂȂ��Ƃ�
	{
		//�傫���͏����l�ɂ��Ă���
		m_comboSprite.SetScale(COMBO_NUM_SCALE);
		m_combo10Sprite.SetScale(COMBO_NUM_SCALE);
	}

	m_comboSprite.Update();
	m_combo10Sprite.Update();
}

void Combo::Render(RenderContext& rc)
{
	if (m_player->GetGameState() != MAIN_GAME_NUM)
	{
		return;
	}

	if (m_combo != 0)
	{
		//�R���{��2���܂ōs������\��
		if (m_combo >= 10)
		{
			m_combo10Sprite.Draw(rc);
		}

		m_comboSprite.Draw(rc);
		m_killSprite.Draw(rc);
	}
}