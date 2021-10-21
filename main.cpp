#define GLFW_INCLUDE_NONE

#include<iostream>
#include<GLFW/glfw3.h>
#include<glad/glad.h>
#include <cmath>

#include"shaderClass.h"
#include"VAO.h"
#include"VAO.h"
#include"EBO.h"

GLfloat vertices[] =
{
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
    -0.5f / 2,  0.5f * float(sqrt(3)) / 6, 0.0f,
    0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
    0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,
};

GLuint indices[] = 
{
    0, 3, 5,
    3, 2, 4,
    5, 4, 1 
};    


int main(){

    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGlTest", NULL, NULL);
    
    if (window == NULL)
    {
        std::cout << "Falied to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }        
    glfwMakeContextCurrent(window);

    gladLoadGL();

    glViewport(0,0,800,800);
    
   
    
    Shader shaderProgram("default.vert", "default.frag");

    VAO VAO1;
    VAO1.Bind();


    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));


    VAO1.LinkAttrib(VBO1, 0); 
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

   
    
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        shaderProgram.Activate();

        VAO1.Bind();


        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        glfwPollEvents();
    } 
   
    
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();


    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
