#ifndef SETTINGS_H
#define SETTINGS_H

#include <cstdint>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace settings
{
	namespace screen
	{
		constexpr std::uint32_t DEFAULT_WIDTH = 1920;
		constexpr std::uint32_t DEFAULT_HEIGHT = 1080;

	}

	namespace camera
	{
		constexpr glm::vec3 DEFAULT_POSITION = glm::vec3( 0.0f, 0.0f, 5.0f );
		constexpr glm::vec3 DEFAULT_UP = glm::vec3( 0.0f, 1.0f, 0.0f );
		constexpr glm::vec3 DEFAULT_FRONT = glm::vec3( 0.0f, 0.0f, -1.0f );

		constexpr float DEFAULT_YAW = -90.0f;
		constexpr float DEFAULT_PITCH = 0.0f;
		constexpr float DEFAULT_PAN_SPEED = 2.5f; // 2.5f;
		constexpr float DEFAULT_TILT_SENSITIVITY = 0.02f;
		constexpr float DEFAULT_ZOOM = 45.0f;
	}
}

#endif
