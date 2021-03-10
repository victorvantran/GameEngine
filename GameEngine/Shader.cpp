#include "Shader.h"

Shader::Shader() : _shaderProgramId( 0 )
{

}


Shader::Shader( const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath ) : _shaderProgramId( 0 )
{
	this->createShaderProgram( vertexShaderFilePath, fragmentShaderFilePath );
}


Shader::~Shader()
{
	glDeleteProgram( this->_shaderProgramId );
}


GLuint Shader::getShaderProgramId() const
{
	return this->_shaderProgramId;
}


void Shader::setBool( const std::string& name, bool value ) const
{
	glUniform1i( glGetUniformLocation( this->_shaderProgramId, name.c_str() ), ( GLint )value );
	return;
}


void Shader::setInt( const std::string& name, int value ) const
{
	glUniform1i( glGetUniformLocation( this->_shaderProgramId, name.c_str() ), ( GLint )value );
	return;
}


void Shader::setFloat( const std::string& name, float value ) const
{
	glUniform1f( glGetUniformLocation( this->_shaderProgramId, name.c_str() ), ( GLfloat )value );
	return;
}


void Shader::setVec2( const std::string& name, const glm::vec2& value ) const
{
	glUniform2fv( glGetUniformLocation( this->_shaderProgramId, name.c_str() ), 1, &value[0] );
}


void Shader::setVec2( const std::string& name, float x, float y ) const
{
	glUniform2f( glGetUniformLocation( this->_shaderProgramId, name.c_str() ), x, y );
}


void Shader::setVec3( const std::string& name, const glm::vec3& value ) const
{
	glUniform3fv( glGetUniformLocation( this->_shaderProgramId, name.c_str() ), 1, &value[0] );
}


void Shader::setVec3( const std::string& name, float x, float y, float z ) const
{
	glUniform3f( glGetUniformLocation( this->_shaderProgramId, name.c_str() ), x, y, z );
}


void Shader::setVec4( const std::string& name, const glm::vec4& value ) const
{
	glUniform4fv( glGetUniformLocation( this->_shaderProgramId, name.c_str() ), 1, &value[0] );
}


void Shader::setVec4( const std::string& name, float x, float y, float z, float w ) const
{
	glUniform4f( glGetUniformLocation( this->_shaderProgramId, name.c_str() ), x, y, z, w );
}


void Shader::setMat2( const std::string& name, const glm::mat2& mat ) const
{
	glUniformMatrix2fv( glGetUniformLocation( this->_shaderProgramId, name.c_str() ), 1, GL_FALSE, &mat[0][0] );
}


void Shader::setMat3( const std::string& name, const glm::mat3& mat ) const
{
	glUniformMatrix3fv( glGetUniformLocation( this->_shaderProgramId, name.c_str() ), 1, GL_FALSE, &mat[0][0] );
}


void Shader::setMat4( const std::string& name, const glm::mat4& mat ) const
{
	glUniformMatrix4fv( glGetUniformLocation( this->_shaderProgramId, name.c_str() ), 1, GL_FALSE, &mat[0][0] );
}


void Shader::setTextureUnit( const std::string& name, int value ) const
{
	glUniform1i( glGetUniformLocation( this->_shaderProgramId, name.c_str() ), ( GLint )value );
	return;
}


void Shader::createShaderProgram( const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath )
{
	// Load Shader Code
	std::string vertexShaderString = Shader::loadShaderSourceCode( vertexShaderFilePath.c_str() );
	const char* vertexShaderSourceCode = vertexShaderString.c_str();
	std::string fragmentShaderString = Shader::loadShaderSourceCode( fragmentShaderFilePath.c_str() );
	const char* fragmentShaderSourceCode = fragmentShaderString.c_str();

	// Create Vertex Shader
	GLuint vertexShaderId = Shader::createShaderObject( GL_VERTEX_SHADER, vertexShaderFilePath );

	// Compile FragmentShader
	GLuint fragmentShaderId = Shader::createShaderObject( GL_FRAGMENT_SHADER, fragmentShaderFilePath );

	// Create ShaderProgram
	this->_shaderProgramId = glCreateProgram();
	glAttachShader( this->_shaderProgramId, vertexShaderId );
	glAttachShader( this->_shaderProgramId, fragmentShaderId );
	glLinkProgram( this->_shaderProgramId );
	Shader::checkShaderError( this->_shaderProgramId, GL_LINK_STATUS );
	glValidateProgram( this->_shaderProgramId );
	Shader::checkShaderError( this->_shaderProgramId, GL_VALIDATE_STATUS );

	// Clean up and delete shader objects once linked into our program
	glUseProgram( this->_shaderProgramId );
	glDetachShader( this->_shaderProgramId, vertexShaderId );
	glDetachShader( this->_shaderProgramId, fragmentShaderId );
	glDeleteShader( vertexShaderId );
	glDeleteShader( fragmentShaderId );

	glUseProgram( 0 );

	std::cout << "CREATED SHADER PROGRAM " << this->_shaderProgramId << std::endl;
	return;
}


void Shader::use()
{
	glUseProgram( this->_shaderProgramId );
	return;
}


std::string Shader::loadShaderSourceCode( const char* filepath )
{
	// Pass a filename, return the source code of the file to dynamically compile during runtime
	// vertex and fragment shader glsl files
	std::string contents = "";

	std::ifstream shaderFile;

	shaderFile.exceptions( std::ifstream::failbit | std::ifstream::badbit );

	try
	{
		shaderFile.open( filepath );

		std::stringstream shaderContentBuffer;
		shaderContentBuffer << shaderFile.rdbuf();

		shaderFile.close();

		contents = shaderContentBuffer.str();

		if ( contents.size() == 0 ) std::cout << "ERROR::SHADER::NO_CONTENT\n" << filepath << std::endl;
	}
	catch ( const std::ifstream::failure& e )
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


GLuint Shader::createShaderObject( GLenum shaderType, const std::string& filePath )
{
	std::string shaderString = Shader::loadShaderSourceCode( filePath.c_str() );
	const char* shaderSourceCode = shaderString.c_str();

	GLuint shaderId = glCreateShader( shaderType );
	glShaderSource( shaderId, 1, &shaderSourceCode, NULL ); // attach the shader source to the shader object
	glCompileShader( shaderId ); // compile the shader
	Shader::checkShaderError( shaderId, GL_COMPILE_STATUS );

	return shaderId;
}