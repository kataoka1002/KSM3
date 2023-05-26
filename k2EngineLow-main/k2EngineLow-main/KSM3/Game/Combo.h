#pragma once
class Player;
class Combo : public IGameObject
{
public:
	Combo();
	~Combo();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void ComboUpdate()
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

    void SpriteInit(const char* effectFilePath,int place)
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

	Player* m_player = nullptr;

	SpriteRender m_comboSprite;
    SpriteRender m_combo10Sprite;
    SpriteRender m_killSprite;

    Vector3 COMBO_NUM_SCALE = { 0.5f,0.5f,0.5f };   //�R���{���̑傫��(�����l)
    Vector3 m_numScale = Vector3::Zero;             //�R���{���̑傫��

	int COMBO_ZERO = 0;
	int m_combo = 0;                        //�R���{��
    int COMBO_RESET_COUNT = 300;            //�R���{�����Z�b�g�����܂ł̎���
    int m_comboResetCount = 0;              
};

