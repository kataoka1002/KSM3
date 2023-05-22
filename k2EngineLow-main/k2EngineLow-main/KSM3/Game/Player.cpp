#include "stdafx.h"
#include "Player.h"
#include <math.h>
#include "Left_arm_weapons.h"
#include "Customize_UI_ver2.h"
#include "Game.h"
#include "Result.h"
#include "GameCamera.h"
#include "Title.h"
#include "Boss.h"

Player::Player() 
{
	//プレイヤーのモデルとポーズ画面のスプライトの初期化
	player_modelRender.Init("Assets/modelData/player.tkm");
	pouse_spriteRender.Init("Assets/sprite/pouse.DDS", 1920.0f, 1080.0f);
	m_playerDeadSprite.Init("Assets/sprite/player/YOU_LOSE.DDS", 1280.0f, 720.0f);
	m_playerDeadSprite.SetScale({ 1.4f,1.4f,1.0f });
	m_playerDeadSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_deadSpriteColw });
	m_playerDeadSprite.Update();
	//キャラコンの初期化
	characterController.Init(70.0f, 150.0f, player_position);
}

Player::~Player()
{
	DeleteGO(m_machineGunSE);
	DeleteGO(m_runSE);
	DeleteGO(m_walkSE);
}

bool Player::Start()
{
	m_game = FindGO<Game>("game");
	m_gameCamera = FindGO<GameCamera>("gamecamera");

	//効果音の作成(流し続ける音源なのでインスタンスを保持させる)
	m_machineGunSE = NewGO<SoundSource>(0);
	m_runSE = NewGO<SoundSource>(0);
	m_walkSE = NewGO<SoundSource>(0);

	//効果音の設定
	m_machineGunSE->Init(enMachineGun);	//初期化
	m_machineGunSE->SetVolume(0.5f * m_game->SEvol);	//音量調整
	m_runSE->Init(enPlayerRun);	//初期化
	m_runSE->SetVolume(0.5f * m_game->SEvol);	//音量調整
	m_walkSE->Init(enRunning);	//初期化
	m_walkSE->SetVolume(0.5f * m_game->SEvol);	//音量調整

	return true;
}

void Player::Update() 
{
	//プレイヤーが死んでいてリザルト中でないときの処理
	if (m_playerDead == true && game_state != 2)
	{
		m_deadCount++;
		if (m_deadCount <= 60)
		{
			//だんだん透明度を上げていく
			m_deadSpriteColw += 1.0f / 60.0f;
		}
		else if (m_deadCount > 60 && m_deadCount<=65 && m_playDeadSE == false)
		{
			//死亡音再生
			m_deadSE = NewGO<SoundSource>(0);					//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
			m_deadSE->Init(enPlayerDead);						//初期化
			m_deadSE->SetVolume(2.0f * m_game->BGMvol);			//音量調整
			m_deadSE->Play(false);
			m_playDeadSE = true;
		}
		else if (m_deadCount >= 300)
		{
			//リザルトへ
			m_result = NewGO<Result>(1, "result");
			game_state = 2;			//リザルトステートへ
			//色付きに戻す
			g_renderingEngine->SetGrayScale(false);
			//セーブしていた効果音の大きさに戻してやる(この後にGameクラスをDeleteするので必要ないかも)
			//m_game->SEvol = m_game->SaveSEvol;
			//YOU LOSEの透明度を0に戻す
			m_deadSpriteColw = 0.0f;
			DeleteGO(m_game);
		}
		m_playerDeadSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_deadSpriteColw });
		m_playerDeadSprite.Update();
		return;
	}

	//登場シーンの間の処理
	if (game_state == 4)
	{
		//モデルのポジション更新
		player_modelRender.SetPosition(player_position);
		player_modelRender.Update(true);
		return;
	}

	if (game_state == 0) //メインゲーム
	{
		Move();			//移動処理
		MachineGunSE();	//マシンガンの効果音再生
		RunSE();		//足音の再生

		//スタートボタンを押すとポーズ画面に移動
		if (g_pad[0]->IsTrigger(enButtonStart)) 
		{
			game_state = 1;

			//メニュー画面移動SE
			m_kettei = NewGO<SoundSource>(0);					//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
			m_kettei->Init(enKetteiSE);							//初期化
			m_kettei->SetVolume(2.0f * m_game->SEvol);			//音量調整
			m_kettei->Play(false);
		}

		//モデルの更新
		player_modelRender.Update(true);
	}
	else if (game_state == 1) //ポーズ画面
	{
		pause();
	}
	else if (game_state == 2)
	{
		//リザルト中は攻撃音も出さない
		m_machineGunSE->Stop();
	}
	else if (game_state == 3)
	{
		//カスタマイズ中は攻撃音も出さない
		m_machineGunSE->Stop();
	}

	//HPが0以下になるなると死亡
	if (m_playerHP <= 0 && m_playerDead == false)
	{
		//死亡の演出
		g_renderingEngine->SetGrayScale(true);	//画面全体を灰色にする
		m_playerDead = true;

		//効果音を消す
		m_game->SEvol = 0.0f;
	}
}

void Player::Move()
{
	player_moveSpeed = { 0.0f,0.0f,0.0f };//移動速度の初期化

	Vector3 stickL;
	throttle = 0;
	stickL.x = g_pad[0]->GetLStickXF();
	//スティックを倒した量の取得
	throttle = g_pad[0]->GetRTrigger();

	Vector3 right = g_camera3D->GetRight();
	right.y = 0.0f;
	right *= stickL.x * 120.0f;

	//スピードが0じゃないならエフェクトを出す
	if (throttle != 0)
	{
		MakeEfe();	
	}
		
	playerForward.Normalize();

	//xかzの移動速度があったら(スティックの入力があったら)。
	//回転処理
	if (stickL.x!=0.0f)
	{
		playerForward.x = playerForward.x * cos(stickL.x * -0.05) - playerForward.z * sin(stickL.x * -0.05);
		playerForward.z = playerForward.x * sin(stickL.x * -0.05) + playerForward.z * cos(stickL.x * -0.05);

		player_rotation.SetRotationY(atan2(playerForward.x, playerForward.z));
	}
	//回転していないときの移動
	if (throttle != 0.0f) 
	{
		//だんだん速くする
		accelerator += 0.05;
		if (accelerator >= 2) 
		{
			accelerator = 2;	//最大値は2
		}
	}
	else 
	{
		//だんだん遅くする
		accelerator -= 0.05;
		if (accelerator <= 0) 
		{
			accelerator = 0;	//最小値は0
		}
	}

	move_s = 4.0f * accelerator;
	player_moveSpeed += playerForward  * move_s * (throttle / 2.0f);

	player_position = characterController.Execute(player_moveSpeed, 1.0f / 60.0f);

	//座標を教える。
	player_modelRender.SetPosition(player_position);
	player_modelRender.SetRotation(player_rotation);
}

void Player::MakeEfe()
{
	//プレイヤーのボタンを押している量によって砂ぼこりの量を変える
	if (throttle < 126.0f)
	{
		//動いている間20フレームごとに砂ぼこりを発生させる
		if (effectCount > 20)
		{
			//砂ぼこりエフェクトの初期化と再生
			sunabokoriEffect = NewGO<EffectEmitter>(0);
			sunabokoriEffect->Init(enSunabokori);
			sunabokoriEffect->SetScale({ 4.0f,4.0f,4.0f });
			sunabokoriEffect->SetRotation(player_rotation);
			sunabokoriEffect->SetPosition(player_position);
			sunabokoriEffect->Play();

			effectCount = 0;	//カウントリセット
		}
	}
	else if (throttle > 127.0f)
	{
		//動いている間3フレームごとに砂ぼこりを発生させる
		if (effectCount > 3)
		{
			//砂ぼこりエフェクトの初期化と再生
			sunabokoriEffect = NewGO<EffectEmitter>(0);
			sunabokoriEffect->Init(enSunabokori);
			sunabokoriEffect->SetScale({ 4.0f,4.0f,4.0f });
			sunabokoriEffect->SetRotation(player_rotation);
			sunabokoriEffect->SetPosition(player_position);
			sunabokoriEffect->Play();

			effectCount = 0;	//カウントリセット
		}
	}
	effectCount++;
}

void Player::pause() 
{
	if (g_pad[0]->IsTrigger(enButtonB)) 
	{
		game_state = 0;	//メインゲームに戻る

		//メニュー画面移動SE
		m_kettei = NewGO<SoundSource>(0);					//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
		m_kettei->Init(enCancelSE);							//初期化
		m_kettei->SetVolume(2.0f * m_game->SEvol);			//音量調整
		m_kettei->Play(false);

	}
	else if (g_pad[0]->IsTrigger(enButtonA)) 
	{
		game_end_state = 1;	//ゲーム終了

		DeleteGO(m_game);
		Title* title = NewGO<Title>(0, "title");
		DeleteGO(m_gameCamera);
		DeleteGO(this);

		//もしボス戦ならボスを消す
		if (bossState == 1)
		{
			Boss* m_boss = FindGO<Boss>("boss");
			DeleteGO(m_boss);
		}
	}
}

void Player::RunSE()
{
	if (throttle <= 0)	//動いてない時
	{
		//効果音停止
		m_walkSE->Stop();
		m_runSE->Stop();

		return;
	}

	if (throttle > 0 && throttle <= 127 && m_runSE->IsPlaying() != true)	//ゆっくり動いている時
	{
		//歩く音再生
		m_walkSE->Play(true);
	}
	else if (throttle > 127 && m_walkSE->IsPlaying() != true)	//速く動いている時
	{
		//走る音再生
		m_runSE->Play(true);
	}


	//走っているとき歩きの音は止める
	if (throttle > 127)
	{
		m_walkSE->Stop();
	}
	//歩いているとき走りの音は止める
	if (throttle > 0 && throttle <= 127)
	{
		m_runSE->Stop();
	}
}

void Player::MachineGunSE()
{
	if (g_pad[0]->IsPress(enButtonRB1) && m_machineGunSE->IsPlaying() != true)
	{
		m_machineGunSE->Play(true);	//続けて再生
	}
	else if(g_pad[0]->IsPress(enButtonRB1) == false)
	{
		m_machineGunSE->Stop();		//攻撃じゃないなら停止
	}
}

void Player::Render(RenderContext& rc)
{
	player_modelRender.Draw(rc);

	//ポーズ中ならポーズ画面を表示
	if (game_state == 1)
	{
		pouse_spriteRender.Draw(rc);
	}
	m_playerDeadSprite.Draw(rc);
}