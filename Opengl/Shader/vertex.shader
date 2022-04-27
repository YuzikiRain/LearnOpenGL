#version 330 core
layout (location = 0) in vec3 aPos;
layout(location = 1) in vec3 normal;
layout (location = 2) in vec2 aTexCoord;

out vec4 fragmentPositionWS;
out vec3 ourColor;
out vec2 ourTexCoord;
out vec3 normalOUT;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    fragmentPositionWS = model * vec4(aPos, 1.0);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    ourTexCoord = aTexCoord;
    normalOUT = normal;
}