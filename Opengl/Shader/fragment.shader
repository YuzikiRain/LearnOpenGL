#version 330 core
out vec4 FragColor;

in vec4 fragmentPositionWS;
in vec3 normalOUT;
in vec3 ourColor;
in vec2 ourTexCoord;

uniform sampler2D  texture0;
uniform sampler2D  texture1;

uniform vec3 lightPositionWS;
uniform vec3 lightColor;

void main()
{
	vec3 norm = normalize(normalOUT);
	vec3 lightDirection = normalize(fragmentPositionWS.xyz - lightPositionWS);
	float diffuse = max(dot(lightDirection, norm), 0.0f);
	//diffuse = 1.0f;
	//FragColor = mix(texture(texture0, ourTexCoord), texture(texture1, ourTexCoord), 0.3) * vec4(lightColor, 1.0f) * diffuse;
	FragColor = vec4(lightColor * diffuse, 1.0f);
}