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
		m_combo++;                              //コンボを1増やす
        m_numScale = COMBO_NUM_SCALE;	        //コンボ数のサイズ初期化
        m_comboResetCount = COMBO_RESET_COUNT;	//カウントのリセット

        //一の位
        switch (m_combo % 10) //コンボ数によってスプライトを変える
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
            // エラー処理など、m_comboNow が予想外の値の場合の処理を追加
            break;
        }

        //十の位
        switch (m_combo / 10) //コンボ数によってスプライトを変える
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
            // エラー処理など、m_comboNow が予想外の値の場合の処理を追加
            break;
        }
	}

    void SpriteInit(const char* effectFilePath,int place)
    {
        //位によって変える
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

    Vector3 COMBO_NUM_SCALE = { 0.5f,0.5f,0.5f };   //コンボ数の大きさ(初期値)
    Vector3 m_numScale = Vector3::Zero;             //コンボ数の大きさ

	int COMBO_ZERO = 0;
	int m_combo = 0;                        //コンボ数
    int COMBO_RESET_COUNT = 300;            //コンボがリセットされるまでの時間
    int m_comboResetCount = 0;              
};

