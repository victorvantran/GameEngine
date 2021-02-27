#ifndef TINKER_GAME_H
#define TINKER_GAME_H


#include <cmath>
#include "Game.h"
#include "Shader.h"
#include "Mesh.h"
#include "TestMesh.h"
#include "BasicMesh.h"
#include "Texture.h"

class TinkerGame : public Game
{
private:
	Shader _lightingShader;
	Shader _lightSourceShader;
	BasicMesh _basicMesh;
	Texture _texture0;
	Texture _texture1;




public:
	TinkerGame() : 
		Game(), 
		_lightingShader(),
		_lightSourceShader(),
		_basicMesh(),
		_texture0(), _texture1() {}
	TinkerGame( std::uint16_t windowWidth, std::uint16_t windowHeight, std::string windowTitle ) :
		Game( windowWidth, windowHeight, windowTitle ), 
		_lightingShader(),
		_lightSourceShader(),
		_basicMesh(),
		_texture0(), _texture1() {}
	~TinkerGame() {}


	void initialize()
	{

	}


	void loadContent()
	{
		// Load Textures
		//this->_texture0.load( "assets/textures/aperture_science_cube.png" );
		//this->_texture0.load( "assets/textures/dewey_finn.jpg" );
		this->_texture0.load( "assets/textures/wooden_crate.png" );
		this->_texture1.load( "assets/textures/crate_specular_borders.png" );


		// Load Shader
		this->_lightSourceShader.load( "assets/shaders/basic_vertex_shader.glsl", "assets/shaders/lightsource_fragment_shader.glsl" );

		
		this->_lightingShader.load( "assets/shaders/basic_vertex_shader.glsl", "assets/shaders/basic_fragment_shader.glsl" );
		this->_lightingShader.use();
		this->_lightingShader.setInt( "material.diffuse", 0 );
		this->_lightingShader.setInt( "material.specular", 1 );


		// Load Meshes
		/*
		Vertex vertices[] =
		{
			Vertex( glm::vec3( -0.5f,	0.5f,	0.0f ), glm::vec4( 1.0f,	0.0f,	0.0f,	1.0f ), glm::vec2( 0.0f, 1.0f ) ),
			Vertex( glm::vec3( -0.5f,	-0.5f,	0.0f ), glm::vec4( 0.0f,	1.0f,	0.0f,	1.0f ), glm::vec2( 0.0f, 0.0f ) ),
			Vertex( glm::vec3( 0.5f,	-0.5f,	0.0f ), glm::vec4( 0.0f,	0.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 0.0f ) ),
			Vertex( glm::vec3( 0.5f,	0.5f,	0.0f ), glm::vec4( 1.0f,	1.0f,	0.0f,	1.0f ), glm::vec2( 1.0f, 1.0f ) )
		};
		*/

		// Cube
		/*
		Vertex vertices[] =
		{
			Vertex( glm::vec3( -0.5f, -0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 0.0f ) ),
			Vertex( glm::vec3( 0.5f, -0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 0.0f ) ),
			Vertex( glm::vec3( 0.5f,  0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 1.0f ) ),
			Vertex( glm::vec3( 0.5f,  0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 1.0f ) ),
			Vertex( glm::vec3( -0.5f,  0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 1.0f ) ),
			Vertex( glm::vec3( -0.5f, -0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 0.0f ) ),

			Vertex( glm::vec3( -0.5f, -0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 0.0f ) ),
			Vertex( glm::vec3( 0.5f, -0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 0.0f ) ),
			Vertex( glm::vec3( 0.5f,  0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 1.0f ) ),
			Vertex( glm::vec3( 0.5f,  0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 1.0f ) ),
			Vertex( glm::vec3( -0.5f,  0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 1.0f ) ),
			Vertex( glm::vec3( -0.5f, -0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 0.0f ) ),

			Vertex( glm::vec3( -0.5f,  0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 0.0f ) ),
			Vertex( glm::vec3( -0.5f,  0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 1.0f ) ),
			Vertex( glm::vec3( -0.5f, -0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 1.0f ) ),
			Vertex( glm::vec3( -0.5f, -0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 1.0f ) ),
			Vertex( glm::vec3( -0.5f, -0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 0.0f ) ),
			Vertex( glm::vec3( -0.5f,  0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 0.0f ) ),

			Vertex( glm::vec3( 0.5f,  0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 0.0f ) ),
			Vertex( glm::vec3( 0.5f,  0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 1.0f ) ),
			Vertex( glm::vec3( 0.5f, -0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 1.0f ) ),
			Vertex( glm::vec3( 0.5f, -0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 1.0f ) ),
			Vertex( glm::vec3( 0.5f, -0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 0.0f ) ),
			Vertex( glm::vec3( 0.5f,  0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 0.0f ) ),

			Vertex( glm::vec3( -0.5f, -0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 1.0f ) ),
			Vertex( glm::vec3( 0.5f, -0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 1.0f ) ),
			Vertex( glm::vec3( 0.5f, -0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 0.0f ) ),
			Vertex( glm::vec3( 0.5f, -0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 0.0f ) ),
			Vertex( glm::vec3( -0.5f, -0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 0.0f ) ),
			Vertex( glm::vec3( -0.5f, -0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 1.0f ) ),

			Vertex( glm::vec3( -0.5f,  0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 1.0f ) ),
			Vertex( glm::vec3( 0.5f,  0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 1.0f ) ),
			Vertex( glm::vec3( 0.5f,  0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 0.0f ) ),
			Vertex( glm::vec3( 0.5f,  0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 1.0f, 0.0f ) ),
			Vertex( glm::vec3( -0.5f,  0.5f,  0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 0.0f ) ),
			Vertex( glm::vec3( -0.5f,  0.5f, -0.5f ), glm::vec4( 1.0f,	1.0f,	1.0f,	1.0f ), glm::vec2( 0.0f, 1.0f ) ),
		};


		std::uint32_t indices[] =
		{
			0, 1, 2, 3, 4, 5,
			6, 7, 8, 9, 10, 11,
			12, 13, 14, 15, 16, 17,
			18, 19, 20, 21, 22, 23,
			24, 25, 26, 27, 28, 29,
			30, 31, 32, 33, 34, 35
		};

		this->_cubeMesh.loadPrimitives(
			vertices, 6,
			sizeof( vertices ) / ( sizeof( vertices[0] * 6 ) ),
			indices, sizeof( indices ) / sizeof( indices[0] )
		);

		*/


		float vertices[] = {
			
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,	0.0f, 0.0f,
		
			
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,	0.0f, 0.0f,
			

			
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,	1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,	0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,	1.0f, 0.0f,


			
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,	1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,	0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,	0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,	1.0f, 0.0f,
			 

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,	0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,	1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,	1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,	1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,	0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,	0.0f, 1.0f,


			
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,	0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,	1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,	1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,	1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,	0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,	0.0f, 1.0f,
			
			
			
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,	0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,	1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,	1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f, 0.0f,	1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f, 0.0f,	0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f, 0.0f,	0.0f, 1.0f,
		};

		std::uint32_t indices[] =
		{
			0, 1, 2, 3, 4, 5,
			6, 7, 8, 9, 10, 11,
			12, 13, 14, 15, 16, 17,
			18, 19, 20, 21, 22, 23,
			24, 25, 26, 27, 28, 29,
			30, 31, 32, 33, 34, 35
		};

		this->_basicMesh.loadPrimitives(
			vertices, 8,
			sizeof( vertices ) / ( sizeof( vertices[0] ) * 8 ),
			indices, sizeof( indices ) / sizeof( indices[0] )
		);




		return;
	}


	void update()
	{
		this->processInput( this->_renderManager.getWindow() );

		return;
	}


	void render()
	{
		// Clear the colorbuffer
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		// World Environment
		glm::vec3 cubeWorldPositions[] =
		{
			glm::vec3( 0.0f,  0.0f,  0.0f ),
			glm::vec3( 2.0f,  5.0f, -5.0f ),
			glm::vec3( -1.5f, -2.2f, -2.5f ),
			glm::vec3( -3.8f, -2.0f, -12.3f ),
			glm::vec3( 2.4f, -0.4f, -3.5f ),
			glm::vec3( -1.7f,  3.0f, -7.5f ),
			glm::vec3( 1.3f, -2.0f, -2.5f ),
			glm::vec3( 1.5f,  2.0f, -2.5f ),
			glm::vec3( 1.5f,  0.2f, -1.5f ),
			glm::vec3( -1.3f,  1.0f, -1.5f )
		};

		glm::mat4 projection = glm::perspective( glm::radians( this->_camera._zoom ), ( float )this->_windowWidth / ( float )this->_windowHeight, 0.1f, 100.0f );
		glm::mat4 view = this->_camera.getViewMatrix();


		// Caclulate light source color
		/*
		glm::vec3 lightColor;
		lightColor.x = sin( glfwGetTime() * 1.0f );
		lightColor.y = sin( glfwGetTime() * 0.2f );
		lightColor.z = sin( glfwGetTime() * 0.3f );
		*/
		glm::vec3 lightColor = glm::vec3( 1.0f );






		// Draw Light Source
		this->_lightSourceShader.use();
		this->_lightSourceShader.setMat4( "projection", projection );
		this->_lightSourceShader.setMat4( "view", view );
		glm::vec3 lightSourcePos = glm::vec3( 1.2f, 1.0f, 2.0f );
		glm::mat4 lightSourceModel = glm::mat4( 1.0f );
		lightSourceModel = glm::translate( lightSourceModel, lightSourcePos );
		lightSourceModel = glm::scale( lightSourceModel, glm::vec3( 0.2f ) );
		this->_lightSourceShader.setMat4( "model", lightSourceModel );


		this->_lightSourceShader.setVec3( "lightColor", lightColor );

		this->_basicMesh.draw();


		// Draw Cubes
		for ( int i = 0; i < 10; i++ )
		{
			this->_lightingShader.use();

			// World Properties
			this->_lightingShader.setMat4( "projection", projection );
			this->_lightingShader.setMat4( "view", view );
			//glm::vec3 cubePos = glm::vec3( 0.0f, 0.0f, 0.0f );
			glm::vec3 cubePos = glm::vec3( 
				cubeWorldPositions[i].x + (  ( i % 2 == 0 ) ? 1 : - 1 ) * std::cosf( glfwGetTime() ) * 5.0f,
				cubeWorldPositions[i].y,
				cubeWorldPositions[i].z + ( ( i % 2 == 0 ) ? 1 : -1 ) * std::sinf( glfwGetTime() ) * 5.0f 
			);
			glm::mat4 cubeModel = glm::mat4( 1.0f );
			//cubeModel = glm::translate( cubeModel, cubePos );
			//cubeModel = glm::rotate( cubeModel, glm::radians( 360.0f * -std::sinf( glfwGetTime() ) ), glm::vec3( 1.0f, 0.3f, -0.4f ) );
			this->_lightingShader.setMat4( "model", cubeModel );


			// Light Properties
			this->_lightingShader.setVec3( "lightPos", lightSourcePos ); // Light will be coming from light source origin position
			glm::vec3 diffuseColor = lightColor * glm::vec3( 0.8f );
			glm::vec3 ambientColor = diffuseColor * glm::vec3( 0.05f );
			this->_lightingShader.setVec3( "light.ambient", ambientColor );
			this->_lightingShader.setVec3( "light.diffuse", diffuseColor );
			this->_lightingShader.setVec3( "light.specular", glm::vec3( 1.0f ) );


			// Material Properties
			// Calculate norm matrix to account for non-uniform scaling and rotation
			glm::mat3 normMatrix = glm::mat3( glm::transpose( glm::inverse( cubeModel ) ) );
			this->_lightingShader.setMat3( "normMatrix", normMatrix );
			this->_lightingShader.setVec3( "material.specular", glm::vec3( 0.5f ) );
			this->_lightingShader.setFloat( "material.shininess", 64.0f );


			// Bind texture
			this->_texture0.bind( 0 );
			this->_texture1.bind( 1 );

			// Draw
			this->_basicMesh.draw();
		}
		


		

		// Swap Buffers
		glfwSwapBuffers( this->_renderManager.getWindow() );

		return;
	}
};


#endif