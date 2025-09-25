#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "StandardIncludes.h"

class Camera
{
public:
    Camera(Resolution& _resolution, float _fov = 45.0f, float _near = 0.1f, float _far = 1000.0f);

    void LookAt(const glm::vec3& _position, const glm::vec3& _lookAt, const glm::vec3& _up);

    void SetProjection(const glm::mat4& proj) { projection = proj; }

    inline glm::mat4 GetProjection() const { return projection; }
    inline glm::mat4 GetView() const { return view; }

private:
    glm::mat4 projection;
    glm::mat4 view;
};
#endif // !_CAMERA_H_
