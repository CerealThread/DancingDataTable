#version 430 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


out vec4 fColor;
void main(void)
{
    fColor = color;
    gl_Position = (projection*view*model*position);

}
