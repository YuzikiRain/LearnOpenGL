#version 330 core
out vec4 FragColor;

in vec3 fragmentPositionWS;
in vec3 normalOUT;
in vec3 ourColor;
in vec2 ourTexCoord;

uniform sampler2D  texture0;
uniform sampler2D  texture1;

uniform vec3 lightPositionWS;
uniform vec3 lightColor;
uniform vec3 viewPositionWS;
uniform vec4 tintColor;

void main()
{
	vec3 objectColor = mix(texture(texture0, ourTexCoord), texture(texture1, ourTexCoord), 0.3).rgb;

	// ambient
	float ambientStrength = 0.3f;
	vec3 ambient = ambientStrength * lightColor;

	// diffuse
	vec3 normal = normalize(normalOUT);
	vec3 lightDirection = normalize(lightPositionWS - fragmentPositionWS);
	float diffuse = max(dot(lightDirection, normal), 0.0f);
	vec3 diffuseColor = diffuse * lightColor;

	// specular
	vec3 viewDirection = normalize(viewPositionWS - fragmentPositionWS);
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float specular = pow(max(dot(viewDirection, reflectDirection), .0f), 64);
	float specularStrength = 2f;
	vec3 specularColor = specularStrength * specular * lightColor;

	vec3 result = objectColor * (diffuseColor + specularColor + ambient);
	FragColor = vec4(result, 1.0f);
}