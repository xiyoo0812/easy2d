#version 330

in vec2 texCoordO;
in vec4 colorO;
uniform sampler2D texSampler;
out vec4 FragColor;

void main()
{
    vec4 samperColor = texture2D(texSampler, texCoordO);
    FragColor = samperColor * colorO;
}
