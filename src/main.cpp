#include "window.h"

constexpr int CW_USEDEFAULT = 0x80000000;

auto main() -> int
{
	auto window = swCreateWindow({
		.x = CW_USEDEFAULT,
		.y = CW_USEDEFAULT,
		.width = CW_USEDEFAULT,
		.height = CW_USEDEFAULT,
		.name = "Starter Window"
	});
		
	while (!ShouldClose(window))
	{
		PumpMessages(window);
	}
}

