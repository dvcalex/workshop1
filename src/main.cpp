#include "cube.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main()
{
    if (!glfwInit())
    {
        std::cout << "error with glfwInit()!" << std::endl;
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create a window and its opengl context
    GLFWwindow* window = glfwCreateWindow(640, 480, "openglworkshop1", NULL, NULL);
    if (!window)
    {
        std::cout << "error with glfwCreateWindow()!" << std::endl;
        glfwTerminate();
        return 1;
    }

    // make the window's context current
    glfwMakeContextCurrent(window);

    // not necessary, but caps the framerate to the monitor refresh rate
    glfwSwapInterval(1);

    // can only init glew once we have a valid context
    if (glewInit() != GLEW_OK)
    {
        std::cout << "error with glewInit()!" << std::endl;
        glfwTerminate();
        return 1;
    }
    std::cout << glGetString(GL_VERSION) << std::endl;

    // vertex buffer object
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);                                                                 // generate
    glBindBuffer(GL_ARRAY_BUFFER, vbo);                                                    // bind so we can use
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube::Vertices), cube::Vertices, GL_STATIC_DRAW); // fill with data

    // vertex array object
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // set up vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // for safety
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // position
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // texcoord

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT); // clear the screen

        // --- render here ---

        glfwSwapBuffers(window); // swap front and back buffers

        glfwPollEvents(); // poll for and process events
    }

    // cleanup
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glfwTerminate();
    return 0;
}
