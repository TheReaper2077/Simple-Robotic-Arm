#include "ImGuiLayer.h"
#include "ECS.h"
#include "Window.h"
#include "Events.h"
#include "TimeStep.h"

REGISTRY_DEF;

void lucy::ImGuiLayer::Init() {
	auto& window = registry.store<Window>();
	// auto& functions = registry.store<Functions>();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;
	// io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	io.ConfigWindowsMoveFromTitleBarOnly = true;
	io.ConfigDockingWithShift = true;

	// io.BackendFlags |= ImGuiBackendFlags_PlatformHasViewports;

	ImGui_ImplSDL2_InitForOpenGL(window.sdl_window, (void*)window.sdl_glcontext);
	ImGui_ImplOpenGL3_Init("#version 400");

	ImGui::StyleColorsDark();

	Events::AddFunction([](SDL_Event& event) {
		ImGui_ImplSDL2_ProcessEvent(&event);
	});
}

void lucy::ImGuiLayer::RenderBegin() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	auto& window = registry.store<Window>();
	// // auto& functions = registry.store<Functions>();

	// Screen
	static bool p_open = false;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(window.size.x, window.size.y));

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	ImGui::Begin("DockSpace", &p_open, window_flags);

	ImGui::PopStyleVar(3);
	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DockingEnable) {
		
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}
	ImGui::End();
}

void lucy::ImGuiLayer::RenderEnd() {
	auto& window = registry.store<Window>();
	// // auto& functions = registry.store<Functions>();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	// ImGui::UpdatePlatformWindows();
	// ImGui::RenderPlatformWindowsDefault();

	// window.SetCurrent();
}
