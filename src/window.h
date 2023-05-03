#pragma once

#include <memory>

namespace starter_window
{

struct WindowCreateParams
{
	int x;
	int y;
	int width;
	int height;
	const char* name;
};

class Window
{
public:
	virtual ~Window() = default;
	virtual bool PumpMessages() = 0;
};

}

std::unique_ptr<starter_window::Window> swCreateWindow(starter_window::WindowCreateParams params);
