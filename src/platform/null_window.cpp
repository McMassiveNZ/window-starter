#include "window.h"

namespace starter_window
{

struct NullWindowImpl
{
};

void PumpMessages(NullWindowImpl&)
{
}

bool ShouldClose(const NullWindowImpl&)
{
	return true;
}

} // namespace starter_window

starter_window::Window swCreateWindow(starter_window::WindowCreateParams)
{
	return starter_window::NullWindowImpl{};
}