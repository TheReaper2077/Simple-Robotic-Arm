#pragma once

#include "ECS.h"

namespace lucy {
	struct State {
		static Entity camera, editor_camera;
		static void Update();
	};
}