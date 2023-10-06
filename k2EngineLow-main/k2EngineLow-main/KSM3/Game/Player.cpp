#include "stdafx.h"
#include <math.h>
#include <map>
#include <random>
#include "Player.h"
#include "Customize_UI_ver2.h"
#include "Game.h"
#include "Result.h"
#include "GameCamera.h"
#include "Title.h"
#include "Boss.h"
#include "Player_Macro.h"
#include "Title.h"



Player::Player() 
{

	//タイトルを見つける
	m_title = FindGO<Title>("title");


}



Player::~Player()
{

	//削除
	DeleteGO(m_machineGunSE);
	DeleteGO(m_runSE);
	DeleteGO(m_walkSE);
	DeleteGO(m_game);
	DeleteGO(m_gameCamera);


	//もしボス戦なら
	if (m_bossState == 1)
	{
		
		//ボスを探す
		Boss* m_boss = FindGO<Boss>("boss");
		

		//ボスを消す
		DeleteGO(m_boss);

	}

}



bool Player::Start()
{

	//モデルの初期化
	InitModel();


	//ゲームとゲームカメラを見つける
	m_game = FindGO<Game>("game");
	m_gameCamera = FindGO<GameCamera>("gamecamera");


	//スプライトの初期化
	InitSprite();


	//SEの初期化
	InitSE();


	return true;

}



void Player::Update() 
{
	//世界が止まっているなら
	if (m_game->IsStopWorld() != false)
	{
		//マシンガン発射音を停止
		m_machineGunSE->Stop();
		return;
	}

	//プレイヤーが死んでいてリザルト中でないとき
	if (m_playerDead == true && m_gameState != RESULT_NUM)
	{

		//死んでからリザルトまでの処理
		PlayerDeadtoResult();

		return;
	}


	//登場シーンの間
	if (m_gameState == OP_NUM)
	{

		//モデルのポジション更新
		m_playerModel->SetPosition(m_playerPosition);
		m_playerModel->Update(true);

		return;
	}


	//メインゲームのとき
	if (m_gameState == MAIN_GAME_NUM) 
	{

		//移動処理
		Move();	


		//マシンガンの効果音再生			
		MachineGunSE();


		//足音の再生
		RunSE();		


		//ポーズ画面を選択する処理
		PauseSelect();	

	}
	else if (m_gameState == PAUSE_NUM) 
	{

		//ポーズ画面
		pause();

	}
	else if (m_gameState == RESULT_NUM)
	{

		//リザルト中は攻撃音も出さない
		m_machineGunSE->Stop();

	}
	else if (m_gameState == CUSTOMIZE_NUM)
	{

		//カスタマイズ中は攻撃音も出さない
		m_machineGunSE->Stop();

	}


	//プレイヤーが死んだときの処理
	PlayerDead();	

}



void  Player::InitSprite()
{

	//ポーズ画面のスプライトの初期化
	m_pouseSprite.Init("Assets/sprite/pouse.DDS", 1920.0f, 1080.0f);


	//プレイヤーが死んだときのスプライトの初期化
	m_playerDeadSprite.Init("Assets/sprite/player/YOU_LOSE.DDS", 1280.0f, 720.0f);
	m_playerDeadSprite.SetScale({ 1.4f,1.4f,1.0f });
	m_playerDeadSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_deadSpriteColw });
	m_playerDeadSprite.Update();

}



void  Player::InitModel()
{

	//メモリの確保
	m_playerModel = std::make_unique<ModelRender>();


	//カラー選択がランダムの場合
	if (m_playerColorData == 6)
	{

		//プレイヤーモデルをランダムカラーで初期化
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(0, 7);
		m_playerColorRandom = dis(gen);
		m_playerModel->Init(getPlayer_color(m_playerColorRandom));

	}
	else 
	{

		//プレイヤーモデルを指定されたカラーで初期化
		m_playerModel->Init(getPlayer_color(m_playerColorData));
		//レインボーが選ばれたらUVスクロールを起こす
		if (m_playerColorData == 5)
		{
			m_playerModel->PlayUVScroll();
		}


		//変数にタイトルで指定されたカラーを覚えさせておく
		m_playerColorRandom = m_playerColorData;

	}


	//キャラコンの初期化
	m_characterController.Init(70.0f, 150.0f, m_playerPosition);

}



void  Player::InitSE()
{

	//効果音の作成(流し続ける音源なのでインスタンスを保持させる)

	m_machineGunSE = NewGO<SoundSource>(0);
	m_machineGunSE->Init(enMachineGun);					//初期化
	m_machineGunSE->SetVolume(0.5f * m_game->GetSEVol());	//音量調整


	m_runSE = NewGO<SoundSource>(0);
	m_runSE->Init(enPlayerRun);							//初期化
	m_runSE->SetVolume(0.5f * m_game->GetSEVol());			//音量調整


	m_walkSE = NewGO<SoundSource>(0);
	m_walkSE->Init(enRunning);							//初期化
	m_walkSE->SetVolume(0.5f * m_game->GetSEVol());			//音量調整

}



void Player::PlayerDeadtoResult()
{

	//カウントアップ
	m_deadCount++;


	//カウントによって処理を変更する
	if (m_deadCount <= 60)
	{

		//だんだん透明度を上げていく
		m_deadSpriteColw += 1.0f / 60.0f;

	}
	else if (m_deadCount > 60 && m_deadCount <= 65 && m_playDeadSE == false)
	{

		//死亡音再生
		m_deadSE = NewGO<SoundSource>(0);					//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
		m_deadSE->Init(enPlayerDead);						//初期化
		m_deadSE->SetVolume(2.0f * m_game->GetBGMVol());			//音量調整
		m_deadSE->Play(false);


		//死亡時のSEを流したフラグを立てる
		m_playDeadSE = true;

	}
	else if (m_deadCount > 150 && m_deadBakuhaPlay == false)
	{

		//エフェクト発生
		MakeEfe(enFeatherBall, m_playerRotation, { 20.0f,20.0f,20.0f }, m_playerPosition);
		MakeEfe(enTyakudan, m_playerRotation, { 20.0f,20.0f,20.0f }, m_playerPosition);


		//死亡時のエフェクトを流したフラグを立てる
		m_deadBakuhaPlay = true;

	}
	else if (m_deadCount >= 300)
	{

		//リザルトの作成
		m_result = NewGO<Result>(1, "result");


		//リザルトステートへ
		m_gameState = RESULT_NUM;			


		//色付きに戻す
		g_renderingEngine->SetGrayScale(false);


		//セーブしていた効果音の大きさに戻す
		m_game->SetSEVol(m_game->GetSaveSEvol());


		//リザルトにそのデータを送る
		m_result->SetVolume(m_game->GetBGMVol(), m_game->GetSEVol());


		//YOU LOSEの透明度を0に戻す
		m_deadSpriteColw = 0.0f;


		//ゲームクラスの削除
		DeleteGO(m_game);

	}


	//スプライトの更新
	m_playerDeadSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_deadSpriteColw });
	m_playerDeadSprite.Update();
}



void Player::Move()
{

	//移動速度の初期化
	m_playerMoveSpeed = { 0.0f,0.0f,0.0f };


	//スティックを倒した量の取得
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();


	//アクセルボタンの入力量の取得
	m_throttle = 0.0f;

	//Rボタン
	m_throttle = g_pad[0]->GetRTrigger();

	//Lボタン
	if (m_throttle == 0.0f)
	{
		m_throttle = g_pad[0]->GetLTrigger();
	}


	//カメラの右向きを取得
	Vector3 right = g_camera3D->GetRight();
	right.y = 0.0f;
	right *= stickL.x * 120.0f;


	//スピードが0じゃないなら
	if (m_throttle != 0)
	{
		
		//エフェクトを出す
		MakeSunabokoriEfe();

	}


	//プレイヤーの正面ベクトルを正規化
	m_playerForward.Normalize();


	//xかzの移動速度があったら(スティックの入力があったら)。
	//回転処理
	if (stickL.x != 0.0f)
	{

		m_playerForward.x = m_playerForward.x * cos(stickL.x * -0.05) - m_playerForward.z * sin(stickL.x * -0.05);
		m_playerForward.z = m_playerForward.x * sin(stickL.x * -0.05) + m_playerForward.z * cos(stickL.x * -0.05);

		m_playerRotation.SetRotationY(atan2(m_playerForward.x, m_playerForward.z));

	}


	//回転していないときの移動
	if (m_throttle != 0.0f)
	{

		//だんだん速くする
		m_accelerator += 0.05;


		//最大値は2
		if (m_accelerator >= 2)
		{
			m_accelerator = 2;
		}

	}
	else
	{

		//だんだん遅くする
		m_accelerator -= 0.05;


		//最小値は0
		if (m_accelerator <= 0)
		{
			m_accelerator = 0;
		}

	}


	m_move = 4.0f * m_accelerator;
	m_playerMoveSpeed += m_playerForward * m_move * (m_throttle / 2.0f);


	//座標を教える。
	m_playerPosition = m_characterController.Execute(m_playerMoveSpeed, 1.0f / 60.0f);
	m_characterController.SetPosition({ m_playerPosition.x ,0.0f,m_playerPosition.z });


	//プレイヤーのY座標は固定
	m_playerPosition.y = 0.0f;


	//モデルの更新
	m_playerModel->SetPosition(m_playerPosition);
	m_playerModel->SetRotation(m_playerRotation);
	m_playerModel->Update(true);

}



//死亡の演出
void Player::PlayerDead()
{

	//HPが0以下になるなると死亡
	if (m_playerHP <= 0 && m_playerDead == false)
	{

		//画面全体を灰色にする
		g_renderingEngine->SetGrayScale(true);	


		//プレイヤーは死んだ
		m_playerDead = true;					


		//効果音を消す
		m_game->SetSEVol(0.0f);


		//エフェクト発生
		MakeEfe(enSword, m_playerRotation, { 13.0f,13.0f,13.0f }, m_playerPosition);

	}

}



void Player::MakeSunabokoriEfe()
{

	//プレイヤーのボタンを押している量によって砂ぼこりの量を変える
	if (m_throttle < 126.0f)
	{

		//動いている間20フレームごとに砂ぼこりを発生させる
		if (m_effectCount > 20)
		{

			//砂ぼこりエフェクトの初期化と再生
			MakeEfe(enSunabokori, m_playerRotation, { 4.0f,4.0f,4.0f }, m_playerPosition);

			
			//カウントリセット
			m_effectCount = 0;	

		}

	}
	else if (m_throttle > 127.0f)
	{

		//動いている間3フレームごとに砂ぼこりを発生させる
		if (m_effectCount > 3)
		{

			//砂ぼこりエフェクトの初期化と再生
			MakeEfe(enSunabokori, m_playerRotation, { 4.0f,4.0f,4.0f }, m_playerPosition);


			//カウントリセット
			m_effectCount = 0;	

		}

	}


	//カウントアップ
	m_effectCount++;

}



void Player::PauseSelect()
{

	//スタートボタンを押すとポーズ画面に移動
	if (g_pad[0]->IsTrigger(enButtonStart))
	{

		//ポーズ画面へ
		m_gameState = PAUSE_NUM;


		//メニュー画面移動SE
		m_kettei = NewGO<SoundSource>(0);					//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
		m_kettei->Init(enKetteiSE);							//初期化
		m_kettei->SetVolume(2.0f * m_game->GetSEVol());			//音量調整
		m_kettei->Play(false);

	}

}



void Player::pause() 
{

	if (g_pad[0]->IsTrigger(enButtonB)) 
	{

		//メインゲームに戻る
		m_gameState = MAIN_GAME_NUM;	


		//メニュー画面移動SE
		m_kettei = NewGO<SoundSource>(0);					//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
		m_kettei->Init(enCancelSE);							//初期化
		m_kettei->SetVolume(2.0f * m_game->GetSEVol());			//音量調整
		m_kettei->Play(false);

	}
	else if (g_pad[0]->IsTrigger(enButtonA)) 
	{

		//ゲーム終了
		m_gameEndState = 1;	


		//自分自身の削除
		DeleteGO(this);


		//タイトルの生成
		Title* title = NewGO<Title>(0, "title");

	}

}



void Player::RunSE()
{
	
	//動いてない時
	if (m_throttle <= 0)	
	{

		//効果音停止
		m_walkSE->Stop();
		m_runSE->Stop();

		return;
	}


	//ゆっくり動いている時
	if (m_throttle > 0 && m_throttle <= 127 && m_runSE->IsPlaying() != true)	
	{

		//歩く音再生
		m_walkSE->Play(true);

	}
	//速く動いている時
	else if (m_throttle > 127 && m_walkSE->IsPlaying() != true)	
	{

		//走る音再生
		m_runSE->Play(true);

	}


	//走っているとき
	if (m_throttle > 127)
	{
		
		//歩きの音は止める
		m_walkSE->Stop();

	}


	//歩いているとき
	if (m_throttle > 0 && m_throttle <= 127)
	{
		
		//走りの音は止める
		m_runSE->Stop();

	}

}



void Player::MachineGunSE()
{

	//ボタンを押している間
	if (g_pad[0]->IsPress(enButtonLB1) && m_machineGunSE->IsPlaying() != true && m_playerDead != true)
	{

		//マシンガン発射音を続けて再生
		m_machineGunSE->Play(true);	

	}
	//ボタンを離したら
	else if(g_pad[0]->IsPress(enButtonLB1) == false)
	{

		//マシンガン発射音を停止
		m_machineGunSE->Stop();		

	}


	//プレイヤーが死んだら
	if (m_playerDead == true)
	{

		//マシンガン発射音を停止
		m_machineGunSE->Stop();

	}

}



void  Player::MakeEfe(EffectName name, Quaternion rot, Vector3 scale, Vector3 pos)
{

	//エフェクト発生
	EffectEmitter* efe = NewGO<EffectEmitter>(0);
	efe->Init(name);
	efe->SetScale(scale);
	efe->SetRotation(rot);
	efe->SetPosition(pos);
	efe->Play();

}



void Player::Render(RenderContext& rc)
{

	//プレイヤーが死亡して爆破した演出があったら
	if (m_deadBakuhaPlay == true)
	{

		//ここで処理を止める
		return;

	}


	//プレイヤーモデル表示
	m_playerModel->Draw(rc);


	//ポーズ中なら
	if (m_gameState == PAUSE_NUM)
	{

		//ポーズ画面を表示
		m_pouseSprite.Draw(rc);

	}


	//YOU LOSEのスプライト表示
	m_playerDeadSprite.Draw(rc);
}