#version 410 core
layout(location = 0) in vec3 _position;
layout(location = 1) in vec3 _normal;
layout(location = 2) in vec3 _color;
layout (location = 3) in vec2 _texCoords;


out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
out vec3 Color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    FragPos = vec3(model*vec4(_position, 1.0f));
    Normal = mat3(transpose(inverse(model))) * _normal;
    TexCoords = _texCoords;
    gl_Position = projection * view *vec4(FragPos, 1.0);

    Color = _color;
}
