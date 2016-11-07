cbuffer MATRIX : register(b0)
{
matrix model_matrix;
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
float3 tex_coord : TEXCOORD;
};

VS_OUTPUT VS(VS_INPUT vs_in, in uint ID : SV_VertexID)
{
VS_OUTPUT vs_out;
float3 CubeVertices[4] = {float3(-1,-1,0.999),
                          float3(-1,1,0.999),
                          float3(1,-1,0.999),
                          float3(1,1,0.999)};
vs_out.pos = float4(CubeVertices[ID],1);
float3x3 onlyview_matrix = transpose((float3x3)(view_matrix));
vs_out.tex_coord = mul(CubeVertices[ID],onlyview_matrix);
return vs_out;
}

TextureCube<float3> cubemap : register(t1);
SamplerState sample : register(s0);
float3 PS(VS_OUTPUT vs_out) : SV_Target
{
float3 color = cubemap.Sample(sample,vs_out.tex_coord);
return color;
}