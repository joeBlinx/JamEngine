#version 330

out vec4 color;

in vec2 uvOut;
uniform sampler2D texture2D;

void main() {

    color = texture(texture2D, uvOut);
}
