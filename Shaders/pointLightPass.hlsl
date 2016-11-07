cbuffer MATRIX : register(b0)
{
matrix model_matrix;
matrix view_matrix;
matrix proj_matrix;
};
cbuffer LIGHT_POS : register(b1)
{
float4 light_pos;
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
float3 normal : NORMAL;
float2 tex_coord : TEXCOORD;
float4 frag_pos : FRAG;
float4 light_pos : LIGHT;
float4 cam_pos : CAMERA;
};

VS_OUTPUT VS(VS_INPUT vs_in)
{
VS_OUTPUT vs_out;
float4 world_pos = mul(vs_in.pos,model_matrix);
vs_out.normal = mul(vs_in.normal,(float3x3)model_matrix);
vs_out.tex_coord = vs_in.tex_coord;
vs_out.frag_pos = world_pos;
vs_out.pos = mul(mul(world_pos,view_matrix),proj_matrix);
vs_out.light_pos = light_pos;
vs_out.cam_pos = float4(view_matrix._41,view_matrix._42,view_matrix._43,1);
return vs_out;
}

cbuffer SHADOW_PROJ : register(b2)
{
matrix shadow_proj_matrix;
};
Texture2D<float3> diffusemap : register(t0);
TextureCube<float> shadowmap : register(t1);
SamplerState sample : register(s0);
SamplerState depthsample : register(s1);
float3 PS(VS_OUTPUT vs_out) : SV_Target
{
float4 vec = vs_out.frag_pos - vs_out.light_pos;
float projD = max(max(abs(vec.x),abs(vec.y)),abs(vec.z));
float3 dist_vec = (float3)vec;
float dist = length(dist_vec);
float a = -0.00055319520678;
float b = 0.113829880;
float atten = 1/(0.1+b*(dist)+(dist*dist)*a);
float s = shadowmap.Sample(depthsample,normalize(dist_vec));
float normalize_dist = (shadow_proj_matrix._33*projD + shadow_proj_matrix._43)/projD;
float3 color = diffusemap.Sample(sample,vs_out.tex_coord);
if (normalize_dist-0.00005<s)
{
return color*saturate(dot(normalize(vs_out.normal),normalize(-dist_vec)))*1;
}
else return color*0.2;
}