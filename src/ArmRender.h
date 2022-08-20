#pragma once

#include <LucyGL/LucyGL.h>

class ArmRender {
public:
	void Initialize();
	void Render(lgl::FrameBuffer* framebuffer);
};