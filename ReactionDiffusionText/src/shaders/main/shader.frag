#version 150
uniform sampler2DRect feedback;

float kernel[9];
vec2 offset[9];

float passes = 1.0;
uniform float feed;
uniform float kill;
uniform float Du;
uniform float Dv;
uniform sampler2DRect tex0;

out vec4 gl_fragColor;

void main(){
    vec2 st = gl_TexCoord[0].st;
    
    offset[0] = vec2( 0.0, -1.0);
    offset[1] = vec2(-1.0,  0.0);
    offset[2] = vec2( 0.0,  0.0);
    offset[3] = vec2( 1.0,  0.0);
    offset[4] = vec2( 0.0,  1.0);
    
    offset[5] = vec2(-1.0, -1.0);
    offset[6] = vec2( 1.0, -1.0);
    offset[7] = vec2(-1.0,  1.0);
    offset[8] = vec2( 1.0,  1.0);
    
    kernel[0] = 1.0;
    kernel[1] = 1.0;
    kernel[2] = -6.82842712;
    kernel[3] = 1.0;
    kernel[4] = 1.0;
    
    kernel[5] = 0.707106781;
    kernel[6] = 0.707106781;
    kernel[7] = 0.707106781;
    kernel[8] = 0.707106781;
    
    vec2 lap = vec2(0.0, 0.0);
    for(int i=0; i<9; i++){
        vec2 tmp = texture2DRect(tex0, st + offset[i]).rb;
        lap += tmp * kernel[i];
    }
    
    vec2 uv = texture2DRect(tex0, st).rb;
    float du = Du*lap.r - uv.r*uv.g*uv.g + feed*(1.0 - uv.r);
    float dv = Dv*lap.g + uv.r*uv.g*uv.g - (feed+kill)*uv.g;
    vec2 dst = uv + passes*vec2(du, dv);
    
    gl_fragColor = vec4(dst.r, 0.0, dst.g, 1.0);;
}
