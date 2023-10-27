#include "VAO.h"

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

void VAO::linkAttrib(VBO &VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset)
{
    VBO.bind();
    // Скажем OpenGL как читать VBO
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    // Скажем OpenGL как использовать VBO
    glEnableVertexAttribArray(layout);
    VBO.unbind();
}

void VAO::bind()
{
    glBindVertexArray(ID);
}

void VAO::unbind()
{
    glBindVertexArray(0);
}

void VAO::remove()
{
    glDeleteVertexArrays(1, &ID);
}
