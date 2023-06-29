#include "stdafx.h"
#include "Combo.h"
#include "Player.h"

namespace
{
	//�R���{�����Z�b�g�����܂ł̎���
	const int COMBO_RESET_COUNT = 300;            
	
	//�R���{���̑傫��(�����l)
	const Vector3 COMBO_NUM_SCALE = { 0.5f,0.5f,0.5f };   

	//�R���{���̏����l
	const int COMBO_ZERO = 0;
}

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

void Combo::ComboUpdate()
{
    m_combo++;                              //�R���{��1���₷
    m_numScale = COMBO_NUM_SCALE;	        //�R���{���̃T�C�Y������
    m_comboResetCount = COMBO_RESET_COUNT;	//�J�E���g�̃��Z�b�g

    //��̈�
    switch (m_combo % 10) //�R���{���ɂ���ăX�v���C�g��ς���
    {
    case 1:
        SpriteInit("Assets/sprite/player/1_kill.dds", 1);
        break;
    case 2:
        SpriteInit("Assets/sprite/player/2_kill.dds", 1);
        break;
    case 3:
        SpriteInit("Assets/sprite/player/3_kill.dds", 1);
        break;
    case 4:
        SpriteInit("Assets/sprite/player/4_kill.dds", 1);
        break;
    case 5:
        SpriteInit("Assets/sprite/player/5_kill.dds", 1);
        break;
    case 6:
        SpriteInit("Assets/sprite/player/6_kill.dds", 1);
        break;
    case 7:
        SpriteInit("Assets/sprite/player/7_kill.dds", 1);
        break;
    case 8:
        SpriteInit("Assets/sprite/player/8_kill.dds", 1);
        break;
    case 9:
        SpriteInit("Assets/sprite/player/9_kill.dds", 1);
        break;
    case 0:
        SpriteInit("Assets/sprite/player/0_kill.dds", 1);
        break;
    default:
        // �G���[�����ȂǁAm_comboNow ���\�z�O�̒l�̏ꍇ�̏�����ǉ�
        break;
    }

    //�\�̈�
    switch (m_combo / 10) //�R���{���ɂ���ăX�v���C�g��ς���
    {
    case 1:
        SpriteInit("Assets/sprite/player/1_kill.dds", (m_combo / 10) * 10);
        break;
    case 2:
        SpriteInit("Assets/sprite/player/2_kill.dds", (m_combo / 10) * 10);
        break;
    case 3:
        SpriteInit("Assets/sprite/player/3_kill.dds", (m_combo / 10) * 10);
        break;
    case 4:
        SpriteInit("Assets/sprite/player/4_kill.dds", (m_combo / 10) * 10);
        break;
    case 5:
        SpriteInit("Assets/sprite/player/5_kill.dds", (m_combo / 10) * 10);
        break;
    case 6:
        SpriteInit("Assets/sprite/player/6_kill.dds", (m_combo / 10) * 10);
        break;
    case 7:
        SpriteInit("Assets/sprite/player/7_kill.dds", (m_combo / 10) * 10);
        break;
    case 8:
        SpriteInit("Assets/sprite/player/8_kill.dds", (m_combo / 10) * 10);
        break;
    case 9:
        SpriteInit("Assets/sprite/player/9_kill.dds", (m_combo / 10) * 10);
        break;
    default:
        // �G���[�����ȂǁAm_comboNow ���\�z�O�̒l�̏ꍇ�̏�����ǉ�
        break;
    }
}

void Combo::SpriteInit(const char* effectFilePath, int place)
{
    //�ʂɂ���ĕς���
    if (place == 1)
    {
        m_comboSprite.Init(effectFilePath, 1600.0f, 900.0f);
        m_comboSprite.SetScale(COMBO_NUM_SCALE);
        m_comboSprite.SetPosition({ -600.0f,150.0f,0.0f });
        m_comboSprite.Update();
    }

    if (place == 10)
    {
        m_combo10Sprite.Init(effectFilePath, 1600.0f, 900.0f);
        m_combo10Sprite.SetScale(COMBO_NUM_SCALE);
        m_combo10Sprite.SetPosition({ -665.0f,150.0f,0.0f });
        m_combo10Sprite.Update();
    }
    else if (place == 20 || place == 30)
    {
        m_combo10Sprite.Init(effectFilePath, 1600.0f, 900.0f);
        m_combo10Sprite.SetScale(COMBO_NUM_SCALE);
        m_combo10Sprite.SetPosition({ -680.0f,150.0f,0.0f });
        m_combo10Sprite.Update();
    }
}

void Combo::Render(RenderContext& rc)
{
    if (m_player->GetGameState() != MAIN_GAME_NUM || m_combo == 0)
    {
        return;
    }


    //�R���{��2���܂ōs������\��
    if (m_combo >= 10)
    {
        m_combo10Sprite.Draw(rc);
    }

    m_comboSprite.Draw(rc);
    m_killSprite.Draw(rc);

}