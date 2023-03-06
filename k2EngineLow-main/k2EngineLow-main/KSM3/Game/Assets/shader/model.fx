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
    float ptRange;		//ポイントライトの影響範囲
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
	float3 eyePos;				//視点のデータ
    float3 ambientLight;		//アンビエントライトの強さ
	//ポイントライト用
    PointLight pointLight;
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
	//ディレクションライトによるLambert拡散反射光を計算する
   float3 diffDirection = CalcLambertDiffuse(directionLight.dirDirection, directionLight.dirColor, psIn.normal);
   //ディレクションライトによるPhong鏡面反射光を計算する
   float3 specDirection = CalcPhongSpecular(directionLight.dirDirection, directionLight.dirColor, psIn.worldPos, psIn.normal);


	//ポイントライトゾーン
	/////////////////////////////////////////////////////
	//サーフェイスに入射するポイントライトの光の向きを計算する
    float3 ptLigDir = psIn.worldPos - pointLight.ptPosition;
	//正規化
	ptLigDir = normalize(ptLigDir);
	//減衰なしのLambert拡散反射光を計算する
    float3 diffPoint = CalcLambertDiffuse(
		ptLigDir,			//ポイントライトの方向
		pointLight.ptColor, //ポイントライトのカラー
		psIn.normal			//サーフェイスの法線
	);
	//減衰なしのPhong鏡面反射の計算
    float3 specPoint = CalcPhongSpecular(
		ptLigDir,			//ライトの方向
		pointLight.ptColor, //ライトのカラー
		psIn.worldPos,		//サーフェイスのワールド座標
		psIn.normal			//サーフェイスの法線
	);
	//ポイントライトとの距離を計算する
    float distance = length(psIn.worldPos - pointLight.ptPosition);
	//影響率は距離に比例して小さくなっていく
    float affect = 1.0f - 1.0f / pointLight.ptRange * distance;
	//影響力がマイナスにならないように
	if (affect < 0.0f)
	{
		affect = 0.0f;
	}
	//影響を指数関数的にする
	affect = pow(affect, 3.0f);
	//拡散反射光と鏡面反射光に減衰率を乗算して影響を弱める
	diffPoint *= affect;
	specPoint *= affect;
	/////////////////////////////////////////////////////
	

	//2つの反射光を合算して最終的な反射光を求める
	float3 diffuseLig = diffPoint + diffDirection;
    float3 specularLig = specPoint + specDirection;
	//拡散反射光と鏡面反射光と環境光を足して最終的な光を求める
    float3 lig = diffuseLig + specularLig + ambientLight;
	

	//テクスチャからカラーをフェッチ
	float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);

	//最終出力カラーに光を乗算する
	albedoColor.xyz *= lig;

	return albedoColor;
}


//ココから関数の定義
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
