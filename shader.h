#ifndef SHADER_H
#define SHADER_H
#include	<glad/glad.h>
#include	<string>
#include	<fstream>
#include	<sstream>
#include	<iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Shader
{
	public:
		unsigned int ID;
		Shader(const char *vertexPath, const char *fragmentShader);
		void use();
		void setBool(const std::string &name, bool value);
		void setBool(const std::string &name, bool value1, bool value2);
		void setBool(const std::string &name, bool value1, bool value2, 
										bool value3);
		void setBool(const std::string &name, bool value1, bool value2,
										bool value3, bool value4);
		void setInt(const std::string &name, int value1) ;
		void setInt(const std::string &name, int value1, int value2) ;
		void setInt(const std::string &name, int value1, int value2,
										int value3);
		void setInt(const std::string &name, int value1, int value2,
										int value3, int value4);
		void setFloat(const std::string &name, float value1) ;
		void setFloat(const std::string &name, float value1, float value2) ;
		void setFloat(const std::string &name, float value1, float value2,
										float value3);
		void setFloat(const std::string &name, float value1, float value2,
										float value3, float value4);
		void setMat4(const std::string &name, glm::mat4 &matrix);
						void setVec3(const std::string &name, glm::vec3 &vec);
};
#endif
