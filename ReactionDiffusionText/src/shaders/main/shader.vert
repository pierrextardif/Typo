#version 150
precision mediump float;
uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec3 normal;
in vec2 texcoord;
in vec4 color;

out vec2 fragCoord;
out float positionZ;

void main()
{
    
    fragCoord = texcoord;
    positionZ = normal.z;
    
    gl_Position = modelViewProjectionMatrix * position;
}
