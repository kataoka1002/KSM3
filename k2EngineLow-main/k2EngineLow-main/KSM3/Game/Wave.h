#pragma once
class Game;
class Player;
class Boss;
class GuideLight;
class Wave3Clear;
class Wave : public IGameObject
{
public:
	Wave();
	~Wave();
	bool Start();
	void Update();
	void HandleWaveLogic();
	void MakeGuide();
	void TimeCount();
	void SpritePlay();
	void TimerRotation();
	void GageSetScale();
	void ExecuteBossBattle();
	void Render(RenderContext& rc);

	/// <summary>
	/// ���C���Q�[�����������̓|�[�Y��ʒ����𔻒�
	/// </summary>
	/// <returns></returns>
	bool IsInMainGameOrPause();

	/// <summary>
	/// �{�X�킶��Ȃ����ǂ����𒲂ׂ�
	/// </summary>
	/// <returns>true : �{�X�킶��Ȃ� , false : �{�X��</returns>
	bool IsNotBossBattle() ;

	/// <summary>
	/// �E�F�[�u�N���A�Ƀ|�C���^���Z�b�g����
	/// </summary>
	/// <param name="pointa"></param>
	void SetWaveClear(Wave3Clear* pointa)
	{
		m_waveClear = pointa;
	}


	/// <summary>
	/// �{�X���Z�b�g����
	/// </summary>
	/// <param name="pointa"></param>
	void SetBoss(Boss* pointa)
	{
		m_boss = pointa;
	}


	/// <summary>
	/// �{�X��ɍs���邩�ǂ�����Ԃ�
	/// </summary>
	/// <returns>true : �s���� , false : �s���Ȃ�</returns>
	bool GetGoBoss()
	{
		return m_goBoss;
	}


	/// <summary>
	/// ���[�f�B���O�J�E���g��Ԃ�
	/// </summary>
	/// <returns></returns>
	int GetLoadCount()
	{
		return Loading_count;
	}


	/// <summary>
	/// �E�F�[�u�N���A��Ԃ�
	/// </summary>
	/// <returns></returns>
	Wave3Clear* GetWaveClear()
	{
		return m_waveClear;
	}

private:
	Game* m_game = nullptr;
	Player* m_player = nullptr;
	Boss* m_boss = nullptr;
	GuideLight* m_guide = nullptr;
	Wave3Clear* m_waveClear = nullptr;

	SpriteRender	m_waveStartSprite;							//�E�F�[�u���ς�������ɗ����X�v���C�g
	SpriteRender	m_waveStartWakuSprite;						//�E�F�[�u���ς�������ɗ����X�v���C�g�̘g
	SpriteRender	m_waveGageNakami;							//�E�F�[�u�̃Q�[�W���g
	SpriteRender	m_waveGageWaku;								//�E�F�[�u�̃Q�[�W�g
	SpriteRender	m_TimerSprite;								//�^�C�}�[
	SpriteRender	m_TimerSprite2;								//�^�C�}�[2
	SpriteRender	m_missionSprite;							//�~�b�V����
	SpriteRender	m_loadingSprite;

	FontRender		m_timerFont;								//�^�C�}�[��\������t�H���g
	Vector3			m_spritePos = Vector3::Zero;				//�X�v���C�g�𓮂������߂̕ϐ�
	Vector3         m_moveSpeed = Vector3::Zero;
	Quaternion		m_timerRot;
	Vector4			Loading_color = { 1.0f,1.0f,1.0f,0.0f };

	int				m_waveNum = 0;								//�E�F�[�u�̃i���o�[(�S����3��̃E�F�[�u������)
	int				m_ensyutuCount = 0;
	int				m_guideCount = 0;
	int				Loading_count = 0;
	float			m_timer = 0.0f;								//�^�C�}�[
	float			m_wakuA = 0.0f;								//�g�̃��l
	bool			m_ensyutuNow = false;						//���o�����ǂ���
	bool			m_goBoss = false;							//�{�X��֍s���邩�ǂ���
	bool			m_spriteChangeFlag = false;
	bool			m_playerUISet = false;

};

