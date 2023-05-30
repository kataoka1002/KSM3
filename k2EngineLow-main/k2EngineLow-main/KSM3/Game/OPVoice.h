#pragma once
class Game;

class OPVoice : public IGameObject
{
public:
	OPVoice();
	~OPVoice();
	bool Start();
	void Update();
	void ChangeSprite();
	void Render(RenderContext& rc);

	SpriteRender m_voiceSprite;
	SpriteRender m_voiceFrameSprite;

	SoundSource* m_voiceSE = nullptr;
	SoundSource* m_putunSE = nullptr;
	Game* m_game = nullptr;

	float m_frameScaleY = 0.0f;		//�X�v���C�g��Y�����̑傫��
	int m_spriteChangeCount = 0;	//�X�v���C�g���؂�ւ��(�g��̖{�����ς��)�Ԋu�̃J�E���g
	int m_voiceSpriteState = 0;		//�g��̖{���ƃX�e�[�g�̐�������
	bool m_scaleDown = false;		//�X�v���C�g�����������邩�ǂ���
};

