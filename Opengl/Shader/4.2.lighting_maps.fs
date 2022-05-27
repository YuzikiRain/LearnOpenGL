#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;    
    float shininess;
}; 

struct DirectionalLight { 
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
struct PointLight {
    vec3 position;  
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
};
#define POINT_LIGHTS_LIMIT 4
uniform PointLight pointLights[POINT_LIGHTS_LIMIT]

struct SpotLight {
    vec3 position;  
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
  
uniform vec3 viewPos;
uniform Material material;
uniform DirectionalLight directionalLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;

void main()
{
    vec3 normal = normalize(Normal);

    vec3 result = CaculateDirectionalLight(directionalLight, normal);
    for (int i = 0; i < POINT_LIGHTS_LIMIT; i++)
    {
        result += CaculateDirectionalLight(pointLight, normal, );
    }
    FragColor = vec4(result, 1.0);
} 

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal)
{
    vec3 lightDir = light.direction;

    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    // diffuse 
    vec3 norm = normalize(normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

    return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(PointLight light, vec3 normal, lightDir)
{
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    // diffuse 
    vec3 norm = normalize(normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

    float distance = length(FragPos - light.position);
    float attenuation = 1 / (light.constant + distance * light.linear + distance * light.quadratic * light.quadratic)

    return (ambient + diffuse + specular) * attenuation;
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal)
{
    vec3 lightDir = normalize(light.position - FragPos);
    float theta = dot(light.direction, -lightDir);
    // 表示外圆锥到内圆锥的夹角的余弦值
    float epsilon = light.cutOff - light.outerCutOff;
    // 表示当前位置到内圆锥的夹角的余弦值
    float delta = theta - light.outerCutOff;
    // 夹角越大，余弦值delta越小，intensity越小
    float intensity = delta / epsilon;

    float distance = length(FragPos - light.position);
    float attenuation = 1 / (light.constant + distance * light.linear + distance * light.quadratic * light.quadratic)


    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    // diffuse 
    vec3 norm = normalize(normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

    return (ambient + diffuse + specular) * attenuation * intensity;
}