#pragma pack_matrix( row_major )

Texture2D mainTexture : register(t0);

SamplerState aSampler : register(s0);

static const int MAX_DIR_LIGHTS = 2;
static const int MAX_POINT_LIGHTS = 16;
static const int MAX_SPOT_LIGHTS = 16;

// Material properties
struct Material
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;  // Hack: w holds the specular power
    float scale;
};

// Light properties
struct PhongADS
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
};

// Basic Phong Illumination computation
void PhongModel(
	Material mat,
	PhongADS lightint,
	float3 L,
	float3 normal,
	float3 DirToEye,
	out float4 ambient,
	out float4 diffuse,
	out float4 spec
)
{
	// every light source adds to the ambient light total
	ambient = mat.Ambient * lightint.Ambient;

	float diffuseFactor = dot(L, normal);

	// Diffuse and specular contribution only if not facing away from light source
	if (diffuseFactor > 0.0f)
	{
		diffuse = diffuseFactor * mat.Diffuse * lightint.Diffuse;

		float3 r = reflect( -L, normal);		// Compute the reflected ray of light
		float spec_val = max(dot(r, DirToEye.xyz), 0);
		float specFactor = pow(spec_val, mat.Specular.w);
		spec = specFactor * mat.Specular * lightint.Specular;
	}
	else
	{
		diffuse = float4(0, 0, 0, 0);
		spec = float4(0, 0, 0, 0);
	}
}

// Directional Light Data
struct DirectionalLight
{
	PhongADS LightInt;
	float4 Direction;
};

// Point Light data
struct PointLight
{
	PhongADS LightInt;
	float4 Position;
	float4 Attenuation;
	float Range;
};

// Spot light data
struct SpotLight
{
	PhongADS LightInt;
	float4 Position;
	float4 Attenuation;
	float4 Direction;
	float SpotExp;
	float Range;
};

//  Constant Buffers
cbuffer CamData : register(b0)
{
	float4x4 View;
	float4x4 Projection;
};

cbuffer LightParameters : register(b1)
{
    DirectionalLight DirLight[MAX_DIR_LIGHTS];
    PointLight PntLight[MAX_POINT_LIGHTS];
    SpotLight SpLight[MAX_SPOT_LIGHTS];
    float4 EyePosWorld;
};

cbuffer InstanceData : register(b2)
{
	float4x4 World;
	float4x4 WorldInv;
	Material Mater;
};

cbuffer FogData : register(b3)
{
    float FogStart;
    float FogRange;
    float4 FogColor;
}

// Directional Light Computation
void ComputeDirectionalLight(
	Material mat,
	DirectionalLight DirLit,
	float4 normal,
	float4 DirToEye,
	out float4 ambient,
	out float4 diffuse,
	out float4 spec
)
{
	// Zeroing out the initial ADS contributions
	ambient = float4(0, 0, 0, 0);
	diffuse = float4(0, 0, 0, 0);
	spec = float4(0, 0, 0, 0);

	// we compute ligth in the model-space 
	// For directional light, the source is infinitely far, so translation have no effect
	float3 L = normalize(mul(-DirLit.Direction.xyz, (float3x3)WorldInv));

	PhongModel(mat, DirLit.LightInt, L, normal.xyz, DirToEye.xyz, ambient, diffuse, spec);
}

// Point Light Computation
void ComputePointLight(
	Material mat,
	PointLight PLight,
	float4 posms,
	float4 normal,
	float4 DirToEye,
	out float4 ambient,
	out float4 diffuse,
	out float4 spec
)
{
	// Zeroing out the ADS contributions
	ambient = float4(0, 0, 0, 0);
	diffuse = float4(0, 0, 0, 0);
	spec = float4(0, 0, 0, 0);

	// we compute the model-space position
	float3 litPosMS = mul(PLight.Position, WorldInv).xyz;
	float3 L = litPosMS - posms.xyz;
    L *= Mater.scale;

	// Early out if out of range
	float d = length(L);
	if (d > PLight.Range)
		return;

	L /= d;	// normalize 

	PhongModel(mat, PLight.LightInt, L, normal.xyz, DirToEye.xyz, ambient, diffuse, spec);

	// Now we attenuate based on range
	float att = 1 / dot(PLight.Attenuation.xyz, float3(1,d, d*d) );
	// Ambient not attenuated
	diffuse *= att;
	spec *= att;
}

// Spot Light Computation
void ComputeSpotLight(
	Material mat,
	SpotLight SptLight,
	float4 posms,
	float4 normal,
	float4 DirToEye,
	out float4 ambient,
	out float4 diffuse,
	out float4 spec
)
{
	// Zeroing out the ADS contributions
	ambient = float4(0, 0, 0, 0);
	diffuse = float4(0, 0, 0, 0);
	spec = float4(0, 0, 0, 0);

	// ****** Same calculations as Point Light  ****

	// we compute the model-space position
	float3 litPosMS = mul(SptLight.Position, WorldInv).xyz;
    float3 L = litPosMS - posms.xyz;
    L *= Mater.scale;

	float d = length(L);
	if (d > SptLight.Range)
		return;

	L /= d;  // normalize 

	PhongModel(mat, SptLight.LightInt, L, normal.xyz, DirToEye.xyz, ambient, diffuse, spec);

	// Now we attenuate based on range
	float att = 1 / dot(SptLight.Attenuation.xyz, float3(1, d, d*d));

	// Ambient not attenuated
	diffuse *= att;
	spec *= att;

	// *****************************************

	// now we compute the spotlight factor
	float4 msLitDir = SptLight.Direction;
	msLitDir.w = 0; // making sure we have a vector and not a point
	msLitDir = normalize(mul(msLitDir, WorldInv));
	float spot = pow(max(dot(-L, msLitDir.xyz), 0), SptLight.SpotExp);

	ambient *= spot;
	diffuse *= spot;
	spec *= spot;
}



// ******* Shader operations

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION; // 0
	float4 PosMS : POSITION;  // 16
    float2 Tex : TEXCOORD;    // 32
	float4 Norm : NORMAL;	  // 40
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS( float3 Pos : POSITION, float2 Tex : TEXCOORD, float3 nor : NORMAL )
{
    float4 expandedPos;
    expandedPos.x = Pos.x;
    expandedPos.y = Pos.y;
    expandedPos.z = Pos.z;
    expandedPos.w = 1.0f;
	
    float4 expandedNor;
    expandedNor.x = nor.x;
    expandedNor.y = nor.y;
    expandedNor.z = nor.z;
    expandedNor.w = 0.0f;
	
    VS_OUTPUT output;
    output.PosMS = expandedPos; // We pass along the raw model space position 
	output.Norm = expandedNor;	 // and the face normal

    output.Pos = mul( expandedPos, World );
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );
    output.Tex = Tex;

    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( VS_OUTPUT input ) : SV_Target
{
	// Compute light values in model-space
	float4 msEyePos = mul(EyePosWorld, WorldInv);
	float4 msDirToEye = normalize(msEyePos - input.PosMS);

	float4 ambient	= float4(0, 0, 0, 0);
	float4 diffuse	= float4(0, 0, 0, 0);
	float4 spec		= float4(0, 0, 0, 0);

    float4 A, D, S;
		
		
    for (int i = 0; i < MAX_DIR_LIGHTS; i++)
    {
        ComputeDirectionalLight(Mater, DirLight[i], normalize(input.Norm), msDirToEye, A, D, S);

        ambient += A;
        diffuse += D;
        spec += S;
    }
	
    for (int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
        ComputePointLight(Mater, PntLight[i], input.PosMS, normalize(input.Norm), msDirToEye, A, D, S);

        ambient += A;
        diffuse += D;
        spec += S;
    }
	
    for (int i = 0; i < MAX_SPOT_LIGHTS; i++)
    {        
        ComputeSpotLight(Mater, SpLight[i], input.PosMS, normalize(input.Norm), msDirToEye, A, D, S);

        ambient += A;
        diffuse += D;
        spec += S;
    }

	float4 litColor = ambient + diffuse + spec;

    // return litColor;
    // return mainTexture.Sample(aSampler, input.Tex);
    // return mainTexture.Sample(aSampler, input.Tex) * litColor;
	
    litColor = mainTexture.Sample(aSampler, input.Tex) * litColor;
	
	// Compute fog density as function of distance to eye
	if (Mater.scale <= 0.0f)
        return litColor * 0.0f;
	
    float fogStart = FogStart / Mater.scale;
    float fogRange = FogRange / Mater.scale;
    
    
	float distToEye = length(msEyePos - input.PosMS);
    float FogPercent = saturate((distToEye - fogStart) / fogRange); // See https://msdn.microsoft.com/en-us/library/windows/desktop/bb509645(v=vs.85).aspx
	
	// blend litColor with fog level
    litColor = litColor * (1 - FogPercent) + FogColor * FogPercent;
	
    return litColor;
}
