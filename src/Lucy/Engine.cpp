#include "Engine.h"
#include "Window.h"

#include <LucyRE/LucyRE.h>

#include "ImGuiLayer.h"
#include "TimeStep.h"
#include "Events.h"
#include <chrono>
#include <iostream>
#include <assert.h>
#include <SDL2/SDL.h>
#include <glm/gtx/string_cast.hpp>
#include <glad/glad.h>
#include <Systems/Systems.h>
#include <LucyGL/LucyGL.h>

void lucy::Engine::Init() {
	auto null_entity = registry.create();
	auto& window = registry.store<Window>();
	auto& editorwindow = registry.store<EditorWindow>();

	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	window.InitSDLWindow();

	lgl::Initialize(SDL_GL_GetProcAddress);
	lre::Initialize();

	ImGuiLayer::Init();

	AddRuntimeSystem(System::CameraSystem);
	AddImGuiSystem(System::EditorSystem);

	editorwindow.framebuffer = new lgl::FrameBuffer(editorwindow.size.x, editorwindow.size.y, false);
}

void lucy::Engine::Mainloop() {
	auto& window = registry.store<Window>();

	for (auto system_func: init_systems) {
		system_func(/*registry*/);
	}

	while (!Events::IsQuittable()) {
		const auto& start_time = std::chrono::high_resolution_clock::now();

		Events::Update();

		lgl::ClearColor(0, 0, 0, 1);
		lgl::Clear(lgl::COLOR_BUFFER_BIT | lgl::DEPTH_BUFFER_BIT);
		lgl::Viewport(0, 0, window.size.x, window.size.y);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthFunc(GL_LEQUAL);

		for (auto system_func: systems_array) {
			system_func(/*registry*/);
		}

		ImGuiLayer::RenderBegin();

		for (auto system_func: imgui_systems) {
			system_func(/*registry*/);
		}

		ImGuiLayer::RenderEnd();

		window.SwapWindow();

		const auto& end_time = std::chrono::high_resolution_clock::now();
		TimeStep::dt = std::chrono::duration<double, std::ratio<1, 60>>(end_time - start_time).count();
	}

	registry.clear();
}

void lucy::Engine::Destroy() {
	
}

void lucy::Engine::AddRuntimeSystem(system_func func) {
	for (auto fn: systems_array)
		assert(func != fn);

	systems_array.push_back(func);
}

void lucy::Engine::AddInitializationSystem(system_func func) {
	for (auto fn: init_systems)
		assert(func != fn);

	init_systems.push_back(func);
}

void lucy::Engine::AddImGuiSystem(system_func func) {
	for (auto fn: imgui_systems)
		assert(func != fn);

	imgui_systems.push_back(func);
}
