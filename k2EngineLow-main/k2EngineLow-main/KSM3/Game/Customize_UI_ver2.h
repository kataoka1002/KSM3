#pragma once
#include"Game.h"

class Player;
class Drop_item;
class Left_arm_weapons;
class Right_arm_weapons;
class Customize_area;
class GameCamera;
class Core_weapons;
class Drop_item;
class Shoulder_weapons;
class Right_leg_weapons;
class Left_leg_weapons;

class Customize_UI_ver2 :public IGameObject
{
public:
	Customize_UI_ver2();
	~Customize_UI_ver2();
	bool Start();
	void Update();
	void Setup();
	void Render(RenderContext& rc);
	void Custom_model_body();
	void Custom_model_Left_arm();
	void Custom_model_Right_arm();
	void Custom_model_Left_leg();
	void Custom_model_Right_leg();
	void Custom_model_Shoulder();
	void Custom_model_Core();
	void Custom_UI();
	void Window();
	void trance_setup();
	void trance();
	void tranceOut();
	void tranceOutInit();

	void init_parameter(int Drop,int line,int row);
	void InitParameter(IntPair point, int itemNum);

	void PlaySE(SoundName name,float vol);


	Game* m_game = nullptr;
	GameCamera* m_gameCamera = nullptr;
	Core_weapons* m_coreWeapon = nullptr;
	Drop_item* m_dropItem = nullptr;
	Right_arm_weapons* m_rightArmWeapon = nullptr;
	Left_arm_weapons* m_leftArmWeapon = nullptr;
	Shoulder_weapons* m_shoulderWeapon = nullptr;
	Right_leg_weapons* m_rightLegWeapon = nullptr;
	Left_leg_weapons* m_leftLegWeapon = nullptr;
	//SoundSource* m_sentakuIdouSE = nullptr;			//戦艦砲SE


	SpriteRender m_selectSheet;
	Vector3 m_selectSheetPosition={0.0f,650.0f,0.0f};//350
	SpriteRender m_parameterSheet;
	Vector3 m_parameterSheetPosition ={ -1200.0f,38.0f,0.0f };//-500


	SpriteRender m_confirmationWindow;

	Player* m_player = nullptr;
	Customize_area* m_customizeArea = nullptr;
	
	std::unique_ptr<ModelRender> custom_model_body;
	std::unique_ptr<ModelRender> custom_model_Core;
	std::unique_ptr<ModelRender> custom_model_shoulder;
	std::unique_ptr<ModelRender> custom_model_shoulder2;	//肩のマシンガン用のモデル
	std::unique_ptr<ModelRender> custom_model_Right_arm;
	std::unique_ptr<ModelRender> custom_model_Right_leg;
	std::unique_ptr<ModelRender> custom_model_Left_arm;
	std::unique_ptr<ModelRender> custom_model_Left_leg;

	Quaternion custom_model_body_rotation;
	Vector3 custom_model_body_position = { 10500.0f,0.0f,0.0f };//10000

	int custom_point[2][3] = { {0,0,0},
							   {0,0,0} };
	int custom_kinds = 0;
	int selection_position=0;
	int fast_count=0;
	int window_count = 0;
	Vector3 cw_lp;//コア装備のローカルポジション
	Vector3 raw_lp;//右腕装備のローカルポジション
	Vector3 law_lp;//左腕装備のローカルポジション
	Vector3 sw_lp;//肩装備のローカルポジション
	Vector3 sw2_lp;//マシンガンのローカルポジション
	Vector3 rlw_lp;//右足装備のローカルポジション
	Vector3 llw_lp;//左足装備のローカルポジション

	bool Right_arm_weapon_set = false;//右手の装備がセットされているか
	bool Left_arm_weapon_set = false;//左手の装備がセットされているか
	bool Shoulder_weapon_set = false;//肩の装備がセットされているか
	bool Right_leg_weapon_set = false;//右足の装備がセットされているか
	bool Left_leg_weapon_set = false;//左足の装備がセットされているか

	Vector3 scale2 = { 2.0f, 2.0f, 2.0f };//2倍のscale
	bool window_open=false;//ウィンドウがオープンするか
	bool confirmatino_window_open = false;//確認ウィンドウの表示確認
	bool window_select = false;//ウィンドウの選択肢のどっちが選択されているか
	int column = 0, line=0;

	int trance_state = 1;//遷移のステート 0 :遷移終了 1:遷移中 2: 3:カスタムからゲームの遷移中

	SpriteRender trance_sheet[4];//遷移時の黒隠し 1,2:下 3,4:上

	Vector3 trance_sheet01_position = { 2880.0f,-530.0f,0.0f };
	Vector3 trance_sheet02_position = { 2880.0f,-530.0f,0.0f };
	Vector3 trance_sheet03_position = { -2880.0f,530.0f,0.0f };
	Vector3 trance_sheet04_position = { -2880.0f,530.0f,0.0f };

	int trance_sheet_count=0;//遷移カウント
	Vector4 trance_sheet_color={ 0.0f,0.0f,0.0f,1.0f };

	bool recovery = false;
	//float trance_sheet_α = 1;//アルファ値
};

