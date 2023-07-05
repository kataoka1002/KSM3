#pragma once
class Lighting;
class SoundManage;

class Title : public IGameObject
{
public:
	Title();
	~Title();
	void Update();
	bool Start();
	void SetUp();
	void TitleMove();
	void Menu();
	void Render(RenderContext& rc);
	void PlaySE(int track_number, float vol);

private:
	Lighting* m_lighting = nullptr;

	SpriteRender m_titleSprite;
	SpriteRender m_pressSprite;
	SpriteRender m_whiteOutSprite;
	SpriteRender m_sideLineSprite;
	SpriteRender m_mainMenuSprite;
	SpriteRender m_mainMenuBaseSprite;
	SpriteRender m_backOKSprite;
	SpriteRender m_selectPointSprite;
	SpriteRender m_selectPointPowSprite;
	SpriteRender m_loadingSprite;
	SpriteRender m_soundSprite;
	SpriteRender m_soundSprite2;
	SpriteRender m_soundSpriet3;
	SpriteRender m_optionSprite;
	SpriteRender m_BGMSoundBerSprite;
	SpriteRender m_SESoundBerSprite;
	SpriteRender m_controlesSprite;
	SpriteRender m_menuTranceSprite[9];
	SpriteRender m_playerColorSprite;
	ModelRender m_battleshipgunModel;		//battleship_gun
	ModelRender m_machinegunModel;			//machine_gun
	ModelRender m_gigaplasmaModel;			//Giga_Plasma
	ModelRender m_backGroundModel;			//�w�i�B
	Quaternion m_modelRotarionX;			//���f����x����]�B
	Quaternion m_modelRotarionY;			//���f����y����]�B
	Quaternion m_rotation;					//���̑��̉�]�B

	Vector4 m_pressSpriteColor				= { 1.0f,1.0f,1.0f,1.0f };
	Vector4 m_whiteOutColor					= { 1.0f,1.0f,1.0f,0.0f };
	Vector4 m_mainMenuBaseSpriteColor		= { 1.0f,1.0f,1.0f,0.5f };
	Vector4 m_selectPointPowColor			= { 1.0f,1.0f,1.0f,2.0f };
	Vector4 m_loadingSpriteColor			= { 1.0f,1.0f,1.0f,0.0f };
	Vector4 m_soundSpriteColor				= { 1.0f,1.0f,1.0f,1.0f };
	Vector3 m_modelPosition					= { -300.0f,50.0f,200.0f };		//���f�������̋��ꏊ�B
	Vector3 m_backGroundModelPosition		= { 0.0f,-100.0f,100.0f };
	Vector3 m_targetPosition				= { -300.0f,50.0f,200.0f };
	Vector3 m_cameraPosition				= { -300.0f,-50.0f,-50.0f };	//�J�����̋��ꏊ�B
	Vector3 m_titleScale					= { 0.85f,0.85f,0.0f };
	Vector3 m_selectSpritePosition			= { 0.0f,0.0f,0.0f };
	Vector3 m_tranceSheetScale				= { 0.0f,0.85f,1.0f };
	Vector3 m_BGMBerScale					= { 0.85f,0.85f,1.0f };
	Vector3 m_SEBerScale					= { 0.85f,0.85f,1.0f };
	Vector3 m_BGMBerPosition				= { -352.7f,169.4f,0.0f };
	Vector3 m_SEBerPosition					= { -352.7f,101.5f,0.0f };
	Vector3 m_menuTranceTitlePos			= { -651.0f,316.5f,0.0f};		//�^�C�g������
	Vector3 m_menuTrancePos1				= { -646.0f,170.0f,0.0f };		//���j���[1�i��
	Vector3 m_menuTrancePos2				= { -646.0f,100.0f,0.0f };		//���j���[2�i��
	Vector3 m_menuTrancePos3				= { -646.0f,30.0f,0.0f };		//���j���[3�i��
	Vector3 m_menuTrancePos4				= { -646.0f,-39.5f,0.0f };		//���j���[4�i��
	Vector3 m_menuTrancePos5				= { -646.0f,-107.0f,0.0f };		//���j���[5�i��
	Vector3 m_menuTrancePos6				= { -646.0f,-176.5f,0.0f };		//���j���[6�i��
	Vector3 m_menuTrancePos7				= { -646.0f,-244.0f,0.0f };		//���j���[7�i��
	Vector3 m_menuTranceOKBackPos			= { -646.0f,-394.0f,0.0f };		//OK_BACK����
	Vector2 m_menuTrancePivot				= { 0.0f,0.5f };
	Vector2 m_BGMBerPivot					= { 0.0f,0.5f };
	Vector2 m_SEBerPivot					= { 0.0f,0.5f };

	int m_modelScale				= 10.0f;			//���f���̑傫���B
	int m_modelChangeState			= 0;				//time���ĂȂ��Ă邯�ǃX�e�[�g�ł��B
	int m_titlePattern				= 0;				//�p�^�[�����S���B
	int m_playerColorData			= 0;
	int m_titleState				= 0;				//0:�^�C�g�� 1:�J�ڑO�� 2:�J�ڌ㔼 3:���C�����j���[ 4:Loading 5:option 6:
	int m_selectPoint				= 0;				//�^�C�g���̃X�v���C�g�����_�[�̐錾
	int m_fastCount					= 1;
	int m_pressCount				= 0;
	int m_pressDirection			= -1;
	int m_whiteOutCount				= 0;
	int m_selectPointPowCount		= 0;
	int m_selectPointPowDirection	= -1;
	int m_soundSetState				= 0;				//0:�����Ȃ� 1:BGM 2:SE
	float m_timer					= 0;				//���ԁB
	float m_BGMVolume				= 1.0f;				//BGM�̃{�����[��
	float m_SEVolume				= 1.0f;				//SE�̃{�����[��

};

