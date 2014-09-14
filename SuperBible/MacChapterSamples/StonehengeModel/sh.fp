// sh.fp
// Stonehenge "stone" fragment shader
#version 150

uniform sampler2D colorMap;   // Color Map
uniform sampler2D normalMap; // Normal Map

in vec2 vTexCoordVary;
in vec3 vLightLocal;

out vec4    vFragColor;


//vec4 vLightColor = vec4(0.33, 0.07, 0.93, 1.0);
vec4 vLightColor = vec4(0.8, 0.9, 1.0, 1.0);


void main (void)
    {
    vec3 norm = texture(normalMap, vTexCoordVary).rgb;
    norm = (norm - 0.5) * 2.0;
    float i = max(0.0, dot(norm, vLightLocal));

    i += 0.3; // ambient offset

    vFragColor = texture(colorMap, vTexCoordVary) * i;
    vFragColor *= vLightColor;
    }
