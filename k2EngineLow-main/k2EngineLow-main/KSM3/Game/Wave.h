#pragma once
class Game;
class Player;
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

	SpriteRender	m_waveStartSprite;							//�E�F�[�u���ς�������ɗ����X�v���C�g
	SpriteRender	m_waveGage;									//�E�F�[�u�̃Q�[�W

	int				m_waveNum = 0;								//�E�F�[�u�̃i���o�[(�S����3��̃E�F�[�u������)
	int				m_ensyutuCount = 0;
	float			m_timer = 0.0f;								//�^�C�}�[
	bool			m_ensyutuNow = false;						//���o�����ǂ���
	FontRender		m_timerFont;								//�^�C�}�[��\������t�H���g
	Vector3			m_spritePos = Vector3::Zero;				//�X�v���C�g�𓮂������߂̕ϐ�
	Vector3         m_moveSpeed = Vector3::Zero;

	const float		TIME_LIMIT = 180.0f;						//�P�E�F�[�u�̃^�C�����~�b�g
	const Vector3	SPRITE_POSITION = { 1000.0f,0.0f,0.0f };	//�E�F�[�u�ύX�X�v���C�g�̏����ꏊ
};

