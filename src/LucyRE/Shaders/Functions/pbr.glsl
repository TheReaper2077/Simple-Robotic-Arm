vec3 albedo;
float metallic;
float roughness;
float ao;

vec3 fresnelSchlick(float cosTheta, vec3 F0);
float DistributionGGX(vec3 N, vec3 H, float roughness);
float GeometrySchlickGGX(float NdotV, float roughness);
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness);

vec3 PointCalculatePBR(vec3 N, vec3 V, vec3 light_position, vec3 light_color);
vec3 DirCalculatePBR(vec3 N, vec3 V, vec3 light_position, vec3 light_direction, vec3 light_color);

vec3 fresnelSchlick(float cosTheta, vec3 F0) {
	return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

float DistributionGGX(vec3 N, vec3 H, float roughness) {
	float a = roughness * roughness;
	float a2 = a * a;
	float NdotH = max(dot(N, H), 0.0);
	float NdotH2 = NdotH * NdotH;
	
	float num = a2;
	float denom = (NdotH2 * (a2 - 1.0) + 1.0);
	denom = 3.14159265359 * denom * denom;
	
	return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness) {
	float r = (roughness + 1.0);
	float k = (r * r) / 8.;
	
	float num = NdotV;
	float denom = NdotV * (1.0 - k) + k;
	
	return num / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
	float NdotV = max(dot(N, V), 0.0);
	float NdotL = max(dot(N, L), 0.0);
	float ggx2 = GeometrySchlickGGX(NdotV, roughness);
	float ggx1 = GeometrySchlickGGX(NdotL, roughness);
	
	return ggx1 * ggx2;
}

vec3 PointCalculatePBR(vec3 N, vec3 V, vec3 light_position, vec3 light_color) {
	vec3 L = normalize(light_position - frag_pos);
	vec3 H = normalize(V + L);
	
	float distance = length(light_position - frag_pos);
	float attenuation = 1.0 / (distance * distance);
	vec3 radiance = light_color * attenuation;
	
	vec3 F0 = vec3(0.04);
	F0 = mix(F0, albedo, metallic);
	vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);
	
	float NDF = DistributionGGX(N, H, roughness);
	float G = GeometrySmith(N, V, L, roughness);
	
	vec3 numerator = NDF * G * F;
	float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + .0001;
	vec3 specular = numerator / denominator;
	
	vec3 kS = F;
	vec3 kD = vec3(1.0) - kS;
	
	kD *= 1.0 - metallic;
	
	float NdotL = max(dot(N, L), 0.0);
	return (kD * albedo / 3.14159265359 + specular) * radiance * NdotL;
}

vec3 DirCalculatePBR(vec3 N, vec3 V, vec3 light_position, vec3 light_direction, vec3 light_color) {
	vec3 L = normalize(-light_direction);
	vec3 H = normalize(V + L);
	
	float distance = length(light_position - frag_pos);
	float attenuation = 1.0 / (distance * distance);
	vec3 radiance = light_color;
	
	vec3 F0 = vec3(0.04);
	F0 = mix(F0, albedo, metallic);
	vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);
	
	float NDF = DistributionGGX(N, H, roughness);
	float G = GeometrySmith(N, V, L, roughness);
	
	vec3 numerator = NDF * G * F;
	float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + .0001;
	vec3 specular = numerator / denominator;
	
	vec3 kS = F;
	vec3 kD = vec3(1.0) - kS;
	
	kD *= 1.0 - metallic;
	
	float NdotL = max(dot(N, L), 0.0);
	return (kD * albedo / 3.14159265359 + specular) * radiance * NdotL;
}