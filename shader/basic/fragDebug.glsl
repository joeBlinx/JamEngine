#version 330

out vec4 color;

in vec2 uvOut;
uniform float diameter;

uniform bool isSquare;

void main() {
    vec4 black = vec4(0, 0, 0, 1);
    if(isSquare){
        color = black;

    }else{
    float lengthCircle = length(uvOut - vec2(0.5)) ;
        float min = 0.01;
        float max = 0.05;
        float maxDiameter = 50;
        float delta;
        if(diameter > maxDiameter){
            delta = min;
        }else{
            delta = max - (diameter/maxDiameter)*min;
         }

         if(lengthCircle < 0.5 && lengthCircle > 0.5-delta){
              color = black;
         }else
         {
            color = vec4(0);
         }
    }
}
