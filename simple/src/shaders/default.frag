#version 330 core
out vec4 FragColor;

// Ввод цвета из вершинного шейдера
in vec3 color;
// Ввод координат текстуры из вершинного шейдера
in vec2 texCoord;
// Ввод нормали
in vec3 normal;
// Ввод текущей позиции
in vec3 crntPos;

// Получаем единицу текстуры из основной функции
uniform sampler2D tex0;

// Получаем цвет света
uniform vec4 lightColor;
// Получаем позицию освещения
uniform vec3 lightPos;
// Получаем позицию камеры
uniform vec3 camPos;


void main()
{
    // Устанавливаем базовое глобальное освещение
    float ambient = 0.2f;
    // Нормализуем вектор нормали
    vec3 norm = normalize(normal);
    // Расчитываем направление освещения
    vec3 lightDirection = normalize(lightPos - crntPos);
    // Расчитываем диффузию света
    float diffuse = max(dot(norm, lightDirection), 0.0f);
    // Расчитываем силу света, учитывая направление камеры
    float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, norm);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

    // Устанавливаем цвет фрагмента 
    FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient + specular);
}  