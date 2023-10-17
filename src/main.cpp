#include <glad/glad.h> // glad должен включаться первым
#include <GLFW/glfw3.h>

#include <iostream>

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

    // Основной цикл программы
    while (!glfwWindowShouldClose(window))
    {
        // Указываем цвет фона
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Очищаем задний буфер и устанавливаем цвет фона
        glClear(GL_COLOR_BUFFER_BIT);
        // Меняем задний и передний буферы местами
        glfwSwapBuffers(window);
        // Запускаем все события, необходимые для работы GLFW
        glfwPollEvents();
    }

    // Удаляем окно
    glfwDestroyWindow(window);
    // Завершаем работу GLFW
    glfwTerminate();
    return 0;
}