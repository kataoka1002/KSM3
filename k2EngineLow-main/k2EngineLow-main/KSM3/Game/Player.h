#pragma once

class Left_arm_weapons;
class Customize_UI_ver2;
class Result;
class Game;
class GameCamera;

class Player:public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();									//更新処理
	void Render(RenderContext& rc);					//描画処理
	void Move();									//移動処理
	void RunSE();									//ステート管理
	void pause();									//ポーズ画面
	void MakeEfe();									//エフェクト再生
	void MachineGunSE();
	void PlayerDead();

	Result* m_result = nullptr;
	Left_arm_weapons* p_left_arm_weapons = nullptr;
	Customize_UI_ver2* p_customize_ui_ver2 = nullptr;
	Game* m_game = nullptr;
	SoundSource* m_machineGunSE = nullptr;			//マシンガンSE
	SoundSource* m_runSE = nullptr;					//足音SE
	SoundSource* m_walkSE = nullptr;				//足音SE
	SoundSource* m_kettei = nullptr;
	SoundSource* m_deadSE = nullptr;
	GameCamera* m_gameCamera = nullptr;
	EffectEmitter* sunabokoriEffect = nullptr;
	EffectEmitter* m_deadEffect = nullptr;

	ModelRender player_modelRender;					//モデルレンダー
	SpriteRender pouse_spriteRender;				//pause画面用のスプライトレンダー
	SpriteRender m_playerDeadSprite;				//プレイヤーが死んだときのスプライトレンダー
	CharacterController characterController;		//キャラクターコントローラー
	Vector3 player_position = {0.0f,0.0f,-1000.0f};						//座標
	Vector3 player_moveSpeed;						//移動速度
	Vector3 playerForward = { 0.0f, 0.0f, 1.0f };	//プレイヤーの正面ベクトル
	Quaternion player_rotation;						//クォータニオン

	int m_deadCount = 0;
	int game_state = 4;								//ゲームがどの状態かの管理(0メインゲーム,1ポーズ画面,2リザルト,3カスタマイズ,4最初のシーン)
	int game_end_state = 0;							//ゲームの終了判定
	int bossState = 0;								//ボス戦かどうか
	int effectCount = 0;							//エフェクト関係
	int killEnemy = 0;								//敵を殺した数(10になるとウェーブが進む)
	int p_custom_point[2][3] = { {0,0,0},{0,0,0} };	//[0][0]右腕,[0][1]肩,[0][2]左腕,[1][0]右足,[1][2]左足
	float accelerator = 0;
	float brake = 0;
	float throttle = 0;
	float move_s;
	float m_playerHP = 500.0f;						//プレイヤーのHP
	float m_playerHPMax = 500.0f;					//プレイヤーのHPの最大値
	float m_deadSpriteColw = 0.0f;					//プレイヤー死亡時のスプライトの透明度
	bool attack_state_la = false;
	bool attack_state_ll = false;
	bool attack_state_rl = false;
	bool attack_state_ra = false;
	bool attack_state_s = false;
	bool m_cameraMove = false;						//カメラ切り替え中かどうか
	bool enemy_survival = true;
	bool boss_survival = true;
	bool m_playerDead = false;						//プレイヤーが死んだかどうか
	bool m_playDeadSE = false;						//死亡音を鳴らしたかどうか
};

