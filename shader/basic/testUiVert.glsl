#version 330

layout(location = 0) in vec2 vertices;
uniform vec2 size;
uniform mat4 camera;

out float x;
void main() {
    gl_Position = vec4(size*vertices, 0, 1);
    x = gl_Position.x;
}
