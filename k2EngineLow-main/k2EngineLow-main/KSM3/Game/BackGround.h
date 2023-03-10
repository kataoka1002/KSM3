#pragma once
class BackGround : public IGameObject
{
public:
    BackGround();
    ~BackGround();


    bool Start();
    void Update();
    void Render(RenderContext& rc);

    ModelRender modelRender;
    PhysicsStaticObject physicsStaticObject;//静的物理オブジェクト。
};

