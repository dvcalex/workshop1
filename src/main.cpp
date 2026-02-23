#include "cube.hpp"
#include "shader.hpp"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
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
    constexpr int Width = 640;
    constexpr int Height = 480;
    GLFWwindow* window = glfwCreateWindow(Width, Height, "openglworkshop1", NULL, NULL);
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

    // load GL functions once we have a valid context
    if (!gladLoadGL(glfwGetProcAddress))
    {
        std::cout << "error with gladLoadGL()!" << std::endl;
        glfwTerminate();
        return 1;
    }
    std::cout << glGetString(GL_VERSION) << std::endl;

    glEnable(GL_DEPTH_TEST); // enable depth testing

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

    // element buffer object
    GLuint ebo = 0;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube::Indices), cube::Indices, GL_STATIC_DRAW);

    GLuint shaderProgram = shader::createProgram("res/shaders/cube.vert", "res/shaders/cube.frag");

    while (!glfwWindowShouldClose(window))
    {
        // clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // --- render here ---

        // bind shader program and vao
        glBindVertexArray(vao);
        glUseProgram(shaderProgram);

        // define transformation matrices
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 view = glm::lookAt(glm::vec3(0.f, 1.7f, 1.7f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), Width / (float)Height, 0.1f, 100.0f);

        glm::mat4 mvp = projection * view * model; // combine on cpu

        // send mvp to the shader
        GLint mvpLoc = glGetUniformLocation(shaderProgram, "u_mvp");
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

        glDrawElements(GL_TRIANGLES, cube::IndexCount, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window); // swap front and back buffers
        glfwPollEvents();        // poll for and process events
    }

    // cleanup
    glDeleteProgram(shaderProgram);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);
    glfwTerminate();
    return 0;
}
