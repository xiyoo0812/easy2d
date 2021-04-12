#version 330

in vec4 color;
in float isHUD;
in vec4 position;
in vec2 texCoord;
uniform mat4 matScale;
uniform mat4 matView;
uniform mat4 matProj;
out vec2 texCoordO;
out vec4 colorO;

void main()
{
    vec4 wPos = position;
    wPos *= matScale;
    wPos *= matProj;
    if(isHUD < 0.5)
    {
        wPos *= matView;
    }
    gl_Position = vec4(wPos.x, wPos.y, wPos.z, 1.0);
    texCoordO = texCoord;
    colorO = color;
}
