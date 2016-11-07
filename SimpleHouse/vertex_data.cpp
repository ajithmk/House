#include "render.h"
extern MATRIces outMatrix;
void objreader(string,vector<Vertex>&,vector<INT32>&);
void vertexTangentGen(vector<Vertex>&, vector<INT>&);
ID3D11Texture2D* pointLight_DepthCube = NULL;
void createVerBuff()
{
	ofstream err("vertex_issues.txt");
	INT num_of_obj = repository.getNumOfObjs();
	string* obj=new string[num_of_obj];
	err << "Parsing obj" << endl;

	obj[0]= "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\DecoShape.obj";
	obj[1] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\HouseStairsShape.obj";
	obj[2] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\BalconyStairsShape.obj";
	obj[3] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\KitchenShelfShape.obj";
	obj[4] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\TopWesternRoomShelfShape.obj";
	obj[5] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\EasternRoomShelfShape.obj";
	obj[6] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\BottomRoomShelfShape.obj";
	
	obj[7]= "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\HallWalls1Shape.obj";
	obj[8]= "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\HallWalls3Shape.obj";
	obj[9]= "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\HallWalls4Shape.obj";
	obj[10] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\HallWalls2Shape.obj";
	
	obj[11] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\OuterWallsShape.obj";
	
	obj[12] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\AtticFloorShape.obj";
	obj[13] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\BottomBathroomFloorShape.obj";
	obj[14] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\HouseFloorShape.obj";
	obj[15] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\smallBathroomFloorShape.obj";
	obj[16] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\TopBathroomFloorShape.obj";
	obj[17] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\TopEasternRoomFloorShape.obj";
	obj[18] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\TopWesternRoomFloorShape.obj";
	obj[19] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\UpperHallFloorShape.obj";

	obj[20] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\AtticRoofShape.obj";
	obj[21] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\BottomRoomRoofShape.obj";
	obj[22] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\HouseRoofShape.obj";
	obj[23] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\KitchenRoofShape.obj";
	obj[24] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\LowerHallRoofShape.obj";
	obj[25] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\smallBathroomRoofShape.obj";
	obj[26] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\TopBathroomRoofShape.obj";
	obj[27] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\TopEasternRoomRoofShape.obj";
	obj[28] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\TopWesternRoomRoofShape.obj";
	obj[29] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\UpperHallRoofShape.obj";
	obj[30] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\ShrineRoofShape.obj";
	
	obj[31] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\AtticWallsShape.obj";
	obj[32] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\ShrineClosetWallsShape.obj";
	obj[33] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\ShrineWallsShape.obj";
	obj[34] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\SmallBathroomWallsShape.obj";
	obj[35] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\TopBathroomWallsShape.obj";
	obj[36] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\TopEasternRoomWallsShape.obj";
	obj[37] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\TopWesternRoomWallsShape.obj";
	obj[38] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\KitchenWallsShape.obj";
	obj[39] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\BottomRoomWallsShape.obj";
	obj[40] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\BottomBathroomWallsShape.obj";
	
	obj[41] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\CompoundShape.obj";
	
	obj[42] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\BalconyShape.obj";
	obj[43] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\GravelShape.obj";
	obj[44] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\HouseBaseShape.obj";
	obj[45] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\TankShape.obj";
	
	obj[46] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\HallWallConnectorShape.obj";
	
	obj[47] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\MudlandShape.obj";

	obj[48] = "C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\MayaAPITest\\x64\\Debug\\BillBoardShape.obj";
	
	RACK::VERTEXBUFFERINFO* info = repository.getAdditionalVertexInfo();
	Vertex* vertex;
	vector<Vertex>* vertex_attr;
	vector<INT>* index;
	vertex_attr=new vector<Vertex>[num_of_obj];
	index = new vector<INT32> [num_of_obj];
	system("PAUSE");
	for (int j = 0; j < num_of_obj; j++)
	{
		objreader(obj[j], vertex_attr[j], index[j]);
		vertexTangentGen(vertex_attr[j], index[j]);
		info[j].SIZES_V = vertex_attr[j].size();
		info[j].SIZES_I = index[j].size();
		err << dec << "sizes\n" << info[j].SIZES_V << "\n" << info[j].SIZES_I << "\n";
	}
	system("PAUSE");
	err << "Done!" << endl;
	for (int j = 0; j < num_of_obj; j++)
	{
		if(j==0){info[j].OFFSETS_I=0;info[j].OFFSETS_V=0;}
		else{ info[j].OFFSETS_I = info[j-1].OFFSETS_I + info[j-1].SIZES_I;
		      info[j].OFFSETS_V = info[j-1].OFFSETS_V + info[j-1].SIZES_V;}
		err <<dec<< "offsets\n" << info[j].OFFSETS_V << "\n" << info[j].OFFSETS_I << "\n";
	}
	//Below for loop is calculating vertex and index buffer.
	INT32* v_i=new INT32[info[num_of_obj - 1].OFFSETS_I + info[num_of_obj - 1].SIZES_I];
	vertex=new Vertex[info[num_of_obj - 1].OFFSETS_V + info[num_of_obj - 1].SIZES_V];
	for (int j = 0; j < num_of_obj; j++)
	{
		for(int i=0;i<info[j].SIZES_V;i++)
		{
			vertex[i+info[j].OFFSETS_V]=vertex_attr[j][i];
		}
		for(int i=0;i<info[j].SIZES_I;i++)
		{
			v_i[i + info[j].OFFSETS_I] = index[j][i];
		}
	} 
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd,sizeof(bd));
    bd.ByteWidth=sizeof(Vertex)*(info[num_of_obj - 1].OFFSETS_V + info[num_of_obj - 1].SIZES_V);
    bd.Usage=D3D11_USAGE_DEFAULT;
    bd.BindFlags=D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags=0;
    bd.MiscFlags=0;
    D3D11_SUBRESOURCE_DATA init;
    init.pSysMem=vertex;
	HRESULT status4, status7;
	ID3D11Buffer** vertexBuffer = new ID3D11Buffer*;
    status4=device->CreateBuffer(&bd,&init,vertexBuffer);
	repository.insertResource(RACK::CONSTANTBUFFER, "vertexBuffer", vertexBuffer);
    UINT stride=sizeof(Vertex);
    UINT offset=0;
    immediateContext->IASetVertexBuffers(0,1, &*reinterpret_cast<ID3D11Buffer**>(repository.getResource(RACK::CONSTANTBUFFER, "vertexBuffer")),&stride,&offset);
    immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	D3D11_BUFFER_DESC bd1;
	ZeroMemory(&bd1,sizeof(bd1));
	bd1.ByteWidth=sizeof(INT32)*(info[num_of_obj - 1].OFFSETS_I + info[num_of_obj - 1].SIZES_I);
	bd1.Usage=D3D11_USAGE_DEFAULT;
	bd1.BindFlags=D3D11_BIND_INDEX_BUFFER;
	D3D11_SUBRESOURCE_DATA init1;
	init1.pSysMem=v_i;
	ID3D11Buffer** indexBuffer = new ID3D11Buffer*;
	status7=device->CreateBuffer(&bd1,&init1,indexBuffer);
	repository.insertResource(RACK::CONSTANTBUFFER, "indexBuffer", indexBuffer);
	immediateContext->IASetIndexBuffer(*reinterpret_cast<ID3D11Buffer**>(repository.getResource(RACK::CONSTANTBUFFER, "indexBuffer")),DXGI_FORMAT_R32_UINT,0);
}
void compileShaders()
{
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TANGENT",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,16,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,32,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,44,D3D11_INPUT_PER_VERTEX_DATA,0 }
	};
	UINT numElements = ARRAYSIZE(layout);
	const INT num_of_shaders = 4;
	ID3D10Blob *vsShaderBlob[num_of_shaders], *vsErrorBlob[num_of_shaders], *psErrorBlob[num_of_shaders], *psShaderBlob[num_of_shaders];
	LPCTSTR s[num_of_shaders];
	s[0] = TEXT("C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\SimpleHouse\\Shaders\\pointLightPass.hlsl");
	s[1] = TEXT("C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\SimpleHouse\\Shaders\\Skybox.hlsl");
	s[2] = TEXT("C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\SimpleHouse\\Shaders\\pointlight_depthpass.hlsl");
	s[3] = TEXT("C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\SimpleHouse\\Shaders\\normal_pass.hlsl");
	HRESULT status1, status2, status3, status5, status6;
	ofstream err("vert errors.txt");
	err << "What happened\n" << endl;
	LPCSTR shader_type = "vs_5_0";
	LPCSTR main_func = "VS";


	for (int i = 0; i<num_of_shaders; i++)
	{
		shader_type = "vs_5_0";
		main_func = "VS";
		status1 = D3DCompileFromFile(s[i], NULL, NULL, main_func, shader_type, D3DCOMPILE_ENABLE_STRICTNESS, NULL, &vsShaderBlob[i], &vsErrorBlob[i]);
		shader_type = "ps_5_0";
		main_func = "PS";
		status2 = D3DCompileFromFile(s[i], NULL, NULL, main_func, shader_type, D3DCOMPILE_ENABLE_STRICTNESS, NULL, &psShaderBlob[i], &psErrorBlob[i]);
		err << hex << showbase << status1 << "\n" << status2 << "\n" << endl;
	}
	ID3D11InputLayout** vertexLayout = new ID3D11InputLayout*;
	status3 = device->CreateInputLayout(layout, numElements, vsShaderBlob[0]->GetBufferPointer(), vsShaderBlob[0]->GetBufferSize(), vertexLayout);
	repository.insertResource(RACK::INPUTLAYOUT, "vertexLayout", vertexLayout);
	immediateContext->IASetInputLayout(*reinterpret_cast<ID3D11InputLayout**>(repository.getResource(RACK::INPUTLAYOUT, "vertexLayout")));
	ID3D11VertexShader** pointLight_vertexShader = new ID3D11VertexShader*;
	ID3D11PixelShader** pointLight_pixelShader = new ID3D11PixelShader*;
	status5 = device->CreateVertexShader(vsShaderBlob[0]->GetBufferPointer(), vsShaderBlob[0]->GetBufferSize(), NULL, pointLight_vertexShader);
	status6 = device->CreatePixelShader(psShaderBlob[0]->GetBufferPointer(), psShaderBlob[0]->GetBufferSize(), NULL, pointLight_pixelShader);
	err << hex << showbase << status5 << "\n" << endl;
	err << hex << showbase << status6 << "\n" << endl;
	repository.insertResource(RACK::VSHADER, "pointLight_vertexShader", pointLight_vertexShader);
	repository.insertResource(RACK::PSHADER, "pointLight_pixelShader", pointLight_pixelShader);

	ID3D11VertexShader** skyBox_vertexShader = new ID3D11VertexShader*;
	ID3D11PixelShader** skyBox_pixelShader = new ID3D11PixelShader*;
	status5 = device->CreateVertexShader(vsShaderBlob[1]->GetBufferPointer(), vsShaderBlob[1]->GetBufferSize(), NULL, skyBox_vertexShader);
	status6 = device->CreatePixelShader(psShaderBlob[1]->GetBufferPointer(), psShaderBlob[1]->GetBufferSize(), NULL, skyBox_pixelShader);
	err << hex << showbase << status5 << "\n" << endl;
	err << hex << showbase << status6 << "\n" << endl;
	repository.insertResource(RACK::VSHADER, "skyBox_vertexShader", skyBox_vertexShader);
	repository.insertResource(RACK::PSHADER, "skyBox_pixelShader", skyBox_pixelShader);

	ID3D11VertexShader** pointLightD_vertexShader = new ID3D11VertexShader*;
	ID3D11PixelShader** pointLightD_pixelShader = new ID3D11PixelShader*;
	status5 = device->CreateVertexShader(vsShaderBlob[2]->GetBufferPointer(), vsShaderBlob[2]->GetBufferSize(), NULL, pointLightD_vertexShader);
	status6 = device->CreatePixelShader(psShaderBlob[2]->GetBufferPointer(), psShaderBlob[2]->GetBufferSize(), NULL, pointLightD_pixelShader);
	err << hex << showbase << status5 << "\n" << endl;
	err << hex << showbase << status6 << "\n" << endl;
	repository.insertResource(RACK::VSHADER, "pointLightD_vertexShader", pointLightD_vertexShader);
	repository.insertResource(RACK::PSHADER, "pointLightD_pixelShader", pointLightD_pixelShader);

	ID3D11VertexShader** pointLightNormal_vertexShader = new ID3D11VertexShader*;
	ID3D11PixelShader** pointLightNormal_pixelShader = new ID3D11PixelShader*;
	status5 = device->CreateVertexShader(vsShaderBlob[3]->GetBufferPointer(), vsShaderBlob[3]->GetBufferSize(), NULL, pointLightNormal_vertexShader);
	status6 = device->CreatePixelShader(psShaderBlob[3]->GetBufferPointer(), psShaderBlob[3]->GetBufferSize(), NULL, pointLightNormal_pixelShader);
	err << hex << showbase << status5 << "\n" << endl;
	err << hex << showbase << status6 << "\n" << endl;
	repository.insertResource(RACK::VSHADER, "pointLightNormal_vertexShader", pointLightNormal_vertexShader);
	repository.insertResource(RACK::PSHADER, "pointLightNormal_pixelShader", pointLightNormal_pixelShader);

	for (int i = 0; i < num_of_shaders; i++)
	{
		if (vsShaderBlob[i])vsShaderBlob[i]->Release();
		if (psShaderBlob[i])psShaderBlob[i]->Release();
		if (psErrorBlob[i])psErrorBlob[i]->Release();
		if (vsErrorBlob[i])vsErrorBlob[i]->Release();
	}
}
void bufferConstantsSetup()
{
	ofstream err("constantBuffer_issues.txt");
	D3D11_SUBRESOURCE_DATA sd;
	D3D11_BUFFER_DESC bd;
	sd.pSysMem = &outMatrix;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(MATRIces);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.Usage = D3D11_USAGE_DYNAMIC;
	ID3D11Buffer** constBuffer = new ID3D11Buffer*;
	device->CreateBuffer(&bd, &sd, constBuffer);
	repository.insertResource(RACK::CONSTANTBUFFER, "constBuffer", constBuffer);
	immediateContext->VSSetConstantBuffers(0, 1, &(*reinterpret_cast<ID3D11Buffer**>(repository.getResource(RACK::CONSTANTBUFFER, "constBuffer"))));
	system("PAUSE");
	struct light
	{
		float pos[4];
	}light1;
	light1.pos[0] = 0.0f; 
	light1.pos[1] = 20.0f;
	light1.pos[2] = 10.0f;
	light1.pos[3] = 1.0f;
	struct diffuse
	{
		float dif[4];
	}diffuse1;
	diffuse1.dif[0] = 0.933f;
	diffuse1.dif[1] = 0.91f;
	diffuse1.dif[2] = 0.667f;
	diffuse1.dif[3] = 1.0f;
	struct smoon_plane
	{
		float x[4];
	}smoon_pane1;
	smoon_pane1.x[0] = 0.0f;
	smoon_pane1.x[1] = -1.0f;
	smoon_pane1.x[2] = -1.0f;
	smoon_pane1.x[3] = 0.0f;
	struct smoon_diffuse
	{
		float x[4];
	}smoon_diffuse1;
	smoon_diffuse1.x[0] = 0.450f;
	smoon_diffuse1.x[1] = 0.588f;
	smoon_diffuse1.x[2] = 0.784f;
	smoon_diffuse1.x[3] = 1.0f;
	struct sambience
	{
		float x[4];
	}sambience1;
	sambience1.x[0] = 0.09f;
	sambience1.x[1] = 0.1176f;
	sambience1.x[2] = 0.1568f;
	sambience1.x[3] = 1.0f;
	ID3D11Buffer** light_pos = new ID3D11Buffer*;
	ID3D11Buffer** diffuse_color = new ID3D11Buffer*;
	ID3D11Buffer** ambience_color = new ID3D11Buffer*;
	ID3D11Buffer** moon_plane = new ID3D11Buffer*;
	ID3D11Buffer** moon_diffuse = new ID3D11Buffer*;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(light);
	D3D11_SUBRESOURCE_DATA sd1;
	ZeroMemory(&sd1, sizeof(D3D11_SUBRESOURCE_DATA));
	sd1.pSysMem = &light1;
	HRESULT gt = device->CreateBuffer(&bd, &sd1, light_pos);
	repository.insertResource(RACK::CONSTANTBUFFER, "light_pos", light_pos);
	err << hex << showbase << gt << "\n";
	immediateContext->VSSetConstantBuffers(1, 1, reinterpret_cast<ID3D11Buffer**>(repository.getResource(RACK::CONSTANTBUFFER, "light_pos")));
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(diffuse);
	D3D11_SUBRESOURCE_DATA sd2;
	ZeroMemory(&sd2, sizeof(D3D11_SUBRESOURCE_DATA));
	sd2.pSysMem = &diffuse1;
	device->CreateBuffer(&bd, &sd2, diffuse_color);
	repository.insertResource(RACK::CONSTANTBUFFER, "diffuse_pos", diffuse_color);
	immediateContext->PSSetConstantBuffers(2, 1, reinterpret_cast<ID3D11Buffer**>(repository.getResource(RACK::CONSTANTBUFFER, "diffuse_pos")));

	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(smoon_plane);
	ZeroMemory(&sd2, sizeof(D3D11_SUBRESOURCE_DATA));
	sd2.pSysMem = &smoon_pane1;
	device->CreateBuffer(&bd, &sd2, moon_plane);
	repository.insertResource(RACK::CONSTANTBUFFER, "moon_plane", moon_plane);
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(smoon_diffuse);
	ZeroMemory(&sd2, sizeof(D3D11_SUBRESOURCE_DATA));
	sd2.pSysMem = &smoon_diffuse1;
	device->CreateBuffer(&bd, &sd2, moon_diffuse);
	repository.insertResource(RACK::CONSTANTBUFFER, "moon_diffuse", moon_diffuse);
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(sambience);
	ZeroMemory(&sd2, sizeof(D3D11_SUBRESOURCE_DATA));
	sd2.pSysMem = &sambience1;
	device->CreateBuffer(&bd, &sd2, ambience_color);
	repository.insertResource(RACK::CONSTANTBUFFER, "ambience_color", ambience_color);

	ID3D11Buffer **pointLightShadow_buffer = new ID3D11Buffer*;
	D3D11_BUFFER_DESC sb;
	ZeroMemory(&sb, sizeof(D3D11_BUFFER_DESC));
	sb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	sb.ByteWidth = sizeof(shadow_matrix);
	sb.CPUAccessFlags = 0;
	sb.Usage = D3D11_USAGE_DEFAULT;
	device->CreateBuffer(&sb, NULL, pointLightShadow_buffer);
	repository.insertResource(RACK::CONSTANTBUFFER, "pointLightShadow_buffer", pointLightShadow_buffer);
	struct proj
	{
		XMMATRIX projm;
	}proj_in;
	sb.ByteWidth = sizeof(proj);
	ID3D11Buffer** pointLight_ShaodwProj = new ID3D11Buffer*;
	device->CreateBuffer(&sb, NULL, pointLight_ShaodwProj);
	proj_in.projm = XMMatrixTranspose(XMMatrixPerspectiveFovLH(XMConvertToRadians(90.0f), 1.0, 0.1f, 400.0f));
	immediateContext->UpdateSubresource(*pointLight_ShaodwProj, 0, NULL, &proj_in, 0, 0);
	repository.insertResource(RACK::CONSTANTBUFFER, "pointLight_ShaodwProj", pointLight_ShaodwProj);
}
void textureBufferSetup()
{
	ofstream err("textureBuffer_issues.txt");
	LPCTSTR *texture;
	INT num_of_obj = repository.getNumOfObjs();
	texture = new LPCTSTR[num_of_obj];
	LPCTSTR normal[1] = { TEXT("C:\\Users\\Ajith\\Documents\\Gimp\\Working_folder\\roomwallhm.dds") };
	LPCTSTR height[1]= { TEXT("C:\\Users\\Ajith\\Documents\\Gimp\\Working_folder\\roomwallhm.png") };
	texture[0] = TEXT("C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\SimpleHouse\\Textures\\Custom textures\\pencil_shades.png");
	texture[1] = TEXT("C:\\Users\\Ajith\\Documents\\Gimp\\Working_folder\\woodenplank.png");
	texture[2] = TEXT("C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\SimpleHouse\\Textures\\Woodenplank wall\\seamlessWood.dds");
	texture[3] = TEXT("C:\\Users\\Ajith\\Documents\\Gimp\\Working_folder\\floor1.png");
	texture[4] = TEXT("C:\\Users\\Ajith\\Documents\\Gimp\\Working_folder\\ceiling1.png");
	texture[5] = TEXT("C:\\Users\\Ajith\\Documents\\Gimp\\Working_folder\\roomwall.png");
	texture[6] = TEXT("C:\\Users\\Ajith\\Documents\\Gimp\\Working_folder\\stone1.png");
	texture[7] = TEXT("C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\SimpleHouse\\Textures\\Cement\\cement.png");
	texture[8] = TEXT("C:\\Users\\Ajith\\Documents\\Gimp\\Working_folder\\pattern1.png");
	texture[9] = TEXT("C:\\nonSystem\\users\\ajith\\documents\\visual studio 2015\\Projects\\SimpleHouse\\Textures\\Ground\\normal_ground.png");
	texture[10] = TEXT("C:\\Users\\Ajith\\Documents\\Gimp\\Working_folder\\skyCubeMap.dds");
	HRESULT texprob, com;
	com = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	err << hex << showbase << com << "this\n" << endl;
	ID3D11ShaderResourceView** pencil_shades = new ID3D11ShaderResourceView*;
	ID3D11ShaderResourceView** normalSRV = new ID3D11ShaderResourceView*;
	ID3D11ShaderResourceView** heightSRV = new ID3D11ShaderResourceView*;
	if (FAILED(texprob = CreateDDSTextureFromFile(device, immediateContext, normal[0], nullptr, normalSRV)))
	{
		err << hex << showbase << texprob << "uy\n" << endl;
		MessageBox(0, L"roomwallnm loading failed boss", (LPCWSTR)L"You are fucked", MB_OK);
		exit(0);
	}
	repository.insertResource(RACK::SHADERRESOURCE, "normalSRV", normalSRV);
	if (FAILED(texprob = CreateWICTextureFromFile(device, immediateContext, height[0], nullptr, heightSRV)))
	{
		err << hex << showbase << texprob << "uy\n" << endl;
		MessageBox(0, L"roomwallhm loading failed boss", (LPCWSTR)L"You are fucked", MB_OK);
		exit(0);
	}
	repository.insertResource(RACK::SHADERRESOURCE, "heightSRV", heightSRV);
	if (FAILED(texprob = CreateWICTextureFromFile(device, immediateContext, texture[0], nullptr, pencil_shades)))
		{
			err << hex << showbase << texprob << "uy\n" << endl;
			MessageBox(0, L"Texture loading failed boss", (LPCWSTR)L"You are fucked", MB_OK);
			exit(0);
		}
	repository.insertResource(RACK::SHADERRESOURCE, "pencil_shades", pencil_shades);
	ID3D11ShaderResourceView** skyBoxSRV = new ID3D11ShaderResourceView*;
	if (FAILED(texprob = CreateDDSTextureFromFile(device, immediateContext, texture[10], nullptr, skyBoxSRV)))
	{
		err << hex << showbase << texprob << "\n" << endl;
		MessageBox(0, L"SkyCubeMap loading failed boss", (LPCWSTR)L"You are fucked", MB_OK);
		exit(0);
	}
	repository.insertResource(RACK::SHADERRESOURCE, "skyBoxSRV", skyBoxSRV);
	ID3D11ShaderResourceView** OuterWallWood = new ID3D11ShaderResourceView*;
	if (FAILED(texprob = CreateDDSTextureFromFile(device, immediateContext, texture[2], nullptr, OuterWallWood)))
	{
		err << hex << showbase << texprob << "\n" << endl;
		MessageBox(0, L"OuterWallWood loading failed boss", (LPCWSTR)L"You are fucked", MB_OK);
		exit(0);
	}
	repository.insertResource(RACK::SHADERRESOURCE, "OuterWallWood", OuterWallWood);

	ID3D11ShaderResourceView** WoodenPlank = new ID3D11ShaderResourceView*;
	if (FAILED(texprob = CreateWICTextureFromFile(device, immediateContext, texture[1], nullptr, WoodenPlank)))
	{
		err << hex << showbase << texprob << "\n" << endl;
		MessageBox(0, L"WoodenPlank loading failed boss", (LPCWSTR)L"You are fucked", MB_OK);
		exit(0);
	}
	repository.insertResource(RACK::SHADERRESOURCE, "WoodenPlank", WoodenPlank);

	ID3D11ShaderResourceView** floor1 = new ID3D11ShaderResourceView*;
	if (FAILED(texprob = CreateWICTextureFromFile(device, immediateContext, texture[3], nullptr, floor1)))
	{
		err << hex << showbase << texprob << "\n" << endl;
		MessageBox(0, L"floor1 loading failed boss", (LPCWSTR)L"You are fucked", MB_OK);
		exit(0);
	}
	repository.insertResource(RACK::SHADERRESOURCE, "floor1", floor1);

	ID3D11ShaderResourceView** ceiling1 = new ID3D11ShaderResourceView*;
	if (FAILED(texprob = CreateWICTextureFromFile(device, immediateContext, texture[4], nullptr, ceiling1)))
	{
		err << hex << showbase << texprob << "\n" << endl;
		MessageBox(0, L"ceiling1 loading failed boss", (LPCWSTR)L"You are fucked", MB_OK);
		exit(0);
	}
	repository.insertResource(RACK::SHADERRESOURCE, "ceiling1", ceiling1);

	ID3D11ShaderResourceView** roomwall = new ID3D11ShaderResourceView*;
	if (FAILED(texprob = CreateWICTextureFromFile(device, immediateContext, texture[5], nullptr, roomwall)))
	{
		err << hex << showbase << texprob << "\n" << endl;
		MessageBox(0, L"roomwall loading failed boss", (LPCWSTR)L"You are fucked", MB_OK);
		exit(0);
	}
	repository.insertResource(RACK::SHADERRESOURCE, "roomwall", roomwall);

	ID3D11ShaderResourceView** stone1 = new ID3D11ShaderResourceView*;
	if (FAILED(texprob = CreateWICTextureFromFile(device, immediateContext, texture[6], nullptr, stone1)))
	{
		err << hex << showbase << texprob << "\n" << endl;
		MessageBox(0, L"stone1 loading failed boss", (LPCWSTR)L"You are fucked", MB_OK);
		exit(0);
	}
	repository.insertResource(RACK::SHADERRESOURCE, "stone1", stone1);

	ID3D11ShaderResourceView** cement = new ID3D11ShaderResourceView*;
	if (FAILED(texprob = CreateWICTextureFromFile(device, immediateContext, texture[7], nullptr, cement)))
	{
		err << hex << showbase << texprob << "\n" << endl;
		MessageBox(0, L"cement loading failed boss", (LPCWSTR)L"You are fucked", MB_OK);
		exit(0);
	}
	repository.insertResource(RACK::SHADERRESOURCE, "cement", cement);

	ID3D11ShaderResourceView** pattern1 = new ID3D11ShaderResourceView*;
	if (FAILED(texprob = CreateWICTextureFromFile(device, immediateContext, texture[8], nullptr, pattern1)))
	{
		err << hex << showbase << texprob << "\n" << endl;
		MessageBox(0, L"pattern1 loading failed boss", (LPCWSTR)L"You are fucked", MB_OK);
		exit(0);
	}
	repository.insertResource(RACK::SHADERRESOURCE, "pattern1", pattern1);

	ID3D11ShaderResourceView** normal_ground = new ID3D11ShaderResourceView*;
	if (FAILED(texprob = CreateWICTextureFromFile(device, immediateContext, texture[9], nullptr, normal_ground)))
	{
		err << hex << showbase << texprob << "\n" << endl;
		MessageBox(0, L"normal_ground loading failed boss", (LPCWSTR)L"You are fucked", MB_OK);
		exit(0);
	}
	repository.insertResource(RACK::SHADERRESOURCE, "normal_ground", normal_ground);

	HRESULT view1, view2, view3;
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.ArraySize = 6;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_DEPTH_STENCIL;
	desc.CPUAccessFlags = 0;
	desc.Format = DXGI_FORMAT_R32_TYPELESS;
	desc.Height = 1024;
	desc.Width = desc.Height;
	desc.MipLevels = 1;
	desc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	view1 = device->CreateTexture2D(&desc, NULL, &pointLight_DepthCube);
	err << hex << showbase << view1 << " pointLight_DepthCube\n";
	D3D11_SHADER_RESOURCE_VIEW_DESC pointLight_DepthCube_SRVD;
	ID3D11ShaderResourceView** pointLight_DepthCube_SRV = new ID3D11ShaderResourceView*;
	ZeroMemory(&pointLight_DepthCube_SRVD, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	pointLight_DepthCube_SRVD.Format = DXGI_FORMAT_R32_FLOAT;
	pointLight_DepthCube_SRVD.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	pointLight_DepthCube_SRVD.TextureCube.MipLevels = 1;
	pointLight_DepthCube_SRVD.TextureCube.MostDetailedMip = 0;
	view2 = device->CreateShaderResourceView(pointLight_DepthCube, &pointLight_DepthCube_SRVD, pointLight_DepthCube_SRV);
	err << hex << showbase << view2 << "\n";
	repository.insertResource(RACK::SHADERRESOURCE, "pointLight_DepthCube_SRV", pointLight_DepthCube_SRV);
	ID3D11DepthStencilView** pointLight_DepthCube_DSV=new ID3D11DepthStencilView*[6];
	D3D11_DEPTH_STENCIL_VIEW_DESC pointLight_DepthCube_DSVD;
	for (int i = 0; i<6; i++)
	{
		ZeroMemory(&pointLight_DepthCube_DSVD, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		pointLight_DepthCube_DSVD.Format = DXGI_FORMAT_D32_FLOAT;
		pointLight_DepthCube_DSVD.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
		pointLight_DepthCube_DSVD.Texture2DArray.ArraySize = 1;
		pointLight_DepthCube_DSVD.Texture2DArray.FirstArraySlice = i;
		pointLight_DepthCube_DSVD.Texture2DArray.MipSlice = 0;
		view3 = device->CreateDepthStencilView(pointLight_DepthCube, &pointLight_DepthCube_DSVD, &pointLight_DepthCube_DSV[i]);
		err << hex << showbase << view3 << "\n";
	}
	repository.insertResource(RACK::DEPTHSTENCILVIEW, "pointLight_DepthCube_DSV", pointLight_DepthCube_DSV);

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	ID3D11SamplerState** LinearSampler = new ID3D11SamplerState*;
	device->CreateSamplerState(&sampDesc, LinearSampler);
	repository.insertResource(RACK::SAMPLER, "LinearSampler", LinearSampler);
	immediateContext->PSSetSamplers(0, 1, reinterpret_cast<ID3D11SamplerState**>(repository.getResource(RACK::SAMPLER, "LinearSampler")));
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	float border[4] = { 0.0,0.0,0.0,0.0 };
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	ID3D11SamplerState** PointSampler = new ID3D11SamplerState*;
	repository.insertResource(RACK::SAMPLER, "PointSampler", PointSampler);
	device->CreateSamplerState(&sampDesc, PointSampler);
	immediateContext->PSSetSamplers(1, 1, reinterpret_cast<ID3D11SamplerState**>(repository.getResource(RACK::SAMPLER, "PointSampler")));
}