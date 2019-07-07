#version 150
uniform sampler2DRect tex0;
uniform sampler2DRect feedback;

uniform float u_time;
uniform float flowingColorsRainbow;

out vec4 fragColor;

uniform float feedbackAmt;


float hash( float n )
{
    return fract(sin(n)*43758.5453123);
}

float noise( in vec2 x )
{
    vec2 p = floor(x);
    vec2 f = fract(x);
    
    f = f*f*(3.0-2.0*f);
    
    float n = p.x + p.y*157.0;
    
    return mix(mix( hash(n+  0.0), hash(n+  1.0),f.x),
               mix( hash(n+157.0), hash(n+158.0),f.x),f.y);
}

// hue by netgrind(?)

vec3 hue(vec3 color, float shift) {
    
    const vec3  kRGBToYPrime = vec3 (0.299, 0.587, 0.114);
    const vec3  kRGBToI     = vec3 (0.596, -0.275, -0.321);
    const vec3  kRGBToQ     = vec3 (0.212, -0.523, 0.311);
    
    const vec3  kYIQToR   = vec3 (1.0, 0.956, 0.621);
    const vec3  kYIQToG   = vec3 (1.0, -0.272, -0.647);
    const vec3  kYIQToB   = vec3 (1.0, -1.107, 1.704);
    
    // Convert to YIQ
    float   YPrime  = dot (color, kRGBToYPrime);
    float   I      = dot (color, kRGBToI);
    float   Q      = dot (color, kRGBToQ);
    
    // Calculate the hue and chroma
    float   hue     = atan (Q, I);
    float   chroma  = sqrt (I * I + Q * Q);
    
    // Make the user's adjustments
    hue += shift;
    
    // Convert back to YIQ
    Q = chroma * sin (hue);
    I = chroma * cos (hue);
    
    // Convert back to RGB
    vec3    yIQ   = vec3 (YPrime, I, Q);
    color.r = dot (yIQ, kYIQToR);
    color.g = dot (yIQ, kYIQToG);
    color.b = dot (yIQ, kYIQToB);
    
    return color;
}

float fractalNoise(vec2 pos) {
    float n = 0.;
    float scale = 1. / 1.5;
    for (int i = 0; i < 5; i += 1) {
        n += noise(pos) * scale;
        scale *= 0.5;
        pos *= 2.;
    }
    return n;
}
void main(){
    vec2 uv = gl_FragCoord.xy;
    
    vec2 polarUv = (uv * 2.0 - 1.0);
    float angle = atan(polarUv.y, polarUv.x);
    
    // // Scale up the length of the vector by a noise function feeded by the angle and length of the vector
    float ll = length(polarUv)*0.5 - fractalNoise(vec2(sin(angle*4. + u_time*2.) + length(uv)*10., length(uv)*20. + sin(angle*4.)))*0.005 ;
    
    vec3 base = texture(tex0, uv).rgb;
    
    // // Convert the scaled coordinates back to cartesian
    vec2 offs = vec2(cos(angle)*ll + 0.5, sin(angle)*ll + 0.5);
    
    // // sample the last texture with uv's slightly scaled up
    vec3 overlay = texture(feedback, offs).rgb;
    
    // // Since the colors of the iChannel0 are monochrome, set a color channel to zero to do a hue shift
    base.b = 0.;
    
    // // Apply a hue shift to the overlaid image so it cascades in the feedback loop
    overlay = hue(overlay, .25 * sin(flowingColorsRainbow * 0.01));
    
    // // Additively blend the colors together
    vec4 col = vec4(clamp(base + overlay*feedbackAmt, vec3(0.),vec3(1.)), 1.0);
    // vec4 col = vec4(base + overlay*feedbackAmt, 1.0);
    
    fragColor = col;
    
    // fragColor = texture(tex0, uv);
}
