#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#include"Renderer.h"

#include"VertexBuffer.h"
#include"VertexBufferLayout.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"Shader.h"
#include"Texture.h"

int main(void)
{
	{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/*Changing OpenGL mode from compatiblility to Core Mode*/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4); //version Major.minor version 3.3 //not working for me :(
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	//glfwSwapInterval(1);   //make the refresh rate = refresh rate of the monitor OR sync with a V sync in my case this is a default 


	if (glewInit() != GLEW_OK) {
		std::cout << "Error" << std::endl;
	}
	std::cout << glGetString(GL_VERSION) << std::endl;

	float positions[] = {
		-0.5f,-0.5f, 0.0f, 0.0f,//0 botton left
		 0.5f,-0.5f, 1.0f, 0.0f,//1 bottom right
		 0.5f, 0.5f, 1.0f, 1.0f,//2 top right
		-0.5f, 0.5f, 0.0f, 1.0f //3 top left
	};

	unsigned int indices[] = {
		0,1,2,
		0,2,3
	};
	
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	VertexArray va;
	VertexBuffer vb(positions, 4 * 4 * sizeof(float));
	
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);
	
	IndexBuffer ib(indices, 6);

	Shader shader("res/shader/Basic.shader");
	shader.Bind();
	shader.SetUniform4f("u_Color", 0.08f, 0.03f, 0.08f, 1.0f);

	Texture texture("res/textures/logo.png");
	texture.Bind();
	shader.SetUniform1i("u_Texture", 0);
	
	va.UnBind();
	vb.UnBind();
	ib.UnBind();
	shader.UnBind();

	Renderer renderer;

	float r = 0.0f;
	float increment = 0.05f;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{	//we are doing this every frame
		/* Render here */
		
		//code down
		shader.Bind();
		shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
		
		renderer.Draw(va, ib, shader);

		if (r > 1.0f)
		{
			increment = -0.05f;
		}
		else if (r < 0.0f)
		{
			increment = 0.05f;
		}
		r += increment;

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	
	}
	glfwTerminate();
	return 0;
}
