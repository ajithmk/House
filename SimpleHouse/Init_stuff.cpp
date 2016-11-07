#include "render.h"
ID3D11Device *device=NULL;
ID3D11DeviceContext *immediateContext=NULL;
IDXGISwapChain *swapChain=NULL;
RACK repository(49);
MATRIces outMatrix;
ofstream fs("Hresult.txt");
bool setupDX(HWND hWnd)
{
	ID3D11Texture2D *backBuffer;
	DXGI_SWAP_CHAIN_DESC sd;
	outMatrix.Model_matrix = XMFLOAT4X4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	outMatrix.VIew_matrix = XMFLOAT4X4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	outMatrix.Proj_matrix = XMFLOAT4X4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	outMatrix.Cam_Pos = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	ZeroMemory(&sd,sizeof(sd));
	sd.BufferDesc.Width=250;
	sd.BufferDesc.Height=250;
	sd.BufferDesc.RefreshRate.Numerator=60;
	sd.BufferDesc.RefreshRate.Denominator=60;
	sd.BufferDesc.Format=DXGI_FORMAT_R8G8B8A8_UNORM;
	//sd.BufferDesc.Format=DXGI_FORMAT_R16_UNORM;
	sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
	sd.BufferUsage=DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount=1;
	sd.Windowed=true;
	sd.OutputWindow=hWnd;
	HRESULT hr;
	if(FAILED(D3D11CreateDeviceAndSwapChain(NULL,D3D_DRIVER_TYPE_HARDWARE,NULL,D3D11_CREATE_DEVICE_DEBUG,0,0,D3D11_SDK_VERSION,&sd,&swapChain, &device, NULL, &immediateContext)))return FALSE;
	if(FAILED(swapChain->GetBuffer(NULL,__uuidof(ID3D11Texture2D),(LPVOID*)(&backBuffer))))return FALSE;
	D3D11_RENDER_TARGET_VIEW_DESC v;
	v.Format=sd.BufferDesc.Format;
	v.ViewDimension=D3D11_RTV_DIMENSION_TEXTURE2D;
	v.Texture2D.MipSlice=0;
	ID3D11RenderTargetView** renderTargetView = new ID3D11RenderTargetView*;
	hr=device->CreateRenderTargetView(backBuffer,&v,renderTargetView);
	repository.insertResource(RACK::RENDERTARGET, "renderTargetView", renderTargetView);
	if(backBuffer)backBuffer->Release();
	if(FAILED(hr))return FALSE;
	ID3D11Texture2D* depthStencilBuffer=NULL;
	D3D11_TEXTURE2D_DESC d;
	ZeroMemory(&d,sizeof(d));
	d.BindFlags=D3D11_BIND_DEPTH_STENCIL;
	d.Format=DXGI_FORMAT_D24_UNORM_S8_UINT;
	d.Usage=D3D11_USAGE_DEFAULT;
	d.Width=250;
	d.Height=250;
	d.CPUAccessFlags=0;
	d.ArraySize=1;
	d.MipLevels=1;
	d.SampleDesc.Count=1;
	d.SampleDesc.Quality=0;
	device->CreateTexture2D(&d,NULL,&depthStencilBuffer);
	ID3D11DepthStencilView** depthStencilBufferView = new ID3D11DepthStencilView*;
	device->CreateDepthStencilView(depthStencilBuffer,NULL,depthStencilBufferView);
	repository.insertResource(RACK::DEPTHSTENCILVIEW, "depthStencilBufferView", depthStencilBufferView);
	if(depthStencilBuffer)depthStencilBuffer->Release();
	immediateContext->OMSetRenderTargets(1, (reinterpret_cast<ID3D11RenderTargetView**>(repository.getResource(RACK::RENDERTARGET, "renderTargetView"))),
		*(reinterpret_cast<ID3D11DepthStencilView**>(repository.getResource(RACK::DEPTHSTENCILVIEW,"depthStencilBufferView"))));
	D3D11_DEPTH_STENCIL_DESC dsDesc;
	ZeroMemory(&dsDesc,sizeof(dsDesc));
	dsDesc.DepthEnable=true;
	dsDesc.DepthWriteMask=D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc=D3D11_COMPARISON_LESS;
	ID3D11DepthStencilState** pDSState = new ID3D11DepthStencilState*;
	device->CreateDepthStencilState(&dsDesc,pDSState);
	repository.insertResource(RACK::DEPTHSTENCILSTATE, "pDSState", pDSState);
	immediateContext->OMSetDepthStencilState(*reinterpret_cast<ID3D11DepthStencilState**>(repository.getResource(RACK::DEPTHSTENCILSTATE, "pDSState")),1);
	fs << "Done" << endl;
	return TRUE;
}
void cleanup()
{
	if( immediateContext ) immediateContext->ClearState();
    if( swapChain ) swapChain->Release();
    if( immediateContext ) immediateContext->Release();
    if( device ) device->Release();
}
void changeSize(INT width,INT height,HWND hWnd)
{
	if(swapChain)
	{
		immediateContext->OMSetRenderTargets(0,0,0);
		ID3D11RenderTargetView** renderTargetView = reinterpret_cast<ID3D11RenderTargetView**>(repository.getResource(RACK::RENDERTARGET, "renderTargetView"));
		if (*renderTargetView) { (*renderTargetView)->Release(); }
		HRESULT hr,hr1,hr2;
		hr=swapChain->ResizeBuffers(0,0,0,DXGI_FORMAT_R8G8B8A8_UNORM,0);
		ID3D11Texture2D* backBuffer;
		D3D11_RENDER_TARGET_VIEW_DESC v;
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferDesc.Width = 250;
		sd.BufferDesc.Height = 250;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 60;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		//sd.BufferDesc.Format=DXGI_FORMAT_R16_UNORM;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;
		sd.Windowed = true;
		sd.OutputWindow = hWnd;
		v.Format = sd.BufferDesc.Format;
		v.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		v.Texture2D.MipSlice = 0;
		hr1=swapChain->GetBuffer(NULL,__uuidof(ID3D11Texture2D),(LPVOID*)&backBuffer);
		hr2=device->CreateRenderTargetView(backBuffer,&v,renderTargetView);
		ID3D11DepthStencilView** depthStencilBufferView = reinterpret_cast<ID3D11DepthStencilView**>(repository.getResource(RACK::DEPTHSTENCILVIEW, "depthStencilBufferView"));
		if(*depthStencilBufferView)(*depthStencilBufferView)->Release();
		ID3D11Texture2D* depthStencilBuffer=NULL;
		D3D11_TEXTURE2D_DESC d;
		ZeroMemory(&d,sizeof(d));
		d.BindFlags=D3D11_BIND_DEPTH_STENCIL;
		d.Format=DXGI_FORMAT_D24_UNORM_S8_UINT;
		d.Usage=D3D11_USAGE_DEFAULT;
		d.Width=width;
		d.Height=height;
		d.CPUAccessFlags=0;
		d.ArraySize=1;
		d.MipLevels=1;
		d.SampleDesc.Count=1;
		d.SampleDesc.Quality=0;
		device->CreateTexture2D(&d,NULL,&depthStencilBuffer);
		D3D11_DEPTH_STENCIL_VIEW_DESC depthDesc;
		ZeroMemory(&depthDesc,sizeof(depthDesc));
		depthDesc.Format=d.Format;
		depthDesc.ViewDimension=D3D11_DSV_DIMENSION_TEXTURE2D;
		depthDesc.Texture2D.MipSlice=0;
		device->CreateDepthStencilView(depthStencilBuffer,&depthDesc,depthStencilBufferView);
		if(depthStencilBuffer)depthStencilBuffer->Release();
		immediateContext->OMSetRenderTargets(1, (reinterpret_cast<ID3D11RenderTargetView**>(repository.getResource(RACK::RENDERTARGET, "renderTargetView"))),
			*(reinterpret_cast<ID3D11DepthStencilView**>(repository.getResource(RACK::DEPTHSTENCILVIEW, "depthStencilBufferView"))));
		D3D11_VIEWPORT vp;
		vp.Width=FLOAT(width);
		vp.Height=FLOAT(height);
		vp.MaxDepth=1.0f;
		vp.MinDepth=0.0f;
		vp.TopLeftX=0.0f;
		vp.TopLeftY=0.0f;
		immediateContext->RSSetViewports(1,&vp);
		backBuffer->Release();
		FLOAT fAspect=FLOAT(width)/FLOAT(height);
		fs<<fAspect<<"\n";
		XMMATRIX proj=XMMatrixPerspectiveFovLH(XMConvertToRadians(80.0f),fAspect,5.0f,1100.0f);
		D3D11_MAPPED_SUBRESOURCE data;
		immediateContext->Map(*reinterpret_cast<ID3D11Buffer**>(repository.getResource(RACK::CONSTANTBUFFER, "constBuffer"))
			                  ,0,D3D11_MAP_WRITE_DISCARD,0,&data);
		XMStoreFloat4x4(&outMatrix.Proj_matrix, XMMatrixTranspose(proj));
		memcpy(data.pData,&outMatrix,sizeof(MATRIces));
		immediateContext->Unmap(*reinterpret_cast<ID3D11Buffer**>(repository.getResource(RACK::CONSTANTBUFFER, "constBuffer")),0);
	}

}