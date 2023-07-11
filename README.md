<body>
  <![スクリーンショット 2023-07-08 144253](https://github.com/kataoka1002/KSM3/assets/122655580/32de5c09-ac11-4ec8-8afe-9c0ddb305622)>
</body>

# Evolvive
![スクリーンショット 2023-07-08 144253](https://github.com/kataoka1002/KSM3/assets/122655580/32de5c09-ac11-4ec8-8afe-9c0ddb305622)

<br />

## チーム紹介
> ### 所属
> 河原電子ビジネス専門学校　ゲームクリエイター科
> ### メンバー
> * 重永　翔　　　(しげなが　しょう)
> * 片岡　海人　　(かたおか　うみと)
> * 村上　和志　　(むらかみ　かずし)
> * 前田　小太郎　(まえだ　こたろう)

<br />

## 目次
> 1. [作品概要](#anchor1)
> 2. [作成したソースコード](#anchor2)
> 3. [作成したエンジンコード](#anchor3)
> 4. [ゲーム内容](#anchor4)
> 5. [操作説明](#anchor5)
> 6. [技術紹介](#anchor6)

<br />

<a id="anchor1"></a>
## 1.作品概要
> <dl>
>  <dt>タイトル</dt>
>  <dd>Evolvive</dd>
>  <dt>制作人数</dt>
>  <dd>4人</dd>
>  <dt>制作期間</dt>
>  <dd>2023年2月～2023年5月（日本ゲーム大賞2023 用期間）
>  <br />
>  2023年6月～2023年7月（リファクタリング 期間）</dd>
>  <dt>ゲームジャンル</dt>
>  <dd>アクションゲーム</dd>
>  <dt>プレイ人数</dt>
>  <dd>1人</dd>
>  <dt>対応ハード</dt>
>  <dd>PC Windows10,11</dd>
>  <dt>対応コントローラー</dt>
>  <dd>Xbox 360 コントローラー</dd>
>  <dt>使用言語</dt>
>  <dd>C++
>  <br />
>  HLSL<dd>
>  <dt>エンジン</dt>
>  <dd>学校内製の簡易エンジン(DirectX12)</dd>
>  <dt>プログラム</dt>
>  <dd>Visual Studio 2022</dd>
>  <dt>3Dモデル</dt>
>  <dd>3ds MAX</dd>
>  <dt>エフェクト</dt>
>  <dd>Effeckseer</dd>
>  <dt>画像</dt>
>  <dd>Adobe Photoshop</dd>
>  <dt>バージョン管理</dt>
>  <dd>Git Hub
>  <br />
>  Fork</dd>
>  <dt>タスク管理</dt>
>  <dd>Notion</dd>
>  <dt>連絡</dt>
>  <dd>Slack</dd>
>  <dt>GitHubのURL</dt>
>  <dd>https://github.com/kataoka1002/KSM3.git</dd> 
> </dl>

<br />

<a id="anchor1"></a>
## 2.作成したソースコード
> * AttackBase.cpp
> * AttackBase.h
> * Battle_ship_attack.cpp
> * Battle_ship_attack.h
> * Core_weapons_attack.cpp 
> * Core_weapons_attack.h 
> * Customize_UI_ver2.cpp	
> * Customize_UI_ver2.h	
> * Combo.cpp
> * Combo.h
> * Drop_item.cpp
> * Drop_item.h	
> * Enemy.cpp
> * Enemy.h
> * EnemyBase.cpp
> * EnemyBase.h
> * Enemy_Bullet.cpp
> * Enemy_Bullet.h
> * Enemy_Far.cpp
> * Enemy_Far.h
> * Enemy_BulletFar.cpp
> * Enemy_BulletFar.h
> * Enemy_HP_UI.cpp
> * Enemy_HP_UI.h
> * Enemy_Near.cpp
> * Enemy_Near.h
> * Game.cpp		
> * Game.h			
> * GameCamera.cpp	
> * GameCamera.h			
> * GigatonCannonAttack.cpp
> * GigatonCannonAttack.h
> * Right_arm_weapons.cpp	
> * Right_arm_weapons.h		
> * Left_arm_weapons.cpp	
> * Left_arm_weapons.h		
> * Left_leg_weapons.cpp	
> * Left_leg_weapons.h		
> * MachineGunAttack.cpp
> * MachineGunAttack.h
> * Player.cpp			
> * Player.h			
> * PlayerUI.cpp
> * PlayerUI.h
> * Shoulder_weapons.cpp	
> * Shoulder_weapons.h		
> * Wave.cpp
> * Wave.h
> * Wave3Clear.cpp
> * Wave3Clear.h
> * WeaponBase.cpp
> * WeaponBase.h

<br />

<a id="anchor1"></a>
## 3.作成したエンジンコード
> * Bloom.cpp
> * Bloom.h
> * FontRender.cpp
> * FontRender.h
> * ModelRender.cpp
> * ModelRender.h
> * RenderingEngine.cpp
> * RenderingEngine.h
> * SceneLight.cpp
> * SceneLight.h
> * SpriteRender.cpp
> * SpriteRender.h
> * ToonMap.cpp
> * ToonMap.h
> * model.fx
> * gaussianBlur.fx
> * shadowReciever.fx
> * sprite.fx

<br />

<a id="anchor1"></a>
## 4.ゲーム内容
> 敵を倒してドロップしたアイテムを装備し、進んでいくゲーム。<br />
> 自分好みのカスタマイズで敵を翻弄しよう！

<br />

<a id="anchor1"></a>
## 5.操作説明
> ![操作説明](https://github.com/kataoka1002/KSM3/assets/122655580/84628a07-4fc5-4005-b8a9-4c71acd8f195)

<br />

<a id="anchor1"></a>
## 6.技術紹介
