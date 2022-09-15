#include "ArmControl.h"
#include <chrono>
#include <time.h>
#include "InverseKinematics.h"
#include <iostream>
#include <Structures/Transform.h>
#include <Structures/Camera.h>
#include <imgui_lucy_impl.h>
#include "Vertices.h"

REGISTRY_DEF;
REGISTRY_STORE_DEF(editorwindow, lucy::EditorWindow);

char port[] = "\\\\.\\COM3";
char serial_data[MAX_DATA_LENGTH];
uint8_t data_package[27] = { '&', 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, '$', '\n' };

void ArmControl::Initialize() {
	self->servo_angle[0] = 90;
	self->servo_angle[1] = 90;
	self->servo_angle[2] = 90;
	self->servo_angle[3] = 90;
	
	self->angle[0] = 90;
	self->angle[1] = 90;
	self->angle[2] = 90;
	self->angle[3] = 180;
	self->angle[4] = 180;
	self->angle[5] = 30;

	self->arm_length[0] = 10.5;
	self->arm_length[1] = 9.8;
	self->arm_length[2] = 12;

	self->init = true;
}

void ArmControl::SetServo(int servo) {
	self->servo_angle[servo] = self->angle[servo];
}

float* ArmControl::GetArmLengths() {
	return self->arm_length;
}

float* ArmControl::GetAngles() {
	return self->angle;
}

void ArmControl::ImGuiLayer() {
	if (!self->init) return;

	if (ImGui::Begin("Arm Control")) {
		ImGui::DragFloat("Base Y", &self->angle[0], 0.1f, 0.0f, 180.0f, "%.2f");
		ImGui::DragFloat("Base X", &self->angle[1], 0.1f, 0.0f, 180.0f, "%.2f");
		ImGui::DragFloat("Elbow X", &self->angle[2], 0.1f, 0.0f, 180.0f, "%.2f");
		ImGui::DragFloat("Hand X", &self->angle[3], 0.1f, 0.0f, 180.0f, "%.2f");
		ImGui::DragFloat("Hand Y", &self->angle[4], 0.1f, 0.0f, 180.0f, "%.2f");
		ImGui::DragFloat("Gripper", &self->angle[5], 0.1f, 0.0f, 180.0f, "%.2f");
		if (ImGui::Button("Close Gripper")) {
			self->angle[5] = 10;
		}
		if (ImGui::Button("Open Gripper")) {
			self->angle[5] = 90;
		}

		ImGui::Spacing();

		ImGui::DragFloat("Base Length", &self->arm_length[0], 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::DragFloat("Elbow Length", &self->arm_length[1], 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::DragFloat("Hand Length", &self->arm_length[2], 0.1f, 0.0f, 0.0f, "%.2f");

		ImGui::Spacing();
		
		ImGui::DragFloat3("Target", &self->target[0], 0.1f, 0.0f, 0.0f, "%.2f");

		ImGui::Spacing();

		ImGui::Checkbox("Enable IK", &self->enable_ik);

		if (!self->servo_is_at_pos)
			ImGui::TextColored({ 0, 0, 1, 1 }, "Servo Moving");
		else
			ImGui::TextColored({ 0, 1, 0, 1 }, "Servo At Position");
		
		if (self->play_state == PLAYING) {
			ImGui::TextColored({ 0, 1, 0, 1 }, "PLAYING");
		}
		if (self->play_state == STOPPED) {
			ImGui::TextColored({ 1, 0, 0, 1 }, "STOPPED");
		}
		if (self->play_state == PAUSED) {
			ImGui::TextColored({ 1, 1, 0, 1 }, "PAUSED");
		}

		ImGui::Spacing();

		if (ImGui::Button("PLAY")) {
			self->play_state = PLAYING;
		}
		if (ImGui::Button("PAUSE")) {
			self->play_state = PAUSED;
		}
		if (ImGui::Button("STOP")) {
			self->play_state = STOPPED;
			self->curr_saved_idx = 0;
		}

		ImGui::Spacing();

		if (ImGui::Button("SAVE")) {
			self->play_state = STOPPED;

			int& idx = self->num_saved;

			for (int i = 0; i < 6; i++)
				self->saved_angles[idx][i] = self->angle[i];

			// std::cout << idx << '\n';

			idx++;
		}

		if (ImGui::Button("CLEAR")) {
			self->num_saved = 0;
		}

		ImGui::End();
	}

	if (ImGui::Begin("Positions")) {
		for (auto& pair: self->positions_store) {
			if (ImGui::Selectable(pair.first.c_str())) {

			}
		}

		ImGui::End();
	}
}

float progress_len = 500, progress_iter = 1 / progress_len;
static float prev_angle[6], next_angle[6];

void ArmControl::Update() {
	IKUpdate(self->target);

	static std::clock_t last_time = std::clock();
	static float progress = 0;

	if (self->play_state == PLAYING && self->num_saved > 0) {
		float offset = EaseFunc(progress, 1.9);

		if (progress >= 1) {
			for (int i = 0; i < NUM_SERVO; i++)
				prev_angle[i] = self->servo_angle[i];

			self->curr_saved_idx++;
			progress = 0;
		} else {
			for (int i = 0; i < NUM_SERVO; i++)
				self->angle[i] = prev_angle[i] + (self->saved_angles[self->curr_saved_idx][i] - prev_angle[i]) * offset;

			progress += progress_iter;
		}
	} else {
		for (int i = 0; i < NUM_SERVO; i++)
			prev_angle[i] = self->servo_angle[i];
	}

	if (self->curr_saved_idx >= self->num_saved) {
		self->play_state = STOPPED;
		self->curr_saved_idx = 0;
	}

	for (int i = 0; i < NUM_SERVO; i++)
		SetServo(i);

	Transmission();
}

void ArmControl::Transmission() {
	if (!self->init) return;

	if (self->serial_port == nullptr) {
		self->serial_port = new SerialPort(port);

		if (self->serial_port->isConnected())
			std::cout << "Ardunio Connection Established\n";
		else
			std::cout << "Error Unable to Establish Connection\n";
	}

	if (self->serial_port != nullptr) {
		if (self->serial_port->isConnected()) {
			while (true) {
				auto size = self->serial_port->readSerialPort(serial_data, MAX_DATA_LENGTH);

				if (size) {
					if (serial_data[0] == 'M') {
						self->servo_is_at_pos = (
							(*(float*)(&serial_data[1]) == float(self->servo_angle[0])) &&
							 (*(float*)(&serial_data[5]) == float(self->servo_angle[1])) &&
							  (*(float*)(&serial_data[9]) == float(self->servo_angle[2])) &&
							   (*(float*)(&serial_data[13]) == float(self->servo_angle[3])) &&
							    (*(float*)(&serial_data[17]) == float(self->servo_angle[4])) &&
								 (*(float*)(&serial_data[21]) == float(self->servo_angle[5])));
						// std::cout.write(serial_data, size);
					}
				} else {
					break;
				}
			}

			*(float*)(&data_package[1]) = self->servo_angle[0];
			*(float*)(&data_package[5]) = self->servo_angle[1];
			*(float*)(&data_package[9]) = self->servo_angle[2];
			*(float*)(&data_package[13]) = self->servo_angle[3];
			*(float*)(&data_package[17]) = self->servo_angle[4];
			*(float*)(&data_package[21]) = self->servo_angle[5];

			self->serial_port->writeSerialPort((char*)data_package, 27);
		}
	}
}

lgl::VertexArray* cube_vao = nullptr;
lgl::VertexBuffer* cube_vbo = nullptr;
lgl::IndexBuffer* cube_ibo = nullptr;

lucy::Transform target_transform, transform[4], temp_transform;

lgl::Shader* shader = nullptr;

void ArmControl::Render() {
	if (editorwindow.framebuffer == nullptr) return;

	if (shader == nullptr) {
		shader = new lgl::Shader("D:\\C++\\Robotic Arm\\src\\LucyRE\\Shaders\\vertex.glsl", "D:\\C++\\Robotic Arm\\src\\LucyRE\\Shaders\\color.glsl", true);
	}

	if (cube_vao == nullptr) {
		cube_vao = lre::Vertex::P1N1::VertexArray();
	}

	if (cube_vbo == nullptr) {
		cube_vbo = new lgl::VertexBuffer();
		cube_vbo->Bind();
		cube_vbo->Allocate(sizeof(cube_vertices));
		cube_vbo->AddDataDynamic(cube_vertices, sizeof(cube_vertices));
	}

	if (cube_ibo == nullptr) {
		cube_ibo = new lgl::IndexBuffer();
		cube_ibo->Bind();
		cube_ibo->Allocate(sizeof(cube_indices));
		cube_ibo->AddData(cube_indices, sizeof(cube_indices));
	}

	if (lucy::State::editor_camera != (lucy::Entity)0) {
		auto& transform = registry.get<lucy::Transform>(lucy::State::editor_camera);
		auto& camera = registry.get<lucy::Camera>(lucy::State::editor_camera);
	
		lre::SetProjection(camera.projection);
		lre::SetView(camera.view);
	}

	editorwindow.framebuffer->Bind();

	lre::SetModel(glm::mat4(1.0f));

	lgl::ClearColor(0, 0, 0, 1);
	lgl::Clear(lgl::COLOR_BUFFER_BIT | lgl::DEPTH_BUFFER_BIT);
	lgl::Viewport(0, 0, editorwindow.size.x, editorwindow.size.y);

	lre::RenderLine({ 0, 0, 0 }, { 1000, 0, 0 }, { 1, 0, 0, 1 });
	lre::RenderLine({ 0, 0, 0 }, { 0, 1000, 0 }, { 0, 1, 0, 1 });
	lre::RenderLine({ 0, 0, 0 }, { 0, 0, 1000 }, { 0, 0, 1, 1 });

	lre::Render_Lines();

	auto base = glm::rotate(glm::mat4(1.0f), glm::radians(self->angle[0]), glm::vec3(0, 1, 0));

	shader->Bind();

	{
		target_transform.scale = { 1, 1, 1};
		target_transform.translation = self->target;
		target_transform.translation.y -= 0.5;

		lre::SetModel(target_transform.GetModel());
		lre::Render(lgl::TRIANGLE, nullptr, cube_vao, cube_vbo, cube_ibo, sizeof(cube_indices)/sizeof(uint32_t));
	}

	{
		transform[0].rotation.x = self->angle[1] - 90;

		transform[0].scale = { 1, self->arm_length[0], 1};

		lre::SetModel(base * transform[0].GetModel());
		lre::Render(lgl::TRIANGLE, nullptr, cube_vao, cube_vbo, cube_ibo, sizeof(cube_indices)/sizeof(uint32_t));

		transform[0].scale = { 1, 1, 1 };
	}

	{
		transform[1].rotation.x = (self->angle[2] - 180) + transform[0].rotation.x;

		transform[1].translation = transform[0].translation + glm::vec3(0, self->arm_length[0], 0) * transform[0].GetRotationQuat();

		transform[1].scale = { 1, self->arm_length[1], 1 };

		lre::SetModel(base * transform[1].GetModel());
		lre::Render(lgl::TRIANGLE, nullptr, cube_vao, cube_vbo, cube_ibo, sizeof(cube_indices)/sizeof(uint32_t));

		transform[1].scale = { 1, 1, 1 };
	}

	{
		transform[2].rotation.x = (self->angle[3] - 180) + transform[1].rotation.x;
		transform[2].translation = transform[1].translation + glm::vec3(0, self->arm_length[1], 0) * transform[1].GetRotationQuat();
		transform[2].scale = { 1, self->arm_length[2], 1 };

		lre::SetModel(base * transform[2].GetModel());
		lre::Render(lgl::TRIANGLE, nullptr, cube_vao, cube_vbo, cube_ibo, sizeof(cube_indices)/sizeof(uint32_t));
	}

	shader->UnBind();
	editorwindow.framebuffer->UnBind();
}

bool ArmControl::IsIKEnable() {
	return self->enable_ik;
}

bool ArmControl::IsServoAtPosition() {
	return self->servo_is_at_pos;
}

float ArmControl::EaseFunc(float x, float t) {
	return pow(x, t) / (pow(x, t) + pow(1 - x, t));
}
