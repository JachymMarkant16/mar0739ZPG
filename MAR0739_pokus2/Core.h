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

#include <SOIL.h>

#include "ShaderProgram.h"
#include "ModelObject.h"
#include "Camera.h"
#include <iostream>
#include <vector>
class Core
{
private:
	Core();
	static Core* instance;
	GLFWwindow* window;
	Camera* camera;
	std::vector<ModelObject> objects;
	bool mouseDown = false;
	glm::mat4 projection;
	int controlledObj = 1;
	static void error_callback(int error, const char* description) { fputs(description, stderr); }
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Core* core = core->getInstance();
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			core->camera->moveFront();
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			core->camera->moveBack();
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			core->camera->moveLeft();
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			core->camera->moveRight();
		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
			core->controlledObj = 1;
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
			core->controlledObj = 2;
		if(glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS)
			core->objects[core->controlledObj].MoveRight(-1);
		if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS)
			core->objects[core->controlledObj].MoveRight(1);
	}
	static void window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }
	static void window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }
	static void window_size_callback(GLFWwindow* window, int width, int height) {
		printf("resize %d, %d \n", width, height);
		glViewport(0, 0, width, height);
		Core* core = core->getInstance();
		core->projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	}
	static void cursor_callback(GLFWwindow* window, double x, double y) {
		Core* core = core->getInstance();
		if (core->camera->getInitLook()) {
			core->camera->setLastXY(x, y);
			core->camera->setInitLook(false);
		}
		if (core->mouseDown)
		{
			instance->camera->lookAround(x, y);
		}
		printf("cursor_callback \n"); 
	}
	static void button_callback(GLFWwindow* window, int button, int action, int mode) {
		Core* core = core->getInstance();
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
			core->mouseDown = true;
			core->camera->setInitLook(true);
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
			core->mouseDown = false;
			core->camera->setInitLook(true);
		}
		if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
	}

public:
	static Core* getInstance() {
		if (!instance)
			instance = new Core;
		return instance;
	}
	void setData(int width, int height, const char* windowName);
	void initCore();
	void start();
	void addObject(ModelObject object);
};