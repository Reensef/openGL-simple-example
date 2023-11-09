#include "camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
    Camera::width = width;
    Camera::height = height;
    Camera::position = position;
}

void Camera::matrix(float FOVdeg, float nearPlane, float farPlane,
                    Shader &shader, const char *uniform)
{
    // Инициализания матриц единицами
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    // Устанавливаем направление камеры
    view = glm::lookAt(position, position + orientation, up);
    // Устанавливаем перспективу
    projection = glm::perspective(glm::radians(FOVdeg), (float)(width / height),
                                  nearPlane, farPlane);

    // Передаем матрицу в шейдер
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE,
                       glm::value_ptr(projection * view));
}

void Camera::inputs(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        position += speed * orientation;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        position += speed * -glm::normalize(glm::cross(orientation, up));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        position += speed * -orientation;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        position += speed * glm::normalize(glm::cross(orientation, up));
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        position += speed * up;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        position += speed * -up;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        // Скрывем курсор
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if (firstClick)
        {
            firstClick = false;
            glfwSetCursorPos(window, (width / 2), (height / 2));
        }

        double mouseX;
        double mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        // Нормализуем координаты
        float rotX = sensitivity * (float)(mouseY - height / 2) / height;
        float rotY = sensitivity * (float)(mouseX - height / 2) / height;

        glm::vec3 newOrientation = glm::rotate(
            orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up)));

        // Запрещаем камере закидывать взгляд за 180
        if (!((glm::angle(newOrientation, up) <= glm::radians(5.0f)) || (glm::angle(newOrientation, -up) <= glm::radians(5.0f))))
        {
            orientation = newOrientation;
        }

        orientation = glm::rotate(orientation, glm::radians(-rotY), up);
        glfwSetCursorPos(window, (width / 2), (height / 2));
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }
}
