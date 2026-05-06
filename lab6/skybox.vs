#version 330 core

// Позиція вершини cube
layout(location = 0) in vec3 aPos;

// Координати для cube-map texture
out vec3 TexCoords;

// Матриці
uniform mat4 view;
uniform mat4 proj;

void main()
{
    // Для cube-map прикріплюємо  координати вершини
    
    TexCoords = aPos;

    // Перетворення вершини
    vec4 pos = proj * view * vec4(aPos, 1.0);

    // Skybox завжди повинен бути позаду сцени
    // xyww змушує depth = 1.0
    gl_Position = pos.xyww;
}