#include "VBO.h"

VBO::VBO(GLfloat *vertices, GLsizeiptr size)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    // Introduce the vertices into the VBO
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
}

void VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}
void VBO::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void VBO::remove()
{
    glDeleteBuffers(1, &ID);
}
