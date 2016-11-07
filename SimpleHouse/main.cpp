#include "render.h"
void renderscene(void);
bool setupDX(HWND);
void cleanup();
void changeSize(INT,INT,HWND);
void InputProcess(Input);
void MouseProcess(POINT);
RECT client_rect;
POINT pt,cur_pos,prevPos={0,0},dist;
void createVerBuff(void);
void compileShaders(void);
void bufferConstantsSetup(void);
void textureBufferSetup(void);
void ShadowPass(INT width=250,INT height=250);
ofstream main("main.txt");
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	MSG msg={0};WNDCLASS wc={};HWND hWnd;
	wc.style=CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
	wc.lpfnWndProc=WndProc;
	wc.hInstance=hInstance;
	wc.hIcon=NULL;
	wc.hbrBackground= (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.hCursor=LoadCursor(NULL,IDC_ARROW);
	wc.lpszMenuName=NULL;
	wc.lpszClassName=L"lpszAppName";
	if(RegisterClass(&wc)==0)
		return FALSE;
	hWnd=CreateWindow(L"lpszAppName",L"lpszAppName",
		WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
		0,0,
		250,250,
		NULL,NULL,
		hInstance,NULL);
	if(hWnd==NULL)
		return FALSE;
	ShowWindow(hWnd,SW_SHOW);
	while(WM_QUIT!=msg.message )
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		}
		else renderscene();
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HDC hDC;
	HWND active_win;
	int xPos,yPos;
	switch (uMsg)
	{
	case WM_CREATE:
		{
			main<<"set\n";
		bool status=setupDX(hWnd);
		if(!status)return FALSE;
		main<<"ok!\n"<<endl;
		compileShaders();
		createVerBuff();
		bufferConstantsSetup();
		textureBufferSetup();
		ShadowPass();
		}
		break;
	case WM_PAINT:
		{
			renderscene();
		ValidateRect(hWnd,NULL);
		}
		break;
	case WM_DESTROY:
		{
		cleanup();
		PostQuitMessage(0);
		}
		break;
	case WM_SIZE:
		changeSize(LOWORD(lParam),HIWORD(lParam),hWnd);
		main<<LOWORD(lParam)<<" "<<HIWORD(lParam)<<"\n";
		InvalidateRect(hWnd,NULL,FALSE);
		break;
	case WM_ACTIVATE:
		{
			if((LOWORD(wParam)==WA_ACTIVE))
			{
				ShowCursor(FALSE);
				GetClientRect(hWnd,&client_rect);
			    GetCursorPos(&cur_pos);
			    ScreenToClient(hWnd,&cur_pos);
			    (pt).x=client_rect.right;(pt).y=client_rect.bottom;
			    ClientToScreen(hWnd,&pt);
			    SetCursorPos((pt).x/2,(pt).y/2);
			}
		 }
		break;
	case WM_MOUSEACTIVATE:
		{
			GetClientRect(hWnd,&client_rect);
			GetCursorPos(&cur_pos);
			ScreenToClient(hWnd,&cur_pos);
			if((cur_pos.x>0)&(cur_pos.x<client_rect.right)&(cur_pos.y>0)&(cur_pos.y<client_rect.bottom))
			{
			    prevPos.x=pt.x/2;prevPos.y=pt.y/2;
				(pt).x=client_rect.right;(pt).y=client_rect.bottom;
			    ClientToScreen(hWnd,&pt);
			    SetCursorPos((pt).x/2,(pt).y/2);
			}
		}
		return (MA_NOACTIVATE);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			{
				InputProcess(STRAFE_UP);
				InvalidateRect(hWnd,NULL,FALSE);
			}
			break;
		case VK_DOWN:
			{
				InputProcess(STRAFE_DOWN);
				InvalidateRect(hWnd,NULL,FALSE);
			}
			break;
		}
		break;
	case WM_CHAR:
		switch (wParam)
		{
	case 0x61:
		{
			InputProcess(LEFT);
			InvalidateRect(hWnd,NULL,FALSE);
		}
		break;
	case 0x64:
		{
			InputProcess(RIGHT);
		    InvalidateRect(hWnd,NULL,FALSE);
		}
		break;
	case 0x73:
		{
			InputProcess(DOWN);
			InvalidateRect(hWnd,NULL,FALSE);
		}
		break;
	case 0x77:
		{
			InputProcess(UP);
			InvalidateRect(hWnd,NULL,FALSE);
		}
		break;
	case VK_ESCAPE:
		{
			PostQuitMessage(0);
		}
		break;
	//case VK_CONTROL:
		//{
			//HCURSOR curHandle=(HCURSOR)LoadImage(NULL,MAKEINTRESOURCE(OCR_HAND),2,0,0,LR_DEFAULTSIZE|LR_SHARED);
			//SetCursor(curHandle);
		//}
		//break;
		}
		break;
	//case WM_KEYUP:
		//switch(wParam)
		//{
		//case VK_CONTROL:
			//HCURSOR curHandle=(HCURSOR)LoadImage(NULL,MAKEINTRESOURCE(OCR_NORMAL),2,0,0,LR_DEFAULTSIZE|LR_SHARED);
			//SetCursor(curHandle);
		//}
		//break;
		//case WM_SETCURSOR:
		//{
			//if((GetKeyState(VK_CONTROL)<0))
			//{
				//HCURSOR curHandle=(HCURSOR)LoadImage(NULL,MAKEINTRESOURCE(OCR_HAND),2,0,0,LR_DEFAULTSIZE|LR_SHARED);
			    //SetCursor(curHandle);
			//}
			//else
			//{
				//HCURSOR curHandle=(HCURSOR)LoadImage(NULL,MAKEINTRESOURCE(OCR_NORMAL),2,0,0,LR_DEFAULTSIZE|LR_SHARED);
			    //SetCursor(curHandle);
			//}
		//}
		//break;
	case WM_MOUSEMOVE:
		{
			active_win=GetActiveWindow();
			if (active_win!=hWnd)
				ShowCursor(TRUE);
			if(active_win==hWnd)
			{
				xPos=GET_X_LPARAM(lParam);yPos=GET_Y_LPARAM(lParam);
				dist.x=xPos-prevPos.x;dist.y=yPos-prevPos.y;
				prevPos.x=xPos;prevPos.y=yPos;
				MouseProcess(dist);
				InvalidateRect(hWnd,NULL,FALSE);
			    GetClientRect(hWnd,&client_rect);
				GetCursorPos(&cur_pos);
				ScreenToClient(hWnd,&cur_pos);
				SetCapture(hWnd);
				if((cur_pos.x<2)|(cur_pos.x>client_rect.right-2)|(cur_pos.y<2)|(cur_pos.y>client_rect.bottom-2))
				{
					(pt).x=client_rect.right;(pt).y=client_rect.bottom;
					prevPos.x=pt.x/2;prevPos.y=pt.y/2;
			        ClientToScreen(hWnd,&pt);
			        SetCursorPos((pt).x/2,(pt).y/2);
			        //SetRect(&client_rect,client_rect.left,client_rect.top,client_rect.right+1,client_rect.bottom+1);
			        //ClipCursor(&client_rect);
					ReleaseCapture();
				}
			}
		}
		break;
		default :
			return(DefWindowProc(hWnd,uMsg,wParam,lParam));
	}
	return(0L);
}