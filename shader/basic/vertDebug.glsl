#version 330

layout(location = 0) in vec2 vertices;
layout(location = 1) in vec2 uv;

uniform mat3 transform;
uniform mat3 scale;
uniform mat4 camera;

out vec2 uvOut;
void main() {

    gl_Position = camera*mat4(scale*transform)*vec4(vertices, 0, 1);

    uvOut = uv;

}
