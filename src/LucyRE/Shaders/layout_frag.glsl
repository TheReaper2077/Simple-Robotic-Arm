#version 450 core

in vec3 normal;
in vec4 color;
in vec2 uv;
in vec3 uvw;
in float textureid;

#define INFO_DEFINE_SET_VAR

#define FUNC_DEFINE_SET_VAR

void main() {
	vec4 result;

	#define FUNC_SET_VAR

	gl_FragData[0] = result;
}