#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Settings.h"

class Camera
{
public:
	enum class PanDirection
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		FORWARD,
		BACKWARD,
	};

public:
	glm::vec3 _position;
	glm::vec3 _front;
	glm::vec3 _up;
	glm::vec3 _right;
	glm::vec3 _worldUp;

	float _yaw;
	float _pitch;

	float _panSpeed;
	float _tiltSensitivity;
	float _zoom;

public:
	Camera( glm::vec3 position = settings::camera::DEFAULT_POSITION, glm::vec3 up = settings::camera::DEFAULT_UP, float yaw = settings::camera::DEFAULT_YAW, float pitch = settings::camera::DEFAULT_PITCH );


	~Camera();


	glm::mat4 getViewMatrix();


	/**
	 * Update the position of the camera based on a direction and deltaTime for velocity
	 *
	 * Pan determines the view matrix
	 *
	 * @param direction a PanDirection represents direction of the camera
	 * @param float deltaTime a float that synchronizes time-based calculations for different hardware
	 * @return void
	 */
	void processPanInput( PanDirection direction, float deltaTime );


	/**
	 * Update the yaw and pitch of the camera
	 *
	 * Tilt determines view matrix
	 *
	 * @param xOffset float to be treated as degrees to be added to yaw
	 * @param yOffset float to be treated as degrees to be added to pitch
	 * @param constrainPitch boolean that toggles the pitch range. Avoids upsidedown
	 * @return void
	 */
	void processTiltInput( float xOffset, float yOffset, GLboolean constrainPitch = true );


	/**
	 * Update the zoom based on offset of the camera
	 *
	 * Zoom determines the projection matrix
	 *
	 * @param yOffset float to be added to the _zoom
	 * @return void
	 */
	void processZoom( float yOffset );


	/**
	 * Update the camera orientation based on yaw and pitch values ( euler values updated )
	 *
	 * Orientation is given by three orthognal vectors: _up, _right, and _front
	 *
	 * @return void
	 */
	void updateCameraOrientation();

};


#endif


// Credits to https://learnopengl.com/Getting-started/Camera