// ground.fp
// Stonehenge ground fragment shader
precision mediump float;


uniform sampler2D colorMap;     // Color Map
uniform sampler2D detailMap;    // Detail Texture

varying vec2 vTexCoordVary;


void main (void)
    {
    vec4 vLayer1 = texture2D(colorMap, vTexCoordVary);
    vec4 vLayer2 = texture2D(detailMap, vTexCoordVary * 30.0);
    gl_FragColor =  vLayer1 * vLayer2;
    }
