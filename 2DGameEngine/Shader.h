#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

#include <cstdint>
#include <string>

#include <iostream>

class Shader
{
private:
	//std::string _vertexCode;
	//std::string _fragmentCode;

	std::uint32_t _shaderProgram;
private:
	static std::string loadShaderSourceCode( const char* filename )
	{
		// Pass a filename, return the source code of the file to dynamically compile during runtime
		// vertex and fragment shader glsl files
		std::ifstream file;
		std::stringstream buf;

		std::string contents = "";

		file.open( filename );

		if ( file.is_open() )
		{
			buf << file.rdbuf();
			contents = buf.str();
		}
		else
		{
			std::cout << "Could not open: " << filename << std::endl;
		}

		file.close();

		return contents;
	}
public:
	Shader() : /*_vertexCode(), _fragmentCode(),*/ _shaderProgram( 0 ) {}
	~Shader() {}

	std::uint32_t getShaderProgram() const
	{
		return this->_shaderProgram;
	}

	void setProgramId( std::uint32_t programId )
	{
		this->_shaderProgram = programId;
		return;
	}


	void load( const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath )
	{
		std::uint32_t vertexShader;
		std::uint32_t fragmentShader;

		// Compile Shaders and create ShaderProgram
		// Debug logging
		int success;
		char infoLog[512];

		// Load Shader Code
		std::string vertexShaderString = Shader::loadShaderSourceCode( vertexShaderFilePath.c_str() );
		const char* vertexShaderSourceCode = vertexShaderString.c_str();
		std::string fragmentShaderString = Shader::loadShaderSourceCode( fragmentShaderFilePath.c_str() );
		const char* fragmentShaderSourceCode = fragmentShaderString.c_str();

		// Compile Vertex Shader
		vertexShader = glCreateShader( GL_VERTEX_SHADER );
		glShaderSource( vertexShader, 1, &vertexShaderSourceCode, NULL ); // attach the shader source to the shader object
		glCompileShader( vertexShader ); // compile the shader
		glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &success ); // error in compilation checking
		if ( !success )
		{
			glGetShaderInfoLog( vertexShader, 512, NULL, infoLog );
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		// Compile FragmentShader
		fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
		glShaderSource( fragmentShader, 1, &fragmentShaderSourceCode, NULL );
		glCompileShader( fragmentShader );
		glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success ); // error in compilation checking
		if ( !success )
		{
			glGetShaderInfoLog( fragmentShader, 512, NULL, infoLog );
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		// Create ShaderProgram
		this->_shaderProgram = glCreateProgram();
		glAttachShader( this->_shaderProgram, vertexShader );
		glAttachShader( this->_shaderProgram, fragmentShader );
		glLinkProgram( this->_shaderProgram );
		glGetProgramiv( this->_shaderProgram, GL_LINK_STATUS, &success );
		if ( !success )
		{
			glGetProgramInfoLog( this->_shaderProgram, 512, NULL, infoLog );
			std::cout << "ERROR::SHADER::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		// Clean up and delete shader objects once linked into our program
		glDetachShader( this->_shaderProgram, vertexShader );
		glDetachShader( this->_shaderProgram, fragmentShader );
		glDeleteShader( vertexShader );
		glDeleteShader( fragmentShader );

		return;
	}


	void use()
	{
		glUseProgram( this->_shaderProgram );
		return;
	}
};