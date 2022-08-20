#version 450 core

in vec4 color;

uniform vec4 u_color;

int type;

void main() {
	switch (type) {
		case 0:
			gl_FragData[0] = color;
			break;
		case 1:
			gl_FragData[0] = u_color;
			break;
	}
}