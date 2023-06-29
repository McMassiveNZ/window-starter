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
