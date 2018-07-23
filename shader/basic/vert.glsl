#version 330

layout(location = 0) in vec2 vertices;
layout(location = 1) in vec2 uv;

out vec2 uvOut;
uniform vec2 orig;
uniform vec2 textureSize;
uniform mat3 transform;
uniform mat3 scale;
uniform mat4 camera;
void main() {

    gl_Position = camera*mat4(scale*transform)*vec4(vertices, 1, 1);
    uvOut = mix(orig, orig+textureSize, vec2(uv.x, uv.y));
}
