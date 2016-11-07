#ifndef UNICODE
#define UNICODE
#endif
#define OEMRESOURCE
#include <Windows.h>
#include <windowsx.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <d3d11.h>
#include <dxgi.h>
#include <DirectXMath.h>
#include <C:\nonSystem\users\ajith\documents\visual studio 2015\DirectXTex-master\DirectXTex\DirectXTex.h>
#include <C:\nonSystem\users\ajith\documents\visual studio 2015\DirectXTex-master\WICTextureLoader\WICTextureLoader.h>
#include <C:\nonSystem\users\ajith\documents\visual studio 2015\DirectXTex-master\DDSTextureLoader\DDSTextureLoader.h>
#include <D3Dcompiler.h>
#include <map>
using namespace DirectX;
using namespace std;
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")
struct Vertex
{
	XMFLOAT4 Pos;
	XMFLOAT4 tangent;
	XMFLOAT3 norm;
	XMFLOAT2 tex;
};
struct MATRIces
	{
		XMFLOAT4X4 Model_matrix;
		XMFLOAT4X4 VIew_matrix;
		XMFLOAT4X4 Proj_matrix;
		XMFLOAT4 Cam_Pos;
	};
struct shadow_matrix
{
	XMMATRIX view_matrix;
	XMMATRIX proj_matrix;
};
enum Input{LEFT,RIGHT,DOWN,UP,STRAFE_UP,STRAFE_DOWN};

class RACK {
public:
	enum ResourceType {
		CONSTANTBUFFER = 0,
		SAMPLER = 1,
		CSHADER = 2,
		DSHADER = 3,
		GSHADER = 4,
		HSHADER = 5,
		PSHADER = 6,
		VSHADER = 7,
		SHADERRESOURCE = 8,
		UAV = 9,
		INPUTLAYOUT = 10,
		BLENDSTATE = 11,
		DEPTHSTENCILVIEW = 12,
		RENDERTARGET = 13,
		SCISSORRECTS = 14,
		STATE = 15,
		VIEWPORTS = 16,
		DEPTHSTENCILSTATE = 17
	};
	typedef struct {
		INT OFFSETS_V;
		INT OFFSETS_I;
		INT SIZES_V;
		INT SIZES_I;
	}VERTEXBUFFERINFO;
private:
	map<string, ID3D11Buffer**> map1;
	map<string, ID3D11SamplerState**> map2;
	map<string, ID3D11VertexShader**> map3;
	map<string, ID3D11GeometryShader**> map4;
	map<string, ID3D11PixelShader**> map5;
	map<string, ID3D11ComputeShader**> map6;
	map<string, ID3D11HullShader**> map7;
	map<string, ID3D11DomainShader**> map8;
	map<string, ID3D11ShaderResourceView**> map9;
	map<string, ID3D11UnorderedAccessView**> map10;
	map<string, ID3D11InputLayout**> map11;
	map<string, ID3D11BlendState**> map12;
	map<string, ID3D11DepthStencilView**> map13;
	map<string, ID3D11RenderTargetView**> map14;
	map<string, D3D11_RECT**> map15;
	map<string, ID3D11RasterizerState**> map16;
	map<string, D3D11_VIEWPORT**> map17;
	map<string, ID3D11DepthStencilState**> map18;

	INT16 num_of_objects{};
	

public:
	RACK(INT16);
	~RACK();
	ResourceType Type;
	VERTEXBUFFERINFO* info;
	void insertResource(ResourceType type, string s , ID3D11Buffer** item)
	{
		map1[s] = item;
	}
	void insertResource(ResourceType type, string s, ID3D11SamplerState** item)
	{
		map2[s] = item;
	}
	void insertResource(ResourceType type, string s, ID3D11VertexShader** item)
	{
		map3[s] = item;
	}
	void insertResource(ResourceType type, string s, ID3D11GeometryShader** item)
	{
		map4[s] = item;
	}
	void insertResource(ResourceType type, string s, ID3D11PixelShader** item)
	{
		map5[s] = item;
	}
	void insertResource(ResourceType type, string s, ID3D11ComputeShader** item)
	{
		map6[s] = item;
	}
	void insertResource(ResourceType type, string s, ID3D11HullShader** item)
	{
		map7[s] = item;
	}
	void insertResource(ResourceType type, string s, ID3D11DomainShader** item)
	{
		map8[s] = item;
	}
	void insertResource(ResourceType type, string s, ID3D11ShaderResourceView** item)
	{
		map9[s] = item;
	}
	void insertResource(ResourceType type, string s, ID3D11UnorderedAccessView** item)
	{
		map10[s] = item;
	}
	void insertResource(ResourceType type, string s, ID3D11InputLayout** item)
	{
		map11[s] = item;
	}
	void insertResource(ResourceType type, string s, ID3D11BlendState** item)
	{
		map12[s] = item;
	}
	void insertResource(ResourceType type, string s, ID3D11DepthStencilView** item)
	{
		map13[s] = item;
	}
	void insertResource(ResourceType type, string s, ID3D11RenderTargetView** item)
	{
		map14[s] = item;
	}
	void insertResource(ResourceType type, string s, D3D11_RECT** item)
	{
		map15[s] = item;
	}
	void insertResource(ResourceType type, string s, ID3D11RasterizerState** item)
	{
		map16[s] = item;
	}
	void insertResource(ResourceType type, string s, D3D11_VIEWPORT** item)
	{
		map17[s] = item;
	}
	void insertResource(ResourceType type, string s, ID3D11DepthStencilState** item)
	{
		map18[s] = item;
	}
	INT getNumOfObjs() { return num_of_objects; }
	VERTEXBUFFERINFO*& getAdditionalVertexInfo() { return info; }
	void* getResource(ResourceType, string);
};

extern ID3D11Device* device;
extern ID3D11DeviceContext* immediateContext;
extern IDXGISwapChain* swapChain;
extern RACK repository;
//class shaders {
//public:
//	shaders(INT8 n,LPCTSTR** paths,LPCSTR** names);
//	~shaders();
//	INT8 num_of_shaders() const;
//private:
//	void compileShader();
//	INT8 n;
//	LPCTSTR** shader_paths{};
//	LPCSTR** shader_names{};
//	LPCSTR shader_types[2] = { "vs_5_0", "ps_5_0" };
//	ID3D10Blob** shaderBlob,**errorBlob;
//	HRESULT* status;
//	ID3D11VertexShader** vert_shad;
//	ID3D11PixelShader** pix_shad;
//	ofstream err{ "Issues.txt" };
//};
//class objects {
//public:
//	objects(INT16 num, string* names);
//	~objects();
//private:
//	void objreader();
//	void vertexTangentGen();
//	INT16 n{};
//	string* obj_names;
//	INT16 *OFFSETS_V, *OFFSETS_I, *SIZES_V, *SIZES_I;
//	struct Vertex
//	{
//		XMFLOAT4 Pos;
//		XMFLOAT4 tangent;
//		XMFLOAT3 norm;
//		XMFLOAT2 tex;
//	};
//	vector<Vertex>* vertex_attr;
//	vector<INT32>* indices;
//	ofstream err{ "obj_problem.txt" };
//};