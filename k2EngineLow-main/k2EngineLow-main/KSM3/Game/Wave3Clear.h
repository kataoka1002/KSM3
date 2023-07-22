#pragma once
class Wave3Clear : public IGameObject, Noncopyable
{
public:
	Wave3Clear();
	~Wave3Clear();
	bool Start();
	void Update();
	void InitInformation();
	void PlayFlash();
	void Render(RenderContext& rc);

private:
	SpriteRender m_fontSprite;
	SpriteRender m_flashSprite;
	SpriteRender m_yellowSprite;

	float m_flashSpriteScale = 1.0f;			//���t���b�V���̑傫��
	float m_yellowSpriteA = 0.0f;				//���F�t���b�V���̃��l
	int m_count = 0;							//�J�E���g
	int m_spriteState = 0;						//0:�G���@1:�r�@2:��
	bool m_flashPlay = false;					//�t���b�V�����Đ����邩�ǂ���
	bool m_fontDrawStop = false;				//�G���r�ŃX�v���C�g���~�߂邩�ǂ���
	bool m_deleteFlash = false;					//���t���b�V�����������ǂ���
	bool m_yellowFinish = false;				//���F�t���b�V�����I��������ǂ���

};

