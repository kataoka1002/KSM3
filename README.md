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
> * [1.作品概要](#anchor1)
> * [2.作成したソースコード](#anchor2)
> * [3.作成したエンジンコード](#anchor3)
> * [4.ゲーム内容](#anchor4)
> * [5.操作説明](#anchor5)
> * [6.技術紹介](#anchor6)
>   * [パス移動](#anchor7)
>   * [画面揺れ](#anchor8)
>   * [導虫](#anchor9)
>   * [コンボ](#anchor10)
>   * [グレースケール](#anchor11)
>   * [トゥーンシェーダー](#anchor12)
>   * [輪郭線](#anchor13)

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

<a id="anchor2"></a>
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

<a id="anchor3"></a>
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

<a id="anchor4"></a>
## 4.ゲーム内容
> #### 敵を倒してドロップしたアイテムを装備し、進んでいくゲーム。<br />
> #### 自分好みのカスタマイズで敵を翻弄しよう！
> 
> <br />
>
> メインゲーム画面
> ![スクリーンショット 2023-07-10 173727](https://github.com/kataoka1002/KSM3/assets/122655580/d2114969-43a5-4123-8f97-1c2940be2aaa)
> カスタマイズ画面
> ![スクリーンショット 2023-07-10 173838](https://github.com/kataoka1002/KSM3/assets/122655580/3522fbad-9878-4c13-83b9-1b9c35595f32)

<br />

<a id="anchor5"></a>
## 5.操作説明
> ![操作説明](https://github.com/kataoka1002/KSM3/assets/122655580/84628a07-4fc5-4005-b8a9-4c71acd8f195)

<br />

<a id="anchor6"></a>
## 6.技術紹介
<a id="anchor7"></a>
> ### パス移動
> *1.* 「場所を表す座標」と「ナンバー」を保持している構造体を作り、パス移動させたいクラスに持たせて初期化します。
> |構造体の配列|[ 0 ]|[ 1 ]|[ 2 ]|[ 3 ]|
> |:-:|:-:|:-:|:-:|:-:|
> |目標座標|座標1|座標2|座標3|座標4|
> |ナンバー|1|2|3|4|
> 
> <br />
>
> *2.* 目標座標と自分の座標の距離を測り一定以下になったら、目標座標の配列を変更します。<br />
> ここで、配列の要素に今のナンバーを直接入れることで次の配列に進めることが出来ます。
> ``` ruby : Enemy.cpp
> //距離が一定以内なら
>	if (m_diffToPoint < 20.0f)
>	{
>		//今目的地としているポイントが配列の最後の要素なら
>		if (m_point->m_num == m_pointList.size()) 
>		{
>			//一番最初のポイントを目的地とする
>			m_point = &m_pointList[0];
>		}
>		else 
>		{
>			//配列の次の要素のポイントを目的地とする
>			m_point = &m_pointList[m_point->m_num];
>		}
>	}
> ```
>-----------------------------
> <a id="anchor8"></a>
> ### 画面揺れ
> *1.* 画面揺れは、カメラの注視点を移動させることで実装しています。<br />
> 注視点から見て左右に揺れるために振動の大きさの半分を引きます。
> ``` ruby : GameCamera.cpp
> //左右に揺れるために半分の値を引く
> int vibHalf = vib / 2;
> 
> //最終的な揺れの大きさを求める
> BGX = rand() % vib - vibHalf;  
> BGY = rand() % vib - vibHalf;
> ```
> <br />
>
> *2.* 揺れる方向がワンパターンにならないように一定の範囲(下図のオレンジ)からランダムに取った座標を設定しており、この範囲を徐々に狭くしていくことで滑らかに揺れを小さくしています。
> 
> <br />
>
> ![揺れ範囲説明](https://github.com/kataoka1002/KSM3/assets/122655580/8becdb00-541c-496e-926f-7b4b2804db3b)
>
>----------------------------------
> <a id="anchor9"></a>
> ### 導虫
> *1.* 光が滑らかに射出されるようにしたいので、まず遠心力を求める。
> ```math
> F = m * \frac{v^2}{r}
> ```
> より、重さを１として計算する。
> ``` ruby : GuideLight.cpp
> float maxCentripetalAccel = speed * speed / curvatureRadius;
> ```
> 
> <br />
>
> *2.* 今いる位置から目標の地点までのベクトルを求める。
> ``` ruby : GuideLight.cpp
> //目標の地点
> Vector3 targetPosition = m_targetPosition;
>  
> //目標までのベクトル
> Vector3 toTarget = targetPosition - m_position;
> ```
> 
> <br />
>
> *3.* 射出速度を正規化し、方向のみの情報を取得する。
> ![vnの正規化](https://github.com/kataoka1002/KSM3/assets/122655580/f9bc9abc-dc8d-4335-818d-95f18918a404)
>
> <br />
>
> *4.* ToTargetと正規化後のvnとの内積を求める。 <br />
> そうすると、ToTargetをvnに射影したときのT'の大きさが求まる(下図の｜T'｜)
> ![Tno](https://github.com/kataoka1002/KSM3/assets/122655580/118ab361-2d8a-4787-94b5-079f6afad481)
> 
> <br />
>
> *5.* T\'からTargetまでのベクトルcentripetalAccel(ベクトルT\`B)を求める。<br />
> 下図より「ベクトルT\`B ＝ ベクトルAB - ベクトルAT\`」① のうち、まだわからないのはベクトルAT\`である。 <br />
> | T\`|は分かっているのでそこから求めると、「ベクトルvn ｘ | T\`| = ベクトルAT\`」となりベクトルAT\`を求められる。<br />
> それを①に代入しベクトルT\`Bを求める。それはベクトルcentripetalAccelであり、曲げるために加える加速度になる。
> ![centripetalAccel](https://github.com/kataoka1002/KSM3/assets/122655580/01f0ca59-c913-446c-ace6-7919b1b1ce4b)
>
>  <br />
>
> *6.* ベクトルcentripetalAccelの大きさを求め、一定の範囲に収める。
> ``` ruby : GuideLight.cpp
> //その長さを求める
> float centripetalAccelMagnitude = centripetalAccel.Length();
>
> //1以上なら長さを1に正規化し,1未満ならそのまま
> if (centripetalAccelMagnitude > 1.0f)
> {
> 	//ベクトルの正規化を行う
> 	centripetalAccel /= centripetalAccelMagnitude;
> }
> ```
> <br />
>
> *7.* 最終的に加える力を求め、速度に加える。
> ``` ruby : GuideLight.cpp
> //長さがmaxCentripetalAccel以下ならそのまま、以上なら長さをmaxCentripetalAccelにする
> Vector3 force = centripetalAccel * maxCentripetalAccel;
>
> //推進力
> force += vn * propulsion;
>
> //空気抵抗
> force -= m_velocity * damping;
>
> //速度積分
> m_velocity += force * g_gameTime->GetFrameDeltaTime();
>```

<a id="anchor10"></a>
> ### コンボ
<a id="anchor11"></a>
> ### グレースケール
<a id="anchor12"></a>
> ### トゥーンシェーダー
<a id="anchor13"></a>
> ### 輪郭線