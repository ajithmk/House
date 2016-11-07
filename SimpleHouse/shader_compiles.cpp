//shaders::shaders(INT8 num, LPCTSTR** shaderPathPointer, LPCSTR** shaderNamePointer)
//	:n{ num }
//{
//	shader_paths = new LPCTSTR*[n];
//	shader_names = new LPCSTR*[n];
//	vert_shad = new ID3D11VertexShader*[n];
//	pix_shad = new ID3D11PixelShader*[n];
//	shaderBlob = new ID3D10Blob*[n];
//	errorBlob = new ID3D10Blob*[n];
//	status = new HRESULT[n];
//	for (INT16 i = 0; i < n; i++)
//	{
//		shader_paths[i] = shaderPathPointer[i];
//	}
//	for (INT16 i = 0; i < n; i++)
//	{
//		shader_names[i] = shaderNamePointer[i];
//	}
//}
//shaders::~shaders() {
//	delete[] shader_paths;
//	delete[] shader_names;
//	delete[] vert_shad;
//	delete[] pix_shad;
//	delete[] shaderBlob, errorBlob, status;
//}
//INT8 shaders::num_of_shaders() const
//{
//	return n;
//}