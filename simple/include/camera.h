#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/rotate_vector.hpp>
#include <gtx/vector_angle.hpp>

#include "shader.h"

class Camera
{
public:
    // позиция камеры
    glm::vec3 position;
    // направление камеры
    glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    // наклон камеры
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 cameraMatrix = glm::mat4(1.0f);

    // переменная для предотвращения рывков камеры
    bool firstClick = true;
    // параметры окна
    int width;
    int height;
    // скорость движения камеры
    float speed = 0.001f;
    // чувствительность поворота
    float sensitivity = 100.0f;

    Camera(int width, int height, glm::vec3 position);

    /*!
        \brief Функция создает и отправляет матрицы вида и проекции в шейдер
        \param shader - шейдер
        \param uniform - униформа
    */
    void matrix(Shader &shader, const char *uniform);

    /*!
        \brief Функция для обновления матриц
        \param FOVdeg - поле зрения камеры
        \param nearPlane - минимальная дистанция для отрисовки
        \param farPlane - максимальная дистанция для отрисовки
    */
    void updateMatrix(float FOVdeg, float nearPlane, float farPlane);

    /*!
        \brief Функция для обработки входных данных
        \param window - указатель на окно, в котором будет работать камера
    */
    void inputs(GLFWwindow *window);
};

#endif // CAMERA_CLASS_H