#include <d3d9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )
#include<d3dx9.h>
#include"Sprite.h"
#include"Menu.h"	
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
LPDIRECT3D9         g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9   g_pd3dDevice = NULL; // Our rendering device
Menu  GameMenu;
PICTURE *g_picture = NULL;
//extern Animation Player;
HRESULT InitD3D( HWND hWnd )
{
    // Create the D3D object, which is needed to create the D3DDevice.
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

   
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

   
    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

    // Device state would normally be set here
	GameMenu.SetDevice(g_pd3dDevice);
	D3DXCreateSprite(g_pd3dDevice, &g_picture->picture);
	D3DXCreateFontW(g_pd3dDevice, 250, 250, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("굴림체"), &g_picture->font);
    return S_OK;
}

VOID InitCharater() {
	//Image newImage = { { 0,0,183,275 },L"아이유 2.jpg" ,{ 960,0,0}, { 0,0,0 } };
	//Player.ImageInit(g_pd3dDevice, &newImage);
	//Player.ImageInit(g_pd3dDevice, &newImage);
	/*newImage = { { 0,0,183,275 },L"아이유 2.jpg" ,{ 450,800,0}, { 0,0,0 } };
	Enemy.ImageInit(g_pd3dDevice, &newImage);*/
}

VOID Cleanup()
{
    if( g_pd3dDevice != NULL )
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )
        g_pD3D->Release();
	if (g_picture != NULL) {
		g_picture->picture->Release();
	}
}


VOID Update() {

	

	switch (GameMenu.GameCheck)
	{
	case MenuCheck::Main:
	if (GetAsyncKeyState(VK_F1)) {
		GameMenu.GameCheck = MenuCheck::Option;
	}

	if (GetAsyncKeyState(VK_F3)) {
	}
		break;
	case MenuCheck::GameStart:
		if (GetAsyncKeyState(VK_F5)) {
			GameMenu.Player._3DirCheck = true;
		}

		if (GetAsyncKeyState(VK_LEFT)) {
			GameMenu.Player.MovePlayer(Move::Left);
		}
		if (GetAsyncKeyState(VK_RIGHT)) {
			GameMenu.Player.MovePlayer(Move::Right);
		}
		if (GetAsyncKeyState(VK_UP)&& GameMenu.Player.JumpCount > 0) {
			GameMenu.Player.MovePlayer(Move::Up);
			GameMenu.Player.JumpCount--;
		}
		if (GetAsyncKeyState(VK_NUMPAD4)) {
			GameMenu.Player.MovePlayer(Move::DirDown);
		}
		if (GetAsyncKeyState(VK_NUMPAD6)) {
			GameMenu.Player.MovePlayer(Move::DirUp);
		}
		if (GetAsyncKeyState(VK_SPACE)&&0x8000&&GameMenu.Player.HpReturn() > 0) {
			GameMenu.Player.BulletCheck = true;
		}
		else {
			GameMenu.Player.BulletCheck = false;
		}
		
		GameMenu.BulletShot();
		break;
	case MenuCheck::Option:
		if (GetAsyncKeyState(VK_F2) && GameMenu.GameCheck != MenuCheck::GameStart) {
			GameMenu.GameCheck = MenuCheck::Main;
		}
		if (GetAsyncKeyState(VK_F3)) {
			GameMenu.GameCheck = MenuCheck::GameStart;
		}
		break;
	}
	
	
}

VOID Render()
{
	RECT rect;
	SetRect(&rect, 1000, 1000, 0, 0);
    // Clear the backbuffer to a blue color
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 0, 0, 255 ), 1.0f, 0 );

    // Begin the scene
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
		g_picture->picture->Begin(D3DXSPRITE_ALPHABLEND);		
         //Rendering of scene objects can happen here
		switch (GameMenu.GameCheck)
		{
		case MenuCheck::Main:
			GameMenu.MainMenu();
			break;
		case MenuCheck::GameStart:
			GameMenu.GameStart();
			break;
		case MenuCheck::Option:
			GameMenu.Option();
			break;
		}
		// End the scene
		g_picture->font->DrawTextA(g_picture->picture,GameMenu.Player.Test,-1,&rect,DT_LEFT,D3DCOLOR_RGBA(255,255,255,255));
		g_picture->picture->End();
        g_pd3dDevice->EndScene();
    }

    // Present the backbuffer contents to the display
    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}




LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	

	if (msg == WM_LBUTTONDOWN && LOWORD(lParam) >502 && LOWORD(lParam)< 1269 && HIWORD(lParam) >505 && HIWORD(lParam)<661) {
		GameMenu.GameCheck = MenuCheck::GameStart;
		//GameMenu.Player.SetRidian(Ridain);
	}
    switch( msg )
    {
        case WM_DESTROY:
            Cleanup();
            PostQuitMessage( 0 );
            return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}




INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
    UNREFERENCED_PARAMETER( hInst );

    // Register the window class
    WNDCLASSEX wc =
    {
        sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
        GetModuleHandle( NULL ), NULL, NULL, NULL, NULL,
        L"D3D Tutorial", NULL
    };
    RegisterClassEx( &wc );

    // Create the application's window
    HWND hWnd = CreateWindow(L"D3D Tutorial", L"D3D Tutorial 01: Direct-X_Tutorial1",
                              WS_POPUP, 0, 0, 1920,1080,
                              NULL, NULL, wc.hInstance, NULL );
    // Initialize Direct3D
    if( SUCCEEDED( InitD3D( hWnd ) ) )
    {
        // Show the window
        ShowWindow( hWnd, SW_SHOWDEFAULT );
        UpdateWindow( hWnd );
		InitCharater();
        // Enter the message loop
        MSG msg;
		ZeroMemory(&msg, sizeof(msg));	
		while (msg.message != WM_QUIT) {
			if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
				Update();
				Render();
			}
		}
    }

    UnregisterClass( L"D3D Tutorial", wc.hInstance );
    return 0;
}



