#include "ArmControl.h"
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
	self->angle[3] = 90;

	self->arm_length[0] = 10.5;
	self->arm_length[1] = 9.8;
	// self->arm_length[0] = 7.5;
	// self->arm_length[1] = 7.5;

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
		ImGui::DragFloat("Arm X", &self->angle[3], 0.1f, 0.0f, 180.0f, "%.2f");
		// ImGui::DragFloat("Arm Y", &transform[2].rotation.y, 0.1f, 0.0f, 0.0f, "%.2f");

		ImGui::Spacing();
		
		ImGui::DragFloat("Base Length", &self->arm_length[0], 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::DragFloat("Elbow Length", &self->arm_length[1], 0.1f, 0.0f, 0.0f, "%.2f");
		// ImGui::DragFloat("Hand Length", &transform[2].scale.y, 0.1f, 0.0f, 0.0f, "%.2f");

		ImGui::Spacing();
		
		ImGui::DragFloat3("Target", &self->target[0], 0.1f, 0.0f, 0.0f, "%.2f");

		ImGui::Spacing();

		ImGui::Checkbox("Enable IK", &self->enable_ik);

		ImGui::End();
	}
}

void ArmControl::Update() {
	IKUpdate(self->target);

	SetServo(0);
	SetServo(1);
	SetServo(2);
	SetServo(3);

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
					std::cout.write(serial_data, size);
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

		transform[1].translation = glm::vec3(0, self->arm_length[0], 0) * transform[0].GetRotationQuat();

		transform[1].scale = { 1, self->arm_length[1], 1 };

		lre::SetModel(base * transform[1].GetModel());
		lre::Render(lgl::TRIANGLE, nullptr, cube_vao, cube_vbo, cube_ibo, sizeof(cube_indices)/sizeof(uint32_t));

		transform[1].scale = { 1, 1, 1 };
	}

	{
		transform[2].rotation.x = (self->angle[3] - 90) + transform[1].rotation.x;
		transform[2].translation = transform[1].translation + glm::vec3(0, self->arm_length[1], 0) * transform[2].GetRotationQuat();
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
