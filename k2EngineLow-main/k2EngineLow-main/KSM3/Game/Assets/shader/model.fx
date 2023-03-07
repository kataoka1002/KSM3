/*!
 * @brief	シンプルなモデルシェーダー。
 */

////////////////////////////////////////////////
// ライト構造体
////////////////////////////////////////////////
struct DirectionLight
{
    float3 dirDirection;	//ディレクションライトの方向
    float3 dirColor;		//ディレクションライトのカラー
};
struct PointLight
{
    float3 ptPosition;	//ポイントライトの位置
    float3 ptColor;		//ポイントライトのカラー
    float  ptRange;		//ポイントライトの影響範囲
};
struct SpotLight
{
    float3 spPosition;		//スポットライトの位置
    float3 spColor;			//スポットライトのカラー
	float  spRange;			//スポットライトの射出範囲
    float3 spDirection;		//スポットライトの射出方向
    float  spAngle;			//スポットライトの射出角度
};

////////////////////////////////////////////////
// 定数バッファ。
////////////////////////////////////////////////
//モデル用の定数バッファ
cbuffer ModelCb : register(b0){
	float4x4 mWorld;
	float4x4 mView;
	float4x4 mProj;
};
//ディレクションライト用の定数バッファ
cbuffer DirectionLightCb : register(b1) {
	//ディレクションライト用
    DirectionLight directionLight;
	
	//ライト用
	float3 eyePos;			//視点のデータ
    float3 ambientLight;	//アンビエントライトの強さ
	
	//ポイントライト用
    PointLight pointLight;
	
	//スポットライト用
    SpotLight spotLight;
}

////////////////////////////////////////////////
// 構造体
////////////////////////////////////////////////
//スキニング用の頂点データをひとまとめ。
struct SSkinVSIn{
	int4  Indices  	: BLENDINDICES0;
    float4 Weights  : BLENDWEIGHT0;
};
//頂点シェーダーへの入力。
struct SVSIn{
	float4 pos 		: POSITION;		//モデルの頂点座標。
	float2 uv 		: TEXCOORD0;	//UV座標。
	float3 normal	: NORMAL;		//法線
	SSkinVSIn skinVert;				//スキン用のデータ。
};
//ピクセルシェーダーへの入力。
struct SPSIn{
	float4 pos 			: SV_POSITION;	//スクリーン空間でのピクセルの座標。
	float2 uv 			: TEXCOORD0;	//uv座標。
	float3 worldPos		: TEXCOORD1;	//ワールド座標
	float3 normal		: NORMAL;		//法線
    float3 normalInView : TEXCOORD2;	//カメラ空間の法線
};

////////////////////////////////////////////////
// グローバル変数。
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0);				//アルベドマップ
StructuredBuffer<float4x4> g_boneMatrix : register(t3);	//ボーン行列。
sampler g_sampler : register(s0);	//サンプラステート。

////////////////////////////////////////////////
// 関数定義。
////////////////////////////////////////////////
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal);
float3 CalcLigFromDirectionLight(SPSIn psIn);
float3 CalcLigFromPointLight(SPSIn psIn);
float3 CalcLigFromSpotLight(SPSIn psIn);
float3 CalcLimPower(SPSIn psIn);

/// <summary>
//スキン行列を計算する。
/// </summary>
float4x4 CalcSkinMatrix(SSkinVSIn skinVert)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
        w += skinVert.Weights[i];
    }
    
    skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);
	
    return skinning;
}

/// <summary>
/// 頂点シェーダーのコア関数。
/// </summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
	SPSIn psIn;
	float4x4 m;
	if( hasSkin ){
		m = CalcSkinMatrix(vsIn.skinVert);
	}else{
		m = mWorld;
	}
    psIn.pos = mul(m, vsIn.pos); // モデルの頂点をワールド座標系に変換
    psIn.worldPos = psIn.pos;
    psIn.pos = mul(mView, psIn.pos); // ワールド座標系からカメラ座標系に変換
    psIn.pos = mul(mProj, psIn.pos); // カメラ座標系からスクリーン座標系に変換

	//頂点法線をピクセルシェーダーに渡す
	psIn.normal = mul(mWorld, vsIn.normal); //法線を回転させる
	psIn.uv = vsIn.uv;
	
    psIn.normalInView = mul(mView, psIn.normal);//カメラ空間の法線を求める

	return psIn;
}

/// <summary>
/// スキンなしメッシュ用の頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
	return VSMainCore(vsIn, false);
}
/// <summary>
/// スキンありメッシュの頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSSkinMain( SVSIn vsIn ) 
{
	return VSMainCore(vsIn, true);
}
/// <summary>
/// ピクセルシェーダーのエントリー関数。
/// </summary>
float4 PSMain(SPSIn psIn) : SV_Target0
{
	//ディレクションライト(鏡面拡散どっちも)によるライティングを計算
    float3 directionLig = CalcLigFromDirectionLight(psIn);
	
	// ポイントライト(鏡面拡散どっちも)によるライティングを計算
    float3 pointLig = CalcLigFromPointLight(psIn);
	
	//ディレクションライト(鏡面拡散どっちも)によるライティングを計算
    float3 spotLig = CalcLigFromSpotLight(psIn);
	
	//リムの計算
    float3 limColor = CalcLimPower(psIn);
	
	
	
	//ディレクションライト、ポイントライト、スポットライト、アンビエントライトを合算して最終的な光を求める
    float3 lig = directionLig + pointLig + ambientLight + spotLig;
	//最終的な反射光にリムの反射光を合算する
    lig += limColor;
	
	//テクスチャからカラーをフェッチ
    float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);

	//最終出力カラーに光を乗算する
    albedoColor.xyz *= lig;

    return albedoColor;
}


//ココから関数の定義
//////////////////////////////////////////////////////////////////////////////////////////////////////
//Lambert拡散反射光を計算する
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal)
{
	// ピクセルの法線とライトの方向の内積を計算する
	float t = dot(normal, lightDirection) * -1.0f;

	// 内積の値を0以上の値にする
	if (t < 0.0f)
	{
		t = 0.0f;
	}

	// 拡散反射光を計算する
	return lightColor * t;
}

//Phong鏡面反射光を計算する
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal)
{
	// 反射ベクトルを求める
	float3 refVec = reflect(lightDirection, normal);

	// 光が当たったサーフェイスから視点に伸びるベクトルを求める
	float3 toEye = eyePos - worldPos;
	toEye = normalize(toEye);

	// 鏡面反射の強さを求める
	float t = dot(refVec, toEye);

	// 鏡面反射の強さを0以上の数値にする
	if (t < 0.0f)
	{
		t = 0.0f;
	}

	// 鏡面反射の強さを絞る
	t = pow(t, 5.0f);

	// 鏡面反射光を求める
	return lightColor * t;
}

//ポイントライトによる反射光を計算する
float3 CalcLigFromDirectionLight(SPSIn psIn)
{
	//ディレクションライトによるLambert拡散反射光を計算する
    float3 diffDirection = CalcLambertDiffuse(directionLight.dirDirection, directionLight.dirColor, psIn.normal);
    //ディレクションライトによるPhong鏡面反射光を計算する
    float3 specDirection = CalcPhongSpecular(directionLight.dirDirection, directionLight.dirColor, psIn.worldPos, psIn.normal);

    return diffDirection + specDirection;
}

//ポイントライトによる反射光を計算する
float3 CalcLigFromPointLight(SPSIn psIn)
{
	// このサーフェイスに入射しているポイントライトの光の向きを計算する
    float3 ligDir = psIn.worldPos - pointLight.ptPosition;

    // 正規化して大きさ1のベクトルにする
    ligDir = normalize(ligDir);

    // 減衰なしのLambert拡散反射光を計算する
    float3 diffPoint = CalcLambertDiffuse(
        ligDir,				// ライトの方向
        pointLight.ptColor, // ライトのカラー
        psIn.normal			// サーフェイスの法線
    );

    // 減衰なしのPhong鏡面反射光を計算する
    float3 specPoint = CalcPhongSpecular(
        ligDir,				// ライトの方向
       pointLight.ptColor,	// ライトのカラー
        psIn.worldPos,		// サーフェイズのワールド座標
        psIn.normal			// サーフェイズの法線
    );

    // 距離による影響率を計算する
    // ポイントライトとの距離を計算する
    float3 distance = length(psIn.worldPos - pointLight.ptPosition);

    // 影響率は距離に比例して小さくなっていく
    float affect = 1.0f - 1.0f / pointLight.ptRange * distance;

    // 影響力がマイナスにならないように補正をかける
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }

    // 影響の仕方を指数関数的にする。今回のサンプルでは3乗している
    affect = pow(affect, 3.0f);

    // 拡散反射光と鏡面反射光に減衰率を乗算して影響を弱める
    diffPoint *= affect;
    specPoint *= affect;

    return diffPoint + specPoint;
}

//スポットライトによる反射光を計算する
float3 CalcLigFromSpotLight(SPSIn psIn)
{
	//サーフェイスに入射するスポットライトの光の向きを計算する
    float3 LigDir = psIn.worldPos - spotLight.spPosition;
	//正規化
    LigDir = normalize(LigDir);
	//減衰なしのLambert拡散反射光を計算する
    float3 diffSpot = CalcLambertDiffuse(
		LigDir,				//スポットライトの方向
		spotLight.spColor,	//スポットライトのカラー
		psIn.normal			//サーフェイスの法線
	);
	//減衰なしのPhong鏡面反射の計算
    float3 specSpot = CalcPhongSpecular(
		LigDir,				//ライトの方向
		spotLight.spColor,	//ライトのカラー
		psIn.worldPos,		//サーフェイスのワールド座標
		psIn.normal			//サーフェイスの法線
	);
	//スポットライトとの距離を計算する
    float distance = length(psIn.worldPos - spotLight.spPosition);
	//影響率は距離に比例して小さくなっていく
    float affect = 1.0f - 1.0f / spotLight.spRange * distance;
	//影響力がマイナスにならないように
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }
	//影響を指数関数的にする
    affect = pow(affect, 3.0f);
	//拡散反射光と鏡面反射光に減衰率を乗算して影響を弱める
    diffSpot *= affect;
    specSpot *= affect;
	//入射光と射出方向の角度を求める
    float angle = dot(LigDir, spotLight.spDirection);
	//dot()で求めた値をacos()に渡して角度を求める
    angle = abs(acos(angle));
	//角度に比例して小さくなっていく影響率を計算する
    affect = 1.0f - 1.0f / spotLight.spAngle * angle;
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }
	//影響を指数関数的にする
    affect = pow(affect, 0.5f);
	//角度による影響率を反射光に乗算して、影響を弱める
    diffSpot *= affect;
    specSpot *= affect;
	
    return diffSpot + specSpot;
}

float3 CalcLimPower(SPSIn psIn)
{
	//サーフェイスの法線と光の入射方向に依存するリムの強さを求める
    float power1 = 1.0f - max(0.0f, dot(directionLight.dirDirection, psIn.normal));
	//サーフェイスの法線と視線の方向に依存するリムの強さを求める
    float power2 = 1.0f - max(0.0f, psIn.normalInView.z * -1.0f);
	//最終的なリムの強さを求める
    float limPower = power1 * power2;
	//pow()を使用し強さの変化を指数関数的にする
    limPower = pow(limPower, 1.3f);
	
	//リムライトのカラーを計算し、返す
    return limPower * directionLight.dirColor;
}
/////////////////////////////////////////////////////////////////////////////////////////////////