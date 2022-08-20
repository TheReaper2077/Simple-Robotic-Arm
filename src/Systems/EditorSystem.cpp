#include "Systems.h"
#include <imgui.h>
#include <Lucy/Lucy.h>
#include <imgui_lucy_impl.h>
#include <Lucy/Window.h>
#include <LucyGL/LucyGL.h>
#include <iostream>

REGISTRY_DEF;
REGISTRY_STORE_DEF(editorwindow, lucy::EditorWindow);
REGISTRY_STORE_DEF(window, lucy::Window);

namespace lucy {
	void EditorPanel() {
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		ImGui::Begin(editorwindow.title.c_str());
		ImGui::PopStyleVar();

		auto pos = ImGui::GetWindowPos();
		auto size = ImGui::GetWindowSize();

		editorwindow.pos.x = pos.x;
		editorwindow.pos.y = pos.y;
		editorwindow.size.x = size.x;
		editorwindow.size.y = size.y;

		if (editorwindow.framebuffer != nullptr)
			// if (editorwindow.framebuffer->width == editorwindow.size.x && editorwindow.framebuffer->height == editorwindow.size.y)
				ImGui::GetWindowDrawList()->AddImage((void*)editorwindow.framebuffer->texture->id, ImVec2(editorwindow.pos.x, editorwindow.pos.y), ImVec2(editorwindow.pos.x + editorwindow.size.x, editorwindow.pos.y + editorwindow.size.y), ImVec2(0, (float)editorwindow.size.y / window.size.y), ImVec2((float)editorwindow.size.x / window.size.x, 0));
		ImGui::End();
	}
}

void lucy::System::EditorSystem() {
	EditorPanel();
}