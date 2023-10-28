#include <glad/glad.h> // glad должен включаться первым
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shader.h"
#include "texture.h"

GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f, -0.5f,     0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
	-0.5f, 0.0f,  0.5f,     0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.0f, 0.0f, 0.0f,	1.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.0f, 0.0f, 0.0f,	0.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.0f, 0.6f, 0.0f,	0.5f, 1.0f,
	 0.0f, -0.8f,  0.0f,     0.0f, 0.6f, 0.0f,	0.5f, 1.0f,
};

GLuint indexes[] = {
    4,0,1,
    4,1,2,
    4,2,3,
    4,3,0,
    5,0,1,
    5,1,2,
    5,2,3,
    5,3,0,};

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

	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);
    
    // Основной цикл программы
    while (!glfwWindowShouldClose(window))
    {
        // Указываем цвет фона
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Очищаем задний буфер и устанавливаем цвет фона
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Активируем программу шейдер
        shaderProgram.activate();

        // Таймер для анимации
		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 0.05)
		{
			rotation += 2.0f;
			prevTime = crntTime;
		}

        // Создадим матрицу модели, содержащей единицы
        glm::mat4 model = glm::mat4(1.0f);
        // Создадим матрицу вида, содержащей единицы
        glm::mat4 view = glm::mat4(1.0f);
        // Создадим матрицу проекции, содержащей единицы
        glm::mat4 proj = glm::mat4(1.0f);

        // Повернем фигуру на 45 градусов
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        // Отодвинем фигуру от нас
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        // Скажем не обрезать фигуру,
        // если она находиться от нас от 0.1 до 100.0
		proj = glm::perspective(glm::radians(45.0f), (float)800 / 800, 0.1f, 100.0f);

        // Выводим матрицы в вершинный шейдер
		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

        // Скажем OpenGL использовать текстуру
        grav_tex.bind();
        // Скажем OpenGL использовать VBO
        VAO1.bind();
        // Скажем OpenGL нарисовать фигуру с 4 вершинами
        glDrawElements(GL_TRIANGLES, sizeof(indexes) / sizeof(int), GL_UNSIGNED_INT, 0);
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