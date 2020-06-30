#include "../headers/shader.h"

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
	//PEGANDO O CODIGO FONTE DAS PASTAS
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	//TENDO CERTEZA DE QUE NÃO HOUVE FALHAS
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);	
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);	
	try
	{
		//ABRINDO AS PASTAS
		
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		
		//JOGANDO O CONTEUDO EM STRING BUFFERS
		
		std::stringstream vShaderStream, fShaderStream;
		
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		
		//FECHANDO AS PASTAS
		
		vShaderFile.close();
		fShaderFile.close();

		//PASSANDO O VALOR DAS STREAMS PARA STRINGS
		
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch(std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULY_READ" << std::endl;
	}
	
	const char *vShaderCode = vertexCode.c_str();
	const char *fShaderCode = fragmentCode.c_str();
	unsigned int vertex, fragment;
	int sucess;
	char infoLog[512];

	//COMPILANDO VERTEX SHADER
	
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	
	//CHECANDO PARA EVENTUAIS ERROS NA COMPILAÇÃO
	
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &sucess);
	if(!sucess)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::VERTEX_SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	//CHECANDO PARA EVENTUAIS ERROS NA COMPILAÇÃO
	
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &sucess);
	if(!sucess)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::FRAGMENT_SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//SHADER PROGRAM
	
	this->ID = glCreateProgram();
	glAttachShader(this->ID, vertex);
	glAttachShader(this->ID, fragment);
	glLinkProgram(this->ID);
	
	glGetProgramiv(this->ID, GL_LINK_STATUS, &sucess);
	
	if(!sucess)
	{
		glGetProgramInfoLog(this->ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use()
{
	glUseProgram(this->ID);
}

void Shader::setBool(const std::string &name, bool value) 
{
	glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value);
}

void Shader::setBool(const std::string &name, bool value1, bool value2) 
{
	glUniform2i(glGetUniformLocation(this->ID, name.c_str()), (int)value1, (int)value2);
}

void Shader::setBool(const std::string &name, bool value1, bool value2, bool value3) 
{
	glUniform3i(glGetUniformLocation(this->ID, name.c_str()), (int)value1, (int)value2, (int)value3);
}

void Shader::setBool(const std::string &name, bool value1, bool value2, 
								bool value3, bool value4) 
{
	glUniform4i(glGetUniformLocation(this->ID, name.c_str()), (int)value1, 
									(int)value2, (int)value3, (int)value4);
}

void Shader::setFloat(const std::string &name, float value) 
{
	glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value1,
								float value2) 
{
	glUniform2f(glGetUniformLocation(this->ID, name.c_str()), value1, value2);
}

void Shader::setFloat(const std::string &name, float value1,
								float value2, float value3) 
{
	glUniform3f(glGetUniformLocation(this->ID, name.c_str()), value1, value2, value3);
}

void Shader::setFloat(const std::string &name, float value1,
								float value2, float value3, float value4) 
{
	glUniform4f(glGetUniformLocation(this->ID, name.c_str()), value1, value2, value3, value4);
}

void Shader::setInt(const std::string &name, int value) 
{
	glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value1, int value2) 
{
	glUniform2i(glGetUniformLocation(this->ID, name.c_str()), value1, value2);
}

void Shader::setInt(const std::string &name, int value1, int value2, int value3) 
{
	glUniform3i(glGetUniformLocation(this->ID, name.c_str()), value1, value2,
									value3);
}

void Shader::setInt(const std::string &name, int value1, int value2, int value3, int value4) 
{
	glUniform4i(glGetUniformLocation(this->ID, name.c_str()), value1, value2,
									value3, value4);
}
void Shader::setMat4(const std::string &name, glm::mat4 &matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 
										1, GL_FALSE, glm::value_ptr(matrix));
}
void Shader::setVec3(const std::string &name, glm::vec3 &vec)
{
	glUniform3f(glGetUniformLocation(this->ID, name.c_str()), vec.x, vec.y, vec.z);
	
}
