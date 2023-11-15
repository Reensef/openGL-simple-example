#include <glad/glad.h> // glad должен включаться первым
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>

#include "EBO.h"
#include "VAO.h"
#include "VBO.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"

GLfloat vertices[] = {
    //     COORDINATES     /        COLORS      /   TexCoord  / Normals
    // Top back side
    0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.225f, 0.36f,
    -0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.225f, 0.36f,
    0.0f, 0.8f, 0.0f, 0.0f, 0.6f, 0.0f, 0.5f, 1.0f, 0.0f, 0.225f, 0.36f,

    // Top right side
    0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.36f, 0.225f, 0.0f,
    0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.36f, 0.225f, 0.0f,
    0.0f, 0.8f, 0.0f, 0.0f, 0.6f, 0.0f, 0.5f, 1.0f, 0.36f, 0.225f, 0.0f,

    // Top front side
    -0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.225f, -0.36f,
    0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.225f, -0.36f,
    0.0f, 0.8f, 0.0f, 0.0f, 0.6f, 0.0f, 0.5f, 1.0f, 0.0f, 0.225f, -0.36f,

    // Top left side
    -0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.36f, 0.225f, 0.0f,
    -0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -0.36f, 0.225f, 0.0f,
    0.0f, 0.8f, 0.0f, 0.0f, 0.6f, 0.0f, 0.5f, 1.0f, -0.36f, 0.225f, 0.0f,

    // Bottom back side
    -0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.225f, -0.36f,
    0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -0.225f, -0.36f,
    0.0f, -0.8f, 0.0f, 0.0f, 0.6f, 0.0f, 0.5f, 1.0f, 0.0f, -0.225f, -0.36f,

    // Bottom right side
    0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.36f, -0.225f, 0.0f,
    0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -0.36f, -0.225f, 0.0f,
    0.0f, -0.8f, 0.0f, 0.0f, 0.6f, 0.0f, 0.5f, 1.0f, -0.36f, -0.225f, 0.0f,

    // Bottom front side
    0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.255f, 0.36f,
    -0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -0.225f, 0.36f,
    0.0f, -0.8f, 0.0f, 0.0f, 0.6f, 0.0f, 0.5f, 1.0f, 0.0f, -0.225f, 0.36f,

    // Bottom left side
    -0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.36f, -0.225f, 0.0f,
    -0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, -0.36f, -0.225f, 0.0f,
    0.0f, -0.8f, 0.0f, 0.0f, 0.6f, 0.0f, 0.5f, 1.0f, -0.36f, -0.225f, 0.0f};

GLuint indexes[] = {
    0, 1, 2,     // Top back side
    3, 4, 5,     // Top right side
    6, 7, 8,     // Top front side
    9, 10, 11,   // Top left side
    12, 13, 14,  // Bottom right side
    15, 16, 17,  // Bottom front side
    18, 19, 20,  // Bottom front side
    21, 22, 23}; // Bottom left side

GLfloat lightVertices[] = {
    -0.1f, -0.1f, 0.1f,
    -0.1f, -0.1f, -0.1f,
    0.1f, -0.1f, -0.1f,
    0.1f, -0.1f, 0.1f,
    -0.1f, 0.1f, 0.1f,
    -0.1f, 0.1f, -0.1f,
    0.1f, 0.1f, -0.1f,
    0.1f, 0.1f, 0.1f};


GLuint lightIndexes[] = {
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7};

int windowWidth = 800;
int windowHeight = 800;

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
  GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, "Simple Window", NULL, NULL);
  // Проверяем, что окно было учспешено создано, иначе завершаем программу с
  // ошибкой
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
  glViewport(0, 0, windowWidth, windowHeight);

  Shader shaderProgram("src/shaders/default.vert", "src/shaders/default.frag");

  VAO VAO1;
  VAO1.bind();

  VBO VBO1(vertices, sizeof(vertices));
  EBO EBO1(indexes, sizeof(indexes));

  VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void *)0);
  VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void *)(3 * sizeof(float)));
  VAO1.linkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void *)(6 * sizeof(float)));
  VAO1.linkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void *)(8 * sizeof(float)));

  VAO1.unbind();
  VBO1.unbind();
  EBO1.unbind();

  Shader lightShader("src/shaders/light.vert", "src/shaders/light.frag");

  VAO lightVAO;
  lightVAO.bind();
  VBO lightVBO(lightVertices, sizeof(lightVertices));
  EBO lightEBO(lightIndexes, sizeof(lightIndexes));
  lightVAO.linkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void *)0);

  lightVAO.unbind();
  lightVBO.unbind();
  lightEBO.unbind();

  glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

  glm::vec3 lightPos = glm::vec3(1.f, 0.5f, 0.0f);
  glm::mat4 lightModel = glm::mat4(1.0f);
  lightModel = glm::translate(lightModel, lightPos);

  Texture grav_tex("C:\\Projects\\tpu-opengl-tutorial\\simple\\src\\textures\\gravel_base_"
                   "color.jpg",
                   GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);

  grav_tex.texUnit(shaderProgram, "tex0", 0);

  float rotation = 0.0f;
  float lightRotation = 0.0f;
  double prevTime = glfwGetTime();

  // Включение буфера глубины
  glEnable(GL_DEPTH_TEST);

  // Создание камеры
  Camera camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 2.0f));

  // Основной цикл программы
  while (!glfwWindowShouldClose(window))
  {
    // Указываем цвет фона
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    // Очищаем задний буфер и устанавливаем цвет фона
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Таймер для анимации
    double crntTime = glfwGetTime();
    if (crntTime - prevTime >= 0.05)
    {
      rotation += 2.0f;
      lightRotation = 2.0f;
      prevTime = crntTime;
    }

    // Включаем управление камеры
    camera.inputs(window);
    // Обвновление матриц проекции и вида
    camera.updateMatrix(45.0f, 0.1f, 100.0f);

    lightShader.activate();

    glUniformMatrix4fv(
        glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(
        glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

    camera.matrix(lightShader, "cameraMatrix");
    lightVAO.bind();
    glDrawElements(GL_TRIANGLES, sizeof(lightIndexes) / sizeof(int), GL_UNSIGNED_INT, 0);

    // Активируем программу шейдер
    shaderProgram.activate();
    // Привязка матриц к вводу шейдера
    camera.matrix(shaderProgram, "cameraMatrix");

    // Создадим матрицу модели, содержащей единицы
    glm::mat4 model = glm::mat4(1.0f);
    // Повернем фигуру
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    // Выводим матрицы в вершинный шейдер
    int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    lightPos = glm::rotate(lightPos, glm::radians(lightRotation), glm::vec3(0.0f, 1.0f, 0.0f));
    lightRotation = 0;
    glUniform4f(
        glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(
        glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.position.x, camera.position.y, camera.position.z);

    // Скажем OpenGL использовать текстуру
    grav_tex.bind();
    // Скажем OpenGL использовать VBO
    VAO1.bind();
    // Скажем OpenGL нарисовать фигуру
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