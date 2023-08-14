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
>   * [UVスクロール](#anchor14)

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
> //求めた長さに遠心力をかける
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
> ```
> ------------------
> <a id="anchor10"></a>
> ### コンボ
> *1.* ０から９までの画像を用意する。
> ![num](https://github.com/kataoka1002/KSM3/assets/122655580/57329888-aebb-4aaa-8b06-5a4bd9564d8a)
>
> *2.* 2桁の数字の左側には「倒した数÷10の整数値」を表示、右側には「倒した数÷10のあまり」を表示する。<br />
> そうすることで、0～9の10個の画像で無限に数値を表示できる。(1桁の時は十の位は表示しない)
> 
> |倒した数|倒した数÷10の整数値|倒した数÷10のあまり|表示される数|
> |:-:|:-:|:-:|:-:|
> |2|0|2|2|
> |10|1|0|10|
> |25|2|5|25|
> 
> <br />
>
> *3.* コンボ数は拡大しながら表示することで躍動感をだす。
> ![combo](https://github.com/kataoka1002/KSM3/assets/122655580/3393185f-96d6-4869-be71-2f70192b606f)
>
> ---------------------
> <a id="anchor11"></a>
> ### グレースケール
> *1.* プレイヤーが破壊されたときに「負けた感」を強く出すために実装しました。<br />
> 下のようにすることで、ピクセルの色を変更することが出来ます。
> ``` ruby : model.fx
> //グレースケールを設定する
> if(setGrayScale == true)
> {
>     float gray = 0.299f * albedoColor.r + 0.587f * albedoColor.g + 0.114f * albedoColor.b;
>        
>     return gray;
> }
> ```
> グレースケールなし
> ![スクリーンショット 2023-07-13 122111](https://github.com/kataoka1002/KSM3/assets/122655580/b2c59762-9a22-4b35-a614-0353db03b89a)
> 
> <br />
>
> グレースケールあり
> ![スクリーンショット 2023-07-13 122134](https://github.com/kataoka1002/KSM3/assets/122655580/f824a6d1-c5b7-4547-a0c8-9ee188fe72dc)
> 
> -----------------------
> <a id="anchor12"></a>
> ### トゥーンシェーダー
> *1.* プレイヤーのおもちゃ感を出すためにトゥーンシェーダーを実装しました。<br />
> まずはモデルの色を決める為のテクスチャを用意します(黒枠は必要なし)(数字はUV座標のU成分)。
> 
> <br />
>
> ![UVtoonSprite](https://github.com/kataoka1002/KSM3/assets/122655580/a190125f-49ae-4695-9f05-e9de61d27076)
> 
> <br />
>
> *2.* モデルの法線とライトの方向を求め、その内積を求めることでモデルにどれくらいの光が当たっているのかを求めます。<br />
> そして、内積は-1～1なので0～1に収まるように計算します。
> ``` ruby : model.fx
> //内積を求める
> float power = dot(psIn.normal * -1.0f, lightDirection);
> 
> //-1～1だった範囲を0～1にする。
> power = power * 0.5f + 0.5f;   
> ```
> 
> <br />
>
> *3.* UV座標のU成分は上図の通りなので、内積が小さいと左側部分で内積が大きいと右側部分の色を取り出します。<br />
> その取り出した色を元のモデルの色に乗算することで陰影がハッキリした表現を行います。
> ``` ruby : model.fx
> //計算結果よりトゥーンシェーダー用のテクスチャから色をフェッチする
> float4 toonColor = g_toonMap.Sample(g_sampler, float2(power, 0.0f));
>
> //モデルカラーに求めたトゥーンカラーをかける
> modelColor *= toonColor;
> ```
> トゥーンシェーダーなし
> ![スクリーンショット 2023-07-26 114533](https://github.com/kataoka1002/KSM3/assets/122655580/2f5172a6-fe8a-4e15-819e-30242306b21e)
> 
> <br />
>
> トゥーンシェーダーあり
> ![スクリーンショット 2023-07-26 114611](https://github.com/kataoka1002/KSM3/assets/122655580/1c5f5480-dc14-4674-bb22-250df583a4fc)
>
> -----------------------
> <a id="anchor13"></a>
> ### 輪郭線
> *1.* まず、モデルの深度値を取るためのテクスチャを用意します。<br />
> ![スクリーンショット 2023-07-26 122237](https://github.com/kataoka1002/KSM3/assets/122655580/b64c19a4-a8a7-4252-8dd3-3a1b961ad2ff)
> 
> <br />
>
> *2.* 基準テクセルの近傍8テクセルを取り出し深度値を求め、その平均値を求める。<br />
> 今回使うテクスチャサイズは横1280,縦720なので、1テクセルずらすためにはそのサイズで割ってやる必要があります。
> ``` ruby : model.fx
> // 近傍8テクセルへのUVオフセット
> float2 uvOffset[8] =
> {
>   float2(            0.0f,  1.0f / 720.0f ), //２
>   float2(            0.0f, -1.0f / 720.0f ), //７
>   float2(  1.0f / 1280.0f,           0.0f ), //５
>   float2( -1.0f / 1280.0f,           0.0f ), //４
>   float2(  1.0f / 1280.0f,  1.0f / 720.0f ), //３
>   float2( -1.0f / 1280.0f,  1.0f / 720.0f ), //１
>   float2(  1.0f / 1280.0f, -1.0f / 720.0f ), //８
>   float2( -1.0f / 1280.0f, -1.0f / 720.0f )  //６
> };
>
> //平均値の計算
> float depthAverage = 0.0f;
> 
> for(int i = 0; i < 8; i++)
> {
>   //深度値を取得して加算
>   depthAverage += g_depthTexture.Sample(g_sampler, uv + uvOffset[i]).x;
> }
> 
> depthAverage /= 8.0f;
> ```
> ![8pixcel](https://github.com/kataoka1002/KSM3/assets/122655580/70812cca-4c9a-459a-8053-7ca5f5599d6b)
> 
> <br />
>
> *3.* 基準テクセル(自身)の深度値と近傍8テクセルの深度値の平均値の差を求め、深度値に一定の差があればそこのピクセルカラーを黒にする。<br />
> これがエッジカラーとなる。
> ``` ruby : model.fx
> // 基準ピクセルの深度値を取得
> float depth = g_depthTexture.Sample(g_sampler, uv).x;
>
> //差が大きかったら
> if ( abs(depth - depthAverage) > 0.0005f)
> {
>   //ピクセルカラーを黒にする
>   return float4(0.0f, 0.0f, 0.0f, 1.0f); // ←これがエッジカラー
> }
>
> //それ以外は普通のカラーを返す
> return modelColor;
> ```
> ![nasiari](https://github.com/kataoka1002/KSM3/assets/122655580/4b50aecd-931b-4c7c-83cc-9b3fe9536528)
> 
> -----------------------
> <a id="anchor14"></a>
> ### UVスクロール
> *1.* ピクセルシェーダーは前フレームの状態を保持できないので、前フレームの座標に移動量を足していくことが出来ません。<br />
> そこで、「速さx時間＝移動量」で求めた値をもともとのUV座標に足すことで、疑似的に表現します。
> ``` ruby : model.fx
> //UVスクロールのフラグが立っているなら
> if (m_UVScrollFlag == 1.0f)
> {
>     psIn.uv.x += 0.015f * deltaTime;
> }
> ```
> ![uvスクロール](https://github.com/kataoka1002/KSM3/assets/122655580/18322fb1-ab7a-47b0-9c97-9ee91e803c5b)
> *2.* それを実行した結果がこちら。<br />
> ![uv_AdobeExpress](https://github.com/kataoka1002/KSM3/assets/122655580/ae133047-fc0d-438e-91ec-022eb2b64637)
