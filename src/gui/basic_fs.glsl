#version 410 core
out vec4 FragColor;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in vec3 Color;



uniform vec3 viewPos;
uniform Material material;
uniform Light light;

vec3 Phong()
{
    vec3 sample_diffuse = texture(material.diffuse, TexCoords).rgb;
    if (dot(sample_diffuse, sample_diffuse)<0.0001)
    sample_diffuse = Color;
    vec3 sample_specular = texture(material.specular, TexCoords).rgb;
    if (dot(sample_specular, sample_specular)<0.0001)
    sample_specular = vec3(0.1, 0.1, 0.1);

    // ambient
    vec3 ambient = light.ambient * sample_diffuse;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * sample_diffuse;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * sample_specular;

    vec3 result = ambient + diffuse + specular;
    return result;
}

void main()
{
    FragColor = vec4(Phong(), 1.0f);
}
