#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D colorMap;
uniform bool isTopFace;

void main()
{
    vec4 texColor = texture(texture1, TexCoord);
    if (isTopFace) {
        vec4 colormapColor = texture(colorMap, TexCoord);
        FragColor = texColor * colormapColor;
    } else {
        FragColor = texColor;
    }
}
