#pragma once

#include "etbdefs.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace ETB {

	class Camera {
	public:
		static Camera* activeCamera;

		glm::vec3 position;
		glm::quat rotation;

		DECLSPEC Camera();
		DECLSPEC void SetPerspective(float fovy, float aspect, float zNear, float zFar);

		DECLSPEC void Use();

		DECLSPEC glm::mat4 GetMatrix();

		DECLSPEC void SetViewport(int32_t x, int32_t y, int32_t width, int32_t height);

	private:
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
	};

}
