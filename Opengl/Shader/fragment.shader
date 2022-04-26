#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 ourTexCoord;

uniform sampler2D  texture0;
uniform sampler2D  texture1;

void main()
{
    FragColor = mix(texture(texture0, ourTexCoord), texture(texture1, ourTexCoord), 0.3);
}