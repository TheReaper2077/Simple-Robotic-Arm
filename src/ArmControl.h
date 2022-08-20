#pragma once

#include <Lucy/Lucy.h>
#include <LucyGL/LucyGL.h>
#include <LucyRE/LucyRE.h>
#include "SerialPort.h"
#include <glm/glm.hpp>

#define NUM_SERVO 6

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
};
