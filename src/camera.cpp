//

#include <glm/detail/type_mat4x4.hpp>
#include <2dEngine/camera.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera * Camera::current = nullptr;

std::vector<Camera *> Camera::cameras;
const glm::mat4 &Camera::getView() const {
    return view;
}

const glm::mat4 &Camera::getProjection() const {
    return projection;
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

Camera::Camera(const glm::vec2 &pos, float bottom, float top,
			   float left, float right, float _near, float _far) : pos(glm::vec3(pos, 1)),
																eye(glm::vec3(pos.x, pos.y, 0)),
																up(glm::vec3(0, 1, 0)),
																_near(_near),
																_far(_far),
																bottom(bottom),
																top(top),
																left(left),
																right(right) {
    view = glm::lookAt(this->pos, eye, up);

    computeProj();
}

glm::mat4 Camera::getCamView() const {
    return projection*view;
}

int Camera::addCamera(Camera *newCam) {
    Camera::cameras.push_back(newCam);
    return Camera::cameras.size() - 1;

}

void Camera::changeCamera(int id) {
    Camera::current = cameras[id];
}

Camera *Camera::getCurrent() {
    return Camera::current;
}

void Camera::move(float x, float y) {

    moveX(x);
    moveY(y);
}

void Camera::moveX(float x) {
    pos.x += x;
    eye.x += x;
    computeLookAt();
}

void Camera::moveY(float y) {
    pos.y += y;
    eye.y += y;
    computeLookAt();
}

void Camera::computeLookAt() {
    view = glm::lookAt(pos, eye, up);
}

void Camera::computeProj() {
	    if(!_far){

        projection = glm::ortho(left, right, bottom, top);

    }else{

        projection = glm::ortho(left, right, bottom, top, _near, _far);
    }
}

void Camera::zoom(float zoom) {

	zoom *=-1;
	left -= zoom;
	right += zoom;
	bottom -= zoom;
	top += zoom;
	computeProj();

}
