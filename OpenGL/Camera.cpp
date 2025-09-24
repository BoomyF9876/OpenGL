#include "Camera.h"

Camera::Camera(Resolution& _resolution, float _fov, float _near, float _far)
{
	projection = glm::perspective(glm::radians(_fov), 
		(float)_resolution.width / (float)_resolution.height, 
		_near, _far);
	view = glm::lookAt(
		glm::vec3(1, 0, 0), 
		glm::vec3(0, 0, 0), //and looks at the origin
		glm::vec3(0, 1, 0)  //Head is up (set to 0,-1,0 to look upside-down)
	);
}

void Camera::LookAt(const glm::vec3& _position, const glm::vec3& _lookAt, const glm::vec3& _up)
{
	view = glm::lookAt(
		_position,
		_lookAt, //and looks at the origin
		_up  //Head is up (set to 0,-1,0 to look upside-down)
	);
}