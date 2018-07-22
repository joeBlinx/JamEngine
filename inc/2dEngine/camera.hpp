//
// Created by joe on 21/07/18.
//
#ifndef INC_2DENGINE_CAMERA_HPP
#define INC_2DENGINE_CAMERA_HPP

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <vector>
class Camera{

private:
    glm::vec3 pos;
    glm::vec3 eye;
    glm::vec3 up;

    float near, far;
    float bottom, top;
    float left, right;

    glm::mat4 projection;
    glm::mat4 view;

    static Camera * current;
    static std::vector<Camera *> cameras;


    void computeLookAt();

    void computeProj();
public:
    Camera(const glm::vec2 &pos,
		   float bottom, float top,
		   float left, float right,
		   float near = 0, float far = 0);

    const glm::vec3 &getPos() const;

    const glm::vec3 & getEye() const;

    const glm::mat4 &getView() const;

    const glm::vec3 &getUp() const;

    const glm::mat4 &getProjection() const;

    void move(float x, float y);

    void moveX(float x);

    void moveY(float y);

    void zoom(float zoom);

    glm::mat4 getCamView() const;

    static int addCamera(Camera *newCam);

    static void changeCamera(int id);

    static Camera * getCurrent();



};

#endif //INC_2DENGINE_CAMERA_HPP
