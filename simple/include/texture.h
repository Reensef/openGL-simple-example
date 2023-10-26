#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include <stb_image.h>

#include "shader.h"

class Texture
{
public:
    GLuint ID;
    GLenum type;
    Texture(const char *image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

    // Присваивает текстуре единицу текстуры
    void texUnit(Shader &shader, const char *uniform, GLuint unit);
    // Связывает текстуру
    void bind();
    // Отвязывает текстуру
    void unbind();
    // Удаляет текстуру
    void remove();
};
#endif