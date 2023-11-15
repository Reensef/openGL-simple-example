#version 330 core
out vec4 FragColor;

// Ввод цвета из вершинного шейдера
in vec3 color;
// Ввод координат текстуры из вершинного шейдера
in vec2 texCoord;

in vec3 normal;
in vec3 crntPos;

// Получаем единицу текстуры из основной функции
uniform sampler2D tex0;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;


void main()
{
    float ambient = 0.2f;

    vec3 norm = normalize(normal);
    vec3 lightDirection = normalize(lightPos - crntPos);

    float diffuse = max(dot(norm, lightDirection), 0.0f);
    
    float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, norm);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;
    
    FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient + specular);
}  