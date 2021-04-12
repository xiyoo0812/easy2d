#version 330

in vec2 texCoord;
in vec4 colorMultiplier;
uniform sampler2D textureSampler;
out vec4 FragColor;

void main()
{
    vec4 sampledColor = texture2D(textureSampler, texCoord);
    FragColor = sampledColor * colorMultiplier;
}
