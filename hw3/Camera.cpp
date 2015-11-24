#include "Camera.h"

Camera::Camera(vec3 _lookFrom, vec3 _lookAt, vec3 _up, float _fovy){
    lookFrom = _lookFrom;
    lookAt = _lookAt;
    up = _up;
    fovy = _fovy;
}