#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	std::uint32_t _shaderProgramId;

private:
	/**
	 * Helper function to load in source code from a shader file path
	 *
	 * @return void
	 */
	static std::string loadShaderSourceCode( const char* filepath );


	/**
	 * Generalized error checking for the compilization and linking process
	 *
	 * @return void
	 */
	static void checkShaderError( GLuint alias, GLenum buildFlag );


	/**
	 * Creates and returns an alias to a shader object
	 *
	 * @return GLuint a reference number to the shader object
	 */
	static GLuint createShaderObject( GLenum shaderType, const std::string& filePath );
public:
	Shader();

	Shader( const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath );

	virtual ~Shader();



	/**
	 * Given paths to a vertex shader and a fragment shader, ultimately create a shader program
	 *
	 * Creates and compiles a vertex and fragment shader object. Attaches these shader objects to a shader program.
	 * Link the entire shader program to be used.
	 *
	 * @return void
	 */
	void createShaderProgram( const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath );


	/// Getters
	GLuint getShaderProgramId() const;


	/// Utility Uniform Functions
	void setBool( const std::string& name, bool value ) const;


	void setInt( const std::string& name, int value ) const;


	void setFloat( const std::string& name, float value ) const;


	void setVec2( const std::string& name, const glm::vec2& value ) const;


	void setVec2( const std::string& name, float x, float y ) const;


	void setVec3( const std::string& name, const glm::vec3& value ) const;


	void setVec3( const std::string& name, float x, float y, float z ) const;


	void setVec4( const std::string& name, const glm::vec4& value ) const;


	void setVec4( const std::string& name, float x, float y, float z, float w ) const;


	void setMat2( const std::string& name, const glm::mat2& mat ) const;


	void setMat3( const std::string& name, const glm::mat3& mat ) const;


	void setMat4( const std::string& name, const glm::mat4& mat ) const;


	/**
	 * Use this shader program
	 *
	 * @return void
	 */
	void use();
};

#endif