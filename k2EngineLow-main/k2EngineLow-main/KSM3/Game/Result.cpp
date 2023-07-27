#include "stdafx.h"
#include "Result.h"
#include "Title.h"
#include "Player.h"
#include "GameCamera.h"
#include "Result_Macro.h"
#include "Array"
#include <time.h>
#include <stdlib.h>
#include <map>
#include <tuple>


using namespace std;


Result::Result() 
{
	m_player = FindGO<Player>("player");
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				m_customPoint[i][j] = m_player->GetCustomPoint(i, j);
			}
		}
	m_gameCamera=FindGO<GameCamera>("gamecamera");

}

Result::~Result()
{	
	DeleteGO(m_gameCamera);
	DeleteGO(m_player);
	DeleteGO(m_sound);
}

bool Result::Start()
{
	FontSet();
	BackSet();

	m_sound = NewGO<SoundSource>(0);		
	m_sound->Init(21);									//初期化
	m_sound->SetVolume(1.0f * m_BGMVolume);				//音量調整
	m_sound->Play(true);

	return true;
}

void Result::Update()
{
	BackGround();
	

	//タイトルへの遷移(フェードあり)
	if (g_pad[0]->IsTrigger(enButtonA)&&m_count!=1) {
		if (m_resultState == 0) {
			m_resultState = 1;
		}
		else if (m_resultState == 1) {
			m_resultState = 2;
		}
		else if (m_resultState == 2) {
			Title* title = NewGO<Title>(0, "title");
			DeleteGO(this);
		}

		SoundSource* m_SE = NewGO<SoundSource>(0);		//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
		m_SE->Init(17);									//初期化
		m_SE->SetVolume(1.0f * m_SEVolume);				//音量調整
		m_SE->Play(false);

		m_count = 0;
	}
	if (m_resultState == 0) {
		//タイマーの初期化
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 10; j++) {
				m_timeNum[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_timeColonSpriteAlpha[i][0]));
			}
		}
		m_timeColonSprite.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_timeColonSpriteAlpha[1][0]));

		//timeの文字の移動(出現）
		if (m_count <= 49) {
			m_timeColor.w += 0.02f;
			m_timePosition.x += 0.5f;
			m_timeSprite.SetPosition(m_timePosition);
			m_timeSprite.SetMulColor(m_timeColor);
			m_timeSprite.Update();
		}

		//タイムの出現
		if (m_count >= 50 && m_count < 55) {
			for (int i = 0; i < 4; i++) {
				m_timeColonSpriteAlpha[i][0] += 0.2f;
				for (int j = 0; j < 10; j++) {
					m_timeNum[i][j].SetMulColor(Vector4(1.0f,1.0f,1.0f,m_timeColonSpriteAlpha[i][0]));
				}
			}
			m_timeColonSprite.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_timeColonSpriteAlpha[1][0]));
		}
		if (m_count >= 55 && m_count < 60) {
			for (int i = 0; i < 4; i++) {
				m_timeColonSpriteAlpha[i][0] -= 0.2f;
				for (int j = 0; j < 10; j++) {
					m_timeNum[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_timeColonSpriteAlpha[i][0]));
				}
			}
			m_timeColonSprite.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_timeColonSpriteAlpha[1][0]));
		}
		if (m_count >= 60 && m_count < 65) {
			for (int i = 0; i < 4; i++) {
				m_timeColonSpriteAlpha[i][0] += 0.2f;
				for (int j = 0; j < 10; j++) {
					m_timeNum[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_timeColonSpriteAlpha[i][0]));
				}
			}
			m_timeColonSprite.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_timeColonSpriteAlpha[1][0]));
		}
		if (m_count >= 65 && m_count < 70) {
			for (int i = 0; i < 4; i++) {
				m_timeColonSpriteAlpha[i][0] -= 0.2f;
				for (int j = 0; j < 10; j++) {
					m_timeNum[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_timeColonSpriteAlpha[i][0]));
				}
			}
			m_timeColonSprite.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_timeColonSpriteAlpha[1][0]));
		}
		if (m_count >=70 && m_count < 110) {
			for (int i = 0; i < 4; i++) {
				m_timeColonSpriteAlpha[i][0] += 0.025f;
				for (int j = 0; j < 10; j++) {
					m_timeNum[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_timeColonSpriteAlpha[i][0]));
				}
			}
			m_timeColonSprite.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_timeColonSpriteAlpha[1][0]));
		}
	}

	//SCORE
	if (m_resultState == 1) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 10; j++) {
				m_scoreNum[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_scoreCommaSpriteAlpha[i][0]));
			}
		}
		m_scoreCommaSprite.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_scoreCommaSpriteAlpha[1][0]));
		if (m_count <= 10) {
			m_boxRotation.AddRotationDegY(33.0f);
			m_playerRotation.AddRotationDegY(33.0f);
			m_boxModel.SetRotation(m_boxRotation);
			m_playerModel.SetRotation(m_playerRotation);
		}

		//Scoreの文字の移動(出現）
		if (m_count <= 49) {
			m_scoreColor.w += 0.02f;
			m_scorePosition.x += 0.5f;
			m_scoreSprite.SetPosition(m_scorePosition);
			m_scoreSprite.SetMulColor(m_scoreColor);
			m_scoreSprite.Update();
		}

		//SCOREの出現
		if (m_count >= 50 && m_count < 55) {
			for (int i = 0; i < 5; i++) {
				m_scoreCommaSpriteAlpha[i][0] += 0.2f;
				for (int j = 0; j < 10; j++) {
					m_scoreNum[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_scoreCommaSpriteAlpha[i][0]));
				}
			}
			m_scoreCommaSprite.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_scoreCommaSpriteAlpha[1][0]));
		}
		if (m_count >= 55 && m_count < 60) {
			for (int i = 0; i < 5; i++) {
				m_scoreCommaSpriteAlpha[i][0] -= 0.2f;
				for (int j = 0; j < 10; j++) {
					m_scoreNum[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_scoreCommaSpriteAlpha[i][0]));
				}
			}
			m_scoreCommaSprite.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_scoreCommaSpriteAlpha[1][0]));
		}
		if (m_count >= 60 && m_count < 65) {
			for (int i = 0; i < 5; i++) {
				m_scoreCommaSpriteAlpha[i][0] += 0.2f;
				for (int j = 0; j < 10; j++) {
					m_scoreNum[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_scoreCommaSpriteAlpha[i][0]));
				}
			}
			m_scoreCommaSprite.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_scoreCommaSpriteAlpha[1][0]));
		}
		if (m_count >= 65 && m_count < 70) {
			for (int i = 0; i < 5; i++) {
				m_scoreCommaSpriteAlpha[i][0] -= 0.2f;
				for (int j = 0; j < 10; j++) {
					m_scoreNum[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_scoreCommaSpriteAlpha[i][0]));
				}
			}
			m_scoreCommaSprite.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_scoreCommaSpriteAlpha[1][0]));
		}
		if (m_count >= 70 && m_count < 110) {
			for (int i = 0; i < 5; i++) {
				m_scoreCommaSpriteAlpha[i][0] += 0.025f;
				for (int j = 0; j < 10; j++) {
					m_scoreNum[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_scoreCommaSpriteAlpha[i][0]));
				}
			}
			m_scoreCommaSprite.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_scoreCommaSpriteAlpha[1][0]));
		}

		
	}

	//ランク
	if (m_resultState == 2) {
		if (m_count <= 10) {
			m_boxRotation.AddRotationDegY(33.0f);
			m_playerRotation.AddRotationDegY(33.0f);
			m_boxModel.SetRotation(m_boxRotation);
			m_playerModel.SetRotation(m_playerRotation);
		}

		if (m_count >= 30 && m_count < 35) {
			m_rankColor.w += 0.2f;
			
		}
		if (m_count >= 30 && m_count < 80) {
			m_rankScale.x -= 0.02f;
			m_rankScale.y -= 0.02f;
			m_rankSheetSprite.SetScale(m_rankScale);
		}
		if (m_count >= 80 && m_count < 100) {
			m_rankSheetColor.w += 0.05f;
			m_rankPosition.x -= 2.5f;
			m_rankSheetSprite.SetPosition(m_rankPosition);
			m_rankSheetSprite.SetMulColor(m_rankSheetColor);
		}
		if (m_count == 1) {
			//タイムとスコアの初期化(ランク用)
			//タイム関係
			
			m_rankTimeSprite.SetMulColor(m_rankTimeColor);
			m_rankTimeSprite.SetPosition(m_rankTimePosition);
			for (int i = 0; i < 2; i++) {
				m_timeColonSpriteAlpha[i][0] =0;
				for (int j = 0; j < 10; j++) {
					m_timeNum[i][j].SetScale(Vector3{ 0.55f,0.55f,0.55f });
					m_timeNum[i][j].SetPosition(Vector3{ (-590.0f + (50.0f * i)),13.0f,0.0f });
					m_timeNum[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_timeColonSpriteAlpha[i][0]));
				}
			}
			for (int i = 2; i < 4; i++) {
				m_timeColonSpriteAlpha[i][0] = 0;
				for (int j = 0; j < 10; j++) {
					m_timeNum[i][j].SetScale(Vector3{ 0.55f,0.55f,0.55f });
					m_timeNum[i][j].SetPosition(Vector3{ (-590.0f + (50.0f * i+1)),13.0f,0.0f });
					m_timeNum[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_timeColonSpriteAlpha[i][0]));
				}
			}
			m_timeColonSprite.SetScale(Vector3{ 0.55f,0.55f,0.55f });
			m_timeColonSprite.SetPosition(Vector3{ -490.0f,13.0f,0.0f });
			m_timeColonSprite.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_timeColonSpriteAlpha[1][0]));
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 10; j++) {
					m_timeNum[i][j].Update();
				}
			}
			m_timeColonSprite.Update();
			m_rankTimeSprite.Update();

			//SCORE関係
			m_rankScoreSprite.SetMulColor(m_rankScoreColor);
			m_rankScoreSprite.SetPosition(m_rankScorePosition);
			for (int i = 0; i < 2; i++) {
				m_scoreCommaSpriteAlpha[i][0] = 0;
				for (int j = 0; j < 10; j++) {
					m_scoreNum[i][j].SetScale(Vector3{ 0.55f,0.55f,0.55f });
					m_scoreNum[i][j].SetPosition(Vector3{ (340.0f + (50.0f * i)),13.0f,0.0f });
					m_scoreNum[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_scoreCommaSpriteAlpha[i][0]));
				}
			}
			for (int i = 2; i < 5; i++) {
				m_scoreCommaSpriteAlpha[i][0] = 0;
				for (int j = 0; j < 10; j++) {
					m_scoreNum[i][j].SetScale(Vector3{ 0.55f,0.55f,0.55f });
					m_scoreNum[i][j].SetPosition(Vector3{ (340.0f + (50.0f * i + 1)),13.0f,0.0f });
					m_scoreNum[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_scoreCommaSpriteAlpha[i][0]));
				}
			}
			m_scoreCommaSprite.SetScale(Vector3{ 0.55f,0.55f,0.55f });
			m_scoreCommaSprite.SetPosition(Vector3{ 440.0f,13.0f,0.0f });
			m_scoreCommaSprite.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_timeColonSpriteAlpha[1][0]));
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 10; j++) {
					m_scoreNum[i][j].Update();
				}
			}
			m_scoreCommaSprite.Update();
			m_rankScoreSprite.Update();
		}
		if (m_count >= 80 && m_count < 100) {

			m_rankTimeColor.w += 0.05f;
			m_rankTimePosition.x += 1.25f;
			m_rankTimeSprite.SetMulColor(m_rankTimeColor);
			m_rankTimeSprite.SetPosition(m_rankTimePosition);
			for (int i = 0; i < 2; i++) {
				m_timeColonSpriteAlpha[i][0] +=0.05f;
				for (int j = 0; j < 10; j++) {
					m_timeNum[i][j].SetPosition(Vector3{ (-590.0f + (50.0f * i)),13.0f,0.0f });
					m_timeNum[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_timeColonSpriteAlpha[i][0]));
				}
			}
			for (int i = 2; i < 4; i++) {
				m_timeColonSpriteAlpha[i][0] += 0.05f;
				for (int j = 0; j < 10; j++) {
					m_timeNum[i][j].SetPosition(Vector3{ (-590.0f + (50.0f * (i + 1))),13.0f,0.0f });
					m_timeNum[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_timeColonSpriteAlpha[i][0]));
				}
			}
			m_rankTimeSprite.Update();
			m_timeColonSprite.SetPosition(Vector3{ -490.0f,13.0f,0.0f });
			m_timeColonSprite.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_timeColonSpriteAlpha[1][0]));

			//SCORE
			m_rankScoreColor.w += 0.05f;
			m_rankScorePosition.x -= 1.25f;
			m_rankScoreSprite.SetMulColor(m_rankScoreColor);
			m_rankScoreSprite.SetPosition(m_rankScorePosition);
			for (int i = 0; i < 2; i++) {
				m_scoreCommaSpriteAlpha[i][0] += 0.05f;
				for (int j = 0; j < 10; j++) {
					m_scoreNum[i][j].SetPosition(Vector3{ (340.0f + (50.0f * i)),13.0f,0.0f });
					m_scoreNum[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_scoreCommaSpriteAlpha[i][0]));
				}
			}
			for (int i = 2; i < 5; i++) {
				m_scoreCommaSpriteAlpha[i][0] += 0.05f;
				for (int j = 0; j < 10; j++) {
					m_scoreNum[i][j].SetPosition(Vector3{ (340.0f + (50.0f * (i + 1))),13.0f,0.0f });
					m_scoreNum[i][j].SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_scoreCommaSpriteAlpha[i][0]));
				}
			}
			m_rankScoreSprite.Update();
			m_scoreCommaSprite.SetPosition(Vector3{ 440.0f,13.0f,0.0f });
			m_scoreCommaSprite.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_scoreCommaSpriteAlpha[1][0]));
		}
		
		
	}
	m_count++;

	//更新
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 10; j++) {
			m_timeNum[i][j].Update();
		}
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			m_scoreNum[i][j].Update();
		}
	}
	for (int i = 1; i <= 4; i++) {
		m_rankSprite[i - 1].SetScale(m_rankScale);
		m_rankSprite[i - 1].SetMulColor(m_rankColor);
		m_rankSprite[i - 1].Update();
	}
	m_rankSheetSprite.Update();
	
	m_boxModel.Update();
	m_playerModel.Update();
}

void Result::FontSet() {

	//タイム関連の初期化
	m_timeSprite.Init("Assets/sprite/time.DDS", 1632.0f, 918.0f);//タイムの文字の読み込み
	m_timeColonSprite.Init("Assets/sprite/colon.DDS", 73.1f, 136.85f);//タイムの:の読み込み
	//タイムの数字の読み込み
	for (int i = 0; i < 4; i++) {
		m_timeColonSpriteAlpha[i][0] = 0;
		for (int j = 0; j < 10; j++) {
			m_timeNum[i][j].Init(getString(j), 86.0f, 161.0f);
		}
	}
	//ポジションの設定
	for (int i = 0; i < 10; i++) {
		m_timeNum[0][i].SetPosition(m_timePosition0);
		m_timeNum[1][i].SetPosition(m_timePosition1);
		m_timeNum[2][i].SetPosition(m_timePosition3);
		m_timeNum[3][i].SetPosition(m_timePosition4);
	}
	m_timeColonSprite.SetPosition(m_timePosition2);
	//更新
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 10; j++) {
			m_timeNum[i][j].Update();
		}
	}


	//SCOREの設定
	if (m_player->GetPlayerDead() == false) {
		m_timeSet[0] = m_minute / 10;//分10の位
		m_timeSet[1] = m_minute % 10;//分1の位
		m_timeSet[2] = m_seconds / 10;//秒10の位
		m_timeSet[3] = m_seconds % 10;//秒1の位
		m_score = (10 - m_minute) * 1000 + (60 - m_seconds) * 10;//SCOREの計算
		m_maxScore = 10 * 1000 + 60 * 10;//マックスSCOREの計算
		//SCOREの各桁がどれだけあるかの計算
		while (m_score >= 10000) {
			m_scoreSet[0]++;
			m_score -= 10000;
			m_total += 10000;
		}
		while (m_score >= 1000) {
			m_scoreSet[1]++;
			m_score -= 1000;
			m_total += 1000;
		}
		while (m_score >= 100) {
			m_scoreSet[2]++;
			m_score -= 100;
			m_total += 100;
		}
		while (m_score >= 10) {
			m_scoreSet[3]++;
			m_score -= 10;
			m_total += 10;
		}
		while (m_score >= 1) {
			m_scoreSet[4]++;
			m_score -= 1;
			m_total += 1;
		}
	}
	else {
		for (int i = 0; i < 5; i++) {
			m_scoreSet[i] = 0;
		}
	}

	m_scoreSprite.Init("Assets/sprite/score.DDS", 1632.0f, 918.0f);//SCOREの文字の読み込み
	m_scoreCommaSprite.Init("Assets/sprite/,.DDS", 73.1f, 136.85f);//SCOREの、の読み込み
	//SCOREの数字の読み込み
	for (int i = 0; i < 5; i++) {
		m_scoreCommaSpriteAlpha[i][0] = 0;
		for (int j = 0; j < 10; j++) {
			m_scoreNum[i][j].Init(getString(j), 86.0f, 161.0f);
		}
	}
	//ポジション設定
	for (int i = 0; i < 10; i++) {
		m_scoreNum[0][i].SetPosition(m_scorePosition0);
		m_scoreNum[1][i].SetPosition(m_scorePosition1);
		m_scoreNum[2][i].SetPosition(m_scorePosition3);
		m_scoreNum[3][i].SetPosition(m_scorePosition4);
		m_scoreNum[4][i].SetPosition(m_scorePosition5);
	}
	m_scoreCommaSprite.SetPosition(m_scorePosition2);
	//更新
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			m_scoreNum[i][j].Update();
		}
	}
	m_scoreCommaSprite.Update();
	m_timeColonSprite.Update();

	//ランクの設定
	m_rankTimeSprite.Init("Assets/sprite/time_rank.DDS", 1632.0f, 918.0f);
	m_rankTimeSprite.SetMulColor(m_rankTimeColor);
	m_rankScoreSprite.Init("Assets/sprite/SCORE_rank.DDS", 1632.0f, 918.0f);
	m_rankScoreSprite.SetMulColor(m_rankScoreColor);
	m_rankSheetSprite.Init("Assets/sprite/Rank.DDS", 1632.0f, 918.0f);//ランクの文字の読み込み
	m_rankSheetSprite.SetPosition(m_rankPosition);
	m_rankSheetSprite.SetMulColor(m_rankSheetColor);
	m_maxScore /= 4;//ランクが四段階のため
	//今回何ランクだったかの計算
	if (m_player->GetPlayerDead() == false) {
		for (int i = 1; i <= 4; i++) {
			m_rankSprite[i - 1].Init(getRank(i - 1), 1632.0f, 918.0f);
			m_rankSprite[i - 1].SetScale(m_rankScale);
			m_rankSprite[i - 1].SetMulColor(m_rankColor);
			if (m_total > m_maxScore * i) {
				m_rankSet++;
			}
			m_rankSprite[i - 1].Update();
		}
	}
	else {
		for (int i = 1; i <= 4; i++) {
			m_rankSprite[i - 1].Init(getRank(i - 1), 1632.0f, 918.0f);
			m_rankSprite[i - 1].SetScale(m_rankScale);
			m_rankSprite[i - 1].SetMulColor(m_rankColor);
			m_rankSet = 0;
			m_rankSprite[i - 1].Update();
		}
	}

	m_rankScoreSprite.Update();
	m_rankTimeSprite.Update();
	m_rankSheetSprite.Update();
}


void Result::BackSet() { //モデルの読み込み
	//プレイヤー
	m_playerModel.Init(getPlayer_result_color(m_player->GetRandomColor()));
	m_playerModel.SetPosition(m_playerPosition);
	m_playerRotation.SetRotationDegY(-135.0f);
	m_playerModel.SetRotation(m_playerRotation);
	//m_playerModel.Update();

	//背景
	m_boxModel.Init("Assets/modelData/Customize_area.tkm");
	m_boxModel.SetPosition(m_boxPosition);
	m_boxModel.SetScale(m_boxScale);
	//m_boxModel.Update();

	//カメラの設定
	m_gameCamera->SetToCameraPos({0.0f, -10.0f, -100.0f});
	//gamecamera->fast_count = 0;
	m_gameCamera->SetTarget({10000.0f,20.0f,0.0f});
	m_gameCamera->GetSpringCamera().Refresh();
	m_gameCamera->SetCameraState(3);

	//コアウェポンの設定
	m_coreModel.Init("Assets/modelData/Versatile_Perforator.tkm");
	

	//肩
	if (m_customPoint[0][1] != 0)	
	{
		//武器によってモデルを変える
		switch (m_customPoint[0][1])
		{
		case 2:	//マシンガン
			//モデルの初期化
			m_shoulderModel.Init("Assets/modelData/machine_gun_drop.tkm");
			//モデルの大きさの設定
			m_shoulderModel.SetScale(m_machinegunScale);



			break;
		case 4:	//ギガトンキャノン
			//モデルの初期化
			m_shoulderModel.Init("Assets/modelData/GIgaton_shoulder.tkm");
			//モデルの大きさの設定
			m_shoulderModel.SetScale(0.8f);



			break;

		case 6:	//戦艦砲
			//モデルの初期化
			m_shoulderModel.Init("Assets/modelData/battleship_gun_shoulder.tkm");
			//モデルの大きさの設定
			m_shoulderModel.SetScale(m_battleshipgunScale);


			break;
		default:
			break;
		}
		
	}

	//右腕
	if (m_customPoint[0][0] != 0)	
	{
		//武器によってモデルを変える
		switch (m_customPoint[0][0])
		{
		case 2:	//マシンガン
			//モデルの初期化
			m_rightArmModel.Init("Assets/modelData/machine_gun_drop.tkm");
			//モデルの大きさの設定
			m_rightArmModel.SetScale(m_machinegunScale);
			

			break;
		case 4:	//ギガトンキャノン
			//モデルの初期化
			m_rightArmModel.Init("Assets/modelData/GIgaton_cannon_Right_arm.tkm");
			m_rightArmModel.SetScale(0.8f);

			break;
		case 6:	//戦艦砲
			//モデルの初期化
			m_rightArmModel.Init("Assets/modelData/battleship_gun_right_arm.tkm");
			m_rightArmModel.SetScale(m_battleshipgunScale);

			break;
		default:
			break;
		}
		m_rightArmModel.Update();
	}

	//右足
	if (m_customPoint[1][0] != 0)	
	{

		//武器によってモデルを変える
		switch (m_customPoint[1][0])
		{
		case 2:	//マシンガン
			//モデルの初期化
			m_rightLeg.Init("Assets/modelData/machine_gun_drop.tkm");
			//モデルの大きさの設定
			m_rightLeg.SetScale(m_machinegunScale);

			break;
		case 4:	//ギガトンキャノン
			//モデルの初期化
			m_rightLeg.Init("Assets/modelData/GIgaton_cannon.tkm");
			//モデルの大きさの設定
			m_rightLeg.SetScale(0.8f);

			break;

		case 6:	//戦艦砲
			//モデルの初期化
			m_rightLeg.Init("Assets/modelData/battleship_gun_right_leg01.tkm");
			//モデルの大きさの設定
			m_rightLeg.SetScale(m_battleshipgunScale);


			break;
		default:
			break;
		}
		m_rightLeg.Update();
	}

	//左腕
	if (m_customPoint[0][2] != 0)	
	{
		switch (m_customPoint[0][2]) {
		case 2:	//マシンガン
			//モデルの初期化
			m_leftArm.Init("Assets/modelData/machine_gun_drop.tkm");
			//モデルの大きさの設定
			m_leftArm.SetScale(m_machinegunScale);
			

			break;
		case 4:	//ギガトンキャノン
			//モデルの初期化
			m_leftArm.Init("Assets/modelData/GIgaton_cannon_Left_arm.tkm");
			//モデルの大きさの設定
			m_leftArm.SetScale(0.8f);
			

			break;

		case 6:	//戦艦砲
			//モデルの初期化
			m_leftArm.Init("Assets/modelData/battleship_gun_left_arm.tkm");
			//モデルの大きさの設定
			m_leftArm.SetScale(m_battleshipgunScale);
			


			break;
		default:
			break;
		}
		m_leftArm.Update();
	}

	//左足
	if (m_customPoint[1][2] != 0)	
	{
		//武器によってモデルを変える
		switch (m_customPoint[1][2])
		{
		case 2:	//マシンガン
			//モデルの初期化
			m_leftLeg.Init("Assets/modelData/machine_gun_drop.tkm");
			//モデルの大きさの設定
			m_leftLeg.SetScale(m_machinegunScale);
			

			break;
		case 4:	//ギガトンキャノン
			//モデルの初期化
			m_leftLeg.Init("Assets/modelData/GIgaton_cannon.tkm");
			//モデルの大きさの設定
			m_leftLeg.SetScale(0.8f);
			

			break;

		case 6:	//戦艦砲
			//モデルの初期化
			m_leftLeg.Init("Assets/modelData/battleship_gun_left_leg01.tkm");
			//モデルの大きさの設定
			m_leftLeg.SetScale(m_battleshipgunScale);
			

			break;
		default:
			break;
		}
		m_leftLeg.Update();
	}
}
void Result::BackGround()
{
	//コアウェポンの動き
	m_coreLocalPos = { 0.0f,80.0f,10.0f };
	Quaternion originRotation = m_playerRotation;
	Vector3 cw_position = m_playerPosition;


	originRotation.Multiply(m_coreLocalPos);
	cw_position += m_coreLocalPos;
	Quaternion cw_Rotation = originRotation;

	m_coreModel.SetRotation(cw_Rotation);
	m_coreModel.SetPosition(cw_position);
	m_coreModel.Update();
		
	//肩
	if (m_customPoint[0][1] != 0)
	{
		//武器によってモデルを変える
		switch (m_customPoint[0][1])
		{
		case 2:	//マシンガン

			//モデルの大きさの設定
			m_shoulderModel.SetScale(m_machinegunScale);
			//ローカルポジションの設定
			m_shoulderLocalPos = { 35.0f,119.0f,0.0f };


			break;
		case 4:	//ギガトンキャノン

			//モデルの大きさの設定
			m_shoulderModel.SetScale(0.8f);
			//ローカルポジションの設定
			m_shoulderLocalPos = { 0.0f,120.0f,0.0f };


			break;

		case 6:	//戦艦砲

			//モデルの大きさの設定
			m_shoulderModel.SetScale(m_battleshipgunScale);
			//ローカルポジションの設定
			m_shoulderLocalPos = { 0.0f,119.0f,0.0f };

			break;
		default:
			break;
		}

		//移動の処理
		Quaternion originRotation = m_playerRotation;
		Vector3 sw_position = m_playerPosition;
		originRotation.Multiply(m_shoulderLocalPos);
		sw_position += m_shoulderLocalPos;
		Quaternion sw_Rotation = originRotation;

		//更新
		m_shoulderModel.SetRotation(sw_Rotation);
		m_shoulderModel.SetPosition(sw_position);

		
		m_shoulderModel.Update();
	}
		
	//右腕
	if (m_customPoint[0][0] != 0)
	{
		//武器によってモデルを変える
		switch (m_customPoint[0][0])
		{
		case 2:	//マシンガン
			//モデルの大きさの設定
			m_rightArmModel.SetScale(m_machinegunScale);
			//ローカルポジションの設定
			m_rightArmLocalPos = { 60.0f,100.0f,0.0f };

			break;
		case 4:	//ギガトンキャノン

			//モデルの大きさの設定
			m_rightArmModel.SetScale(0.8f);
			//ローカルポジションの設定
			m_rightArmLocalPos = { 50.0f,100.0f,30.0f };

			break;
		case 6:	//戦艦砲

			//モデルの大きさの設定
			m_rightArmModel.SetScale(m_battleshipgunScale);
			//ローカルポジションの設定
			m_rightArmLocalPos = { 60.0f,80.0f,-10.0f };

			break;
		default:
			break;
		}

		//移動の処理
		Quaternion originRotation = m_playerRotation;
		Vector3 raw_position = m_playerPosition;
		originRotation.Multiply(m_rightArmLocalPos);
		raw_position += m_rightArmLocalPos;
		Quaternion raw_Rotation = originRotation;

		//更新
		m_rightArmModel.SetRotation(raw_Rotation);
		m_rightArmModel.SetPosition(raw_position);

		
		m_rightArmModel.Update();
	}
		
	//右足
	if (m_customPoint[1][0] != 0)
	{
		//武器によってモデルを変える
		switch (m_customPoint[1][0])
		{
		case 2:	//マシンガン
			//モデルの大きさの設定
			m_rightLeg.SetScale(m_machinegunScale);
			//ローカルポジションの設定
			m_rightLegLocalPos = { 90.0f,30.0f,0.0f };

			break;
		case 4:	//ギガトンキャノン
			//モデルの大きさの設定
			m_rightLeg.SetScale(0.8f);
			//ローカルポジションの設定
			m_rightLegLocalPos = { 55.0f,40.0f,27.0f };

			break;

		case 6:	//戦艦砲
			//モデルの大きさの設定
			m_rightLeg.SetScale(m_battleshipgunScale);
			//ローカルポジションの設定
			m_rightLegLocalPos = { 60.0f,40.0f,40.0f };


			break;
		default:
			break;
		}

		//移動の処理
		Quaternion originRotation = m_playerRotation;
		Vector3 rlw_position = m_playerPosition;
		originRotation.Multiply(m_rightLegLocalPos);
		rlw_position += m_rightLegLocalPos;
		Quaternion rlw_Rotation = originRotation;

		//更新
		m_rightLeg.SetRotation(rlw_Rotation);
		m_rightLeg.SetPosition(rlw_position);

		
		m_rightLeg.Update();
	}
	
	//左腕
	if (m_customPoint[0][2] != 0)
	{
		
		switch (m_customPoint[0][2]) {
		case 2:	//マシンガン
			//モデルの大きさの設定
			m_leftArm.SetScale(m_machinegunScale);
			//ローカルポジションの設定
			m_leftArmLocalPos = { -60.0f,100.0f,0.0f };

			break;
		case 4:	//ギガトンキャノン
			//モデルの大きさの設定
			m_leftArm.SetScale(0.8f);
			//ローカルポジションの設定
			m_leftArmLocalPos = { -50.0f,100.0f,30.0f };

			break;

		case 6:	//戦艦砲
			//モデルの大きさの設定
			m_leftArm.SetScale(m_battleshipgunScale);
			//ローカルポジションの設定
			m_leftArmLocalPos = { -60.0f,80.0f,-10.0f };


			break;
		default:
			break;
		}

		//移動の処理
		Quaternion originRotation = m_playerRotation;
		Vector3 law_position = m_playerPosition;
		originRotation.Multiply(m_leftArmLocalPos);
		law_position += m_leftArmLocalPos;
		Quaternion law_Rotation = originRotation;

		//更新
		m_leftArm.SetRotation(law_Rotation);
		m_leftArm.SetPosition(law_position);
		m_leftArm.Update();
	}

	//左足
	if (m_customPoint[1][2] != 0)
	{
		//武器によってモデルを変える
		switch (m_customPoint[1][2])
		{
		case 2:	//マシンガン

			//モデルの大きさの設定
			m_leftLeg.SetScale(m_machinegunScale);
			//ローカルポジションの設定
			m_leftLegLocalPos = { -90.0f,30.0f,0.0f };

			break;
		case 4:	//ギガトンキャノン
			//モデルの大きさの設定
			m_leftLeg.SetScale(0.8f);
			//ローカルポジションの設定
			m_leftLegLocalPos = { -55.0f,40.0f,27.0f };

			break;

		case 6:	//戦艦砲

			//モデルの大きさの設定
			m_leftLeg.SetScale(m_battleshipgunScale);
			//ローカルポジションの設定
			m_leftLegLocalPos = { -60.0f,40.0f,40.0f };

			break;
		default:
			break;
		}

		//移動の処理
		Quaternion originRotation = m_playerRotation;
		Vector3 llw_position = m_playerPosition;
		originRotation.Multiply(m_leftLegLocalPos);
		llw_position += m_leftLegLocalPos;
		Quaternion llw_Rotation = originRotation;

		//更新
		m_leftLeg.SetRotation(llw_Rotation);
		m_leftLeg.SetPosition(llw_position);

		
		m_leftLeg.Update();
	}
}

void Result::EnemyCount()
{

}

void Result::Render(RenderContext& rc)
{	
	//各部位に装備されているならDrawする
	m_coreModel.Draw(rc);				//コア武器はずっと存在するので分岐なし
	m_playerModel.Draw(rc);				//胴体はずっと存在するので分岐なし
	if (m_customPoint[0][0] !=0)
	{
		m_rightArmModel.Draw(rc);	//右腕
	}
	if (m_customPoint[0][2] != 0)
	{
		m_leftArm.Draw(rc);		//左腕
	}
	if (m_customPoint[0][1] != 0)
	{
		m_shoulderModel.Draw(rc);		//肩
	}
	if (m_customPoint[1][0] != 0)
	{
		m_rightLeg.Draw(rc);	//右足
	}
	if (m_customPoint[1][2] != 0)
	{
		m_leftLeg.Draw(rc);		//左足
	}

	m_boxModel.Draw(rc);

	if (m_resultState == 0) {
		m_timeSprite.Draw(rc);
		for (int i = 0; i < 4; i++) {
			m_timeNum[i][m_timeSet[i]].Draw(rc);
		}
		m_timeColonSprite.Draw(rc);
	}
	if (m_resultState == 1) {
		m_scoreSprite.Draw(rc);
		for (int i = 0; i < 5; i++) {
			m_scoreNum[i][m_scoreSet[i]].Draw(rc);
		}
		m_scoreCommaSprite.Draw(rc);
	}
	if (m_resultState == 2) {
		m_rankSprite[m_rankSet].Draw(rc);
		m_rankSheetSprite.Draw(rc);

		m_rankTimeSprite.Draw(rc);
		for (int i = 0; i < 4; i++) {
			m_timeNum[i][m_timeSet[i]].Draw(rc);
		}
		m_timeColonSprite.Draw(rc);

		m_rankScoreSprite.Draw(rc);
		for (int i = 0; i < 5; i++) {
			m_scoreNum[i][m_scoreSet[i]].Draw(rc);
		}
		m_scoreCommaSprite.Draw(rc);
	}
}