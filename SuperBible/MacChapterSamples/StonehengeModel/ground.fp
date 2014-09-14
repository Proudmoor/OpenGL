// ground.fp
// Stonehenge ground fragment shader
#version 150

uniform sampler2D colorMap;     // Color Map
uniform sampler2D detailMap;    // Detail Texture

in vec2 vTexCoordVary;

out vec4    vFragColor;

void main (void)
    {
    vec4 vLayer1 = texture(colorMap, vTexCoordVary);
    vec4 vLayer2 = texture(detailMap, vTexCoordVary * 30.0);
    vFragColor =  vLayer1 * vLayer2;
    }
