#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "Lighting.h"
#include "SoundManage.h"


Title::Title()
{
	m_lighting = NewGO<Lighting>(1, "lighting");

	g_soundEngine->ResistWaveFileBank(17, "Assets/audio/ketteion.wav");
	g_soundEngine->ResistWaveFileBank(18, "Assets/audio/cancelon.wav");
	g_soundEngine->ResistWaveFileBank(19, "Assets/audio/sentakuidouon.wav");
	g_soundEngine->ResistWaveFileBank(20, "Assets/audio/Title_PRESS.wav");
}

Title::~Title()
{
	DeleteGO(m_lighting);
}
void Title::PlaySE(int track_number, float vol)
{
	SoundSource* m_SE = NewGO<SoundSource>(0);			//一回再生すると終わりなのでインスタンスを保持させない為にここでNewGOする
	m_SE->Init(track_number);									//初期化
	m_SE->SetVolume(vol * m_BGMVolume);				//音量調整
	m_SE->Play(false);
}
bool Title::Start() {
	SetUp();
	return true;
}
void Title::SetUp()
{
	//モデルの読み込み
	m_battleshipgunModel.Init("Assets/modelData/battleship_gun_Drop.tkm");
	m_battleshipgunModel.SetScale(m_modelScale);
	m_machinegunModel.Init("Assets/modelData/machine_gun_drop.tkm");
	m_machinegunModel.SetScale(m_modelScale);
	m_gigaplasmaModel.Init("Assets/modelData/Giga_Plasma.tkm");
	m_gigaplasmaModel.SetScale(m_modelScale);

	m_backGroundModel.Init("Assets/modelData/title_back.tkm");
	
	//画像の読み込み
	m_mainMenuSprite.Init("Assets/sprite/MAIN_MENU.DDS", 1632.0f, 918.0f);
	m_titleSprite.Init("Assets/sprite/title.DDS", 1632.0f, 918.0f);
	m_pressSprite.Init("Assets/sprite/Press_any_button.DDS", 1632.0f, 918.0f);
	m_whiteOutSprite.Init("Assets/sprite/whiteout.DDS", 1632.0f, 918.0f);
	m_whiteOutSprite.SetMulColor(Vector4{ 1.0f,1.0f,1.0f,0.0f });
	m_whiteOutSprite.Update();
	m_sideLineSprite.Init("Assets/sprite/side_line.DDS", 1632.0f, 918.0f);
	m_backOKSprite.Init("Assets/sprite/OK_BACK.DDS", 1632.0f, 918.0f);
	m_mainMenuBaseSprite.Init("Assets/sprite/brack_back.DDS", 1632.0f, 918.0f);
	m_selectPointSprite.Init("Assets/sprite/select_point.DDS", 1632.0f, 918.0f);
	m_selectPointPowSprite.Init("Assets/sprite/select_point_pow.DDS", 1632.0f, 918.0f);
	m_loadingSprite.Init("Assets/sprite/NOW_LOADING.DDS", 1632.0f, 918.0f);

	m_optionSprite.Init("Assets/sprite/OPTION.DDS", 1632.0f, 918.0f);
	m_soundSprite.Init("Assets/sprite/SOUND.DDS", 1632.0f, 918.0f);
	m_soundSprite2.Init("Assets/sprite/SOUND2.DDS", 1632.0f, 918.0f);
	m_soundSpriet3.Init("Assets/sprite/SOUND3.DDS", 1632.0f, 918.0f);
	m_BGMSoundBerSprite.Init("Assets/sprite/gage.DDS", 400.0f, 50.0f);
	m_BGMSoundBerSprite.SetPivot(m_BGMBerPivot);
	m_BGMSoundBerSprite.SetPosition(m_BGMBerPosition);
	m_SESoundBerSprite.Init("Assets/sprite/gage.DDS", 400.0f, 50.0f);
	m_SESoundBerSprite.SetPivot(m_SEBerPivot);
	m_SESoundBerSprite.SetPosition(m_SEBerPosition);

	m_controlesSprite.Init("Assets/sprite/CONTROLES.DDS", 1632.0f, 918.0f);
	m_playerColorSprite.Init("Assets/sprite/Player_color.DDS", 1632.0f, 918.0f);

	m_menuTranceSprite[0].Init("Assets/sprite/MENU_TITLE_TRANCE.DDS", 430.0f, 100.0f);
	for (int i = 1; i < 9; i++) {
		m_menuTranceSprite[i].Init("Assets/sprite/MENU_contents_TRANCE.DDS", 670.0f, 63.0f);
	}

	m_menuTranceSprite[0].SetPosition(m_menuTranceTitlePos);
	m_menuTranceSprite[1].SetPosition(m_menuTrancePos1);
	m_menuTranceSprite[2].SetPosition(m_menuTrancePos2);
	m_menuTranceSprite[3].SetPosition(m_menuTrancePos3);
	m_menuTranceSprite[4].SetPosition(m_menuTrancePos4);
	m_menuTranceSprite[5].SetPosition(m_menuTrancePos5);
	m_menuTranceSprite[6].SetPosition(m_menuTrancePos6);
	m_menuTranceSprite[7].SetPosition(m_menuTrancePos7);
	m_menuTranceSprite[8].SetPosition(m_menuTranceOKBackPos);


	for (int i = 0; i < 9;i++ ) {
		m_menuTranceSprite[i].SetPivot(m_menuTrancePivot);
		m_menuTranceSprite[i].SetScale(m_tranceSheetScale);
		m_menuTranceSprite[i].Update();
	}
	m_BGMSoundBerSprite.Update();
	m_SESoundBerSprite.Update();
	m_loadingSprite.SetMulColor(m_loadingSpriteColor);
	m_loadingSprite.Update();

}

void Title::Update()
{
	if (m_titleState == 0|| m_titleState == 1) {
		TitleMove();
	}
	if (m_titleState >= 2) {
		Menu();
	}

	if (m_titlePattern == 0)//迫ってくるbattをその場で眼だけで追う。
	{
		m_modelPosition.x += 0.6f;
		m_battleshipgunModel.SetPosition(m_modelPosition);

		m_modelRotarionY.SetRotationDegY(120.0f);
		m_modelRotarionX.SetRotationDegX(-25.0f);
		m_rotation = m_modelRotarionX * m_modelRotarionY;
		m_battleshipgunModel.SetRotation(m_rotation);

		m_targetPosition = m_modelPosition;
		m_targetPosition.x += 50.0f;
		g_camera3D->SetTarget(m_targetPosition);
		m_cameraPosition = { 0.0f,-50.0f,-00.0f };
		g_camera3D->SetPosition(m_cameraPosition);
	}
	else if (m_titlePattern == 1)//上前からmacを後ろまで追っていく感じ。
	{
		m_machinegunModel.SetPosition(m_modelPosition);

		m_modelRotarionY.SetRotationDegY(100.0f);
		m_machinegunModel.SetRotation(m_modelRotarionY);

		m_cameraPosition.x -= 1.2f;
		m_targetPosition.x -= 1.20f;
		g_camera3D->SetTarget(m_targetPosition);
		g_camera3D->SetPosition(m_cameraPosition);
	}
	else if (m_titlePattern == 2)//ローアングルからgigaを見上げる感じで。
	{
		m_modelPosition.z -= 0.5f;
		m_gigaplasmaModel.SetPosition(m_modelPosition);

		m_modelRotarionY.SetRotationDegY(180.0f);
		m_modelRotarionX.SetRotationDegX(-15.0f);
		m_rotation = m_modelRotarionX * m_modelRotarionY;
		m_gigaplasmaModel.SetRotation(m_rotation);

		g_camera3D->SetTarget(m_modelPosition);
		m_cameraPosition = { 0.0f,-50.0f,-00.0f };
		g_camera3D->SetPosition(m_cameraPosition);
	}

	m_battleshipgunModel.Update();
	m_machinegunModel.Update();
	m_gigaplasmaModel.Update();
	m_backGroundModel.SetPosition(m_backGroundModelPosition);

	m_backGroundModel.Update();

	m_timer += g_gameTime->GetFrameDeltaTime();
	switch (m_modelChangeState)
	{
	case 0:
		if (m_timer >=10.0f)
		{
			m_modelChangeState = 1;
			m_modelPosition = { -300.0f,00.0f,200.0f };
			m_targetPosition = { -300.0f,-50.0f,500.0f };
			m_cameraPosition = { 600.0f,100.0f,100.0f };
			m_titlePattern = 1;
			m_timer = 0.0f;
		}
		break;
	case 1:
		if (m_timer >= 10.0f)
		{
			m_modelChangeState = 2;
			m_modelPosition = { 0.0f,00.0f,200.0f };
			m_titlePattern = 2;
			m_timer = 0.0f;
		}
		break;
	case 2:
		if (m_timer >= 10.0f)
		{
			m_modelChangeState = 0;
			m_modelPosition= { -300.0f,50.0f,200.0f };
			m_titlePattern = 0;
			m_timer = 0.0f;
		}
		break;
	}
	
	
}

void Title::TitleMove() {
	m_whiteOutSprite.SetMulColor(m_whiteOutColor);
	if (m_pressCount % 100 == 0) {
		m_pressDirection *= -1;
	}
	m_pressSpriteColor.w -= 0.01 * m_pressDirection;
	m_pressSprite.SetMulColor(m_pressSpriteColor);

	if (g_pad[0]->IsTrigger(enButtonA)) {
		PlaySE(20, 2.0f);
		m_titleState = 1;
	}
	if (m_titleState == 1) {
		m_whiteOutColor.w += 0.1;
		if (m_whiteOutCount == 9) {
			m_titleState = 2;
		}
		m_whiteOutCount++;
		m_whiteOutSprite.SetMulColor(m_whiteOutColor);
	}
	

	m_pressCount++;
	m_pressSprite.Update();
	m_whiteOutSprite.Update();
}

void Title::Menu() {
	//遷移
	if (m_titleState == 2) {
		m_whiteOutColor.w -= 0.1;
		if (m_whiteOutCount == 19) {
			m_titleState = 3;
			m_selectPoint = 0;
			m_fastCount = 0;
		}
		m_whiteOutCount++;
	}

	if (m_selectPointPowCount % 100 == 0) {
		m_selectPointPowDirection *= -1;
	}
	m_selectPointPowColor.w -= 0.02 * m_selectPointPowDirection;
	m_selectPointPowSprite.SetMulColor(m_selectPointPowColor);
	m_selectPointPowCount++;

	//メインメニュー
	if (m_titleState == 3) {
		if (m_fastCount >= 1 && m_fastCount < 11) {
			m_tranceSheetScale.x += 0.085f;
		}
		else if (m_fastCount >= 11 && m_fastCount < 21) {
			m_tranceSheetScale.x -= 0.085f;
		}


		if (m_selectPoint >= 0 &&m_selectPoint<=1&& g_pad[0]->IsTrigger(enButtonDown)) {
			m_selectPoint++;
			PlaySE(19, 2.0f);
		}
		if (m_selectPoint <= 2 && m_selectPoint >= 1 && g_pad[0]->IsTrigger(enButtonUp)) {
			PlaySE(19, 2.0f);
			m_selectPoint--;
		}
		if (g_pad[0]->IsTrigger(enButtonA) && m_fastCount != 1&&m_selectPoint==0) {
			m_titleState = 4;
			PlaySE(17, 2.0f);
		}
		if (g_pad[0]->IsTrigger(enButtonA) && m_fastCount != 1 && m_selectPoint == 2) {
			m_titleState = 8;
			PlaySE(17, 2.0f);
			m_selectPoint = 0;
			m_fastCount = 0;
		}
		if (g_pad[0]->IsTrigger(enButtonA) && m_fastCount != 1 && m_selectPoint== 1) {
			PlaySE(17, 2.0f);
			m_selectPoint = 0;
			m_fastCount = 0;
			m_titleState = 5;
			
		}
		if (g_pad[0]->IsTrigger(enButtonB)) {
			PlaySE(18, 2.0f);
			m_titleState = 0;
			m_whiteOutCount = 0;
			m_selectPoint = 0;
			m_fastCount = 0;
		}
		m_fastCount++;


		for (int i = 0; i < 9; i++) {
			m_menuTranceSprite[i].SetScale(m_tranceSheetScale);
		}
		m_menuTranceSprite[0].Update();
		m_menuTranceSprite[8].Update();
		for (int i = 1; i < 4; i++) {
			m_menuTranceSprite[i].Update();
		}
	}
	if (m_titleState == 4) {
		m_loadingSpriteColor.w += 0.1;
		m_loadingSprite.SetMulColor(m_loadingSpriteColor);
		m_loadingSprite.Update();
		if (m_loadingSpriteColor.w >= 1.1f) 
		{
			//ゲームを始めると同時に音量のデータも送る
			Game* game = NewGO<Game>(0, "game");
			game->SetPlayerColorData(m_playerColorData);
			game->SetSEVol(m_BGMVolume);
			game->SetBGM(m_SEVolume);
			DeleteGO(this);
		}
	}

	if (m_titleState == 5) {
		if (m_fastCount >= 1 && m_fastCount < 11) {
			m_tranceSheetScale.x += 0.085f;
		}
		else if (m_fastCount >= 11 && m_fastCount < 21) {
			m_tranceSheetScale.x -= 0.085f;
		}

		if (m_selectPoint >= 0 && m_selectPoint <= 0 && g_pad[0]->IsTrigger(enButtonDown)) {
			PlaySE(19, 2.0f);
			m_selectPoint++;
		}
		if (m_selectPoint <= 1 && m_selectPoint >= 1 && g_pad[0]->IsTrigger(enButtonUp)) {
			PlaySE(19, 2.0f);
			m_selectPoint--;
		}
		if (g_pad[0]->IsTrigger(enButtonA) && m_fastCount != 1&& m_selectPoint==0) {
			PlaySE(17, 2.0f);
			m_titleState = 6;
			m_selectPoint = 0;
			m_fastCount = 0;
		}
		if (g_pad[0]->IsTrigger(enButtonA) && m_fastCount != 1 && m_selectPoint == 1) {
			PlaySE(17, 2.0f);
			m_titleState = 7;
			m_selectPoint = 0;
			m_fastCount = 0;
		}
		if (g_pad[0]->IsTrigger(enButtonB)) {
			PlaySE(18, 2.0f);
			m_titleState = 3;
			m_selectPoint = 0;
			m_fastCount = 0;
		}
		m_fastCount++;

		for (int i = 0; i < 9; i++) {
			m_menuTranceSprite[i].SetScale(m_tranceSheetScale);
		}
		m_menuTranceSprite[0].Update();
		m_menuTranceSprite[8].Update();
		for (int i = 1; i < 3; i++) {
			m_menuTranceSprite[i].Update();
		}
	}

	if (m_titleState == 6) {
		if (m_fastCount >= 1 && m_fastCount < 11) {
			m_tranceSheetScale.x += 0.085f;
		}
		else if (m_fastCount >= 11 && m_fastCount < 21) {
			m_tranceSheetScale.x -= 0.085f;
		}

		if (m_selectPoint >= 0 && m_selectPoint <= 0 && g_pad[0]->IsTrigger(enButtonDown) && m_soundSetState == 0) {
			PlaySE(19, 2.0f);
			m_selectPoint++;
		}
		if (m_selectPoint <= 1 && m_selectPoint >= 1 && g_pad[0]->IsTrigger(enButtonUp) && m_soundSetState == 0) {
			PlaySE(19, 2.0f);
			m_selectPoint--;
		}
		if (g_pad[0]->IsTrigger(enButtonA) && m_fastCount != 1 && m_selectPoint == 0&&m_soundSetState==0) {
			PlaySE(17, 2.0f);
			m_soundSetState = 1;
			m_soundSpriteColor.w = 0.5f;
			m_soundSprite2.SetMulColor(m_soundSpriteColor);
			m_SESoundBerSprite.SetMulColor(m_soundSpriteColor);
		}
		if (g_pad[0]->IsTrigger(enButtonA) && m_fastCount != 1 && m_selectPoint == 1 && m_soundSetState == 0) {
			PlaySE(17, 2.0f);
			m_soundSetState = 2;
			m_soundSpriteColor.w = 0.5f;
			m_soundSprite.SetMulColor(m_soundSpriteColor);
			m_BGMSoundBerSprite.SetMulColor(m_soundSpriteColor);
		}

		if (g_pad[0]->IsTrigger(enButtonB) && m_soundSetState == 0) {
			PlaySE(18, 2.0f);
			m_titleState = 5;
			m_selectPoint = 0;
			m_fastCount = 0;
		}

		if (g_pad[0]->IsPress(enButtonRight) && m_soundSetState == 1) {
			
			m_BGMVolume += 0.01;
			m_BGMBerScale.x += 0.0085;
			if (m_BGMVolume >= 1.0f) {
				m_BGMVolume = 1.0f;
				m_BGMBerScale.x = 0.85f;
			}
			PlaySE(19, 2.0f);
		}
		else if (g_pad[0]->IsPress(enButtonLeft) && m_soundSetState == 1) {
			
			m_BGMVolume -= 0.01;
			m_BGMBerScale.x -= 0.0085;
			if (m_BGMVolume <= 0.0f) {
				m_BGMVolume = 0.0f;
				m_BGMBerScale.x = 0.0f;
			}
			PlaySE(19, 2.0f);
		}

		if (g_pad[0]->IsPress(enButtonRight) && m_soundSetState == 2) {
			
			m_SEVolume += 0.01;
			m_SEBerScale.x += 0.0085;
			if (m_SEVolume >= 1.0f) {
				m_SEVolume = 1.0f;
				m_SEBerScale.x = 0.85f;
			}
			PlaySE(19, 2.0f);
		}
		else if (g_pad[0]->IsPress(enButtonLeft) && m_soundSetState == 2) {
			
			m_SEVolume -= 0.01;
			m_SEBerScale.x -= 0.0085;
			if (m_SEVolume <= 0.0f) {
				m_SEVolume = 0.0f;
				m_SEBerScale.x = 0.0f;
			}
			PlaySE(19, 2.0f);
		}

		if (g_pad[0]->IsTrigger(enButtonB) && m_fastCount != 1 && m_selectPoint == 0 && m_soundSetState == 1) {
			PlaySE(18, 2.0f);
			m_soundSetState = 0;
			m_soundSpriteColor.w = 1.0f;
			m_soundSprite2.SetMulColor(m_soundSpriteColor);
			m_SESoundBerSprite.SetMulColor(m_soundSpriteColor);
		}
		if (g_pad[0]->IsTrigger(enButtonB) && m_fastCount != 1 && m_selectPoint == 1 && m_soundSetState == 2) {
			PlaySE(18, 2.0f);
			m_soundSetState = 0;
			m_soundSpriteColor.w = 1.0f;
			m_soundSprite.SetMulColor(m_soundSpriteColor);
			m_BGMSoundBerSprite.SetMulColor(m_soundSpriteColor);
		}
		m_fastCount++;

		m_BGMSoundBerSprite.SetScale(m_BGMBerScale);
		m_SESoundBerSprite.SetScale(m_SEBerScale);

		m_BGMSoundBerSprite.Update();
		m_SESoundBerSprite.Update();

		for (int i = 0; i < 9; i++) {
			m_menuTranceSprite[i].SetScale(m_tranceSheetScale);
		}
		m_menuTranceSprite[0].Update();
		m_menuTranceSprite[8].Update();
		for (int i = 1; i < 3; i++) {
			m_menuTranceSprite[i].Update();
		}
	}

	if (m_titleState == 7) {
		if (m_fastCount >= 1 && m_fastCount < 11) {
			m_tranceSheetScale.x += 0.085f;
		}
		else if (m_fastCount >= 11 && m_fastCount < 21) {
			m_tranceSheetScale.x -= 0.085f;
		}

		if (m_selectPoint >= 0 && m_selectPoint <= 6 && g_pad[0]->IsTrigger(enButtonDown)) {
			PlaySE(19, 2.0f);
			m_selectPoint++;
		}
		if (m_selectPoint <= 7 && m_selectPoint >= 1 && g_pad[0]->IsTrigger(enButtonUp)) {
			PlaySE(19, 2.0f);
			m_selectPoint--;
		}
		
		if (g_pad[0]->IsTrigger(enButtonB)) {
			PlaySE(18, 2.0f);
			m_titleState = 5;
			m_selectPoint = 0;
			m_fastCount = 0;
		}
		for (int i = 0; i < 9; i++) {
			m_menuTranceSprite[i].SetScale(m_tranceSheetScale);
		}
		m_fastCount++;
		m_menuTranceSprite[0].Update();
		m_menuTranceSprite[8].Update();
		for (int i = 1; i < 9; i++) {
			m_menuTranceSprite[i].Update();
		}
	}

	if (m_titleState == 8) {
		if (m_fastCount >= 1 && m_fastCount < 11) {
			m_tranceSheetScale.x += 0.085f;
		}
		else if (m_fastCount >= 11 && m_fastCount < 21) {
			m_tranceSheetScale.x -= 0.085f;
		}

		if (m_selectPoint >= 0 && m_selectPoint <= 6 && g_pad[0]->IsTrigger(enButtonDown)) {
			PlaySE(19, 2.0f);
			m_selectPoint++;
		}
		if (m_selectPoint <= 7 && m_selectPoint >= 1 && g_pad[0]->IsTrigger(enButtonUp)) {
			PlaySE(19, 2.0f);
			m_selectPoint--;
		}

		if (g_pad[0]->IsTrigger(enButtonB)) {
			PlaySE(18, 2.0f);
			m_titleState = 3;
			m_selectPoint = 0;
			m_fastCount = 0;
		}
		if (g_pad[0]->IsTrigger(enButtonA) && m_fastCount != 1) {
			PlaySE(17, 2.0f);
			m_playerColorData = m_selectPoint;
		}
		for (int i = 0; i < 9; i++) {
			m_menuTranceSprite[i].SetScale(m_tranceSheetScale);
		}
		m_fastCount++;
		m_menuTranceSprite[0].Update();
		m_menuTranceSprite[8].Update();
		for (int i = 1; i < 9; i++) {
			m_menuTranceSprite[i].Update();
		}
	}
	//セレクトポイントの処理
	if (m_titleState >= 3) {
		switch (m_selectPoint)
		{
		case 0:
			m_selectSpritePosition = { 0.0f,0.0f,0.0f };
			m_selectPointSprite.SetPosition(m_selectSpritePosition);
			m_selectPointPowSprite.SetPosition(m_selectSpritePosition);
			break;
		case 1:
			m_selectSpritePosition = { 0.0f,-67.5f,0.0f };
			m_selectPointSprite.SetPosition(m_selectSpritePosition);
			m_selectPointPowSprite.SetPosition(m_selectSpritePosition);
			break;
		case 2:
			m_selectSpritePosition = { 0.0f,-135.0f,0.0f };
			m_selectPointSprite.SetPosition(m_selectSpritePosition);
			m_selectPointPowSprite.SetPosition(m_selectSpritePosition);
			break;
		case 3:
			m_selectSpritePosition = { 0.0f,-202.5f,0.0f };
			m_selectPointSprite.SetPosition(m_selectSpritePosition);
			m_selectPointPowSprite.SetPosition(m_selectSpritePosition);
			break;
		case 4:
			m_selectSpritePosition = { 0.0f,-270.0f,0.0f };
			m_selectPointSprite.SetPosition(m_selectSpritePosition);
			m_selectPointPowSprite.SetPosition(m_selectSpritePosition);
			break;
		case 5:
			m_selectSpritePosition = { 0.0f,-337.5f,0.0f };
			m_selectPointSprite.SetPosition(m_selectSpritePosition);
			m_selectPointPowSprite.SetPosition(m_selectSpritePosition);
			break;
		case 6:
			m_selectSpritePosition = { 0.0f,-405.0f,0.0f };
			m_selectPointSprite.SetPosition(m_selectSpritePosition);
			m_selectPointPowSprite.SetPosition(m_selectSpritePosition);
			break;
		default:
			break;
		}
	}

	m_selectPointSprite.Update();
	m_selectPointPowSprite.Update();
	m_mainMenuBaseSprite.SetMulColor(m_mainMenuBaseSpriteColor);
	m_whiteOutSprite.SetMulColor(m_whiteOutColor);
	m_mainMenuBaseSprite.Update();
	m_whiteOutSprite.Update();
}

void Title::Render(RenderContext& rc)
{
	m_backGroundModel.Draw(rc);
	if (m_titlePattern == 0)
	{
		m_battleshipgunModel.Draw(rc);
	}
	else if (m_titlePattern == 1)
	{
		m_machinegunModel.Draw(rc);
	}
	else if (m_titlePattern == 2)
	{
		m_gigaplasmaModel.Draw(rc);
	}

	//画像のドロー
	if (m_titleState == 0||m_titleState==1) {
		m_titleSprite.Draw(rc);
		m_pressSprite.Draw(rc);
	}
	if (m_titleState >= 3) {
		
		m_mainMenuBaseSprite.Draw(rc);
		m_sideLineSprite.Draw(rc);
		m_backOKSprite.Draw(rc);
		m_selectPointSprite.Draw(rc);
		m_selectPointPowSprite.Draw(rc);
	}
	if (m_titleState == 3) {
		m_mainMenuSprite.Draw(rc);
	}

	

	if (m_titleState == 5) {
		m_optionSprite.Draw(rc);
	}
	if (m_titleState == 6) {
		m_soundSprite.Draw(rc);
		m_soundSprite2.Draw(rc);
		m_soundSpriet3.Draw(rc);
		m_BGMSoundBerSprite.Draw(rc);
		m_SESoundBerSprite.Draw(rc);
	}
	if (m_titleState == 7) {
		m_controlesSprite.Draw(rc);
	}
	if (m_titleState == 8) {
		m_playerColorSprite.Draw(rc);
	}
	for(int i = 0; i < 9; i++) {
		m_menuTranceSprite[i].Draw(rc);
	}
	if (m_titleState == 4) {
		m_loadingSprite.Draw(rc);
	}

	m_whiteOutSprite.Draw(rc);
}