#include "Camera.h"


Camera::Camera( glm::vec3 position, glm::vec3 up, float yaw, float pitch ) :
	_position( position ),
	_front( settings::camera::DEFAULT_FRONT ),
	_worldUp( up ),
	_yaw( yaw ),
	_pitch( pitch ),
	_panSpeed( settings::camera::DEFAULT_PAN_SPEED ),
	_tiltSensitivity( settings::camera::DEFAULT_TILT_SENSITIVITY ),
	_zoom( settings::camera::DEFAULT_ZOOM )
{
	this->updateCameraOrientation();
}


Camera::~Camera() {}



glm::vec3 Camera::getPosition() const
{
	return this->_position;
}


glm::vec3 Camera::getFront() const
{
	return this->_front;
}


glm::vec3 Camera::getUp() const
{
	return this->_up;
}


glm::vec3 Camera::getRight() const
{
	return this->_right;
}


glm::vec3 Camera::getWorldUp() const
{
	return this->_worldUp;
}


float Camera::getYaw() const
{
	return this->_yaw;
}


float Camera::getPitch() const
{
	return this->_pitch;
}


float Camera::getPanSpeed() const
{
	return this->_panSpeed;
}


float Camera::getTiltSensitivity() const
{
	return this->_tiltSensitivity;
}


float Camera::getZoom() const
{
	return this->_zoom;
}


glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt( this->_position, this->_position + this->_front, this->_up );
}


void Camera::processPanInput( PanDirection direction, float deltaTime )
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


void Camera::processTiltInput( float xOffset, float yOffset, GLboolean constrainPitch )
{
	xOffset *= this->_tiltSensitivity;
	yOffset *= this->_tiltSensitivity;

	this->_yaw += xOffset;
	this->_yaw = glm::mod( this->_yaw + xOffset, 360.0f );

	this->_pitch += yOffset;

	if ( constrainPitch )
	{
		if ( this->_pitch > 89.99609375f )
			this->_pitch = 89.99609375f;
		if ( this->_pitch < -89.99609375f )
			this->_pitch = -89.99609375f;
	}

	updateCameraOrientation();

	return;
}


void Camera::processZoom( float yOffset )
{
	this->_zoom -= yOffset;
	if ( this->_zoom < 1.0f ) this->_zoom = 1.0f;
	if ( this->_zoom > 45.0f ) this->_zoom = 45.0f;

	return;
}


void Camera::updateCameraOrientation()
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