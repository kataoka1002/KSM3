#include "stdafx.h"
#include "Combo.h"
#include "Player.h"

namespace
{
	//コンボがリセットされるまでの時間
	const int COMBO_RESET_COUNT = 300;            
	
	//コンボ数の大きさ(初期値)
	const Vector3 COMBO_NUM_SCALE = { 0.5f,0.5f,0.5f };   

	//コンボ数の初期値
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

	if (m_combo != 0)	//コンボがリセットされる時間の処理
	{
		m_comboResetCount--;

		if (m_comboResetCount <= 0)
		{
			m_combo = COMBO_ZERO;					//コンボのリセット
			m_comboResetCount = COMBO_RESET_COUNT;	//カウントのリセット
		}
	}

	if (m_combo >= 1)	//コンボが続いているとき
	{
		m_numScale += Vector3{ 0.05f,0.05f,0.05f };	//拡大

		if (m_numScale.x >= 0.8f)	
		{
			m_numScale = Vector3{ 0.8f,0.8f,0.8f };	//ある程度の大きさでストップ
		}

		m_comboSprite.SetScale(m_numScale);
		m_combo10Sprite.SetScale(m_numScale);
	}
	else if(m_combo == 0)	//コンボが続いてないとき
	{
		//大きさは初期値にしておく
		m_comboSprite.SetScale(COMBO_NUM_SCALE);
		m_combo10Sprite.SetScale(COMBO_NUM_SCALE);
	}

	m_comboSprite.Update();
	m_combo10Sprite.Update();
}

void Combo::ComboUpdate()
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

void Combo::SpriteInit(const char* effectFilePath, int place)
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

void Combo::Render(RenderContext& rc)
{
    if (m_player->GetGameState() != MAIN_GAME_NUM || m_combo == 0)
    {
        return;
    }


    //コンボが2桁まで行ったら表示
    if (m_combo >= 10)
    {
        m_combo10Sprite.Draw(rc);
    }

    m_comboSprite.Draw(rc);
    m_killSprite.Draw(rc);

}