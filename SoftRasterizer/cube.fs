uniform sampler2D tex;
varying vec3 lightDir, normal;

uniform vec3 lightPos;

void main()
{
	normal = normalize(gl_NormalMatrix * gl_Normal);
	lightDir = normalize(lightPos);
	
	
	gl_FragColor = gl_Color * texture2D(tex, gl_TexCoord[0].xy);
}
