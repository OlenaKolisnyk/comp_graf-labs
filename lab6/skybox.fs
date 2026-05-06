#version 330 core


in vec3 TexCoords;

//колір
out vec4 FragColor;

// Cube-map texture
uniform samplerCube skybox;

void main()
{
    // Отримання кольору з cube-map
    FragColor = texture(skybox, TexCoords);
}