/*!
 * @brief	�V���v���ȃ��f���V�F�[�_�[�B
 */

////////////////////////////////////////////////
// ���C�g�\����
////////////////////////////////////////////////
struct DirectionLight
{
    float3 dirDirection; //�f�B���N�V�������C�g�̕���

    float3 dirColor; //�f�B���N�V�������C�g�̃J���[
    
};
struct PointLight
{
    float3 ptPosition; //�|�C���g���C�g�̈ʒu
    float3 ptColor; //�|�C���g���C�g�̃J���[

    float ptRange; //�|�C���g���C�g�̉e���͈�
};
struct SpotLight
{
    float3 spPosition; //�X�|�b�g���C�g�̈ʒu
    float3 spColor; //�X�|�b�g���C�g�̃J���[
    float spRange; //�X�|�b�g���C�g�̎ˏo�͈�
    float3 spDirection; //�X�|�b�g���C�g�̎ˏo����
    float spAngle; //�X�|�b�g���C�g�̎ˏo�p�x
};
struct HemLight
{
    float3 heGroundColor; //�Ƃ�Ԃ��̃��C�g
 
    float3 heSkyColor; //�V�����C�g

    float3 heGroundNormal; //�n�ʂ̖@��
};

////////////////////////////////////////////////
// �萔�o�b�t�@�B
////////////////////////////////////////////////
//���f���p�̒萔�o�b�t�@
cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};
// ���C�g�r���[�v���W�F�N�V�����s��ɃA�N�Z�X����萔�o�b�t�@�[���`
//cbuffer ShadowCb : register(b1)
//{
//float4x4 mLVP;
//};
//�f�B���N�V�������C�g�p�̒萔�o�b�t�@
cbuffer directionLightCb : register(b1)
{
    /*
	//�f�B���N�V�������C�g�p
    DirectionLight directionLight;

	//���C�g�p
    float3 eyePos; //���_�̃f�[�^

    float3 ambientLight; //�A���r�G���g���C�g�̋���
   	
	//�|�C���g���C�g�p
    PointLight pointLight;
	
	//�X�|�b�g���C�g�p
    SpotLight spotLight;
	
	//�������C�g�p
    HemLight hemLight;
*/
    
    float4x4 mLVP;
}




////////////////////////////////////////////////
// �\����
////////////////////////////////////////////////
//�X�L�j���O�p�̒��_�f�[�^���ЂƂ܂Ƃ߁B
struct SSkinVSIn
{
    int4 Indices : BLENDINDICES0;
    float4 Weights : BLENDWEIGHT0;
};
//���_�V�F�[�_�[�ւ̓��́B
struct SVSIn
{
    float4 pos : POSITION; //���f���̒��_���W�B
    float2 uv : TEXCOORD0; //UV���W�B
    float3 tangent : TANGENT;
    float3 biNormal : BINORMAL;
    float3 normal : NORMAL; //�@��
    SSkinVSIn skinVert; //�X�L���p�̃f�[�^�B
};
//�s�N�Z���V�F�[�_�[�ւ̓��́B
struct SPSIn
{
    float4 pos : SV_POSITION;       //�X�N���[����Ԃł̃s�N�Z���̍��W�B
    float2 uv : TEXCOORD0;          //uv���W�B
    float3 worldPos : TEXCOORD1;    //���[���h���W
    float3 normal : NORMAL;         //�@��
    float3 tangent : TANGENT;       //�ڃx�N�g��
    float3 biNormal : BINORMAL;     //�]�x�N�g��
    float3 normalInView : TEXCOORD2;//�J������Ԃ̖@��
    float4 posInLVP : TEXCOORD3;    //
};

////////////////////////////////////////////////
// �O���[�o���ϐ��B
////////////////////////////////////////////////
Texture2D<float4> g_albedo : register(t0); //�A���x�h�}�b�v
Texture2D<float4> g_normalMap : register(t1); //�@���}�b�v�ɃA�N�Z�X���邽�߂̕ϐ���ǉ�
Texture2D<float4> g_specularMap : register(t2); //�X�y�L�����[�}�b�v�ɃA�N�Z�X���邽�߂̕ϐ���ǉ�
StructuredBuffer<float4x4> g_boneMatrix : register(t3); //�{�[���s��B
sampler g_sampler : register(s0); //�T���v���X�e�[�g�B
Texture2D<float4> g_shadowMap : register(t10); // �V���h�E�}�b�v


////////////////////////////////////////////////
// �֐���`�B
////////////////////////////////////////////////
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal);
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal);
float3 CalcLigFromDirectionLight(SPSIn psIn);
float3 CalcLigFromPointLight(SPSIn psIn);
float3 CalcLigFromSpotLight(SPSIn psIn);
float3 CalcLimPower(SPSIn psIn);
float3 CalcLigFromHemLight(SPSIn psIn);
float3 CalcNormalCalcNormal(float3 normal, float3 tangent, float3 biNormal, float2 uv);
float3 CalcNormalMap(SPSIn psIn);
float3 CalcSpecularMap(SPSIn psIn);

/// <summary>
//�X�L���s����v�Z����B
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
/// ���_�V�F�[�_�[�̃R�A�֐��B
/// </summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
    SPSIn psIn;
    
    float4x4 m;
    if (hasSkin)
    {
        m = CalcSkinMatrix(vsIn.skinVert);
    }
    else
    {
        m = mWorld;
    }
    //�V���h�E�̌v�Z�p���[���h���W
    float4 s_worldPos = mul(m, vsIn.pos);
    //psIn.pos = mul(m, vsIn.pos); // ���f���̒��_�����[���h���W�n�ɕϊ�
    //psIn.worldPos = psIn.pos;
    psIn.pos = mul(mView, s_worldPos); // ���[���h���W�n����J�������W�n�ɕϊ�
    psIn.pos = mul(mProj, psIn.pos); // �J�������W�n����X�N���[�����W�n�ɕϊ�

	//���_�@�����s�N�Z���V�F�[�_�[�ɓn��
    psIn.normal = normalize(mul(mWorld, vsIn.normal)); //�@������]������
    //�ڃx�N�g���Ə]�x�N�g�������[���h��Ԃɕϊ�����
    psIn.tangent = normalize(mul(mWorld, vsIn.tangent));
    psIn.biNormal = normalize(mul(mWorld, vsIn.biNormal));

    psIn.uv = vsIn.uv;
	    
    psIn.posInLVP = mul(mLVP, s_worldPos); //���C�g�r���[�X�N���[����Ԃ̍��W���v�Z����
    psIn.normalInView = mul(mView, psIn.normal); //�J������Ԃ̖@�������߂�
    
    return psIn;
}


// �X�L���Ȃ����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�֐��B
SPSIn VSMain(SVSIn vsIn)
{
    return VSMainCore(vsIn, false);
}
// �X�L�����胁�b�V���̒��_�V�F�[�_�[�̃G���g���[�֐��B
SPSIn VSSkinMain(SVSIn vsIn)
{
    return VSMainCore(vsIn, true);
}
//// �V���h�E���f���̒��_�V�F�[�_�[�̃G���g���[�֐�
//float4 PSShadowMain(SPSIn psIn) : SV_Target0
//{
//    // �V���h�E�}�b�v��Z�l��`������
//    return float4(psIn.pos.z, psIn.pos.z, psIn.pos.z, 1.0f);
//}

/// �s�N�Z���V�F�[�_�[�̃G���g���[�֐��B
float4 PSMain(SPSIn psIn) : SV_Target0
{
    //float3 lig = 3.0f;
	//�f�B���N�V�������C�g(���ʊg�U�ǂ�����)�ɂ�郉�C�e�B���O���v�Z
    //float3 directionLig = CalcLigFromDirectionLight(psIn);
	
	//�|�C���g���C�g(���ʊg�U�ǂ�����)�ɂ�郉�C�e�B���O���v�Z
    //float3 pointLig = CalcLigFromPointLight(psIn);
	
	//�X�|�b�g���C�g(���ʊg�U�ǂ�����)�ɂ�郉�C�e�B���O���v�Z
   // float3 spotLig = CalcLigFromSpotLight(psIn);
	
	//�����̌v�Z
    //float3 limColor = CalcLimPower(psIn);
	
	//�������C�g�̌v�Z
    //float3 hemLig = CalcLigFromHemLight(psIn);
	
	//�@���}�b�v�̌v�Z
    //float3 normalMap = CalcNormalMap(psIn);
    
    //�X�y�L�����[�}�b�v�̌v�Z
    //float3 specularMap = CalcSpecularMap(psIn);
    
	
	//�f�B���N�V�������C�g�A�|�C���g���C�g�A�X�|�b�g���C�g�A
	//�A���r�G���g���C�g�A�������C�g�A�@���}�b�v�A�X�y�L�����}�b�v�����Z���čŏI�I�Ȍ������߂�
    //float3 lig = directionLig+pointLig + ambientLight + spotLig + hemLig + normalMap + specularMap;
	//�ŏI�I�Ȕ��ˌ��Ƀ����̔��ˌ������Z����
    //lig += limColor;
	
	//�e�N�X�`������J���[���t�F�b�`
    float4 albedoColor = g_albedo.Sample(g_sampler, psIn.uv);

    
    //�V���h�E�̏���
    /////////////////////////////////////////////////////////////////////////////
    // ���C�g�r���[�X�N���[����Ԃ���UV��Ԃɍ��W�ϊ�
    float2 shadowMapUV = psIn.posInLVP.xy / psIn.posInLVP.w;
    shadowMapUV *= float2(0.5f, -0.5f);
    shadowMapUV += 0.5f;

    // ���C�g�r���[�X�N���[����Ԃł�Z�l���v�Z����
    float zInLVP = psIn.posInLVP.z / psIn.posInLVP.w;

    
    if (shadowMapUV.x > 0.0f && shadowMapUV.x < 1.0f
        && shadowMapUV.y > 0.0f && shadowMapUV.y < 1.0f)
    {
        // �V���h�E�}�b�v�ɕ`�����܂�Ă���Z�l�Ɣ�r����
        // �v�Z����UV���W���g���āA�V���h�E�}�b�v����[�x�l���T���v�����O
        float zInShadowMap = g_shadowMap.Sample(g_sampler, shadowMapUV).r;
        //a = zInShadowMap;
        //a = zInLVP;
        if (zInLVP > zInShadowMap)
        {
            // �Օ�����Ă���
            albedoColor.xyz *= 0.5f;
            
            //albedoColor.x = 1.0f;
            //albedoColor.y = 0.0f;
            //albedoColor.z = 0.0f; 
            //lig *= 0.5f;
        }
        //lig *= 0.5f;
    }
    /////////////////////////////////////////////////////////////////////////////
    
    
	//�ŏI�o�̓J���[�Ɍ�����Z����
    //albedoColor.xyz *= lig;
    //albedoColor.xyz = a;
    return albedoColor;
}


//�R�R����֐��̒�`
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Lambert�g�U���ˌ����v�Z����


/*
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal)
{
	// �s�N�Z���̖@���ƃ��C�g�̕����̓��ς��v�Z����
    float t = dot(normal, lightDirection) * -1.0f;
	// ���ς̒l��0�ȏ�̒l�ɂ���
    if (t < 0.0f)
    {
        t = 0.0f;
    }

	// �g�U���ˌ����v�Z����
    return lightColor * t;
}

//Phong���ʔ��ˌ����v�Z����
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal)
{
	// ���˃x�N�g�������߂�
    float3 refVec = reflect(lightDirection, normal);

	// �������������T�[�t�F�C�X���王�_�ɐL�т�x�N�g�������߂�
    float3 toEye = eyePos - worldPos;
    toEye = normalize(toEye);

	// ���ʔ��˂̋��������߂�
    float t = dot(refVec, toEye);
	// ���ʔ��˂̋�����0�ȏ�̐��l�ɂ���
    if (t < 0.0f)
    {
        t = 0.0f;
    }

	// ���ʔ��˂̋������i��
    t = pow(t, 5.0f);

	// ���ʔ��ˌ������߂�
    return lightColor * t;
}

//�|�C���g���C�g�ɂ�锽�ˌ����v�Z����
float3 CalcLigFromDirectionLight(SPSIn psIn)
{
	//�f�B���N�V�������C�g�ɂ��Lambert�g�U���ˌ����v�Z����
    float3 diffDirection = CalcLambertDiffuse(directionLight.dirDirection, directionLight.dirColor, psIn.normal);
    //�f�B���N�V�������C�g�ɂ��Phong���ʔ��ˌ����v�Z����
    float3 specDirection = CalcPhongSpecular(directionLight.dirDirection, directionLight.dirColor, psIn.worldPos, psIn.normal);

    return diffDirection + specDirection;
}

//�|�C���g���C�g�ɂ�锽�ˌ����v�Z����
float3 CalcLigFromPointLight(SPSIn psIn)
{
	// ���̃T�[�t�F�C�X�ɓ��˂��Ă���|�C���g���C�g�̌��̌������v�Z����
    float3 ligDir = psIn.worldPos - pointLight.ptPosition;

    // ���K�����đ傫��1�̃x�N�g���ɂ���
    ligDir = normalize(ligDir);

    // �����Ȃ���Lambert�g�U���ˌ����v�Z����
    float3 diffPoint = CalcLambertDiffuse(
        ligDir, // ���C�g�̕���
        pointLight.ptColor, // ���C�g�̃J���[
        psIn.normal			// �T�[�t�F�C�X�̖@��
    );

    // �����Ȃ���Phong���ʔ��ˌ����v�Z����
    float3 specPoint = CalcPhongSpecular(
        ligDir, // ���C�g�̕���
       pointLight.ptColor, // ���C�g�̃J���[
        psIn.worldPos, // �T�[�t�F�C�Y�̃��[���h���W
        psIn.normal			// �T�[�t�F�C�Y�̖@��
    );

    // �����ɂ��e�������v�Z����
    // �|�C���g���C�g�Ƃ̋������v�Z����
    float3 distance = length(psIn.worldPos - pointLight.ptPosition);

    // �e�����͋����ɔ�Ⴕ�ď������Ȃ��Ă���
    float affect = 1.0f - 1.0f / pointLight.ptRange * distance;
    // �e���͂��}�C�i�X�ɂȂ�Ȃ��悤�ɕ␳��������
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }

    // �e���̎d�����w���֐��I�ɂ���B����̃T���v���ł�3�悵�Ă���
    affect = pow(affect, 3.0f);

    // �g�U���ˌ��Ƌ��ʔ��ˌ��Ɍ���������Z���ĉe������߂�
    diffPoint *= affect;
    specPoint *= affect;

    return diffPoint + specPoint;
}

//�X�|�b�g���C�g�ɂ�锽�ˌ����v�Z����
float3 CalcLigFromSpotLight(SPSIn psIn)
{
	//�T�[�t�F�C�X�ɓ��˂���X�|�b�g���C�g�̌��̌������v�Z����
    float3 LigDir = psIn.worldPos - spotLight.spPosition;
	//���K��
    LigDir = normalize(LigDir);
	//�����Ȃ���Lambert�g�U���ˌ����v�Z����
    float3 diffSpot = CalcLambertDiffuse(
		LigDir, //�X�|�b�g���C�g�̕���
		spotLight.spColor, //�X�|�b�g���C�g�̃J���[
		psIn.normal			//�T�[�t�F�C�X�̖@��
	);
	//�����Ȃ���Phong���ʔ��˂̌v�Z
    float3 specSpot = CalcPhongSpecular(
		LigDir, //���C�g�̕���
		spotLight.spColor, //���C�g�̃J���[
		psIn.worldPos, //�T�[�t�F�C�X�̃��[���h���W
		psIn.normal			//�T�[�t�F�C�X�̖@��
	);
	//�X�|�b�g���C�g�Ƃ̋������v�Z����
    float distance = length(psIn.worldPos - spotLight.spPosition);
	//�e�����͋����ɔ�Ⴕ�ď������Ȃ��Ă���
    float affect = 1.0f - 1.0f / spotLight.spRange * distance;
	//�e���͂��}�C�i�X�ɂȂ�Ȃ��悤��
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }
	//�e�����w���֐��I�ɂ���
    affect = pow(affect, 3.0f);
	//�g�U���ˌ��Ƌ��ʔ��ˌ��Ɍ���������Z���ĉe������߂�
    diffSpot *= affect;
    specSpot *= affect;
	//���ˌ��Ǝˏo�����̊p�x�����߂�
    float angle = dot(LigDir, spotLight.spDirection);
	//dot()�ŋ��߂��l��acos()�ɓn���Ċp�x�����߂�
    angle = abs(acos(angle));
	//�p�x�ɔ�Ⴕ�ď������Ȃ��Ă����e�������v�Z����
    affect = 1.0f - 1.0f / spotLight.spAngle * angle;
    if (affect < 0.0f)
    {
        affect = 0.0f;
    }
	//�e�����w���֐��I�ɂ���
    affect = pow(affect, 0.5f);
	//�p�x�ɂ��e�����𔽎ˌ��ɏ�Z���āA�e������߂�
    diffSpot *= affect;
    specSpot *= affect;
	
    return diffSpot + specSpot;
}

float3 CalcLimPower(SPSIn psIn)
{
	//�T�[�t�F�C�X�̖@���ƌ��̓��˕����Ɉˑ����郊���̋��������߂�
    float power1 = 1.0f - max(0.0f, dot(directionLight.dirDirection, psIn.normal));
	//�T�[�t�F�C�X�̖@���Ǝ����̕����Ɉˑ����郊���̋��������߂�
    float power2 = 1.0f - max(0.0f, psIn.normalInView.z * -1.0f);
	//�ŏI�I�ȃ����̋��������߂�
    float limPower = power1 * power2;
	//pow()���g�p�������̕ω����w���֐��I�ɂ���
    limPower = pow(limPower, 1.3f);
	
	//�������C�g�̃J���[���v�Z���A�Ԃ�
    return limPower * directionLight.dirColor;
}

float3 CalcLigFromHemLight(SPSIn psIn)
{
	//�T�[�t�F�C�X�̖@���ƒn�ʂ̖@���Ƃ̓��ς��v�Z����
    float t = dot(psIn.normal, hemLight.heGroundNormal);
	//���ς̌��ʂ�0�`1�͈̔͂ɕϊ�
    t = (t + 1.0f) / 2.0f;
	//�n�ʂƓV���F��⊮��t�Ő��`�⊮���A�Ԃ�
    return lerp(hemLight.heGroundColor, hemLight.heSkyColor, t);
}

float3 CalcNormal(float3 normal, float3 tangent, float3 biNormal, float2 uv)
{
    float3 binSpaceNormal = g_normalMap.SampleLevel(g_sampler, uv, 0.0f).xyz;
    binSpaceNormal = (binSpaceNormal * 2.0f) - 1.0f;
    
    float3 newNormal = tangent * binSpaceNormal.x + biNormal * binSpaceNormal.y + normal * binSpaceNormal.z;

    return newNormal;
}

float3 CalcNormalMap(SPSIn psIn)
{
    //�f�B�t���|�Y�}�b�v���T���v�����O
    float4 diffuseMap = g_albedo.Sample(g_sampler, psIn.uv);
    float3 normal = psIn.normal;
    //�@���}�b�v����^���W�F���g�X�y�[�X�̖@�����T���v�����O����
    float3 localNormal = g_normalMap.Sample(g_sampler, psIn.uv).xyz;
    //�^���W�F���g�X�y�[�X�̖@����0�`1�͈̔͂���-1�`1�͈̔͂ɕ�������
    localNormal = (localNormal - 0.5f) * 2.0f;
    //�^���W�F���g�X�y�[�X�̖@�������[���h�X�y�[�X�ɕϊ�����
    normal = psIn.tangent * localNormal.x
           + psIn.biNormal * localNormal.y
           + normal * localNormal.z;
    //�g�U���˂��v�Z���A�Ԃ�
    return max(0.0f, dot(normal, -directionLight.dirDirection)) * directionLight.dirColor;
}

float3 CalcSpecularMap(SPSIn psIn)
{
    //�f�B�t���[�Y�}�b�v���T���v�����O
    float4 diffuseMap = g_albedo.Sample(g_sampler, psIn.uv);
    //�m�[�}���}�b�v�����ɖ@�����v�Z
    float3 normal = CalcNormal(psIn.normal, psIn.tangent, psIn.biNormal, psIn.uv);
    //�g�U���ˌ����v�Z
    float3 diffuseLig = max(0.0f, dot(normal, -directionLight.dirDirection)) * directionLight.dirColor;
    
    //���ʔ��ˌ����v�Z
    //���˃x�N�g�������߂�
    float3 refVec = reflect(directionLight.dirDirection, normal);
    //�������������T�[�t�F�C�X���王�_�ɐL�т�x�N�g�������߂�
    float3 toEye = eyePos - psIn.worldPos;
    toEye = normalize(toEye);
    //���ʔ��˂̋��������߂�
    float t = saturate(dot(refVec, toEye));
    //���ʔ��˂̋������i��
    t = pow(t, 5.0f);
    //���ʔ��ˌ������߂�
    float3 specLig = directionLight.dirColor * t;
    
    //�X�y�L�����}�b�v����X�y�L�������˂̋������T���v�����O
    float specPower = g_specularMap.Sample(g_sampler, psIn.uv).r;
    //���ʔ��˂̋��������ʔ��ˌ��ɏ�Z����
    specLig *= specPower * 50.0f; // ���[ �����̔{���ύX�Ō�������ς��
    
    return specLig;
}
*/



///////////////////////////////////////////////////////////////////////////////////////////////////////////////