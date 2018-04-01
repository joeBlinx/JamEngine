#version 330

layout(location = 0) in vec2 vertices;
layout(location = 1) in vec2 uv;

uniform mat3 transform;
uniform mat3 scale;


out vec2 uvOut;
void main() {

    gl_Position = vec4(scale*transform*vec3(vertices, 1), 1);

    uvOut = uv;

}
