#include <glad/glad.h> // glad должен включаться первым
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <iostream>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shader.h"
#include "texture.h"

GLfloat vertices[] = {
    //             COORDINATE     /         COLORS      / TEXTURE COORDINATE
    -0.5f, 0.5f, 0.0f, 0.0f, 128 / 255.0f, 255 / 255.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.0f, 255 / 255.0f, 0 / 255.0f, 0 / 255.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.0f, 0 / 255.0f, 153 / 255.0f, 0 / 255.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, 0.0f, 255 / 255.0f, 255 / 255.0f, 51 / 255.0f, 1.0f, 0.0f};

GLuint indexes[] = {
    0, 1, 2, 3};

int main()
{
    // Инициализируем GLFW
    glfwInit();

    // Устанавливаем мажорную и минорную версию GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Говорит GLFW использовать основной профиль
    // Таким образом мы будем иметь только современные функции
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Создаем окно размером 800x800 и назвывем его Simple Window
    GLFWwindow *window = glfwCreateWindow(800, 800, "Simple Window", NULL, NULL);
    // Проверяем, что окно было учспешено создано, иначе завершаем программу с ошибкой
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Устанавливаем окно как текущий контекст потока
    glfwMakeContextCurrent(window);

    // Запускаем OpenGL
    gladLoadGL();

    // Устанавливаем сцену
    // В этом случае сцена начинается с координат 0,0 и имеет размер 800x800
    glViewport(0, 0, 800, 800);

    Shader shaderProgram("src/shaders/default.vert", "src/shaders/default.frag");

    VAO VAO1;
    VAO1.bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indexes, sizeof(indexes));

    VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);
    VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    VAO1.linkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    VAO1.unbind();
    VBO1.unbind();
    EBO1.unbind();

    Texture grav_tex("C:\\Projects\\tpu-opengl-tutorial\\simple\\src\\textures\\gravel_base_color.jpg",
                     GL_TEXTURE_2D,
                     GL_TEXTURE0,
                     GL_RGB,
                     GL_UNSIGNED_BYTE);

    grav_tex.texUnit(shaderProgram, "tex0", 0);

    // Основной цикл программы
    while (!glfwWindowShouldClose(window))
    {
        // Указываем цвет фона
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Очищаем задний буфер и устанавливаем цвет фона
        glClear(GL_COLOR_BUFFER_BIT);
        // Активируем программу шейдер
        shaderProgram.activate();
        // Скажем OpenGL использовать текстуру
        grav_tex.bind();
        // Скажем OpenGL использовать VBO
        VAO1.bind();
        // Скажем OpenGL нарисовать фигуру с 4 вершинами
        glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, 0);
        // Меняем задний и передний буферы местами
        glfwSwapBuffers(window);
        // Запускаем все события, необходимые для работы GLFW
        glfwPollEvents();
    }

    grav_tex.remove();
    // Удаляем окно
    glfwDestroyWindow(window);
    // Завершаем работу GLFW
    glfwTerminate();
    return 0;
}