uniform int u_type;
uniform vec4 u_color;
uniform int u_textureid;

vec4 sprite_logic() {
	vec4 result;
	
	switch (u_type) {
		case 0:
			result = GetTexture(int(textureid), uv);
			break;
		case 1:
			result = mix(GetTexture(int(textureid), uv), color, color.w);
			break;
		case 2:
			result = mix(GetTexture(int(textureid), uv), u_color, u_color.w);
			break;
		case 3:
			result = GetTexture(u_textureid, uv);
			break;
		case 4:
			result = mix(GetTexture(u_textureid, uv), color, color.w);
			break;
		case 5:
			result = mix(GetTexture(u_textureid, uv), u_color, u_color.w);
			break;
		case 6:
			result = color;
			break;
		case 7:
			result = u_color;
			break;
	}

	return result;
}