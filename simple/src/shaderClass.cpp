#include "shaderClass.h"

std::string get_file_content(const char *filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return (contents);
    }
    throw(errno);
}

Shader::Shader(const char *vertexFile, const char *fragmentFile)
{
    std::string vertexCode = get_file_content(vertexFile);
    std::string fragmentCode = get_file_content(fragmentFile);

    const char *vertextSource = vertexCode.c_str();
    const char *fragmentSource = fragmentCode.c_str();

    // Create Vertex Shader Object and get its reference
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach vertex shader source to the vertex shader object
    glShaderSource(vertexShader, 1, &vertextSource, NULL);
    // Compile the vertex shader into machine code
    glCompileShader(vertexShader);

    // Create fragment Shader Object and get its reference
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach fragment shader source to the fragment shader object
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    // Compile the fragment shader into machine code
    glCompileShader(fragmentShader);

    // Create shader program object and get its reference
    ID = glCreateProgram();
    // Attach the vertex and fragment shaders to the shader propgram
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    // Wrap-up/Link all the shaders together into the Shader program
    glLinkProgram(ID);

    // Delete the now useless vertex and fragment shader object
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::activate()
{
    glUseProgram(ID);
}

void Shader::remove()
{
    glDeleteProgram(ID);
}
