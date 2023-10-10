#pragma once
class PushButton : public IGameObject
{
public:
	bool Start();
	void Update();
	void CalcScale();
	void PlayNiziButton();
	void Render(RenderContext& rc);

	void SetNiziButtonFlag()
	{
		m_niziButtonFlag = true;
	}

private:
	SpriteRender m_syuutyuuSprite;
	SpriteRender m_buttonSprite;
	SpriteRender m_niziButtonSprite;
	SpriteRender m_oseSprite;

	Vector3 m_syuutyuuScale = { 1.0f, 1.0f, 1.0f };
	Vector3 m_buttonScale = { 0.01f, 0.01f, 1.0f };
	Vector3 m_niziButtonScale = { 1.0f, 1.0f, 1.0f };
	Vector3 m_oseScale = { 0.01f, 0.01f, 1.0f };

	bool m_niziButtonFlag = false;
};

