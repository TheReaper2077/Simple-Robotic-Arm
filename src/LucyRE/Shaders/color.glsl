#version 450 core

in vec3 normal;
in vec4 color;
in float textureid;
in vec3 uvw;
in vec2 uv;

void main() {
	vec3 result = normal;

	if (normal.x < 0) result.x = -normal.x;
	if (normal.y < 0) result.y = -normal.y;
	if (normal.z < 0) result.z = -normal.z;

	gl_FragData[0] = vec4(result, 1.0f);
}