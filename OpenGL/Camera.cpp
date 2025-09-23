#include "Camera.h"

Camera::Camera(Resolution _resolution)
{
	projection = glm::perspective(glm::radians(45.0f), 
		(float)_resolution.width / (float)_resolution.height, 
		0.1f, 100.0f);
	view = glm::lookAt(
		glm::vec3(4,3, 3), 
		glm::vec3(0, 0, 0), //and looks at the origin
		glm::vec3(0, 1, 0)  //Head is up (set to 0,-1,0 to look upside-down)
	);
}