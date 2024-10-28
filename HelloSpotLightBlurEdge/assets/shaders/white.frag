#version 330 core
out vec4 FragColor;
in vec2 uvPos;
in vec3 normal;

void main()
{
    FragColor = vec4(vec3(1.0f, 1.0f, 1.0f), 1.0);
}
