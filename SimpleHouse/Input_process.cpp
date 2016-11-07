#include "render.h"
XMMATRIX Rotation2Vectors(XMVECTOR, XMVECTOR);
extern MATRIces outMatrix;
FLOAT pitchAngle = 0;
const XMVECTOR WX_AXIS{1.0f, 0.0f, 0.0f, 0.0f};
const XMVECTOR WY_AXIS{0.0f, 1.0f, 0.0f, 0.0f};
const XMVECTOR WZ_AXIS{0.0f, 0.0f, 1.0f, 0.0f};
const XMVECTOR WORIGIN{0.0f, 0.0f, 0.0f, 1.0f};
XMVECTOR CUP_AXIS{ 0.0f, 1.0f, 0.0f, 0.0f };
XMMATRIX CameraViewMatrix{ WX_AXIS,WY_AXIS,WZ_AXIS,WORIGIN }, ICameraViewMatrix;
XMMATRIX M{ WX_AXIS,WY_AXIS,WZ_AXIS,WORIGIN };
static ofstream err("Input_process.txt");
XMVECTOR Cam_Pos{ 0.0f,0.0f,0.0f,1.0f };
void InputProcess(Input Key)
{
	XMMATRIX tr_mat;
	switch(Key)
	{
		case LEFT:
			{
				tr_mat=XMMatrixTranslation(1.0f,0.0f,0.0f);
			}
			break;
		case RIGHT:
			{
				tr_mat=XMMatrixTranslation(-1.0f,0.0f,0.0f);
	  		}
			break;
		case DOWN:
			{
				tr_mat=XMMatrixTranslation(0.0f,0.0f,1.0f);
			}
			break;
		case UP:
			{
				tr_mat=XMMatrixTranslation(0.0f,0.0f,-1.0f);
			}
			break;
		case STRAFE_UP:
			{
				tr_mat=XMMatrixTranslation(0.0f,-1.0f,0.0f);
			}
			break;
		case STRAFE_DOWN:
			{
				tr_mat=XMMatrixTranslation(0.0f,1.0f,0.0f);
			}
			break;
	}
	D3D11_MAPPED_SUBRESOURCE data;
	CameraViewMatrix = XMMatrixMultiply(CameraViewMatrix, tr_mat);
	ICameraViewMatrix = XMMatrixInverse(nullptr, CameraViewMatrix);
	Cam_Pos = ICameraViewMatrix.r[3];
	XMStoreFloat4(&outMatrix.Cam_Pos, Cam_Pos);
	XMStoreFloat4x4(&outMatrix.VIew_matrix, XMMatrixTranspose(CameraViewMatrix));
	immediateContext->Map(*reinterpret_cast<ID3D11Buffer**>(repository.getResource(RACK::CONSTANTBUFFER, "constBuffer")),0,D3D11_MAP_WRITE_DISCARD,0,&data);
	std::memcpy(data.pData,&outMatrix,sizeof(MATRIces));
	immediateContext->Unmap(*reinterpret_cast<ID3D11Buffer**>(repository.getResource(RACK::CONSTANTBUFFER, "constBuffer")),0);
	
}
void MouseProcess(POINT pt)
{
	pt.x=-pt.x;pt.y=-pt.y;
	XMMATRIX RotMatAroundY, RotMatAroundX, RotMat;
	RotMatAroundY = XMMatrixRotationAxis(CUP_AXIS, float(XMConvertToRadians(pt.x / 2)));
	RotMatAroundX = XMMatrixRotationAxis(WX_AXIS, float(XMConvertToRadians(pt.y / 2)));
	RotMat = XMMatrixMultiply(RotMatAroundY, RotMatAroundX);
	CameraViewMatrix = XMMatrixMultiply(CameraViewMatrix, RotMat);
	XMStoreFloat4x4(&outMatrix.VIew_matrix, XMMatrixTranspose(CameraViewMatrix));
	pitchAngle += pt.y / 2;
	CUP_AXIS = XMVector4Transform(WY_AXIS, XMMatrixRotationX(XMConvertToRadians(pitchAngle)));
	D3D11_MAPPED_SUBRESOURCE data;
	immediateContext->Map(*reinterpret_cast<ID3D11Buffer**>(repository.getResource(RACK::CONSTANTBUFFER, "constBuffer")),0,D3D11_MAP_WRITE_DISCARD,0,&data);
	std::memcpy(data.pData,&outMatrix,sizeof(MATRIces));
	immediateContext->Unmap(*reinterpret_cast<ID3D11Buffer**>(repository.getResource(RACK::CONSTANTBUFFER, "constBuffer")),0);
}
XMMATRIX Rotation2Vectors(XMVECTOR V1, XMVECTOR V2)
{
	XMVECTOR PERP = XMVector3Normalize(XMVector3Cross(V1, V2));
	XMFLOAT3 b,axis;
	XMStoreFloat3(&b, XMVector3AngleBetweenVectors(V1, V2));
	XMStoreFloat3(&axis, PERP);
	float theta = -b.x;
	float x = axis.x;
	float y = axis.y;
	float z = axis.z;
	err << "****\n";
	err << x << " " << y << " " << z << "\n";
	err << theta << "\n";
	float c = cos(theta);
	float s = sin(theta);
	float t = 1 - c;
	XMFLOAT4X4 RotMat;
	RotMat._11 = (t*x*x) + c;
	RotMat._22 = (t*y*y) + c;
	RotMat._33 = (t*z*z) + c;
	RotMat._12 = (t*x*y) - (s*z);
	RotMat._21 = (t*x*y) + (s*z);
	RotMat._13 = (t*x*z) + (s*y);
	RotMat._31 = (t*x*z) - (s*y);
	RotMat._23 = (t*y*z) - (s*x);
	RotMat._32 = (t*y*z) + (s*x);
	RotMat._14 = 0;
	RotMat._24 = 0;
	RotMat._34 = 0;
	RotMat._41 = 0;
	RotMat._42 = 0;
	RotMat._43 = 0;
	RotMat._44 = 1;
	return XMLoadFloat4x4(&RotMat);
}