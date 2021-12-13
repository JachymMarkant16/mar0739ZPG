#include "Camera.h"
Camera::Camera() {
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    yaw = -90.0f;
    pitch = 0.0f;
    sensitivity = 0.3f;
    count = 0;
}
glm::mat4 Camera::getView() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    cameraSpeed = 0.25f;
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    return view;
}

void Camera::moveFront() {
    cameraPos += cameraSpeed * cameraFront;
}
void Camera::moveBack() {
    cameraPos -= cameraSpeed * cameraFront;
}
void Camera::moveLeft() {
    count++;
    printf(" count : %d\n", count);
    cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}
void Camera::moveRight() {
    cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}
void Camera::setLastXY(float x, float y) {
    lastX = x;
    lastY = y;
}
void Camera::setInitLook(bool look) {
    initLook = look;
}
bool Camera::getInitLook() {
    return initLook;
}
void Camera::lookAround(float x, float y) {
    float xoffset = x - lastX;
    float yoffset = lastY - y; // reversed since y-coordinates range from bottom to top
    lastX = x;
    lastY = y;

    xoffset *= sensitivity;
    yoffset *= sensitivity;
    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}
glm::vec3 Camera::getCameraPos() {
    return this->cameraPos;
}
glm::vec3 Camera::getCameraFront() {
    return this->cameraFront;
}