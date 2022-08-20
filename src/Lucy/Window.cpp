#include "Window.h"

lucy::Window::Window() {
	size = { 1280, 640 };
}

lucy::Window::~Window() {
	Destroy();
}

void lucy::Window::InitSDLWindow() {
	assert(sdl_window == nullptr);

	sdl_window = SDL_CreateWindow(title.c_str(), pos.x, pos.y, size.x, size.y, flags);

	assert(sdl_window);

	sdl_glcontext = SDL_GL_CreateContext(sdl_window);
}

void lucy::Window::InitSDLWindow(const char* title, int pos_x, int pos_y, int width, int height, uint32_t flags) {
	pos.x = pos_x;
	pos.y = pos_y;
	size.x = width;
	size.y = height;
	this->title = std::string(title);
	this->flags |= flags;

	InitSDLWindow();
}

void lucy::Window::SwapWindow() {
	SDL_GL_SwapWindow(sdl_window);
}

void lucy::Window::Destroy() {
	SDL_DestroyWindow(sdl_window);
}

void lucy::Window::SetCurrent() {
	SDL_GL_MakeCurrent(sdl_window, sdl_glcontext);
}

void lucy::Window::ResetSize() {
	int w, h;
	SDL_GetWindowSize(sdl_window, &w, &h);
	size = { w, h };
}

void lucy::Window::ResetPosition() {
	int x, y;
	SDL_GetWindowPosition(sdl_window, &x, &y);
	pos = { x, y };
}

void lucy::Window::Hide() {
	if (!hidden)
		SDL_HideWindow(sdl_window);
	hidden = true;
}

void lucy::Window::Show() {
	if (hidden)
		SDL_ShowWindow(sdl_window);
	hidden = false;
}
