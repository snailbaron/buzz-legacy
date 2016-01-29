#version 330 core
layout(location = 0) in vec2 vertexPosition;

uniform mat3 guiMatrix;
uniform vec2 guiPos;

void main(void)
{
    gl_Position.xyw = guiMatrix * vec3(vertexPosition.x + guiPos.x, vertexPosition.y + guiPos.y, 1.0);
    gl_Position.z = 0.0;
}