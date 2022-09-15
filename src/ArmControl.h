#pragma once

#include <Lucy/Lucy.h>
#include <LucyGL/LucyGL.h>
#include <LucyRE/LucyRE.h>
#include "SerialPort.h"
#include <glm/glm.hpp>
#include <vector>
#include <array>
#include <unordered_map>

#define NUM_SERVO 6

struct Position {
	std::array<float, 6> angles;
};

struct Animation {
	std::vector<Position> angles_states;

	void Add(float a0, float a1, float a2, float a3, float a4, float a5) {
		angles_states.push_back({ a0, a1, a2, a3, a4, a5 });
	}

	void Add(float* angles) {
		Add(angles[0], angles[1], angles[2], angles[3], angles[4], angles[5]);
	}

	void Add(Position pos) {
		angles_states.push_back(pos);
	}
};

class ArmControl {
	SerialPort* serial_port = nullptr;

	static void SetServo(int servo);
	float servo_angle[NUM_SERVO];

	static ArmControl* Instance() {
		static ArmControl instance;
		return &instance;
	}

	float arm_length[3] = { 10.5, 9.3, 3 };
	float angle[NUM_SERVO];

	bool init = false;

	glm::vec3 target = { 5, 5, 5 };

	bool enable_ik = false;
	bool servo_is_at_pos = false;

	std::unordered_map<std::string, Animation> animations_store;
	std::unordered_map<std::string, Position> positions_store;

	enum State {
		PLAYING,
		PAUSED,
		STOPPED,
	};

	State play_state = PAUSED;
	Animation* animation;

	float saved_angles[700][NUM_SERVO];
	int num_saved = 0;
	int curr_saved_idx = 0;

public:
	#define self Instance()

	static float* GetArmLengths();
	static float* GetAngles();

	static void ImGuiLayer();
	static void Initialize();
	static void Update();
	static void Transmission();
	static void Render();

	static bool IsIKEnable();
	static bool IsServoAtPosition();
	static float EaseFunc(float x, float t);

	static void Load(Position pos);
};
