#version 330 core
in vec3 fragPos;
in vec3 fragNormal;

out vec4 outColor;

uniform vec3 viewPos;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

uniform Light light;
uniform vec3 objectColor;

void main() {
    vec3 ambient = light.ambient * objectColor;
    
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * objectColor;
    
    vec3 result = ambient + diffuse;
    outColor = vec4(result, 1.0);
}