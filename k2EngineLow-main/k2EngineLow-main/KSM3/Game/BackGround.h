#pragma once
class BackGround : public IGameObject,Noncopyable
{
public:
    BackGround();
    ~BackGround();

    bool Start();
    void Update();
    void Render(RenderContext& rc);

private:
    std::unique_ptr<ModelRender> m_groundModel;
    PhysicsStaticObject m_physicsStaticObject;//静的物理オブジェクト。
};

