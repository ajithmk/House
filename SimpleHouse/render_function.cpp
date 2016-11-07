#include "render.h"
XMMATRIX I = XMMatrixIdentity();
extern XMMATRIX M;
extern MATRIces outMatrix;
void renderscene()
{
	static ID3D11RenderTargetView** renderTargetView = reinterpret_cast<ID3D11RenderTargetView**>(repository.getResource(RACK::RENDERTARGET, "renderTargetView"));
	static ID3D11DepthStencilView** depthStencilBufferView = reinterpret_cast<ID3D11DepthStencilView**>(repository.getResource(RACK::DEPTHSTENCILVIEW, "depthStencilBufferView"));
	static ID3D11VertexShader** pointLight_vertexShader= reinterpret_cast<ID3D11VertexShader**>(repository.getResource(RACK::VSHADER, "pointLight_vertexShader"));
	static ID3D11PixelShader** pointLight_pixelShader = reinterpret_cast<ID3D11PixelShader**>(repository.getResource(RACK::PSHADER, "pointLight_pixelShader"));
	static ID3D11VertexShader** skyBox_vertexShader = reinterpret_cast<ID3D11VertexShader**>(repository.getResource(RACK::VSHADER, "skyBox_vertexShader"));
	static ID3D11PixelShader** skyBox_pixelShader = reinterpret_cast<ID3D11PixelShader**>(repository.getResource(RACK::PSHADER, "skyBox_pixelShader"));
	static ID3D11VertexShader** pointLightNormal_vertexShader = reinterpret_cast<ID3D11VertexShader**>(repository.getResource(RACK::VSHADER, "pointLightNormal_vertexShader"));
	static ID3D11PixelShader** pointLightNormal_pixelShader = reinterpret_cast<ID3D11PixelShader**>(repository.getResource(RACK::PSHADER, "pointLightNormal_pixelShader"));
	static INT num_of_obj = repository.getNumOfObjs();
	static RACK::VERTEXBUFFERINFO* info = repository.getAdditionalVertexInfo();
	static ID3D11ShaderResourceView** pencil_shades= reinterpret_cast<ID3D11ShaderResourceView**>(repository.getResource(RACK::SHADERRESOURCE, "pencil_shades"));
	static ID3D11ShaderResourceView** normalSRV = reinterpret_cast<ID3D11ShaderResourceView**>(repository.getResource(RACK::SHADERRESOURCE, "normalSRV"));
	static ID3D11ShaderResourceView** heightSRV = reinterpret_cast<ID3D11ShaderResourceView**>(repository.getResource(RACK::SHADERRESOURCE, "heightSRV"));
	static ID3D11ShaderResourceView** skyBoxSRV = reinterpret_cast<ID3D11ShaderResourceView**>(repository.getResource(RACK::SHADERRESOURCE, "skyBoxSRV"));
	static ID3D11ShaderResourceView** OuterWallWood = reinterpret_cast<ID3D11ShaderResourceView**>(repository.getResource(RACK::SHADERRESOURCE, "OuterWallWood"));
	static ID3D11ShaderResourceView** WoodenPlank = reinterpret_cast<ID3D11ShaderResourceView**>(repository.getResource(RACK::SHADERRESOURCE, "WoodenPlank"));
	static ID3D11ShaderResourceView** floor1 = reinterpret_cast<ID3D11ShaderResourceView**>(repository.getResource(RACK::SHADERRESOURCE, "floor1"));
	static ID3D11ShaderResourceView** ceiling1 = reinterpret_cast<ID3D11ShaderResourceView**>(repository.getResource(RACK::SHADERRESOURCE, "ceiling1"));
	static ID3D11ShaderResourceView** roomwall = reinterpret_cast<ID3D11ShaderResourceView**>(repository.getResource(RACK::SHADERRESOURCE, "roomwall"));
	static ID3D11ShaderResourceView** stone1 = reinterpret_cast<ID3D11ShaderResourceView**>(repository.getResource(RACK::SHADERRESOURCE, "stone1"));
	static ID3D11ShaderResourceView** cement = reinterpret_cast<ID3D11ShaderResourceView**>(repository.getResource(RACK::SHADERRESOURCE, "cement"));
	static ID3D11ShaderResourceView** pattern1 = reinterpret_cast<ID3D11ShaderResourceView**>(repository.getResource(RACK::SHADERRESOURCE, "pattern1"));
	static ID3D11ShaderResourceView** normal_ground = reinterpret_cast<ID3D11ShaderResourceView**>(repository.getResource(RACK::SHADERRESOURCE, "normal_ground"));
	static ID3D11ShaderResourceView** pointLight_DepthCube_SRV = reinterpret_cast<ID3D11ShaderResourceView**>(repository.getResource(RACK::SHADERRESOURCE, "pointLight_DepthCube_SRV"));
	static ID3D11Buffer** pointLight_ShadowProj = reinterpret_cast<ID3D11Buffer**>(repository.getResource(RACK::CONSTANTBUFFER, "pointLight_ShaodwProj"));
	static ID3D11Buffer** light_pos = reinterpret_cast<ID3D11Buffer**>(repository.getResource(RACK::CONSTANTBUFFER, "light_pos"));
	static ID3D11Buffer** constBuffer= reinterpret_cast<ID3D11Buffer**>(repository.getResource(RACK::CONSTANTBUFFER, "constBuffer"));
	float clearColor[4]={0.0f,0.0f,0.0f,1.0f};
	float clearUAV[4]={1.0,0.0,0.0,0.0};
	immediateContext->OMSetRenderTargets(1, renderTargetView, *depthStencilBufferView);
	immediateContext->ClearRenderTargetView(*renderTargetView, clearColor);
	immediateContext->ClearDepthStencilView(*depthStencilBufferView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 1);
	immediateContext->VSSetShader(*pointLight_vertexShader, NULL, NULL);
	immediateContext->PSSetShader(*pointLight_pixelShader, NULL, NULL);
	immediateContext->PSSetShaderResources(0, 1, pencil_shades);
	immediateContext->VSSetConstantBuffers(0, 1, constBuffer);
	immediateContext->PSSetShaderResources(1, 1, pointLight_DepthCube_SRV);
	immediateContext->PSSetShaderResources(2, 1, heightSRV);
	immediateContext->VSSetConstantBuffers(1, 1, light_pos);
	immediateContext->PSSetConstantBuffers(2, 1, pointLight_ShadowProj);
	D3D11_MAPPED_SUBRESOURCE data;
	XMStoreFloat4x4(&outMatrix.Model_matrix, I);
	immediateContext->Map(*reinterpret_cast<ID3D11Buffer**>(repository.getResource(RACK::CONSTANTBUFFER, "constBuffer")), 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	std::memcpy(data.pData, &outMatrix, sizeof(MATRIces));
	immediateContext->Unmap(*reinterpret_cast<ID3D11Buffer**>(repository.getResource(RACK::CONSTANTBUFFER, "constBuffer")), 0);
	immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	for (int i = 0; (i<7); i++)
		{
		   immediateContext->DrawIndexed(info[i].SIZES_I,info[i].OFFSETS_I,info[i].OFFSETS_V);
		}
	immediateContext->PSSetShaderResources(0, 1, WoodenPlank);
	for (int i = 7; (i<11); i++)
	{
		immediateContext->DrawIndexed(info[i].SIZES_I, info[i].OFFSETS_I, info[i].OFFSETS_V);
	}
	immediateContext->PSSetShaderResources(0, 1, OuterWallWood);
	for (int i = 11; (i<12); i++)
	{
		immediateContext->DrawIndexed(info[i].SIZES_I, info[i].OFFSETS_I, info[i].OFFSETS_V);
	}
	immediateContext->PSSetShaderResources(0, 1, floor1);
	for (int i = 12; (i<20); i++)
	{
		immediateContext->DrawIndexed(info[i].SIZES_I, info[i].OFFSETS_I, info[i].OFFSETS_V);
	}
	immediateContext->PSSetShaderResources(0, 1, ceiling1);
	for (int i = 20; (i<31); i++)
	{
		immediateContext->DrawIndexed(info[i].SIZES_I, info[i].OFFSETS_I, info[i].OFFSETS_V);
	}
	immediateContext->PSSetShaderResources(0, 1, roomwall);
	for (int i = 31; (i<41); i++)
	{
		immediateContext->DrawIndexed(info[i].SIZES_I, info[i].OFFSETS_I, info[i].OFFSETS_V);
	}
	immediateContext->PSSetShaderResources(0, 1, stone1);
	for (int i = 41; (i<42); i++)
	{
		immediateContext->DrawIndexed(info[i].SIZES_I, info[i].OFFSETS_I, info[i].OFFSETS_V);
	}
	immediateContext->PSSetShaderResources(0, 1, cement);
	for (int i = 42; (i<46); i++)
	{
		immediateContext->DrawIndexed(info[i].SIZES_I, info[i].OFFSETS_I, info[i].OFFSETS_V);
	}
	immediateContext->PSSetShaderResources(0, 1, pattern1);
	for (int i = 46; (i<47); i++)
	{
		immediateContext->DrawIndexed(info[i].SIZES_I, info[i].OFFSETS_I, info[i].OFFSETS_V);
	}
	immediateContext->PSSetShaderResources(0, 1, normal_ground);
	for (int i = 47; (i<48); i++)
	{
		immediateContext->DrawIndexed(info[i].SIZES_I, info[i].OFFSETS_I, info[i].OFFSETS_V);
	}
	XMStoreFloat4x4(&outMatrix.Model_matrix, XMMatrixTranspose(M));
	immediateContext->Map(*reinterpret_cast<ID3D11Buffer**>(repository.getResource(RACK::CONSTANTBUFFER, "constBuffer")), 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	std::memcpy(data.pData, &outMatrix, sizeof(MATRIces));
	immediateContext->Unmap(*reinterpret_cast<ID3D11Buffer**>(repository.getResource(RACK::CONSTANTBUFFER, "constBuffer")), 0);
	immediateContext->DrawIndexed(info[48].SIZES_I, info[48].OFFSETS_I, info[48].OFFSETS_V);
	XMStoreFloat4x4(&outMatrix.Model_matrix, I);
	immediateContext->Map(*reinterpret_cast<ID3D11Buffer**>(repository.getResource(RACK::CONSTANTBUFFER, "constBuffer")), 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	std::memcpy(data.pData, &outMatrix, sizeof(MATRIces));
	immediateContext->Unmap(*reinterpret_cast<ID3D11Buffer**>(repository.getResource(RACK::CONSTANTBUFFER, "constBuffer")), 0);
	immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	immediateContext->VSSetShader(*skyBox_vertexShader, NULL, NULL);
	immediateContext->PSSetShader(*skyBox_pixelShader, NULL, NULL);
	immediateContext->PSSetShaderResources(1, 1, skyBoxSRV);
	immediateContext->Draw(4,0);
	////immediateContext->OMSetRenderTargetsAndUnorderedAccessViews(1,&renderTargetView,depthStencilBufferView,1,1,&pass_uav_view,NULL);
	//immediateContext->ClearRenderTargetView(renderTargetView,clearColor);
	//immediateContext->ClearRenderTargetView(RTV[0],clearColor);
	//immediateContext->ClearRenderTargetView(RTV[1],clearColor);
	//immediateContext->ClearRenderTargetView(RTV[2],clearColor);
	////immediateContext->ClearUnorderedAccessViewFloat(pass_uav_view,clearUAV);
	//immediateContext->OMSetRenderTargets(1,&RTV[0],depthStencilBufferView);
	//immediateContext->ClearDepthStencilView(depthStencilBufferView,D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL,1.0f,1.0f);
	//immediateContext->VSSetShader(vert_shad[1],NULL,NULL);
	//immediateContext->PSSetShader(pix_shad[1],NULL,NULL);
	//immediateContext->PSSetConstantBuffers(1,1,&ambience_color);
	//for(int i=0;(i<num_of_obj)&(i!=9);i++)
	//{
	//
	//	immediateContext->PSSetShaderResources(0,1,&SRV[i]);
	//    immediateContext->DrawIndexed(SIZES_I[i],OFFSETS_I[i],OFFSETS_V[i]);
	//}
	//immediateContext->VSSetShader(vert_shad[2],NULL,NULL);
	//immediateContext->PSSetShader(pix_shad[2],NULL,NULL);
	//immediateContext->VSSetConstantBuffers(1,1,&moon_plane);
	//immediateContext->PSSetConstantBuffers(3,1,&moon_diffuse);
	//immediateContext->OMSetRenderTargets(1,&RTV[1],depthStencilBufferView);
	//immediateContext->ClearDepthStencilView(depthStencilBufferView,D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL,1.0f,1.0f);
	//for(int i=0;(i<num_of_obj)&(i!=9);i++)
	//{
	//
	//	immediateContext->PSSetShaderResources(0,1,&SRV[i]);
	//    immediateContext->DrawIndexed(SIZES_I[i],OFFSETS_I[i],OFFSETS_V[i]);
	//}
	//immediateContext->VSSetShader(vert_shad[3],NULL,NULL);
	//immediateContext->PSSetShader(pix_shad[3],NULL,NULL);
	//immediateContext->VSSetConstantBuffers(0,1,&constBuffer);
	//immediateContext->VSSetConstantBuffers(1,1,&light_pos);
	//immediateContext->PSSetConstantBuffers(2,1,&diffuse_color);
	//immediateContext->PSSetConstantBuffers(3,1,&shadow_proj);
	//immediateContext->OMSetRenderTargets(1,&RTV[2],depthStencilBufferView);
	//immediateContext->ClearDepthStencilView(depthStencilBufferView,D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL,1.0f,1.0f);
	//for(int i=0;(i<num_of_obj)&(i!=9);i++)
	//{
	//
	//	immediateContext->PSSetShaderResources(0,1,&SRV[i]);
	//    immediateContext->DrawIndexed(SIZES_I[i],OFFSETS_I[i],OFFSETS_V[i]);
	//}

	//immediateContext->OMSetRenderTargets(1,&renderTargetView,depthStencilBufferView);
	//immediateContext->ClearDepthStencilView(depthStencilBufferView,D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL,1.0f,1.0f);
	//immediateContext->VSSetShader(vert_shad[4],NULL,NULL);
	//immediateContext->PSSetShader(pix_shad[4],NULL,NULL);
	//immediateContext->VSSetConstantBuffers(0,1,&constBuffer);
	//immediateContext->PSSetShaderResources(0,1,&final_pass_view);
	//for(int i=0;(i<num_of_obj)&(i!=9);i++)
	//{
	//
	//	//immediateContext->PSSetShaderResources(0,1,&SRV[i]);
	//    immediateContext->DrawIndexed(SIZES_I[i],OFFSETS_I[i],OFFSETS_V[i]);
	//}

	//immediateContext->VSSetShader(vert_shad[0],NULL,NULL);
	//immediateContext->PSSetShader(pix_shad[0],NULL,NULL);
	//immediateContext->VSSetConstantBuffers(0,1,&constBuffer);
	//immediateContext->PSSetShaderResources(0,1,&SRV[9]);
	//immediateContext->DrawIndexed(SIZES_I[9],OFFSETS_I[9],OFFSETS_V[9]);
	////immediateContext->OMSetRenderTargets(1,&RTV[1],depthStencilBufferView);
	swapChain->Present(0,0);
}