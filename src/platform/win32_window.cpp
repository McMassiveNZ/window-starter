#include "../window.h"

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

class Win32WindowImpl final : public Window
{
public:
	Win32WindowImpl();
	~Win32WindowImpl() override = default;

	Win32WindowImpl(const Win32WindowImpl&) = delete;
	Win32WindowImpl& operator=(const Win32WindowImpl&) = delete;

	bool init(WindowCreateParams params);
	void PumpMessages() override;
	bool ShouldClose() override;

	HINSTANCE hInstance;
	HWND hWnd;
	bool m_close;
};

Win32WindowImpl::Win32WindowImpl()
	: hInstance(GetModuleHandle(NULL))
	, hWnd(nullptr)
	, m_close(false)
{
}

bool Win32WindowImpl::init(WindowCreateParams params)
{
	const char className[] = "Win32WindowImpl";

	WNDCLASSEX wc = {};

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = className;

	if (RegisterClassEx(&wc) == 0)
	{
		MessageBox(nullptr, "Call to RegisterClass failed", "Fatal Error", MB_OK);
		return false;
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
		return false;
	}

	ShowWindow(window, SW_SHOW);
	return true;
}

void Win32WindowImpl::PumpMessages()
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
		m_close = true;
	}
}

bool Win32WindowImpl::ShouldClose()
{
	return m_close;
}
} // namespace starter_window

std::unique_ptr<starter_window::Window> swCreateWindow(starter_window::WindowCreateParams params)
{
	auto result = std::make_unique<starter_window::Win32WindowImpl>();
	if (result->init(params) == false)
	{
		result = nullptr;
	}

	return result;
}