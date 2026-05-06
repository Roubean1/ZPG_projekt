#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;
uniform sampler2D textureUnitID;
uniform int useTexture;

in vec2 TexCoord;
out vec4 FragColor;

void main() {
    vec3 result = material.ambient;
    
    if (useTexture == 1) {
        result *= texture(textureUnitID, TexCoord).rgb;
    }
    
    FragColor = vec4(result, 1.0);
}