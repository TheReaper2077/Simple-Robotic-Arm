#define LIGHT_VAR_SET

vec4 pbr_logic() {
	vec3 N = normal;
	vec3 V = normalize(view_pos - frag_pos);

	albedo = material.albedo;
	ao = material.ao;
	metallic = material.metallic;
	roughness = material.roughness;

	vec3 Lo = vec3(0.0);

	#define LOGIC_VAR_SET

	vec3 ambient = vec3(0.03) * albedo * ao;
	vec3 color = ambient + Lo;

	color = color / (color + vec3(1.0));
	return pow(color, vec3(1.0 / 2.2));
}