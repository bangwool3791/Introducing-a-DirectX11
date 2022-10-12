//***************************************************************************************
// d3dApp.h by Frank Luna (C) 2011 All Rights Reserved.
//
// Simple Direct3D demo application class.  
// Make sure you link: d3d11.lib d3dx11d.lib D3DCompiler.lib D3DX11EffectsD.lib 
//                     dxerr.lib dxgi.lib dxguid.lib.
// Link d3dx11.lib and D3DX11Effects.lib for release mode builds instead
//   of d3dx11d.lib and D3DX11EffectsD.lib.
//***************************************************************************************

#ifndef D3DAPP_H
#define D3DAPP_H

#include "d3dUtil.h"
#include "GameTimer.h"
#include <string>
#include <d3d11_1.h>
#pragma comment(lib,"d3d11")
#include <DXGI.h>
#pragma comment(lib,"dxgi")
#pragma comment(lib,"dxguid")
#pragma comment(lib,"d3dcompiler")
/*
응용 프로그램의 주창(main window)의 생성, 응용 프로그램 메시지 루프 실행, 
Windows 메시지 처리, Direct3D 초기화를 위한 함수들을 제공한다.
D3DApp 클래스를 상속 받은 자식 클래스에서 가상 함수를 재정의 하여 사용하는 듯하다.
*/
class D3DApp
{
public:
	D3DApp(HINSTANCE hInstance);
	virtual ~D3DApp();
	
	HINSTANCE AppInst()const;
	HWND      MainWnd()const;
	float     AspectRatio()const;
	
	int Run();
 
	// Framework methods.  Derived client class overrides these methods to 
	// implement specific application requirements.

	virtual bool Init();
	virtual void OnResize(); 
	virtual void UpdateScene(float dt)=0;
	virtual void DrawScene()=0; 
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// Convenience overrides for handling mouse input.
	virtual void OnMouseDown(WPARAM btnState, int x, int y){ }
	virtual void OnMouseUp(WPARAM btnState, int x, int y)  { }
	virtual void OnMouseMove(WPARAM btnState, int x, int y){ }

protected:
	bool InitMainWindow();
	bool InitDirect3D();

	void CalculateFrameStats();

protected:

//응용프로그램 인스턴스 핸들
	HINSTANCE mhAppInst;
	//주 창 핸들
	HWND      mhMainWnd;
	//응용 프로그램이 일시 정지된 상태인가?
	bool      mAppPaused;
	//응용프로그램이 최소화된 상태인가 ?
	bool      mMinimized;
	//용용프로그램이 최대화된 상태인가?
	bool      mMaximized;
	//사용자가 크기 조정용 테두리를 끌고 있는 상태인가?
	bool      mResizing;
	/*
	4XMSAA의 품질 수준
	4XMSAA란 ?
	MSAA(Multisample anti-aliasing)
	따라서 4XMSAA를 사용하여 앨리어싱을 매끄럽게한다.
	앨리어싱이란 ?
	 화면상에 대각선을 그린다고 가정 할 때, 픽셀 단위로 그려지므로, 
	 사람의 눈에 대각선이 울퉁불퉁하게 그려질 수 밖에 없다.
	울퉁불퉁한 그래픽 처리를 부드럽게 하는 처리를 앨리어싱이라한다. 
	*/
	UINT      m4xMsaaQuality;
	//경과 시간과 게임 전체 시간을 측정하는데 쓰인다.
	GameTimer mTimer;

	ID3D11Device* md3dDevice;
	ID3D11DeviceContext* md3dImmediateContext;
	IDXGISwapChain* mSwapChain;
	ID3D11Texture2D* mDepthStencilBuffer;
	ID3D11RenderTargetView* mRenderTargetView;
	ID3D11DepthStencilView* mDepthStencilView;
	D3D11_VIEWPORT mScreenViewport;

	// Derived class should set these in derived constructor to customize starting values.
	std::wstring mMainWndCaption;
	D3D_DRIVER_TYPE md3dDriverType;
	int mClientWidth;
	int mClientHeight;
	bool mEnable4xMsaa;
};

#endif // D3DAPP_H