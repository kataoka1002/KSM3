#pragma once
class Game;
class Player;
class Boss;
class Wave : public IGameObject
{
public:
	Wave();
	~Wave();
	bool Start();
	void Update();
	void TimeCount();
	void SpritePlay();

	void GageSetScale();
	void Render(RenderContext& rc);

	Game* m_game = nullptr;
	Player* m_player = nullptr;
	Boss* m_boss = nullptr;

	SpriteRender	m_waveStartSprite;							//�E�F�[�u���ς�������ɗ����X�v���C�g
	SpriteRender	m_waveStartWakuSprite;						//�E�F�[�u���ς�������ɗ����X�v���C�g�̘g
	SpriteRender	m_waveGageNakami;							//�E�F�[�u�̃Q�[�W���g
	SpriteRender	m_waveGageWaku;								//�E�F�[�u�̃Q�[�W�g


	int				m_waveNum = 0;								//�E�F�[�u�̃i���o�[(�S����3��̃E�F�[�u������)
	int				m_ensyutuCount = 0;
	float			m_timer = 0.0f;								//�^�C�}�[
	float			m_wakuA = 0.0f;								//�g�̃��l
	bool			m_ensyutuNow = false;						//���o�����ǂ���
	bool			m_goBoss = false;							//�{�X��֍s���邩�ǂ���
	FontRender		m_timerFont;								//�^�C�}�[��\������t�H���g
	Vector3			m_spritePos = Vector3::Zero;				//�X�v���C�g�𓮂������߂̕ϐ�
	Vector3         m_moveSpeed = Vector3::Zero;

	SpriteRender Loading_Render;
	Vector4 Loading_color = { 1.0f,1.0f,1.0f,0.0f };
	int Loading_count = 0;


	const float		TIME_LIMIT = 180.0f;						//�P�E�F�[�u�̃^�C�����~�b�g
	const Vector3	SPRITE_POSITION = { 1000.0f,0.0f,0.0f };	//�E�F�[�u�ύX�X�v���C�g�̏����ꏊ
};

