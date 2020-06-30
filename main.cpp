#define STB_IMAGE_IMPLEMENTATION
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "headers/stb_image.h"
#include <iostream>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "headers/shader.h"
#include "headers/camera.h"
#include "headers/mashes.hpp"
#include <string>
#include <vector>
#define SCREEN_W 800
#define SCREEN_H 600

//SHADER
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void _main_glfwInit();
GLFWwindow* _main_glfwCreateWindow();
void _main_gladLoaderGLLoader();

//Material

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f,  0.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
Camera c1(cameraPos, cameraFront, NULL);
glm::mat4 projection;
glm::mat4 view;

void mouse_callback(GLFWwindow *window, double xp, double yp)
{
	c1.processInput_mouse(xp, yp);
}

int main()
{
	// INITIALIZING STUFF DO NOT TOUCH
	_main_glfwInit();
	GLFWwindow* window = _main_glfwCreateWindow();
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	_main_gladLoaderGLLoader();

	//SHADER STUFF

	Shader lightShader("shaders/vertexShader1.vs","shaders/fragmentShader2.vs");

	Shader lSourceShader("shaders/vertexShader1.vs", "shaders/fragmentShader1.vs");
	//VERTICE STUFF
	float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};
	glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3( 2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3( 1.3f, -2.0f, -2.5f),
    glm::vec3( 1.5f,  2.0f, -2.5f),
    glm::vec3( 1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	//VERTEX ARRAY OBJECT

	unsigned int VAO1;
	glGenVertexArrays(1, &VAO1);
	glBindVertexArray(VAO1);
	// ..:: Initialization code ::..

	//OBJETO DE BUFFER DE VERTICE STUFF

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//VERTEX INTERPRETATION
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//LIGHT VBO
	unsigned int LIGHTVBO;
	glGenBuffers(1, &LIGHTVBO);
	glBindBuffer(GL_ARRAY_BUFFER, LIGHTVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//TEXTURE SHIT
	unsigned int texture1, texture2;
    // texture 1
    // ---------
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
     // set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
	int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char *data = stbi_load("container2.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
  else
  {
		std::cout << "Failed to load texture" << std::endl;
	}
    // texture 2
    // ---------
    glGenTextures(1, &texture2);
    glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    // load image, create texture and generate mipmaps
    data = stbi_load("container2_specular.png", &width, &height, &nrChannels, 0);
	if (data)
	{
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
  // either set it manually like so:

	glEnable(GL_DEPTH_TEST);
	c1.window = window;
	c1.sens = 0.05;
	//Window Loop
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	projection = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);
	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSetCursorPosCallback(window, mouse_callback);
		c1.wrapper();
		/*
		lightPos.x = sin(glfwGetTime() * 0.5) * 3;
		lightPos.y = 0;
		lightPos.z = cos(glfwGetTime() * 0.5) * 3;
		*/
		// MODEL VIEW AND PROJECTION MATRICES
		lightShader.use();

		//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 1.0f));

		//View Manipulation
		view = c1.getLookAt();

		//LIGHT STUFF
		//Point Lights
		glm::vec3 pointLightPositions[] = {
			glm::vec3( 0.7f,  0.2f,  2.0f),
			glm::vec3( 2.3f, -3.3f, -4.0f),
			glm::vec3(-4.0f,  2.0f, -12.0f),
			glm::vec3( 0.0f,  0.0f, -3.0f)
		};
		std::string ini = "pointLights[";
		for(int i = 0; i<4; i++)
		{
			std::string num = std::to_string(i);
			std::string sattn = ini + num + "].attn";
			glm::vec3 lightAttn(1.0f, 0.7f, 0.17f);
			lightShader.setVec3(sattn, lightAttn);
			std::string spos = ini + num + "].pos";
			lightShader.setVec3(spos, pointLightPositions[i]);
			glm::vec3 lightColor(1.0f);
			std::string sambient = ini + num + "].ambient";
			lightShader.setFloat(sambient, 0.2f, 0.2f, 0.2f);
			std::string sdiffuse = ini + num + "].diffuse";
			lightShader.setFloat(sdiffuse, 0.5f, 0.5f, 0.5f);
			std::string sspecular = ini + num + "].specular";
			lightShader.setFloat(sspecular, 1.0f, 1.0f, 1.0f);
		}
		//Direct Light
		glm::vec3 dirLight(1.0f, 0.0f, 0.0f);
		lightShader.setVec3("dirLight.dir", dirLight);
		lightShader.setFloat("dirLight.ambient", 0.2f, 0.2f, 0.2f);
		lightShader.setFloat("dirLight.diffuse", 0.5f, 0.5f, 0.5f);
		lightShader.setFloat("dirLight.specular", 0.5f, 0.5f, 0.5f);

		//SHADER USING AND RENDERING SETTINGS

		lightShader.setMat4("view", view);
		lightShader.setMat4("projection", projection);

		//MATERIAL STUFF

		lightShader.setFloat("material.objectColor", 1.0f, 1.0f, 1.0f);
	 	lightShader.setFloat("material.ambient", 1.0f, 0.5f, 0.31f);
		lightShader.setInt("material.diffuse", 0);
		lightShader.setInt("material.specular", 1);
		glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
		lightShader.setFloat("material.shininess", 16.0f);
		//BINDING VAO1'S
			//MODEL MANIPUL
			for(int i = 0; i<10; i++)
			{
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, cubePositions[i]);
				float angle = 20.0f * i;
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f,0.3f,0.5f));
				lightShader.setMat4("model", model);
				glBindVertexArray(VAO1);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		lSourceShader.use();
		glm::vec3 lightColor(1.0f);
		//Light stuff
		lSourceShader.setVec3("light.lightColor", lightColor);
		//Matrices
		for(auto s : pointLightPositions)
		{
			glm::mat4 model_cube(1.0f);
			model_cube = glm::translate(model_cube, s);
			model_cube = glm::scale(model_cube, glm::vec3(0.2f));

			lSourceShader.setMat4("model", model_cube);
			lSourceShader.setMat4("view", view);
			lSourceShader.setMat4("projection", projection);
			//BINDING LIGHTING VBO
			glBindVertexArray(LIGHTVBO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glfwSwapBuffers(window);
    glfwPollEvents();
	}


	glDeleteVertexArrays(1, &VAO1);
  glDeleteBuffers(1, &VBO);
 // glDeleteProgram(shaderProgram);
 // glDeleteProgram(shaderProgram1);
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void _main_glfwInit()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
GLFWwindow *_main_glfwCreateWindow()
{
	GLFWwindow* window = glfwCreateWindow(SCREEN_W, SCREEN_H, "Lol", NULL, NULL);
	if (window == NULL)
	{
    	std::cout << "Failed to create GLFW window" << std::endl;
    	glfwTerminate();
    	exit(1);
	}
	return window;
}
void _main_gladLoaderGLLoader()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
    	std::cout << "Failed to initialize GLAD" << std::endl;
    	exit(1);
	}
}
