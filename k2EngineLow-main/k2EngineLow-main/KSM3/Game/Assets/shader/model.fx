/*!
 * @brief	シンプルなモデルシェーダー。
 */


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
	float3 ligDirection;		//ライトの方向
	float3 ligColor;			//ライトのカラー
	float3 eyePos;				//視点のデータにアクセスするための変数
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
	float3 worldPos		: TEXCOORD1;
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
	psIn.pos = mul(m, vsIn.pos);
	psIn.worldPos = vsIn.pos;
	psIn.pos = mul(mView, psIn.pos);
	psIn.pos = mul(mProj, psIn.pos);

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
	//拡散反射ゾーン
	//////////////////////////////////////////////////////
	//ピクセルの法線とライトの方向の内積を計算する
	float t = dot(psIn.normal,ligDirection);

	//内積結果に-1を乗算し、結果が0以下なら0にする
	t *= -1.0f;
	if (t < 0.0f)
	{
		t = 0.0f;
	}
	//ピクセルが受けている光を求める
	float3 diffuseLig = ligColor * t;
	//////////////////////////////////////////////////////


	//鏡面反射ゾーン
	////////////////////////////////////////////////////////
	//反射ベクトルを求める
	float3 refVec = reflect(ligDirection, psIn.normal);
	//光が当たったサーフェイスから視点に伸びるベクトルを求める
	float3 toEye = eyePos - psIn.worldPos;
	//正規化する
	toEye = normalize(toEye);
	//鏡面反射の強さを求め、結果がマイナスなら0にする
	t = dot(refVec, toEye);
	if (t < 0.0f)
	{
		t = 0.0f;
	}
	//鏡面反射の強さを絞る
	t = pow(t, 5.0f);
	//鏡面反射光を求める
	float3 specularLig = ligColor * t;
	///////////////////////////////////////////////////////

	
	//拡散反射光と鏡面反射光を足して最終的な光を求める
	float3 lig = diffuseLig + specularLig;

	//テクスチャからカラーをフェッチ
	float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);

	//ライトの効果を一律で底上げする。
	lig.x += 0.3f;
	lig.y += 0.3f;
	lig.z += 0.3f;

	//最終出力カラーに光を乗算する
	albedoColor.xyz *= lig;

	return albedoColor;
}
