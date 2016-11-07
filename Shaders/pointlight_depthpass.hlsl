cbuffer MATRIX : register(b0)
{
matrix view_matrix;
matrix proj_matrix;
};
struct VS_INPUT
{
float4 pos : POSITION;
float4 tangent : TANGENT;
float3 normal : NORMAL;
float2 tex_coord : TEXCOORD;
}vs_in;
struct VS_OUTPUT
{
float4 pos : SV_Position;
};

VS_OUTPUT VS(VS_INPUT vs_in)
{
VS_OUTPUT vs_out;
vs_out.pos = mul(mul(vs_in.pos,view_matrix),proj_matrix);
return vs_out;
}

void PS(VS_OUTPUT vs_out)
{
float f=0;
}