#version 330 core
// Координаты
layout (location = 0) in vec3 aPos;
// Цвет
layout (location = 1) in vec3 aColor;
// Координаты текстуры
layout (location = 2) in vec2 aTex;

// Вывод цвета для фрагментного шейдера
out vec3 color;
// Вывод координат тектсуры для фрагментного шейдера
out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    // Получаем позиции из матриц
    gl_Position = proj * view * model * vec4(aPos, 1.0);
    // Получаем цвета из массива вершин
    color = aColor;
    // Получаем координаты тектсуры
    texCoord = aTex;
}   