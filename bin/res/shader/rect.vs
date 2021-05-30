#version 330 core

in vec4 color;
in vec4 position;
out vec4 colorO;

void main()
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
    colorO = color;
}