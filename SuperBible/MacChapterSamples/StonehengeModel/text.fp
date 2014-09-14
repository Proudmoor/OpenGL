// text.fp
// Stonehenge text fragment shader
#version 150

uniform sampler2DRect colorMap;   // Color Map

in vec2 vTexCoordVary;

out vec4    vFragColor;

void main (void)
    {
    vFragColor = texture(colorMap, vTexCoordVary);
    //vFragColor = vec4(1.0, 0.0, 0.0, 1.0);
    }
