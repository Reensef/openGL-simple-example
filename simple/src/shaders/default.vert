#version 330 core
// Координаты
layout (location = 0) in vec3 aPos;
// Цвет
layout (location = 1) in vec3 aColor;
// Координаты текстуры
layout (location = 2) in vec2 aTex;
// Координаты нормали
layout (location = 3) in vec3 aNormal;

// Вывод цвета для фрагментного шейдера
out vec3 color;
// Вывод координат текстуры
out vec2 texCoord;
// Вывод координат нормали
out vec3 normal;
out vec3 crntPos;

uniform mat4 model;
// uniform mat4 model2;
uniform mat4 cameraMatrix;

void main()
{
    crntPos = vec3(vec4(aPos, 1.0f) * model);

    // Получаем позиции из матриц
    gl_Position = cameraMatrix * vec4(crntPos, 1.0f);
    // Получаем цвета из массива вершин
    color = aColor;
    // Получаем координаты тектсуры
    texCoord = aTex;
    // Получаем координаты нормали
    normal = aNormal;
}   