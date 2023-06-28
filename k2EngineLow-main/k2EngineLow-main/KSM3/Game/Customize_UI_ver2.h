#pragma once
#include"Game.h"

class Player;
class Drop_item;
class Left_arm_weapons;
class Right_arm_weapons;
class GameCamera;
class Core_weapons;
class Drop_item;
class Shoulder_weapons;
class Right_leg_weapons;
class Left_leg_weapons;

class Customize_UI_ver2 :public IGameObject , Noncopyable
{
public:
	Customize_UI_ver2();
	~Customize_UI_ver2();
	bool Start();
	void Update();
	void SetUp();
	void Render(RenderContext& rc);
	void ExecuteModel();
	void ExecuteBody();
	void ExecuteCore();
	void ExecuteCustom();
	void ExecuteConformatinoWindow();
	void TranceSetUp();
	void TranceIn();
	void TranceOut();
	void InitTrance();
	void InitTranceSheet();
	void InitTranceOut();
	void CheckEquipment(IntPair parts);
	void InitConfirmationWindow(bool isApproval);
	void ExecuteAButtonActionOnCustom();
	void ExecuteAccept();
	void ExecuteReject();
	void PlaySE(SoundName name, float vol);

	/// <summary>
	/// //どこを選択しているかのスプライト設定
	/// </summary>
	/// <param name="selectPosition">今どこを選択しているか</param>
	void InitSelectSheet(int selectPosition);


	template <class T>
	/// <summary>
	/// 武器モデルの処理を行う
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="parts">取り付ける部位のポインタ</param>
	/// <param name="isWeaponSet">武器をセットしているかどうかを表す変数</param>
	/// <param name="model">武器モデル</param>
	/// <param name="siteNum">部位のナンバー</param>
	/// <param name="isShoulder2">マシンガンの2個目かどうか(初期値：false)</param>
	void ExecuteBodyParts(T* parts, bool& isWeaponSet, std::unique_ptr<ModelRender>& model, int siteNum, bool isShoulder2 = false);

	/// <summary>
	/// 武器をプレイヤーに追尾させる計算
	/// </summary>
	/// <param name="localPos">武器のローカルポジション</param>
	/// <param name="model">武器のモデル</param>
	void CalcWeaponTracking(Vector3 localPos, std::unique_ptr<ModelRender>& model);

	/// <summary>
	/// パラメーターシートの設定
	/// </summary>
	/// <param name="point">部位</param>
	/// <param name="cursor">0 : 拾い物 , 1 : 各部位</param>
	void InitParameter(IntPair point, int cursor);


	//getter----------------------------------------------------------------

	Right_arm_weapons* GetRightArmWeapon()
	{
		return m_rightArmWeapon;
	}

	Left_arm_weapons* GetLeftArmWeapon()
	{
		return m_leftArmWeapon;
	}

	Shoulder_weapons* GetShoulderWeapon()
	{
		return m_shoulderWeapon;
	}

	Right_leg_weapons* GetRightLegWeapon()
	{
		return m_rightLegWeapon;
	}

	Left_leg_weapons* GetLeftLegWeapon()
	{
		return m_leftLegWeapon;
	}

	/// <summary>
	/// 右腕に武器を装着しているかどうかを設定
	/// </summary>
	/// <param name="flag">true : 装備あり　false : 装備なし</param>
	void SetIsSetRightArm(bool flag)
	{
		m_rightArmSet = flag;
	}

	/// <summary>
	/// 左腕に武器を装着しているかどうかを設定
	/// </summary>
	/// <param name="flag">true : 装備あり　false : 装備なし</param>
	void SetIsSetLeftArm(bool flag)
	{
		m_leftArmSet = flag;
	}

	/// <summary>
	/// 右足に武器を装着しているかどうかを設定
	/// </summary>
	/// <param name="flag">true : 装備あり　false : 装備なし</param>
	void SetIsSetRightLeg(bool flag)
	{
		m_rightLegSet = flag;
	}

	/// <summary>
	/// 左足に武器を装着しているかどうかを設定
	/// </summary>
	/// <param name="flag">true : 装備あり　false : 装備なし</param>
	void SetIsSetLeftLeg(bool flag)
	{
		m_leftLegSet = flag;
	}

	/// <summary>
	/// 肩に武器を装着しているかどうかを設定
	/// </summary>
	/// <param name="flag">true : 装備あり　false : 装備なし</param>
	void SetIsSetShoulder(bool flag)
	{
		m_shoulderSet = flag;
	}

	/// <summary>
	/// 武器にポインタをセットする
	/// </summary>
	/// <param name="pointa">ポインタ</param>
	void SetRightArmWeapon(Right_arm_weapons* pointa)
	{
		m_rightArmWeapon = pointa;
	}

	/// <summary>
	/// 武器にポインタをセットする
	/// </summary>
	/// <param name="pointa">ポインタ</param>
	void SetLeftArmWeapon(Left_arm_weapons* pointa)
	{
		m_leftArmWeapon = pointa;
	}

	/// <summary>
	/// 武器にポインタをセットする
	/// </summary>
	/// <param name="pointa">ポインタ</param>
	void SetRightLegWeapon(Right_leg_weapons* pointa)
	{
		m_rightLegWeapon = pointa;
	}

	/// <summary>
	/// 武器にポインタをセットする
	/// </summary>
	/// <param name="pointa">ポインタ</param>
	void SetLeftlegWeapon(Left_leg_weapons* pointa)
	{
		m_leftLegWeapon = pointa;
	}

	/// <summary>
	/// 武器にポインタをセットする
	/// </summary>
	/// <param name="pointa">ポインタ</param>
	void SetShoulderWeapon(Shoulder_weapons* pointa)
	{
		m_shoulderWeapon = pointa;
	}

	/// <summary>
	/// 拾った武器の種類を設定する
	/// </summary>
	/// <param name="dropItem">拾った武器の種類</param>
	void SetDropItem(int dropItem)
	{
		m_customKinds = dropItem;
	}

private:
	Game* m_game = nullptr;
	GameCamera* m_gameCamera = nullptr;
	Core_weapons* m_coreWeapon = nullptr;
	Drop_item* m_dropItem = nullptr;
	Right_arm_weapons* m_rightArmWeapon = nullptr;
	Left_arm_weapons* m_leftArmWeapon = nullptr;
	Shoulder_weapons* m_shoulderWeapon = nullptr;
	Right_leg_weapons* m_rightLegWeapon = nullptr;
	Left_leg_weapons* m_leftLegWeapon = nullptr;
	Player* m_player = nullptr;

	std::unique_ptr<ModelRender> m_bodyModel;
	std::unique_ptr<ModelRender> m_coreModel;
	std::unique_ptr<ModelRender> m_shoulderModel;
	std::unique_ptr<ModelRender> m_shoulderModel2;	//肩のマシンガン用のモデル
	std::unique_ptr<ModelRender> m_rightArmModel;
	std::unique_ptr<ModelRender> m_rightLegModel;
	std::unique_ptr<ModelRender> m_leftArmModel;
	std::unique_ptr<ModelRender> m_leftLegModel;

	SpriteRender m_selectSheet;
	SpriteRender m_parameterSheet;
	SpriteRender m_confirmationWindow;
	SpriteRender m_tranceSheet[4];//遷移時の黒隠し 1,2:下 3,4:上
	Quaternion m_customModelRotation;
	Vector3 m_selectSheetPosition = { 0.0f,650.0f,0.0f };
	Vector3 m_parameterSheetPosition = { -1200.0f,38.0f,0.0f };
	Vector3 m_customModelPosition = { 10500.0f,0.0f,0.0f };
	Vector3 m_coreLocalPosition;//コア装備のローカルポジション
	Vector3 m_tranceSheetPosition01 = { 2880.0f,-530.0f,0.0f };
	Vector3 m_tranceSheetPosition02 = { 2880.0f,-530.0f,0.0f };
	Vector3 m_tranceSheetPosition03 = { -2880.0f,530.0f,0.0f };
	Vector3 m_tranceSheetPosition04 = { -2880.0f,530.0f,0.0f };
	Vector4 m_tranceSheetColor = { 0.0f,0.0f,0.0f,1.0f };

	IntPair m_customParts = NON;

	int m_customKinds = 0;
	int m_selectPosition = 0;
	int m_tranceState = 1;						//遷移のステート 0 :遷移終了 1:遷移中 2: 3:カスタムからゲームの遷移中
	int m_tranceSheetCount = 0;					//遷移カウント

	bool m_rightArmSet = false;					//右手の装備がセットされているか
	bool m_leftArmSet = false;					//左手の装備がセットされているか
	bool m_shoulderSet = false;					//肩の装備がセットされているか
	bool m_rightLegSet = false;					//右足の装備がセットされているか
	bool m_leftLegSet = false;					//左足の装備がセットされているか
	bool m_isConformatinoWindowOpen = false;	//確認ウィンドウの表示確認
	bool m_selectedWindow = false;				//ウィンドウの選択肢のどっちが選択されているか
	bool m_isRecovery = false;
	bool m_canGoToConformation = false;
};

