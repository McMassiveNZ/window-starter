#include "window.h"

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>

static LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		case WM_PAINT:
		{
			PAINTSTRUCT ps = {};
			HDC hdc = BeginPaint(window, &ps);
			FillRect(hdc, &ps.rcPaint, reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1));
			EndPaint(window, &ps);
			return 0;
		}
	}
	return DefWindowProc(window, message, wParam, lParam);
}

namespace starter_window
{

struct Win32WindowImpl final
{
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	bool m_close;
};

void PumpMessages(Win32WindowImpl& window)
{
	MSG message = {};
	if (GetMessage(&message, NULL, 0, 0) != 0)
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	else
	{
		// GetMessage returned WM_QUIT
		window.m_close = true;
	}
}

bool ShouldClose(const Win32WindowImpl& window)
{
	return window.m_close;
}
} // namespace starter_window

starter_window::Window swCreateWindow(starter_window::WindowCreateParams params)
{
	const char className[] = "Win32WindowImpl";
	HINSTANCE hInstance = GetModuleHandle(NULL);
	starter_window::Win32WindowImpl result = { 
		.m_hInstance = nullptr, 
		.m_hWnd = nullptr, 
		.m_close = true 
	};

	WNDCLASSEX wc = {};

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = className;

	if (RegisterClassEx(&wc) == 0)
	{
		MessageBox(nullptr, "Call to RegisterClass failed", "Fatal Error", MB_OK);
		return result;
	}

	HWND window = CreateWindowEx(
		0,
		className,
		params.name,
		WS_OVERLAPPEDWINDOW,
		params.x, params.y, params.width, params.height,
		nullptr,
		nullptr,
		hInstance,
		nullptr);

	if (window == nullptr)
	{
		MessageBox(nullptr, "Call to CreateWindow failed", "Fatal Error", MB_OK);
		return result;
	}

	ShowWindow(window, SW_SHOW);

	result.m_hInstance = hInstance;
	result.m_hWnd = window;
	result.m_close = false;

	return result;
}