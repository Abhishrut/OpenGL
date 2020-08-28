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
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"imgui/imgui_impl_glfw.h"
#include"imgui/imgui_impl_opengl3.h"
#include"tests/TestClearColor.h"

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
	window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
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
		-50.f,-50.f, 0.0f, 0.0f,//0 botton left
		 50.f,-50.f, 1.0f, 0.0f,//1 bottom right
		 50.f, 50.f, 1.0f, 1.0f,//2 top right
		-50.f, 50.f, 0.0f, 1.0f //3 top left
	};

	unsigned int indices[] = {
		0,1,2,
		0,2,3
	};
	
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	Renderer renderer;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init((char *)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

	test::TestClearColor test;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{	//we are doing this every frame
		/* Render here */
		renderer.Clear();
		
		test.OnUpdate(0.0f);
		test.OnRender();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
 		
		test.OnImGuiRender();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();

	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}
