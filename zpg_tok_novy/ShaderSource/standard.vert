#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform float w = 500.0;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main() 
{
    vec4 pos = vec4(aPos * w, w);

    vec4 worldPosition = modelMatrix * pos;
    vec4 viewPosition  = viewMatrix * worldPosition;
    vec4 clipPosition  = projectionMatrix * viewPosition;

    FragPos = vec3(worldPosition) / worldPosition.w;
    Normal = mat3(transpose(inverse(modelMatrix))) * aNormal;
    TexCoord = aTexCoord;

    gl_Position = clipPosition;
}