#pragma pack_matrix(row_major)

Texture2D mainTexture : register(t0);
SamplerState aSampler : register(s0);

cbuffer CamData : register(b0)
{
    float4x4 View;
    float4x4 Projection;
}

cbuffer WorldData : register(b1)
{
    float4x4 World;
    float2 textureRect;
    float2 imageRectSize;
    float2 imageRectPos;
}

//--------------------------------------------------------------------------------------
struct VS_INPUT
{
    float3 Pos : POSITION; // 3D position of the sprite model
    float2 Tex : TEXCOORD; // UV coordinates
};

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.Pos = float4(float2(input.Pos.xy * imageRectSize), 0.0f, 1.0f);
    output.Pos = mul(output.Pos, World);
    
    output.Pos = mul(output.Pos, View);
    output.Pos = mul(output.Pos, Projection);
    
    output.Tex = input.Tex;
    output.Tex *= imageRectSize / textureRect;
    output.Tex += imageRectPos / textureRect;
    return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT input) : SV_Target
{
    return mainTexture.Sample(aSampler, input.Tex); // Sampling the texture directly
}
