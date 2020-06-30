#ifndef CAMERA_H
#define CAMERA_H
#include "../headers/camera.h"


Camera::Camera(glm::vec3 pos, glm::vec3 front, GLFWwindow *window)
{
	this->firstMouse = true;
	this->lastX = 400;
	this->lastY = 300;
	this->yaw = -90;
	this->pitch = 0;
	this->deltaTime = 0;
	this->lastFrame = 0;
	this->speed = 2.5f;
	this->pos = pos;
	this->sens = 0.1f;
	this->front = front;
	this->worldUp = glm::vec3(0.0f,1.0f,0.0f);
	this->window = window;
}	

void Camera::wrapper()
{
		float currentFrame = glfwGetTime();
		this->deltaTime = currentFrame - this->lastFrame;
		this->lastFrame = currentFrame;
	  this->speed = 2.5f * this->deltaTime; // adjust accordingly
		this->processInput_kboard();
}

void Camera::processInput_kboard()
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        this->pos += this->speed * this->front;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        this->pos -= this->speed * this->front;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        this->pos -= glm::normalize(glm::cross(this->front, this->up)) * this->speed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        this->pos += glm::normalize(glm::cross(this->front, this->up)) * this->speed;
}

void Camera::processInput_mouse(float xpos, float ypos)
{
	if(this->firstMouse)
	{
			this->lastX = xpos;
			this->lastY = ypos;
			this->firstMouse = false;
	}
	std::cout << xpos << " " << ypos << std::endl;
	float xoffset = lastX - xpos;
	float yoffset = ypos - lastY;
	this->lastX = xpos;
	this->lastY = ypos;
	
	xoffset *= this->sens;
	yoffset *= this->sens;

	this->yaw += xoffset;
	this->pitch += yoffset;

	if(this->pitch > 89.0f)
					this->pitch = 89.0f;
	if(this->pitch < -89.0f)
					this->pitch = -89.0f;
	glm::vec3 direc;
	direc.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	direc.y = sin(glm::radians(this->pitch));
	direc.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front = glm::normalize(direc);
  std::cout << this->front.x << " " << this->front.y << " " << this->front.z << std::endl;
}

glm::mat4 Camera::getLookAt()
{
	glm::vec3 Cright = glm::normalize(glm::cross(this->worldUp, this->front));
	this->up = glm::cross(Cright, this->front);
	return glm::lookAt(this->pos, this->pos + this->front, this->up);
}
#endif
