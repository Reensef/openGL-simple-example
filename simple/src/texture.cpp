#include "texture.h"

Texture::Texture(const char *image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
    // Присваиваем тип текстуры объекту texture
    type = texType;

    // Сохраняем ширину, высоту и количество цветовых каналов изображения
    int widthImg, heightImg, numColCh;
    // Переворачивает изображение так, чтобы оно отображалось правой стороной вверх
    // Это необходимо так как stb и OpenGL имеет разную систему координат для текстур
    stbi_set_flip_vertically_on_load(true);
    // Считываем изображение из файла и сохраняем его в байтах
    unsigned char *bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

    // Генерируем текстурный объект OpenGL
    glGenTextures(1, &ID);
    // Присваиваем текстуру текстурному элементу
    glActiveTexture(slot);
    glBindTexture(texType, ID);

    // Настраиваем тип алгоритма, который используется для уменьшения или увеличения изображения
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Настраиваем способ повторения текстуры (если это вообще происходит)
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Присваиваем изображение объекту текстуры OpenGL
    glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
    // Генерируем MipMaps
    glGenerateMipmap(texType);

    // Удаляем данные изображения в том виде, в каком они уже есть в объекте текстуры OpenGL
    stbi_image_free(bytes);

    // Отменяет привязку объекта текстуры OpenGL, чтобы его нельзя было случайно изменить
    glBindTexture(texType, 0);
}

void Texture::texUnit(Shader &shader, const char *uniform, GLuint unit)
{
    // Получаем местоположение униформы
    GLuint texUni = glGetUniformLocation(shader.ID, uniform);
    // Шейдер необходимо активировать перед изменением значения униформы
    shader.activate();
    // Устанавливаем значение униформы
    glUniform1i(texUni, unit);
}

void Texture::bind()
{
    glBindTexture(type, ID);
}

void Texture::unbind()
{
    glBindTexture(type, 0);
}

void Texture::remove()
{
    glDeleteTextures(1, &ID);
}