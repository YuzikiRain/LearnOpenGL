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

struct Light
{
	vec3 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform Material material;
uniform Light light;

void main()
{
	vec3 objectColor = mix(texture(texture0, ourTexCoord), texture(texture1, ourTexCoord), 0.3).rgb;

	// ambient
	vec3 ambient = material.ambient * lightColor;

	// diffuse
	vec3 normal = normalize(normalOUT);
	//vec3 lightDirection = normalize(lightPositionWS - fragmentPositionWS);
	vec3 lightDirection = normalize(-light.direction);
	float diffuse = max(dot(lightDirection, normal), 0.0f);
	vec3 diffuseColor = diffuse * lightColor;

	// specular
	vec3 viewDirection = normalize(viewPositionWS - fragmentPositionWS);
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float specular = pow(max(dot(viewDirection, reflectDirection), .0f), 64);
	float specularStrength = 2.0f;
	vec3 specularColor = specularStrength * specular * lightColor;

	vec3 result = objectColor * (diffuseColor + specularColor + ambient);
	FragColor = vec4(result, 1.0f);
}