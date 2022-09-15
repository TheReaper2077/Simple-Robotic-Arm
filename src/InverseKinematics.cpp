#include "InverseKinematics.h"
#include <Lucy/Lucy.h>
#include "ArmControl.h"
#include <iostream>

REGISTRY_DEF;
#define TO_DEGREE (180 / 3.14159265359)

bool set_angle(float& var, double angle) {
	if (angle <= 180 && angle >= 0) {
		var = angle;

		return true;
	}

	return false;
}

void IKUpdate(const glm::vec3& target_pos) {
	if (!ArmControl::IsIKEnable()) return;

	auto* arm_len = ArmControl::GetArmLengths();
	auto* angle = ArmControl::GetAngles();
	auto [x, y, z] = target_pos;

	auto base_angle = atan2(x, z) * TO_DEGREE;
	auto a = arm_len[0];
	auto b = arm_len[1] + arm_len[2];

	angle[0] = base_angle;
	auto l = sqrt(x * x + z * z);

	{
		auto c = sqrt(l * l + y * y);

		auto A = acos((b * b + c * c - a * a) / (2 * b * c)) * TO_DEGREE;
		auto B = acos((c * c + a * a - b * b) / (2 * c * a)) * TO_DEGREE;
		auto C = acos((a * a + b * b - c * c) / (2 * a * b)) * TO_DEGREE;

		auto theta = atan2(y, l) * TO_DEGREE;

		angle[1] = B + theta;
		angle[2] = C;
	}
	{
		// float a1 = arm_len[0];
		// float a2 = arm_len[1];
		// float a3 = arm_len[2];

		// float px = l;
		// float py = y;

		// float phi = 180;

		// float wx = px - a3 * cos(phi) * TO_DEGREE;
		// float wy = py - a3 * sin(phi) * TO_DEGREE;

		// float delta = pow(wx, 2) + pow(wy, 2);
		// float c2 = ( delta -pow(a1, 2) -pow(a2, 2))/(2*a1*a2);
		// float s2 = sqrt(1-pow(c2, 2));
		// auto theta_2 = atan2(s2, c2) * TO_DEGREE;

		// auto s1 = ((a1 + a2 * c2) * wy - a2*s2*wx)/delta;
		// auto c1 =((a1 + a2 * c2) * wx + a2*s2*wy)/delta;
		// auto theta_1 = atan2(s1,c1) * TO_DEGREE;
		// auto theta_3 = phi-theta_1-theta_2;

		// angle[1] = theta_1;
		// angle[2] = theta_2;
		// angle[3] = theta_3;
	}
}
