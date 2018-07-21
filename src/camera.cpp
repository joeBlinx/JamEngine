//
// Created by joe on 21/07/18.
//

#include <glm/detail/type_mat4x4.hpp>
#include <2dEngine/camera.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera * Camera::current = nullptr;

std::vector<Camera *> cameras;
const glm::mat4 &Camera::getView() const {
    return view;
}

const glm::mat4 &Camera::getPerspective() const {
    return perspective;
}

const glm::vec3 &Camera::getPos() const {
    return pos;
}

const glm::vec3 & Camera::getEye() const {
    return eye;
}

const glm::vec3 &Camera::getUp() const {
    return up;
}

Camera::Camera(const glm::vec3 &pos, const glm::vec3 &eye, const glm::vec3 &up, float bottom,
               float top, float left, float right, float near, float far): pos(pos),
                                                                           eye(eye),
                                                                           up(up),
                                                                           near(near),
                                                                           far(far),
                                                                           bottom(bottom),
                                                                            top(top),
                                                                           left(left),
                                                                           right(right) {
    view = glm::lookAt(pos, eye, up);
    if(!far){

        perspective = glm::ortho(left, right, bottom, top);

    }else{

        perspective = glm::ortho(left, right, bottom, top, near, far);
    }
}

glm::mat4 Camera::getCamView() const {
    return perspective*view;
}

void Camera::addCamera(Camera *newCam) {
    Camera::cameras.push_back(newCam);

}

void Camera::changeCamera(int id) {
    Camera::current = cameras[id];
}

Camera *Camera::getCurrent() {
    return Camera::current;
}
