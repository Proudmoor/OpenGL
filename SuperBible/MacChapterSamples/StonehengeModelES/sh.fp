// sh.fp
// Stonehenge "stone" fragment shader

precision mediump float;

uniform sampler2D colorMap;   // Color Map
uniform sampler2D normalMap; // Normal Map

varying vec2 vTexCoordVary;
varying vec3 vLightLocal;


vec4 vLightColor = vec4(0.8, 0.9, 1.0, 1.0);


void main (void)
    {
    vec3 norm = texture2D(normalMap, vTexCoordVary).rgb;
    norm = (norm - 0.5) * 2.0;
    float i = max(0.0, dot(norm, vLightLocal));

    i += 0.3; // ambient offset

    gl_FragColor = texture2D(colorMap, vTexCoordVary) * i;
    gl_FragColor *= vLightColor;
    }
