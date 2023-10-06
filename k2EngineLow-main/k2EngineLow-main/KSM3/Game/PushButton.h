#pragma once
class PushButton : public IGameObject
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);
private:
	SpriteRender m_syuutyuuSprite;
	SpriteRender m_buttonSprite;
	SpriteRender m_oseSprite;

	Vector3 m_syuutyuuScale = { 1.0f, 1.0f, 1.0f };
	Vector3 m_buttonScale = { 0.01f, 0.01f, 1.0f };
	Vector3 m_oseScale = { 0.0f, 0.0f, 1.0f };
};

