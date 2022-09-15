#include "Application.h"
#include "ArmControl.h"

void InitApplication() {
	ArmControl::Initialize();
}

void ImGuiApplication() {
	ArmControl::ImGuiLayer();
}

void UpdateApplication() {
	ArmControl::Update();
	ArmControl::Render();
}

// #include "Application.h"
// #include <Lucy/Lucy.h>
// #include <LucyRE/LucyRE.h>
// #include <Structures/Camera.h>
// #include <Structures/Transform.h>
// #include <iostream>
// #include <glm/gtx/string_cast.hpp>
// #include "SerialPort.h"
// #include "Vertices.h"

// REGISTRY_DEF;
// REGISTRY_STORE_DEF(editorwindow, lucy::EditorWindow);

// uint8_t data_package[27] = { '&', 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, '$', '\n' };

// float base_rotation = 0;

// lucy::Transform transform[4];

// lgl::Shader* shader = nullptr;
// lgl::VertexArray* triangle_vertexarray = nullptr;
// lgl::VertexBuffer* triangle_vertexbuffer = nullptr;

// lgl::VertexBuffer* cube_vertexbuffer = nullptr;
// lgl::IndexBuffer* cube_indexbuffer = nullptr;
// lgl::VertexArray* cube_vertexarray = nullptr;

// lgl::VertexBuffer* cylinder_vertexbuffer = nullptr;
// lgl::IndexBuffer* cylinder_indexbuffer = nullptr;
// lgl::VertexArray* cylinder_vertexarray = nullptr;

// glm::vec3 target_point = { 0, 7, 7 };

// SerialPort* arduino = nullptr;
// char port[] = "\\\\.\\COM3";
// char serial_data[MAX_DATA_LENGTH];

// void InitApplication() {
// 	arduino = new SerialPort(port);

// 	if (arduino->isConnected())
// 		std::cout << "Ardunio Connection Established\n";
// 	else
// 		std::cout << "Error Unable to Establish Connection\n";

// 	transform[0].scale = { 1, 10.5, 1 };
// 	transform[0].rotation = { 0, 0, 0 };

// 	transform[1].scale = { 1, 9.8, 1 };
// 	transform[1].rotation = { 45, 0, 0 };
// 	transform[1].parent = &transform[0];

// 	transform[2].scale = { 1, 1, 1 };
// 	transform[2].rotation = { 0, 0, 0 };
// 	transform[2].parent = &transform[1];

// 	transform[3].scale = { 1, 1, 1 };
// 	transform[3].rotation = { 0, 0, 0 };
// 	transform[3].parent = &transform[2];

// 	cube_vertexarray = lre::Vertex::P1N1::VertexArray();

// 	cube_vertexbuffer = new lgl::VertexBuffer();
// 	cube_vertexbuffer->Bind();
// 	cube_vertexbuffer->Allocate(sizeof(cube_vertices));
// 	cube_vertexbuffer->AddDataDynamic(cube_vertices, sizeof(cube_vertices));

// 	cube_indexbuffer = new lgl::IndexBuffer();
// 	cube_indexbuffer->Bind();
// 	cube_indexbuffer->Allocate(sizeof(cube_indices));
// 	cube_indexbuffer->AddData(cube_indices, sizeof(cube_indices));

// 	cylinder_vertexarray = lre::Vertex::P1N1::VertexArray();

// 	cylinder_vertexbuffer = new lgl::VertexBuffer();
// 	cylinder_vertexbuffer->Bind();
// 	cylinder_vertexbuffer->Allocate(sizeof(cylinder_vertices));
// 	cylinder_vertexbuffer->AddDataDynamic(cylinder_vertices, sizeof(cylinder_vertices));

// 	cylinder_indexbuffer = new lgl::IndexBuffer();
// 	cylinder_indexbuffer->Bind();
// 	cylinder_indexbuffer->Allocate(sizeof(cylinder_indices));
// 	cylinder_indexbuffer->AddData(cylinder_indices, sizeof(cylinder_indices));

// 	triangle_vertexarray = lre::Vertex::P1C1::VertexArray();
// 	triangle_vertexbuffer = new lgl::VertexBuffer();

// 	triangle_vertexbuffer->Bind();
// 	triangle_vertexbuffer->Allocate(sizeof(triangle_vertices));
// 	triangle_vertexbuffer->AddDataDynamic(triangle_vertices, sizeof(triangle_vertices));

// 	shader = new lgl::Shader("D:\\C++\\Robotic Arm\\src\\LucyRE\\Shaders\\vertex.glsl", "D:\\C++\\Robotic Arm\\src\\LucyRE\\Shaders\\color.glsl", true);
// }

// void UpdateApplication() {
// 	if (lucy::State::editor_camera != (lucy::Entity)0) {
// 		auto& transform = registry.get<lucy::Transform>(lucy::State::editor_camera);
// 		auto& camera = registry.get<lucy::Camera>(lucy::State::editor_camera);
	
// 		lre::SetProjection(camera.projection);
// 		lre::SetView(camera.view);
// 	}

// 	if (editorwindow.framebuffer != nullptr) {
// 		editorwindow.framebuffer->Bind();

// 		auto base = glm::rotate(glm::mat4(1.0f), glm::radians(base_rotation), glm::vec3(0, 1, 0));

// 		lre::SetModel(glm::mat4(1.0f));

// 		lgl::ClearColor(0, 1, 1, 1);
// 		lgl::Clear(lgl::COLOR_BUFFER_BIT | lgl::DEPTH_BUFFER_BIT);
// 		lgl::Viewport(0, 0, editorwindow.size.x, editorwindow.size.y);

// 		auto init_rotation_temp_1 = transform[0].rotation;
// 		auto init_rotation_temp_2 = transform[1].rotation;
// 		auto init_rotation_temp_3 = transform[2].rotation;
// 		auto init_rotation_temp_4 = transform[3].rotation;

// 		transform[1].rotation += transform[0].rotation;
// 		transform[2].rotation += transform[1].rotation;
// 		transform[3].rotation += transform[2].rotation;
		
// 		auto save_rotation_1 = transform[0].rotation;
// 		auto save_rotation_2 = transform[1].rotation;
// 		auto save_rotation_3 = transform[2].rotation;
// 		auto save_rotation_4 = transform[3].rotation;

// 		transform[0].rotation = { 180 - transform[0].rotation.x, 180 - transform[0].rotation.y, 180 - transform[0].rotation.z };
// 		transform[1].rotation = { 180 - transform[1].rotation.x, 180 - transform[1].rotation.y, 180 - transform[1].rotation.z };
// 		transform[2].rotation = { 180 - transform[2].rotation.x, 180 - transform[2].rotation.y, 180 - transform[2].rotation.z };
// 		transform[3].rotation = { 180 - transform[3].rotation.x, 180 - transform[3].rotation.y, 180 - transform[3].rotation.z };

// 		transform[0].translation = glm::vec3(0, 0, 0);
// 		transform[1].translation = transform[0].translation + (transform[0].GetRotationQuat() * glm::vec3(0, 1, 0)) * transform[0].scale.y;
// 		transform[2].translation = transform[1].translation + (transform[1].GetRotationQuat() * glm::vec3(0, 1, 0)) * transform[1].scale.y;
// 		transform[3].translation = transform[2].translation + (transform[2].GetRotationQuat() * glm::vec3(0, 1, 0)) * transform[2].scale.y;

// 		auto point_0 = base * glm::vec4(transform[0].translation.x, transform[0].translation.y, transform[0].translation.z, 1);
// 		auto point_1 = base * glm::vec4(transform[1].translation.x, transform[1].translation.y, transform[1].translation.z, 1);
// 		auto point_2 = base * glm::vec4(transform[2].translation.x, transform[2].translation.y, transform[2].translation.z, 1);
// 		auto point_3 = base * glm::vec4(transform[3].translation.x, transform[3].translation.y, transform[3].translation.z, 1);

// 		lre::RenderLine({ point_0.x, point_0.y, point_0.z }, { point_1.x, point_1.y, point_1.z });
// 		lre::RenderLine({ point_1.x, point_1.y, point_1.z }, { point_2.x, point_2.y, point_2.z });
// 		lre::RenderLine({ point_2.x, point_2.y, point_2.z }, { point_3.x, point_3.y, point_3.z });

// 		lre::Render_Lines();

// 		shader->Bind();

// 		cube_vertexarray->Bind();
// 		cube_vertexarray->BindVertexBuffer(cube_vertexbuffer, cube_vertexarray->stride);
// 		cube_vertexarray->BindIndexBuffer(cube_indexbuffer);

// 		transform[0].rotation = save_rotation_1;
// 		transform[1].rotation = save_rotation_2;
// 		transform[2].rotation = save_rotation_3;
// 		transform[3].rotation = save_rotation_4;

// 		{
// 			lre::SetModel(base * transform[0].GetModel());
// 			lre::Render(lgl::TRIANGLE, nullptr, cube_vertexarray, cube_vertexbuffer, cube_indexbuffer, sizeof(cube_indices)/sizeof(uint32_t));

// 			auto tmp = transform[0].scale.y;
// 			transform[0].scale.y = 1;
// 			transform[0].rotation.z += 90;
// 			lre::SetModel(base * transform[0].GetModel());
// 			lre::Render(lgl::TRIANGLE, nullptr, cylinder_vertexarray, cylinder_vertexbuffer, cylinder_indexbuffer, sizeof(cylinder_indices)/sizeof(uint32_t));
// 			transform[0].scale.y = tmp;
// 		}
// 		{
// 			lre::SetModel(base * transform[1].GetModel());
// 			lre::Render(lgl::TRIANGLE, nullptr, cube_vertexarray, cube_vertexbuffer, cube_indexbuffer, sizeof(cube_indices)/sizeof(uint32_t));

// 			auto tmp = transform[1].scale.y;
// 			transform[1].scale.y = 1;
// 			transform[1].rotation.z += 90;
// 			lre::SetModel(base * transform[1].GetModel());
// 			lre::Render(lgl::TRIANGLE, nullptr, cylinder_vertexarray, cylinder_vertexbuffer, cylinder_indexbuffer, sizeof(cylinder_indices)/sizeof(uint32_t));
// 			transform[1].scale.y = tmp;
// 		}
// 		{
// 			lre::SetModel(base * transform[2].GetModel());
// 			lre::Render(lgl::TRIANGLE, nullptr, cube_vertexarray, cube_vertexbuffer, cube_indexbuffer, sizeof(cube_indices)/sizeof(uint32_t));

// 			auto tmp = transform[2].scale.y;
// 			transform[2].scale.y = 1;
// 			transform[2].rotation.z += 90;
// 			lre::SetModel(base * transform[2].GetModel());
// 			lre::Render(lgl::TRIANGLE, nullptr, cylinder_vertexarray, cylinder_vertexbuffer, cylinder_indexbuffer, sizeof(cylinder_indices)/sizeof(uint32_t));
// 			transform[2].scale.y = tmp;
// 		}

// 		transform[0].rotation = init_rotation_temp_1;
// 		transform[1].rotation = init_rotation_temp_2;
// 		transform[2].rotation = init_rotation_temp_3;
// 		transform[3].rotation = init_rotation_temp_4;

// 		shader->UnBind();

// 		editorwindow.framebuffer->UnBind();
// 	}
// }
