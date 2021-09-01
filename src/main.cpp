// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#define STB_IMAGE_IMPLEMENTATION
 
#include <pch.h>

#include "glinit.h"
#include "class/Window.h"
#include "class/shader.h"
#include "class/VertexBuffer.h"
#include "class/IndexBuffer.h"
#include "class/VertexArray.h"
#include "class/Mesh.h"
#include "class/Camera.h"
#include "class/Texture.h"
#include "class/Light.h"
#include "class/Material.h"
#include "class/AmbientLight.h"
#include "class/DirectionalLight.h"
#include "class/Time.h"

constexpr int MAX_POINT_LIGHT = 3;

// Window dimension
constexpr GLint WIDTH = 800, HEIGHT = 600;
const char* TITLE = "OPENGL";

// Vertex array and the mesh to render
std::vector<Mesh*> MeshList;

std::unique_ptr<VertexArray> vao;

/// Calculates  normals of objects of Triangle primitive
void CalculateNormal(GLfloat* vertices, GLuint* indices,
	unsigned int vertCount, unsigned int indicesCount, unsigned int vertexLength, unsigned int normalOffset);

void CreateTriangle();
void CreatePlane();

int main()
{
	// THIS MUST TAKE PLACE BEFORE WINDOW CREATION AND GLEW INITIALIZATION
	if (!GlfwInit())
		return -1;

	Window window(WIDTH, HEIGHT, "OpenGL");
	// THIS MUST TAKE PLACE AFTER WINDOW CREATION
	if (!GlewInit())
		return -1;

	window.SetInterval(1);

	glm::mat4 model(1.0f);

	// Code here

	Shader shader("/home/seyan/dev/cpp/gldemo/assets/shaders/vert.shader", "/home/seyan/dev/cpp/gldemo/assets/shaders/frag.shader");

	glm::mat4 proj = glm::perspective(45.f, window.GetBufferWidth() / window.GetBufferHeight(), 0.1f, 100.f);
	shader.SetProjMatrix(proj);

	vao = std::make_unique<VertexArray>();
	vao->Bind();

	CreatePlane();
	CreateTriangle();

	// light
	glm::vec3 Color(1.f, 1.f, 1.f);
	glm::vec3 Direction(0.f, -1.f, -2.f);
	Direction = glm::normalize(Direction);

	AmbientLight ambient(Color, .1f);
	DirectionalLight diffuse(Color, Direction, 0.7f);


	Material glossy(1.f, 32.f);
	Material notGlossy(.2f, 4.f);

	Camera camera(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f), 0.f, 270.f, 5.f, .2f);

	shader.Bind();
	ambient.Bind(shader);
	diffuse.Bind(shader);

	glm::mat4 model2(1.0f);

	Texture texture("/home/seyan/dev/cpp/gldemo/assets/textures/brick.png");
	Texture texture2("/home/seyan/dev/cpp/gldemo/assets/textures/dirt.png");

	texture.Bind(0);
	texture2.Bind(1);

	// Main Loop
	vao->Bind();
	while (!window.WindowShouldClose())
	{
		// User input handling
		glfwPollEvents();
		Time::Update();
		camera.KeyPressUpdate(window.GetKeys(), Time::GetDeltaTime());
		camera.MouseMoveUpdate(window.GetxOffset(), window.GetyOffset());
		shader.SetViewMatrix(camera.CalculateViewMatrix());
		shader.SetUniform3fv("u_CameraPos", camera.GetPosition());

		// Clear screen
		window.ClearColor(.1f, .1f, .1f, .3f);
		window.Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// fps counter
		std::cout << std::fixed << std::setprecision(2)
		 		  << (1 / Time::GetDeltaTime()) 
				  << "fps" << std::endl;

		// Plane
		{
			shader.SetUniform1i("u_textureId", 1);

			model = glm::mat4(1.f);
			model = glm::translate(model, glm::vec3(0.f, -2.f, 0.f));
			//model = glm::rotate(model, glm::radians(45), glm::vec3(0.f, 1.f, 0.f));
			//model = glm::scale(model, glm::vec3(1.f, 1.f, 1.0f));
			shader.SetModelMatrix(model);

			MeshList[0]->RenderMesh(shader);

			shader.SetUniform1f("u_SpecularIntensity", notGlossy.GetSpecularIntensity());
			shader.SetUniform1f("u_SpecularExponent", notGlossy.GetSpecularExponent());
		}

		// Pyramid
		{
			shader.SetUniform1i("u_textureId", 0);

			model2 = glm::mat4(1.f);
			model2 = glm::translate(model2, glm::vec3(1.5f, 0.f, -5.5f));
			model2 = glm::rotate(model2, glm::radians(45.f), glm::vec3(0.f, 1.f, 0.f));
			model2 = glm::scale(model2, glm::vec3(1.f, 1.f, 1.0f));
			shader.SetModelMatrix(model2);

			MeshList[1]->RenderMesh(shader);

			shader.SetUniform1f("u_SpecularIntensity", notGlossy.GetSpecularIntensity());
			shader.SetUniform1f("u_SpecularExponent", notGlossy.GetSpecularExponent());
		}

		window.SwapBuffers();
	}

	glfwTerminate();

	return 0;
}

void CalculateNormal(GLfloat* vertices, GLuint* indices,
	unsigned int vertCount, unsigned int indicesCount, unsigned int vertexLength, unsigned int normalOffset)
{
	for (unsigned int i = 0; i < indicesCount; i += 3)
	{
		unsigned int ind0 = indices[i] * vertexLength;
		unsigned int ind1 = indices[i + 1] * vertexLength;
		unsigned int ind2 = indices[i + 2] * vertexLength;

		glm::vec3 line0(vertices[ind1] - vertices[ind0],
			vertices[ind1 + 1] - vertices[ind0 + 1],
			vertices[ind1 + 2] - vertices[ind0 + 2]
		);
		glm::vec3 line1(vertices[ind2] - vertices[ind0],
			vertices[ind2 + 1] - vertices[ind0 + 1],
			vertices[ind2 + 2] - vertices[ind0 + 2]
		);
		glm::vec3 normal = glm::cross(line0, line1);
		normal = glm::normalize(normal);
		ind0 += normalOffset; ind1 += normalOffset; ind2 += normalOffset;

		vertices[ind0] += normal.x; vertices[ind0 + 1] += normal.y; vertices[ind0 + 2] += normal.z;
		vertices[ind1] += normal.x; vertices[ind1 + 1] += normal.y; vertices[ind1 + 2] += normal.z;
		vertices[ind2] += normal.x; vertices[ind2 + 1] += normal.y; vertices[ind2 + 2] += normal.z;
	}

	for (unsigned int i = 0; i < vertCount / vertexLength; i++)
	{
		unsigned int ind0 = i * vertexLength + normalOffset;
		glm::vec3 normal(vertices[ind0], vertices[ind0 + 1], vertices[ind0 + 2]);
		normal = normalize(normal);
		vertices[ind0] = normal.x; vertices[ind0 + 1] = normal.y; vertices[ind0 + 2] = normal.z;
	}
}

void CreatePlane()
{
	std::vector<GLfloat> vertices = {
		//   x		y	   z		 u		v
			-10.f,  0.f, -10.f,		 0.f,  0.f,		0.f, -1.f, 0.f,
			 10.f,  0.f, -10.f,		10.f,  0.f,		0.f, -1.f, 0.f,
			-10.f,  0.f,  10.f,		 0.f, 10.f,		0.f, -1.f, 0.f,
			 10.f,  0.f,  10.f,		10.f, 10.f,		0.f, -1.f, 0.f
	};

	std::vector<GLuint> indices = {
		0, 2, 1,
		1, 2, 3
	};

	//CalculateNormal(vertices, Indices, 32, 6, 8, 5);

	Mesh* mesh2 = new Mesh(vertices, indices);
	MeshList.push_back(mesh2);
}

void CreateTriangle()
{
	std::vector<GLfloat> vertices = {
		//   x		y	   z		 u		v
			-1.0f, -1.0f, -0.6f,	 0.0f, 0.0f,	 0.0f,	0.0f,  0.0f,	// 0 - bottom left corner
			 0.0f, -1.0f,  1.0f,	 0.5f, 0.0f,	 0.0f,	0.0f,  0.0f,		// 3 - back bottom mid point
			 1.0f, -1.0f, -0.6f,	 1.0f, 0.0f,	 0.0f,  0.0f,  0.0f,	// 1 - bottom right corner
			 0.0f,  1.0f,  0.0f,	 0.5f, 1.0f,	 0.0f,	0.0f,  0.0f		// 2 - top mid point
	};

	std::vector<GLuint> indices = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	CalculateNormal(vertices.data(), indices.data(), 32, 12, 8, 5);

	Mesh* mesh = new Mesh(vertices, indices);
	MeshList.push_back(mesh);
}