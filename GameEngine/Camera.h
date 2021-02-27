#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
	Camera( glm::vec3 position, glm::vec3 up, float yaw, float pitch ) : 
		_position( position ),
		_front( glm::vec3( 0.0f, 0.0f, -1.0f ) ),
		_worldUp( up ),
		_yaw( yaw ),
		_pitch( pitch ),
		_panSpeed( 2.0f ),
		_tiltSensitivity( 0.1f ),
		_zoom( 45.0f )
	{
		this->updateCameraOrientation();
	}

	~Camera() {}


	glm::mat4 getViewMatrix()
	{
		return glm::lookAt( this->_position, this->_position + this->_front, this->_up );
	}


	void processPanInput( PanDirection direction, float deltaTime )
	{
		float velocity = this->_panSpeed * deltaTime;
		if ( direction == PanDirection::UP ) this->_position += this->_worldUp * velocity;
		if ( direction == PanDirection::DOWN ) this->_position -= this->_worldUp * velocity;
		if ( direction == PanDirection::LEFT ) this->_position -= this->_right * velocity;
		if ( direction == PanDirection::RIGHT ) this->_position += this->_right * velocity;
		if ( direction == PanDirection::LEFT ) this->_position -= this->_right * velocity;
		if ( direction == PanDirection::RIGHT ) this->_position += this->_right * velocity;
		if ( direction == PanDirection::FORWARD ) this->_position += this->_front * velocity;
		if ( direction == PanDirection::BACKWARD ) this->_position -= this->_front * velocity;

		return;
	}


	void processTiltInput( float xOffset, float yOffset, GLboolean constrainPitch = true )
	{
		xOffset *= this->_tiltSensitivity;
		yOffset *= this->_tiltSensitivity;

		this->_yaw += xOffset;
		this->_yaw = glm::mod( this->_yaw + xOffset, 360.0f );

		this->_pitch += yOffset;

		if ( constrainPitch )
		{
			if ( this->_pitch > 89.9375f )
				this->_pitch = 89.9375f;
			if ( this->_pitch < -89.9375f )
				this->_pitch = -89.9375f;
		}

		// Update camera orientation vectors using the updated Euler angles
		updateCameraOrientation();

		return;
	}


	void processZoom( float yOffset )
	{
		this->_zoom -= yOffset;
		if ( this->_zoom < 1.0f ) this->_zoom = 1.0f;
		if ( this->_zoom > 45.0f ) this->_zoom = 45.0f;

		return;
	}


	void updateCameraOrientation()
	{
		// Recalculate the front vector
		glm::vec3 newFront;
		newFront.x = std::cosf( glm::radians( this->_yaw ) ) * std::cosf( glm::radians( this->_pitch ) );
		newFront.y = std::sinf( glm::radians( this->_pitch ) );
		newFront.z = std::sinf( glm::radians( this->_yaw ) ) * std::cosf( glm::radians( this->_pitch ) );
		this->_front = glm::normalize( newFront );

		// Recalculate the Right and Up vector
		this->_right = glm::normalize( glm::cross( this->_front, this->_worldUp ) );
		this->_up = glm::normalize( glm::cross( this->_right, this->_front ) );

		return;
	}

};


#endif


// Credits to https://learnopengl.com/Getting-started/Camera