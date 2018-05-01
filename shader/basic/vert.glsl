#version 330

layout(location = 0) in vec2 vertices;
layout(location = 1) in vec2 uv;

out vec2 uvOut;
uniform vec2 orig;
uniform vec2 textureSize;
uniform mat3 transform;
uniform mat3 scale;

void main() {

    gl_Position = vec4(scale*transform*vec3(vertices, 1), 1);

    uvOut = mix(orig, orig+textureSize, vec2(uv.x, uv.y));
}
