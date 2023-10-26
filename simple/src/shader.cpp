#include "shader.h"

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

    // Создаем объект вершинного шейдера
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Объединяем объект вершинного шейдера с его кодом
    glShaderSource(vertexShader, 1, &vertextSource, NULL);
    // Компилируем шейдер
    glCompileShader(vertexShader);

    // Создаем объект фрагментного шейдера
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Объединяем объект фрагментного шейдера с его кодом
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    // Компилируем шейдер
    glCompileShader(fragmentShader);

    // Создаем объект программы шейдера
    ID = glCreateProgram();
    // Объединяем программу шейдера с объектами вершинного и фрагментного шейдера
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    // Связываем все в программе шейдера
    glLinkProgram(ID);

    // Удаляем отработавшие объекты
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
