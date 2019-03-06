#version 330
out vec4 color;
uniform float life;

in float x;
void main() {

    if(x < life)
    {
        color = vec4(0.5, 0, 0, 0.5);
    }else
    {
        color = vec4(0, 0, 0, 0);
    }

}
