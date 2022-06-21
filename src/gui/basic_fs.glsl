#version 410 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse ;
    sampler2D specular;
    float shininess;
};

struct Light {
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
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

    vec3 result = ambient + diffuse + specular;
    return result;
}

void main()
{
    vec3 phong = Phong();
    float pcolor = dot(phong,phong);
    // 如果没有加载纹理图，采样值会是个极小的数，使用顶点颜色进行着色
    if(pcolor < 0.00001)
    {
        FragColor = vec4(Color,1);
    }
    else
    {
        FragColor = vec4(Phong(), 1.0f);//vec4(Color,1);//
    }
}
