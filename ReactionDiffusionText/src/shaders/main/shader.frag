#version 150

float kern[9];
vec2 offset[9];

in vec2 fragCoord;
in vec3 ABReactives;


float passes = 1.0;
uniform float feed;
uniform float kill;
uniform float DiffA;
uniform float DiffB;
uniform vec2 kernelGUI;
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
    
    
    kern[0] = kernelGUI.x;
    kern[1] = kernelGUI.x;
    kern[2] = -1;
    kern[3] = kernelGUI.x;
    kern[4] = kernelGUI.x;
    
    kern[5] = kernelGUI.y;
    kern[6] = kernelGUI.y;
    kern[7] = kernelGUI.y;
    kern[8] = kernelGUI.y;
    
    vec2 lap = vec2(0.0, 0.0);
    for(int i=0; i<9; i++){
        vec2 tmp = texture(tex0, st + offset[i]).rb;
        lap += tmp * kern[i];
    }
    
    vec2 uv = texture(tex0, st).rb;
    float du = DiffA*lap.r - uv.r*uv.g*uv.g + feed*(1.0 - uv.r);
    float dv = DiffB*lap.g + uv.r*uv.g*uv.g - (feed+kill)*uv.g;
    vec2 dst = uv + passes*vec2(du, dv);
    
    fragColor = vec4(dst.r, 0.0, dst.g, 1.0);;
}
