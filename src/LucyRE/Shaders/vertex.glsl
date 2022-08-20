#version 450 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec4 v_color;
layout (location = 2) in vec3 v_normal;
layout (location = 3) in float v_textureid;
layout (location = 4) in vec2 v_uv;
layout (location = 5) in vec3 v_uvw;

layout (std140, binding = 0) uniform ProjectionMatrix {
    mat4 model;
    mat4 view;
    mat4 projection;
	vec3 v_view_pos;
};

out vec3 normal;
out vec4 color;
out float textureid;
out vec3 uvw;
out vec2 uv;

out vec3 frag_pos;
out vec3 view_pos;

void main() {
	normal = mat3(transpose(inverse(model))) * v_normal;
	color = v_color;
	textureid = v_textureid;
	uvw = v_uvw;
	uv = v_uv;

	view_pos = v_view_pos;
	frag_pos = vec3(model * vec4(v_position, 1.0));
	
	gl_Position = projection * view * vec4(frag_pos, 1.0);
}