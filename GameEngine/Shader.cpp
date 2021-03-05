#include "Shader.h"


Shader::Shader() : _id( 0 )
{
}


Shader::Shader( const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath ) : _id( 0 )
{
	this->load( vertexShaderFilePath, fragmentShaderFilePath );
}


Shader::~Shader()
{
	glDeleteProgram( this->_id );
}


GLuint Shader::getProgramId() const
{
	return this->_id;
}


void Shader::setProgramId( std::uint32_t programId )
{
	this->_id = programId;
	return;
}


void Shader::setBool( const std::string& name, bool value ) const
{
	glUniform1i( glGetUniformLocation( this->_id, name.c_str() ), ( GLint )value );
	return;
}


void Shader::setInt( const std::string& name, int value ) const
{
	glUniform1i( glGetUniformLocation( this->_id, name.c_str() ), ( GLint )value );
	return;
}


void Shader::setFloat( const std::string& name, float value ) const
{
	glUniform1f( glGetUniformLocation( this->_id, name.c_str() ), ( GLfloat )value );
	return;
}


void Shader::setVec2( const std::string& name, const glm::vec2& value ) const
{
	glUniform2fv( glGetUniformLocation( this->_id, name.c_str() ), 1, &value[0] );
}


void Shader::setVec2( const std::string& name, float x, float y ) const
{
	glUniform2f( glGetUniformLocation( this->_id, name.c_str() ), x, y );
}


void Shader::setVec3( const std::string& name, const glm::vec3& value ) const
{
	glUniform3fv( glGetUniformLocation( this->_id, name.c_str() ), 1, &value[0] );
}


void Shader::setVec3( const std::string& name, float x, float y, float z ) const
{
	glUniform3f( glGetUniformLocation( this->_id, name.c_str() ), x, y, z );
}


void Shader::setVec4( const std::string& name, const glm::vec4& value ) const
{
	glUniform4fv( glGetUniformLocation( this->_id, name.c_str() ), 1, &value[0] );
}


void Shader::setVec4( const std::string& name, float x, float y, float z, float w ) const
{
	glUniform4f( glGetUniformLocation( this->_id, name.c_str() ), x, y, z, w );
}


void Shader::setMat2( const std::string& name, const glm::mat2& mat ) const
{
	glUniformMatrix2fv( glGetUniformLocation( this->_id, name.c_str() ), 1, GL_FALSE, &mat[0][0] );
}


void Shader::setMat3( const std::string& name, const glm::mat3& mat ) const
{
	glUniformMatrix3fv( glGetUniformLocation( this->_id, name.c_str() ), 1, GL_FALSE, &mat[0][0] );
}


void Shader::setMat4( const std::string& name, const glm::mat4& mat ) const
{
	glUniformMatrix4fv( glGetUniformLocation( this->_id, name.c_str() ), 1, GL_FALSE, &mat[0][0] );
}


void Shader::load( const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath )
{
	// Compile Vertex and Fragment Shaders. Create ShaderProgram by linking the shaders.
	std::cout << "SHADER LOADED" << std::endl;
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
	//glBindAttribLocation( this->_id, 0, "position" ); // tells openGL what part of the data to read in your pipeline
	glLinkProgram( this->_id );
	Shader::checkShaderError( this->_id, GL_LINK_STATUS );
	glValidateProgram( this->_id );
	Shader::checkShaderError( this->_id, GL_VALIDATE_STATUS );

	// Set uniform variables
	glUseProgram( this->_id );
	std::cout << "SHADER ID: " << this->_id << std::endl;

	// Clean up and delete shader objects once linked into our program
	glDetachShader( this->_id, vertexShader );
	glDetachShader( this->_id, fragmentShader );
	glDeleteShader( vertexShader );
	glDeleteShader( fragmentShader );

	glUseProgram( 0 );

	return;
}


void Shader::use()
{
	glUseProgram( this->_id );
	return;
}


std::string Shader::loadShaderSourceCode( const char* filepath )
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

		if ( contents.size() == 0 ) std::cout << "ERROR::SHADER::NO_CONTENT\n" << filepath << std::endl;
	}
	catch ( std::ifstream::failure& e )
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n" << e.what() << std::endl;
	}

	return contents;
}


void Shader::checkShaderError( GLuint alias, GLenum buildFlag )
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


GLuint Shader::createShader( GLenum shaderType, const std::string& filePath )
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