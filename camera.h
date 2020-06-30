#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Camera
{
  public:
					bool firstMouse;
					float lastX;
					float lastY;
          float yaw;
          float pitch;
          float speed;
          float sens;
          float deltaTime;
          float lastFrame;
          glm::vec3 pos;
          glm::vec3 front;
          glm::vec3 up;
					glm::vec3 worldUp;
          GLFWwindow *window;

          //methods
					Camera(glm::vec3 pos, glm::vec3 front, GLFWwindow *window);
          void wrapper();
          void processInput_kboard();
					void processInput_mouse(float xp, float yp);
					glm::mat4 getLookAt();
};
#endif
