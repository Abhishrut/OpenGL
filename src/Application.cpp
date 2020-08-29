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
#include"tests/TestTexture2D.h"


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

		test::Test* currentTest=nullptr;
		test::TestMenu* testMenu = new test::TestMenu(currentTest);
		currentTest = testMenu;
	
		testMenu->RegisterTest<test::TestClearColor>("Clear Color");
		testMenu->RegisterTest<test::TestTexture2D>("2D Texture");

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{	//we are doing this every frame
			/* Render here */
			GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			renderer.Clear();
		
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
 		
			if (currentTest) 
			{
				currentTest->OnUpdate(0.0f);
				currentTest->OnRender();
				ImGui::Begin("Test");
				if (currentTest != testMenu && ImGui::Button("<-"))
				{
					delete currentTest;
					currentTest = testMenu;
				}
				currentTest->OnImGuiRender();
				ImGui::End();
			}
		
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
		delete currentTest;
		if (currentTest != testMenu)
			delete testMenu;
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();

	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}
