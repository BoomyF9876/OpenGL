#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "StandardIncludes.h"

class Camera
{
public:
	Camera() = default;
	Camera(Resolution _resolution);
	~Camera() = default;
	glm::mat4 GetProjection() { return projection; };
	glm::mat4 GetView() { return view; };

private:
	glm::mat4 projection;
	glm::mat4 view;
};
#endif // !_CAMERA_H_
