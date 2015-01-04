#version 150

uniform mat4 model;

uniform struct Light {
    vec3 position;
    vec3 intensities;
} light;

in vec3 fragNormal;
in vec3 fragVert;
in vec4 color;

out vec4 finalColor;



void main () {
    //normal in world coordinates
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 normal = normalize(normalMatrix * fragNormal);
    
    vec3 fragPosition = vec3(model * vec4(fragVert, 1));
    vec3 surfaceToLight = light.position - fragPosition;
    
    float brightness = dot(normal, surfaceToLight) /(length(surfaceToLight) * length(normal));
    brightness = clamp(brightness,0,1);

    finalColor = brightness * vec4(light.intensities, 1) * color;
}