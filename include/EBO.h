#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class EBO
{
public:
    GLuint ID;
    EBO(GLuint *indixes, GLsizeiptr size);

    void bind();
    void unbind();
    void remove();
};

#endif // EBO_CLASS_H