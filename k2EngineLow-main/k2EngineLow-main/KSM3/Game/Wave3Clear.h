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

	float m_flashSpriteScale = 1.0f;			//白フラッシュの大きさ
	float m_yellowSpriteA = 0.0f;				//黄色フラッシュのα値
	int m_count = 0;							//カウント
	int m_spriteState = 0;						//0:雑魚　1:殲　2:滅
	bool m_flashPlay = false;					//フラッシュを再生するかどうか
	bool m_fontDrawStop = false;				//雑魚殲滅スプライトを止めるかどうか
	bool m_deleteFlash = false;					//白フラッシュを消すかどうか
	bool m_yellowFinish = false;				//黄色フラッシュが終わったかどうか

};

