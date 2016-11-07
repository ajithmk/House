cbuffer MATRIX : register(b0)
{
	matrix model_matrix;
	matrix view_matrix;
	matrix proj_matrix;
	float4 Cam_Pos;
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
	float2 tex_coord : TEXCOORD;
	float3 lightDir : LIGHTDIR;
	float3 viewDir : VIEWDIR;
	float3 normal : NORMAL;
};

VS_OUTPUT VS(VS_INPUT vs_in)
{
	VS_OUTPUT vs_out;
	vs_out.tex_coord = vs_in.tex_coord;
	vs_out.pos = mul(mul(mul(vs_in.pos, model_matrix), view_matrix), proj_matrix);
	float3 temp = (float3)(light_pos - vs_in.pos);
	float3 temp1 = (float3)(Cam_Pos - vs_in.pos);
	float3 bitangent = cross(vs_in.normal, (float3)vs_in.tangent)*vs_in.tangent.w;
	float3x3 tbn = { (float3)vs_in.tangent, bitangent, vs_in.normal };
	vs_out.lightDir = mul(tbn,temp);
	vs_out.viewDir = mul(tbn,temp1);
	//vs_out.lightDir = mul(temp, transpose(tbn));
	//vs_out.lightDir = float3(dot((float3)vs_in.tangent, temp), dot(bitangent, temp), dot(vs_in.normal, temp));
	//vs_out.viewDir = float3(dot((float3)vs_in.tangent, temp1), dot(bitangent, temp1), dot(vs_in.normal, temp1));
	vs_out.normal = vs_in.normal;
	return vs_out;
}


Texture2D<float3> diffusemap : register(t0);
Texture2D<float3> normalmap : register(t1);
Texture2D<float3> heightmap : register(t2);
SamplerState sample : register(s0);

float2 ParallaxMap(float2 coord, float3 dir)
{
	dir.y = -dir.y;
	const float minLayers = 8;
	const float maxLayers = 32;
	float numLayers = lerp(minLayers, maxLayers, abs(dot(float3(0.0, 0.0, 1.0), dir)));
	float layerDepth = 1.0 / numLayers;
	float currentLayerDepth = 0.0;
	float2 P = (dir.xy * 0.1) - 0.01;
	float2 deltaTexCoords = P / numLayers;
	float2 currentTexCoords = coord;
	float currentDepthMapValue = heightmap.Sample(sample, coord).r;
	[unroll(32)] while (currentLayerDepth < currentDepthMapValue)
	{
		currentTexCoords -= deltaTexCoords;
		currentDepthMapValue = heightmap.Sample(sample, currentTexCoords).r;
		currentLayerDepth += layerDepth;
	}
	float2 prevTexCoords = currentTexCoords + deltaTexCoords;
	float afterDepth = currentDepthMapValue - currentLayerDepth;
	float beforeDepth = heightmap.Sample(sample, prevTexCoords).r - currentLayerDepth + layerDepth;
	float weight = afterDepth / (afterDepth - beforeDepth);
	float2 finalTexCoords = prevTexCoords*weight + currentTexCoords*(1 - weight);
	return finalTexCoords;
}

float3 PS(VS_OUTPUT ps_in) : SV_Target
{
    float a = -0.00055319520678;
    float b = 0.113829880;
    float dist = length(ps_in.lightDir);
    float atten = 1/(0.1+b*(dist)+(dist*dist)*a);
    float2 pt_coord = ParallaxMap(ps_in.tex_coord,normalize(ps_in.viewDir));
    float3 color = diffusemap.Sample(sample,ps_in.tex_coord)*saturate(dot(normalize(2*(normalmap.Sample(sample,ps_in.tex_coord))-1),normalize(ps_in.lightDir)));
    //float3 color = diffusemap.Sample(sample,pt_coord)*saturate(dot(normalize(2*(normalmap.Sample(sample,pt_coord))-1),normalize(ps_in.lightDir)));
    //float3 color = diffusemap.Sample(sample,pt_coord);
    return color;
}