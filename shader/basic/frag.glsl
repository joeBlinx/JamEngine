#version 330

out vec4 color;

in vec2 uvOut;
uniform sampler2D texture2D;
uniform int hasTexture;

void main() {

    if(hasTexture != 0){
        color = texture(texture2D, uvOut);

    }else{
        color = vec4(0, 0, 0.5, 1);
    }
}
