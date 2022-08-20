#pragma once

#include <imgui.h>
#include <imgui_lucy_impl.h>
#include <imgui_internal.h>
#include <imgui_stdlib.h>
#include "Events.h"
#include "Window.h"

namespace lucy {
	class ImGuiLayer {
	public:
		ImGuiLayer() {}
		~ImGuiLayer() {}

		static void Init();

		static void RenderBegin();

		static void RenderEnd();
	};
}