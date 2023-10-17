#include "EBO.h"

EBO::EBO(GLuint *indexes, GLsizeiptr size)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    // Внедрение индексов
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indexes, GL_DYNAMIC_DRAW);
}

void EBO::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}
void EBO::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void EBO::remove()
{
    glDeleteBuffers(1, &ID);
}
