#pragma once

/// <summary>
/// �t�F�[�h�B
/// </summary>
class Fade : public IGameObject
{
public:
	Fade();
	~Fade();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
	void StartFadeIn()
	{
		m_state = enState_FadeIn;
	}
	void StartFadeOut()
	{
		m_state = enState_FadeOut;
	}

	bool IsFade() const
	{
		return m_state != enState_Idle;
	}
	float GetCurrentAlpha() const
	{
		return m_currentAlpha;
	}

private:
	enum EnState {
		enState_FadeIn,			//�t�F�[�h�C�����B
		enState_FadeOut,		//�t�F�[�h�A�E�g���B
		enState_Idle,			//�A�C�h�����B
	};
	SpriteRender	m_spriteRender;				//�X�v���C�g�����_�\�B
	EnState			m_state = enState_Idle;		//��ԁB
	float			m_currentAlpha = 1.0f;		//���݂̃��l�B������ύX����Ɖ摜�������ɂȂ�B
};