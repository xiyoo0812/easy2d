#version 330

in vec4 position;
in float isHUD;
uniform mat4 scaleMatrix;
uniform mat4 viewInverseMatrix;
uniform mat4 projectionMatrix;
out vec2 texCoord;

void main()
{
    vec4 wPos = position;
    wPos *= scaleMatrix;
    wPos *= projectionMatrix;
    if(isHUD < 0.5)
    {
        wPos *= viewInverseMatrix;
    }
    gl_Position = vec4(5 * wPos.x, 5 * wPos.y, wPos.z, 1.0);
}
