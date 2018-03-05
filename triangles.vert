#version 410 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;

uniform mat4 Model;
out vec3 colour;

void main() {
    colour = vColor;
    gl_Position = Model * vec4(vPosition, 1.0);

}
