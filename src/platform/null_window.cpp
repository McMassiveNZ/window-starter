#include "../window.h"

namespace starter_window
{

class NullWindowImpl final : public Window
{
public:
	NullWindowImpl() = default;
	~NullWindowImpl() override = default;

	NullWindowImpl(NullWindowImpl&&) = delete;
	NullWindowImpl& operator=(NullWindowImpl&&) = delete;
	NullWindowImpl(const NullWindowImpl&) = delete;
	NullWindowImpl& operator=(const NullWindowImpl&) = delete;

	void PumpMessages() override {}
	bool ShouldClose() override { return false; }

};

} // namespace starter_window

std::unique_ptr<starter_window::Window> swCreateWindow(starter_window::WindowCreateParams)
{
	auto result = std::make_unique<starter_window::NullWindowImpl>();
	return result;
}
