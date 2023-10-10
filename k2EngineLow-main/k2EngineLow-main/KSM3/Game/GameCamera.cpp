#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "Customize_UI_ver2.h"
#include "Game.h"


namespace
{
	//ステートナンバー
	const int CAMERA_STATE_ZAKO = 0;
	const int CAMERA_STATE_BOSS = 1;
	const int CAMERA_STATE_QTE = 2;
	const int CAMERA_STATE_CUSTOMIZE = 3;
	const int CAMERA_STATE_OP = 4;

	//stickの入力量にかけられる数
	const float MULTIPLYABLE_NUM = 1.3f;

	//揺れの減少量
	const int VIB_DECREASE_AMOUNT = 10;
	const int BIGVIB_DECREASE_AMOUNT = 10;
	const int FINALVIB_DECREASE_AMOUNT = 40;

	//揺れの最大値
	const float VIBRATION_MAX = 640.0f;
	const float VIBRATION_BIG_MAX = 2560.0f;
	const float VIBRATION_FINAL_MAX = 5120.0f;

	//メインゲーム中のカメラポジション
	const Vector3 MAIN_TO_CAMERA_POS = { 0.0f, 500.0f, -700.0f };
	const Vector3 CUSTOMIZE_TO_CAMERA_POS = { 0.0f, 10.0f, -300.0f };

}

GameCamera::GameCamera()
{

	//ばねカメラの初期化
	m_springCamera.Init(
		*g_camera3D,		//ばねカメラの処理を行うカメラを指定する。
		500.0f,				//カメラの移動速度の最大値。
		true,				//カメラと地形とのあたり判定を取るかどうかのフラグ。trueだとあたり判定を行う。
		5.0f				//カメラに設定される球体コリジョンの半径。第３引数がtrueの時に有効になる。
	);


	//カメラのニアクリップとファークリップを設定
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(80000.0f);


	//注視点から視点に向かうベクトルの設定
	m_toCameraPos.Set(MAIN_TO_CAMERA_POS);

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{

	//プレイヤーを探す
	m_player = FindGO<Player>("player");


	//ゲームを探す
	m_game = FindGO<Game>("game");


	//効果音の設定
	m_walkSE = NewGO<SoundSource>(0);
	m_walkSE->Init(enRunning);						//初期化
	m_walkSE->SetVolume(0.5f * m_game->GetSEVol());	//音量調整


	return true;
}

void GameCamera::Update()
{
	//世界が止まっているなら
	if (m_game->IsStopWorld() != false)
	{
		//視点を計算する。
		m_position = m_target + m_toCameraPos;

		//ばねカメラの設定
		m_springCamera.SetTarget(m_target);
		m_springCamera.SetPosition(m_position);
		m_springCamera.UpdateSpringCamera();
		m_springCamera.UpdateCamera();
		return;
	}

	//直前のカメラポジションを保存
	Vector3 toCameraPosOld = m_toCameraPos;


	//パッドによる回転量の計算
	CalcRotation();


	//注視点から視点までのベクトルを正規化する
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	

	//雑魚戦の時
	if (m_cameraState == CAMERA_STATE_ZAKO)
	{

		//注視点を設定
		m_target = m_player->GetPlayerPosition();


		//プレイヤの足元からちょっと上を注視点とする
		m_target.y += 180.0f;		


		//カメラが上向きすぎ
		if (toPosDir.y < 0.1f)
		{

			//直前のポジションに戻す
			m_toCameraPos = toCameraPosOld;

		}
		//カメラが下向きすぎ
		else if (toPosDir.y > 0.8f) 
		{

			//直前のポジションに戻す
			m_toCameraPos = toCameraPosOld;

		}


		//画面揺れの処理
		ManageVibration();

	}
	//ボス戦の時
	else if (m_cameraState == CAMERA_STATE_BOSS)
	{

		//注視点を計算する。
		m_target = m_player->GetPlayerPosition();
		

		//プレイヤの足元からちょっと上を注視点とする
		m_target.y += 200.0f;		


		//カメラが上向きすぎ
		if (toPosDir.y < -0.2f)
		{

			//直前のポジションに戻す
			m_toCameraPos = toCameraPosOld;

		}
		//カメラが下向きすぎ
		else if (toPosDir.y > 0.7f)
		{

			//直前のポジションに戻す
			m_toCameraPos = toCameraPosOld;

		}

	}
	else if (m_cameraState == CAMERA_STATE_QTE)
	{
		//QTE用にしたい
	}
	//カスタマイズ画面の時
	else if (m_cameraState == CAMERA_STATE_CUSTOMIZE)
	{

		//ポジションの設定
		m_toCameraPos.Set(CUSTOMIZE_TO_CAMERA_POS);


		//プレイヤの足元からちょっと上を注視点とする
		m_target.y = 100.0f;

	}
	else if (m_cameraState == CAMERA_STATE_OP)
	{
	
		//オープニング中のカメラ移動処理
		OPMove();

	}


	//カスタム画面とリザルト以外の時
	if (m_cameraState != CAMERA_STATE_CUSTOMIZE && m_player->GetGameState() != RESULT_NUM && m_cameraState != CAMERA_STATE_QTE)
	{
		//揺れの大きさを足す
		m_target.x += BGX;
		m_target.y += BGY;
	}


	//視点を計算する。
	m_position = m_target + m_toCameraPos;
	

	//ばねカメラの設定
	m_springCamera.SetTarget(m_target);
	m_springCamera.SetPosition(m_position);
	m_springCamera.Update();


	//カメラの前方向の設定(ｘとｚの情報だけで良い)
	m_cameraForward.x = m_target.x - m_position.x;
	m_cameraForward.z = m_target.z - m_position.z;
	m_cameraForward.Normalize();

}

void GameCamera::CalcRotation()
{
	//メインゲーム中にプレイヤーが死んでないなら
	if (m_cameraState != CAMERA_STATE_CUSTOMIZE && m_cameraState != CAMERA_STATE_OP && m_player->GetPlayerDead() != true && m_cameraState != CAMERA_STATE_QTE)
	{

		//パッドの入力を使ってカメラを回す
		m_stickPowerX = g_pad[0]->GetRStickXF() * MULTIPLYABLE_NUM;
		m_stickPowerY = g_pad[0]->GetRStickYF() * MULTIPLYABLE_NUM;

	}
	else
	{
		//入力量は0にする
		m_stickPowerX = 0;
		m_stickPowerY = 0;
	}


	//Y軸周りの回転
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, m_stickPowerX);
	qRot.Apply(m_toCameraPos);


	//X軸周りの回転。
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();

	qRot.SetRotationDeg(axisX, m_stickPowerY);
	qRot.Apply(m_toCameraPos);

}

void GameCamera::OPMove()
{

	//注視点を計算する。
	m_target = m_player->GetPlayerPosition();
	

	//プレイヤの足元からちょっと上を注視点とする
	m_target.y += 180.0f;		


	if (m_opCount >= 0 && m_opCount <= 200)
	{

		//プレイヤーを前へ進める
		m_player->AddPositionZ(5.0f);


		//注視点から視点までのベクトルを設定
		m_toCameraPos.Set(50.0f, 40.0f, 500.0f);

	}
	else if (m_opCount > 200 && m_opCount <= 280)
	{

		//プレイヤーを前へ進める
		m_player->AddPositionZ(3.0f);


		//Y軸周りの回転
		Quaternion YRot;
		YRot.SetRotationDeg(Vector3::AxisY, 1.0f);
		YRot.Apply(m_toCameraPos);


		//X軸周りの回転
		Quaternion XRot;
		XRot.SetRotationDeg(Vector3::AxisX, -0.95f);
		XRot.Apply(m_toCameraPos);

	}
	else if (m_opCount > 280 && m_opCount <= 400)
	{

		//ゲーム中の視点に合わせる
		m_toCameraPos.Set(MAIN_TO_CAMERA_POS);

	}
	else if (m_opCount > 400)
	{

		//ばねカメラの初期化
		m_springCamera.Init(
			*g_camera3D,		//ばねカメラの処理を行うカメラを指定する。
			50000.0f,			//カメラの移動速度の最大値。
			true,				//カメラと地形とのあたり判定を取るかどうかのフラグ。trueだとあたり判定を行う。
			5.0f				//カメラに設定される球体コリジョンの半径。第３引数がtrueの時に有効になる。
		);


		//キャラコンをプレイヤーが今いる位置で設定
		m_player->SetCharacterControllerPosition(m_player->GetPlayerPosition());
		m_game->SetUp();
		m_player->SetGameState(0);
		m_cameraState = CAMERA_STATE_ZAKO;

	}


	//動いている間
	if (m_walkSE->IsPlaying() != true && m_opCount < 280)
	{
		
		//足音再生
		m_walkSE->Play(true);

	}
	//動きが止まったら
	else if (m_opCount >= 280)
	{
		
		//足音停止
		m_walkSE->Stop();

	}


	//動いている間に30フレーム経ったら
	if (m_effectCount > 30 && m_opCount < 280)
	{

		//砂ぼこりエフェクトの初期化と再生
		m_sunabokoriEffect = NewGO<EffectEmitter>(0);
		m_sunabokoriEffect->Init(enSunabokori);
		m_sunabokoriEffect->SetScale({ 4.0f,4.0f,4.0f });
		m_sunabokoriEffect->SetRotation(m_player->GetPlayerRotation());
		m_sunabokoriEffect->SetPosition(m_player->GetPlayerPosition());
		m_sunabokoriEffect->Play();

		
		//カウントリセット
		m_effectCount = 0;

	}


	//エフェクト発生間隔のカウントをアップ
	m_effectCount++;


	//OP中のカメラ制御カウントをアップ
	m_opCount++;

}

void GameCamera::ManageVibration()
{

	//揺れのフラグが立ったら
	if (m_vibFlag == true)
	{

		//揺れの最大値を設定
		static int Vibration = VIBRATION_MAX;


		//揺れの処理
		PlayVibration(VIB_DECREASE_AMOUNT, VIBRATION_MAX, m_vibFlag, Vibration);

	}


	//大きな揺れのフラグが立ったら
	if (m_bigVibFlag == true)
	{

		//揺れの最大値を設定
		static int Vibration = VIBRATION_BIG_MAX;


		//揺れの処理
		PlayVibration(BIGVIB_DECREASE_AMOUNT, VIBRATION_BIG_MAX, m_bigVibFlag, Vibration);

	}


	//最後の揺れのフラグが立ったら
	if (m_finalVibFlag == true)
	{

		//揺れの最大値を設定
		static int Vibration = VIBRATION_FINAL_MAX;


		//揺れの処理
		PlayVibration(FINALVIB_DECREASE_AMOUNT, VIBRATION_FINAL_MAX, m_finalVibFlag, Vibration);

	}

}

void GameCamera::PlayVibration(int decline,int maxVib, bool& flag,int& vibration)
{

		//振幅の設定
		int vib = vibration / 2;	


		//揺れを徐々に小さくする
		vibration -= decline;


		//揺れの大きさが0になったら
		if (vib == 0)
		{
			//揺れの為に必要な変数を初期化
			flag = false;
			BGX = 0; BGY = 0;
			vibration = maxVib;
		}
		else
		{
			//左右に揺れるために半分の値を引く
			int vibHalf = vib / 2;
			BGX = rand() % vib - vibHalf;
			BGY = rand() % vib - vibHalf;
		}

}

void GameCamera::SetQTE(Vector3 enemyPos)
{
	//ターゲットを敵に向けて
	m_target = enemyPos;

	//カメラまでの距離は半分にする
	m_toCameraPos *= 0.5f;

	//カメラステートはQTE用
	m_cameraState = CAMERA_STATE_QTE;

	//時を止める
	m_game->StopWorld();

	//ボタンを押せを表示
	m_game->SetPushButton();
}

void GameCamera::SetOffQTE()
{
	//時を進める
	m_game->ReStartWorld();

	//カメラのまでの距離を元に戻す
	m_toCameraPos *= 2.0f;

	//ステートを雑魚戦に戻す
	m_cameraState = CAMERA_STATE_ZAKO;
}