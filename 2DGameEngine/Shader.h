#ifndef SHADER_H
#define SHADER_H

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
	std::uint32_t _id;
private:
	static std::string loadShaderSourceCode( const char* filepath )
	{
		// Pass a filename, return the source code of the file to dynamically compile during runtime
		// vertex and fragment shader glsl files

		std::string contents = "";

		std::ifstream shaderFile;
		try
		{
			shaderFile.open( filepath );

			std::stringstream shaderContentBuffer;
			shaderContentBuffer << shaderFile.rdbuf();

			shaderFile.close();

			contents = shaderContentBuffer.str();
		}
		catch ( std::ifstream::failure& e )
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n" << e.what() << std::endl;
		}


		return contents;

		/*
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
		*/
	}


	static void checkShaderError( GLuint alias, GLenum buildFlag )
	{
		GLint success;
		GLchar infoLog[512];

		switch ( buildFlag )
		{
		case GL_COMPILE_STATUS:
			glGetShaderiv( alias, buildFlag, &success ); // error in compilation checking
			if ( !success )
			{
				glGetShaderInfoLog( alias, 512, NULL, infoLog );
				std::cout << "ERROR::SHADER::SHADER::COMPILE\n" << infoLog << std::endl;
			}
			break;
		case GL_LINK_STATUS:
			glGetProgramiv( alias, GL_LINK_STATUS, &success );
			if ( !success )
			{
				glGetProgramInfoLog( alias, 512, NULL, infoLog );
				std::cout << "ERROR::SHADER::SHADER_PROGRAM::LINK\n" << infoLog << std::endl;
			}
			break;
		case GL_VALIDATE_STATUS:
			glGetProgramiv( alias, GL_VALIDATE_STATUS, &success );
			if ( !success )
			{
				glGetProgramInfoLog( alias, 512, NULL, infoLog );
				std::cout << "ERROR::SHADER::SHADER_PROGRAM::VALIDATE\n" << infoLog << std::endl;
			}
			break;
		default:
			break;
		}

		return;
	}


	static GLuint createShader( GLenum shaderType, const std::string& filePath )
	{
		// Create, compiles, and returns the alias to a shader
		std::string shaderString = Shader::loadShaderSourceCode( filePath.c_str() );
		const char* shaderSourceCode = shaderString.c_str();

		GLuint shader = glCreateShader( shaderType );
		glShaderSource( shader, 1, &shaderSourceCode, NULL ); // attach the shader source to the shader object
		glCompileShader( shader ); // compile the shader
		Shader::checkShaderError( shader, GL_COMPILE_STATUS );

		return shader;
	}
public:
	Shader() : _id( 0 ) {}


	~Shader() 
	{
		glDeleteProgram( this->_id );
	}


	/// Getters
	GLuint getProgramId() const
	{
		return this->_id;
	}


	/// Setters
	void setProgramId( std::uint32_t programId )
	{
		this->_id = programId;
		return;
	}


	/// Utility Uniform Functions
	void setBool( const std::string& name, bool value ) const 
	{
		glUniform1i( glGetUniformLocation( this->_id, name.c_str() ), ( GLint )value );
		return;
	}


	void setInt( const std::string& name, int value ) const
	{
		glUniform1i( glGetUniformLocation( this->_id, name.c_str() ), ( GLint )value );
		return;
	}


	void setFloat( const std::string& name, float value ) const
	{
		glUniform1f( glGetUniformLocation( this->_id, name.c_str() ), ( GLfloat )value );
		return;
	}


	///
	void load( const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath )
	{
		// Compile Vertex and Fragment Shaders. Create ShaderProgram by linking the shaders.

		// Load Shader Code
		std::string vertexShaderString = Shader::loadShaderSourceCode( vertexShaderFilePath.c_str() );
		const char* vertexShaderSourceCode = vertexShaderString.c_str();
		std::string fragmentShaderString = Shader::loadShaderSourceCode( fragmentShaderFilePath.c_str() );
		const char* fragmentShaderSourceCode = fragmentShaderString.c_str();

		// Create Vertex Shader
		GLuint vertexShader = Shader::createShader( GL_VERTEX_SHADER, vertexShaderFilePath );

		// Compile FragmentShader
		GLuint fragmentShader = Shader::createShader( GL_FRAGMENT_SHADER, fragmentShaderFilePath );

		// Create ShaderProgram
		this->_id = glCreateProgram();
		glAttachShader( this->_id, vertexShader );
		glAttachShader( this->_id, fragmentShader );
		glBindAttribLocation( this->_id, 0, "position" ); // tells openGL what part of the data to read in your pipeline
		glLinkProgram( this->_id );
		Shader::checkShaderError( this->_id, GL_LINK_STATUS );
		glValidateProgram( this->_id );
		Shader::checkShaderError( this->_id, GL_VALIDATE_STATUS );

		// Clean up and delete shader objects once linked into our program
		glDetachShader( this->_id, vertexShader );
		glDetachShader( this->_id, fragmentShader );
		glDeleteShader( vertexShader );
		glDeleteShader( fragmentShader );


		glUseProgram( this->_id );
		glUniform1i( glGetUniformLocation( this->_id, "texture0" ), 0 );
		glUniform1i( glGetUniformLocation( this->_id, "texture1" ), 1 );
		return;
	}


	void use()
	{
		glUseProgram( this->_id );
		return;
	}

};

#endif