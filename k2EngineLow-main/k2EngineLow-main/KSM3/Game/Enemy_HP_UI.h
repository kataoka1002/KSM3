#pragma once
class Enemy_Near;
class Enemy;
class Enemy_Far;
class Player;
class Game;
class GameCamera;

class Enemy_HP_UI : public IGameObject
{
public:
	Enemy_HP_UI();
	~Enemy_HP_UI();
	bool Start();
	void Update();
	void CalcPosition();
	void CalcScale();
	Vector3 SendHPBer(Vector3 size, Vector3 scale);	//画像の移動量を求める
	void Render(RenderContext& rc);
	template <class T>

	/// <summary>
	/// 一定距離以内&カメラの視野に入っているなら体力表示
	/// </summary>
	/// <param name="enemy">エネミーのクラス</param>
	/// <returns>true : 描画する、false : 描画しない</returns>
	bool CalcAngle(T enemy);

	/// <summary>
	/// 近距離エネミーをセット
	/// </summary>
	/// <param name="pointa">ポインタ</param>
	void SetEnemyNear(Enemy_Near* pointa)
	{
		m_enemyNear = pointa;
	}

	/// <summary>
	/// エネミーをセット
	/// </summary>
	/// <param name="pointa">ポインタ</param>
	void SetEnemy(Enemy* pointa)
	{
		m_enemy = pointa;
	}

	/// <summary>
	/// 遠距離エネミーをセット
	/// </summary>
	/// <param name="pointa">ポインタ</param>
	void SetEnemyFar(Enemy_Far* pointa)
	{
		m_enemyFar = pointa;
	}

private:
	Enemy_Near* m_enemyNear = nullptr;
	Enemy* m_enemy = nullptr;
	Enemy_Far* m_enemyFar = nullptr;
	Player* m_player = nullptr;
	Game* m_game = nullptr;
	GameCamera* m_camera = nullptr;

	SpriteRender m_HPSprite;
	SpriteRender m_HPFrameSprite;

	Vector2 m_position = Vector2::Zero;
	Vector3 m_scale = {1.0f,1.0f,0.0f};
};

