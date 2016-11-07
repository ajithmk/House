#include "render.h"
extern ID3D11Texture2D* pointLight_DepthCube;
void ShadowPass(INT width,INT height)
{
	ofstream si("shadow issues.txt");
	shadow_matrix shadow_matrices[6];
	XMVECTOR CamPos = XMVectorSet(0.0f, 20.0f, 10.0f, 1.0f);
	XMVECTOR PY = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR NY = XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f);
	XMVECTOR PX = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR NX = XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR PZ = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR NZ = XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);
	shadow_matrices[0].view_matrix = XMMatrixTranspose(XMMatrixLookToLH(CamPos, PX, PY));
	shadow_matrices[1].view_matrix = XMMatrixTranspose(XMMatrixLookToLH(CamPos, NX, PY));
	shadow_matrices[4].view_matrix = XMMatrixTranspose(XMMatrixLookToLH(CamPos, PZ, PY));
	shadow_matrices[5].view_matrix = XMMatrixTranspose(XMMatrixLookToLH(CamPos, NZ, PY));
	shadow_matrices[2].view_matrix = XMMatrixTranspose(XMMatrixLookToLH(CamPos, PY, NZ));
	shadow_matrices[3].view_matrix = XMMatrixTranspose(XMMatrixLookToLH(CamPos, NY, PZ));
	FLOAT fAspect = FLOAT(1.0) / FLOAT(1.0);
	shadow_matrices[0].proj_matrix = XMMatrixTranspose(XMMatrixPerspectiveFovLH(XMConvertToRadians(90.0f), fAspect, 0.1f, 400.0f));
	shadow_matrices[1].proj_matrix = shadow_matrices[0].proj_matrix;
	shadow_matrices[2].proj_matrix = shadow_matrices[0].proj_matrix;
	shadow_matrices[3].proj_matrix = shadow_matrices[0].proj_matrix;
	shadow_matrices[4].proj_matrix = shadow_matrices[0].proj_matrix;
	shadow_matrices[5].proj_matrix = shadow_matrices[0].proj_matrix;
	D3D11_VIEWPORT vp;
	vp.Width=1024;
	vp.Height=1024;
	vp.MaxDepth=1.0f;
	vp.MinDepth=0.0f;
	vp.TopLeftX=0.0f;
	vp.TopLeftY=0.0f;
	immediateContext->RSSetViewports(1,&vp);
	D3D11_DEPTH_STENCIL_DESC dp;
	ZeroMemory(&dp, sizeof(dp));
	dp.DepthEnable = TRUE;
	dp.StencilEnable = FALSE;
	dp.DepthFunc = D3D11_COMPARISON_LESS;
	dp.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dp.StencilEnable = FALSE;
	ID3D11DepthStencilState* depthState;
	device->CreateDepthStencilState(&dp, &depthState);
	immediateContext->OMSetDepthStencilState(depthState, NULL);
	INT num_of_obj = repository.getNumOfObjs();
	RACK::VERTEXBUFFERINFO* info = repository.getAdditionalVertexInfo();
	ID3D11Buffer** pointLightShadow_buffer = reinterpret_cast<ID3D11Buffer**>(repository.getResource(RACK::CONSTANTBUFFER, "pointLightShadow_buffer"));
	ID3D11DepthStencilView** pointLight_DepthCube_DSV= reinterpret_cast<ID3D11DepthStencilView**>(repository.getResource(RACK::DEPTHSTENCILVIEW, "pointLight_DepthCube_DSV"));
	ID3D11VertexShader** pointLightD_vertexShader = reinterpret_cast<ID3D11VertexShader**>(repository.getResource(RACK::VSHADER, "pointLightD_vertexShader"));
	ID3D11PixelShader** pointLightD_pixelShader = reinterpret_cast<ID3D11PixelShader**>(repository.getResource(RACK::PSHADER, "pointLightD_pixelShader"));
	immediateContext->VSSetShader(*pointLightD_vertexShader, NULL, NULL);
	immediateContext->PSSetShader(NULL, NULL, NULL);
	immediateContext->VSSetConstantBuffers(0, 1, pointLightShadow_buffer);
	for(int i=0;i<6;i++)
	{
		immediateContext->UpdateSubresource(*pointLightShadow_buffer,0,NULL,&shadow_matrices[i],0,0);
		immediateContext->OMSetRenderTargets(0,NULL, pointLight_DepthCube_DSV[i]);
		immediateContext->ClearDepthStencilView(pointLight_DepthCube_DSV[i],D3D11_CLEAR_DEPTH,1.0f,NULL);
		for (int i = 0; (i<num_of_obj); i++)
		{
			si << i << "\n";
			immediateContext->DrawIndexed(info[i].SIZES_I, info[i].OFFSETS_I, info[i].OFFSETS_V);
		}
	}
//	
//	ZeroMemory(&desc,sizeof(desc));
//	desc.ArraySize=1;
//	desc.BindFlags=D3D11_BIND_SHADER_RESOURCE|D3D11_BIND_DEPTH_STENCIL;
//	desc.CPUAccessFlags=0;
//	desc.Format=DXGI_FORMAT_R32_TYPELESS;
//	desc.Height=1024;
//	desc.Width=desc.Height;
//	desc.MipLevels=1;
//	desc.SampleDesc.Count=1;
//	desc.SampleDesc.Quality=0;
//	desc.Usage=D3D11_USAGE_DEFAULT;
//	ID3D11Texture2D* dir_shadow;
//	view1=device->CreateTexture2D(&desc,NULL,&dir_shadow);
//	si<<hex<<showbase<<view1<<"\n";
//	ZeroMemory(&shader_view,sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
//	shader_view.Format=DXGI_FORMAT_R32_FLOAT;
//	shader_view.ViewDimension=D3D11_SRV_DIMENSION_TEXTURE2D;
//	shader_view.Texture2D.MipLevels=1;
//	shader_view.Texture2D.MostDetailedMip=0;
//	view2=device->CreateShaderResourceView(dir_shadow,&shader_view,&dir_shadow_shader_view);
//	si<<hex<<showbase<<view2<<" but why\n";
//	ID3D11DepthStencilView* dir_shadow_depth_view;
//	ZeroMemory(&dep_view,sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
//	dep_view.Format=DXGI_FORMAT_D32_FLOAT;
//	dep_view.ViewDimension=D3D11_DSV_DIMENSION_TEXTURE2D;
//	dep_view.Texture2D.MipSlice=0;
//	view3=device->CreateDepthStencilView(dir_shadow,&dep_view,&dir_shadow_depth_view);
//	si<<hex<<showbase<<view3<<"\n";
//	si<<"here"<<"\n";
//	XMVECTOR MoonPos=XMVectorSet(0.0f,30.0f,100.0f,1.0f);
//	XMVECTOR MoonDir=XMVectorSet(0.0f,-1.0f,-1.0f,0.0f);
//	shadow_matrices[0].proj_matrix=XMMatrixTranspose(XMMatrixOrthographicLH(400,400,0.1,400));
//	shadow_matrices[0].view_matrix=XMMatrixTranspose(XMMatrixLookToLH(MoonPos,MoonDir,PY));
//	immediateContext->UpdateSubresource(shadow_buffer,0,NULL,&shadow_matrices[0],0,0);
//	immediateContext->OMSetRenderTargets(0,NULL,dir_shadow_depth_view);
//	immediateContext->ClearDepthStencilView(dir_shadow_depth_view,D3D11_CLEAR_DEPTH,1.0f,NULL);
//	for(int j=0;(j<num_of_obj)&(j!=9);j++)
//	{
//	   immediateContext->DrawIndexed(SIZES_I[j],OFFSETS_I[j],OFFSETS_V[j]);
//	}
//	struct sshadow
//	{
//		XMMATRIX sm;
//	}sshadow1;
//	sshadow1.sm=XMMatrixTranspose(XMMatrixMultiply(shadow_matrices[0].proj_matrix,shadow_matrices[0].view_matrix));
//	D3D11_BUFFER_DESC bd;
//	ZeroMemory(&bd,sizeof(D3D11_BUFFER_DESC));
//	bd.BindFlags=D3D11_BIND_CONSTANT_BUFFER;
//	bd.Usage=D3D11_USAGE_DEFAULT;
//	bd.ByteWidth=sizeof(sshadow);
//	D3D11_SUBRESOURCE_DATA sd2;
//	ZeroMemory(&sd2,sizeof(D3D11_SUBRESOURCE_DATA));
//	sd2.pSysMem=&sshadow1;
//	device->CreateBuffer(&bd,&sd2,&dir_shadow_matrix);
//
//	/*ZeroMemory(&desc,sizeof(desc));
//	desc.ArraySize=3;
//	desc.BindFlags=D3D11_BIND_SHADER_RESOURCE|D3D11_BIND_UNORDERED_ACCESS;
//	desc.CPUAccessFlags=0;
//	desc.Format=DXGI_FORMAT_R8G8B8A8_UNORM;
//	desc.Height=250;
//	desc.Width=desc.Height;
//	desc.MipLevels=1;
//	desc.SampleDesc.Count=1;
//	desc.SampleDesc.Quality=0;
//	desc.Usage=D3D11_USAGE_DEFAULT;
//	ID3D11Texture2D* passes;
//	view1=device->CreateTexture2D(&desc,NULL,&passes);
//	ZeroMemory(&shader_view,sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
//	shader_view.Format=DXGI_FORMAT_R8G8B8A8_UNORM;
//	shader_view.ViewDimension=D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
//	shader_view.Texture2DArray.MipLevels=1;
//	shader_view.Texture2DArray.MostDetailedMip=0;
//	shader_view.Texture2DArray.ArraySize=3;
//	view2=device->CreateShaderResourceView(passes,&shader_view,&pass_shader_view);
//	D3D11_UNORDERED_ACCESS_VIEW_DESC uav_view;
//	ZeroMemory(&uav_view,sizeof(D3D11_UNORDERED_ACCESS_VIEW_DESC));
//	uav_view.Format=DXGI_FORMAT_R8G8B8A8_UNORM;
//	uav_view.ViewDimension=D3D11_UAV_DIMENSION_TEXTURE2DARRAY;
//	uav_view.Texture2DArray.FirstArraySlice=0;
//	uav_view.Texture2DArray.ArraySize=3;
//	view3=device->CreateUnorderedAccessView(passes,&uav_view,&pass_uav_view);
//	si<<hex<<showbase<<view1<<"\n"<<view2<<"\n"<<view3<<"\n";*/
//
//	ZeroMemory(&desc,sizeof(desc));
//	desc.ArraySize=3;
//	desc.BindFlags=D3D11_BIND_SHADER_RESOURCE|D3D11_BIND_RENDER_TARGET;
//	desc.CPUAccessFlags=0;
//	desc.Format=DXGI_FORMAT_R8G8B8A8_UNORM;
//	desc.Height=212;
//	desc.Width=234;
//	desc.MipLevels=1;
//	desc.SampleDesc.Count=1;
//	desc.SampleDesc.Quality=0;
//	desc.Usage=D3D11_USAGE_DEFAULT;
//	ID3D11Texture2D* passes;
//	view1=device->CreateTexture2D(&desc,NULL,&passes);
//	D3D11_RENDER_TARGET_VIEW_DESC rt_view;
//	ZeroMemory(&rt_view,sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
//	rt_view.Format=DXGI_FORMAT_R8G8B8A8_UNORM;
//	rt_view.ViewDimension=D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
//	rt_view.Texture2DArray.ArraySize=1;
//	for (int i=0;i<3;i++)
//	{
//	shader_view.Texture2DArray.FirstArraySlice =i;
//	view2=device->CreateRenderTargetView(passes,&rt_view,&RTV[i]);
//	}
//	D3D11_SHADER_RESOURCE_VIEW_DESC final_view;
//	ZeroMemory(&final_view,sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
//	final_view.Format=DXGI_FORMAT_R8G8B8A8_UNORM;
//	final_view.ViewDimension=D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
//	final_view.Texture2DArray.FirstArraySlice=0;
//	final_view.Texture2DArray.ArraySize=3;
//	final_view.Texture2DArray.MipLevels=1;
//	final_view.Texture2DArray.MostDetailedMip=0;
//	view3=device->CreateShaderResourceView(passes,&final_view,&final_pass_view);
//	si<<hex<<showbase<<view1<<"\n"<<view2<<"\n"<<view3<<"\n";
//
//	D3D11_BLEND_DESC bdesc;
//	ZeroMemory(&bdesc,sizeof(D3D11_BLEND_DESC));
//	bdesc.AlphaToCoverageEnable=FALSE;
//	bdesc.IndependentBlendEnable=FALSE;
//	bdesc.RenderTarget[0].BlendEnable=TRUE;
//	bdesc.RenderTarget[0].SrcBlend=D3D11_BLEND_ONE;
//	bdesc.RenderTarget[0].DestBlend=D3D11_BLEND_ONE;
//	bdesc.RenderTarget[0].BlendOp=D3D11_BLEND_OP_ADD;
//	bdesc.RenderTarget[0].SrcBlendAlpha=D3D11_BLEND_ONE;
//	bdesc.RenderTarget[0].DestBlendAlpha=D3D11_BLEND_ONE;
//	bdesc.RenderTarget[0].BlendOpAlpha=D3D11_BLEND_OP_ADD;
//	bdesc.RenderTarget[0].RenderTargetWriteMask=D3D11_COLOR_WRITE_ENABLE_ALL;
//	ID3D11BlendState* blendState;
//	device->CreateBlendState(&bdesc,&blendState);
//	//immediateContext->OMSetBlendState(blendState,0,0xffffffff);
//	
//	immediateContext->OMSetRenderTargets(1,&renderTargetView,depthStencilBufferView);
//	immediateContext->PSSetShaderResources(1,1,&shadow_shader_view);
//	immediateContext->PSSetShaderResources(2,1,&dir_shadow_shader_view);
//	immediateContext->VSSetConstantBuffers(2,1,&shadow_buffer);
//	if(psBlob) psBlob->Release();
//	if(vsBlob) vsBlob->Release();
//	if(psError) psError->Release();
//	if(vsError) vsError->Release();
//	if(vertex_shad) vertex_shad->Release();
//	if(pixel_shad) pixel_shad->Release();
}