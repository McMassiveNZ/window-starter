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

template< typename T >
concept IsWindow = requires(T t) {
   PumpMessages(t);
   ShouldClose(t);
};

class Window
{
public:
	template<IsWindow T>
	Window(T t) 
		: self{std::make_unique<model_t<T>>(std::move(t))}
	{
	}

	~Window() = default;
	Window(Window&&) = default;
	Window& operator=(Window&&) = default;
	Window(const Window&) = delete;
	Window operator=(const Window&) = delete;

	friend void PumpMessages(Window& window) { window.self->PumpMessages_(); }
	friend bool ShouldClose(const Window& window) { return window.self->ShouldClose_(); }

private:
	struct concept_t
	{
		virtual ~concept_t() = default;
		virtual void PumpMessages_() = 0;
		virtual bool ShouldClose_() const = 0;
	};

	template<typename T>
	struct model_t final : concept_t
	{
		model_t(T&& data) : m_data(std::move(data)) {}
		virtual void PumpMessages_() override{ PumpMessages(m_data); }
		virtual bool ShouldClose_() const override { return ShouldClose(m_data); }
		T m_data;
	};

	std::unique_ptr<concept_t> self;
};

}

starter_window::Window swCreateWindow(starter_window::WindowCreateParams params);
