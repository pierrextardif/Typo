#version 150
//uniform sampler2DRect feedback;

float kern[9];
vec2 offset[9];

in vec2 fragCoord;
in vec3 ABReactives;


float passes = 1.0;
uniform float feed;
uniform float kill;
uniform float Du;
uniform float Dv;
uniform vec3 kernelGUI;
uniform sampler2DRect tex0;

out vec4 fragColor;

void main(){
    vec2 st = fragCoord;
    
    offset[0] = vec2( 0.0, -1.0);
    offset[1] = vec2(-1.0,  0.0);
    offset[2] = vec2( 0.0,  0.0);
    offset[3] = vec2( 1.0,  0.0);
    offset[4] = vec2( 0.0,  1.0);
    
    offset[5] = vec2(-1.0, -1.0);
    offset[6] = vec2( 1.0, -1.0);
    offset[7] = vec2(-1.0,  1.0);
    offset[8] = vec2( 1.0,  1.0);
    
//    sumA += getA(i, j, &current) * -1;
//        sumA += getA(i - 1, j, &current) * 0.2;
//        sumA += getA(i + 1, j, &current) * 0.2;
//        sumA += getA(i, j - 1, &current) * 0.2;
//        sumA += getA(i, j + 1, &current) * 0.2;
//        sumA += getA(i - 1, j - 1, &current) * 0.05;
//        sumA += getA(i + 1, j - 1, &current) * 0.05;
//        sumA += getA(i + 1, j + 1, &current) * 0.05;
//        sumA += getA(i - 1, j + 1, &current) * 0.05;
    kern[0] = kernelGUI.x;
    kern[1] = kernelGUI.x;
    kern[2] = kernelGUI.y;
    kern[3] = kernelGUI.x;
    kern[4] = kernelGUI.x;
    
    kern[5] = kernelGUI.z;
    kern[6] = kernelGUI.z;
    kern[7] = kernelGUI.z;
    kern[8] = kernelGUI.z;
//
//    kernel[0] = 1.0;
//    kernel[1] = 1.0;
//    kernel[2] = -6.82842712;
//    kernel[3] = 1.0;
//    kernel[4] = 1.0;
//
//    kernel[5] = 0.707106781;
//    kernel[6] = 0.707106781;
//    kernel[7] = 0.707106781;
//    kernel[8] = 0.707106781;
    
    vec2 lap = vec2(0.0, 0.0);
    for(int i=0; i<9; i++){
        vec2 tmp = texture(tex0, st + offset[i]).rb;
        lap += tmp * kern[i];
    }
    
    vec2 uv = texture(tex0, st).rb;
    float du = Du*lap.r - uv.r*uv.g*uv.g + feed*(1.0 - uv.r);
    float dv = Dv*lap.g + uv.r*uv.g*uv.g - (feed+kill)*uv.g;
    vec2 dst = uv + passes*vec2(du, dv);
    
    fragColor = vec4(dst.r, 0.0, dst.g, 1.0);;
}
