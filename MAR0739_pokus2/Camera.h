#pragma once
#pragma once
//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>
// Include GLM
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
class Camera
{
private:
	glm::mat4 view;
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	float cameraSpeed = 0.05f;
	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame
	float lastX;
	float lastY;
	float yaw;
	float pitch;
	bool initLook = false;
	float sensitivity;
public:
	Camera();
	glm::mat4 getView();
	void moveFront();
	void moveBack();
	void moveLeft();
	void moveRight();
	void setLastXY(float x, float y);
	void setInitLook(bool look);
	bool getInitLook();
	void lookAround(float x, float y);
};

