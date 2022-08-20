#include "InverseKinematics.h"
#include <Lucy/Lucy.h>
#include "ArmControl.h"
#include <iostream>

REGISTRY_DEF;

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

	auto base_theta = atan2(x, z) * (180 / 3.14159265359);
	auto a = arm_len[0];
	auto b = arm_len[1];
	auto l = sqrt(x * x + z * z);
	auto c = sqrt(l * l + y * y);

	auto C = acos((a * a + b * b - c * c) / (2 * a * b)) * (180 / 3.14159265359);
	auto A = acos((b * b + c * c - a * a) / (2 * b * c)) * (180 / 3.14159265359);
	auto B = acos((c * c + a * a - b * b) / (2 * c * a)) * (180 / 3.14159265359);

	angle[0] = base_theta;
	angle[1] = B + (atan2(y, l) * (180 / 3.14159265359));
	angle[2] = C;
}
