#version 330 core

struct Light {
    int type;
    vec3 color;
    vec3 position;
    vec3 direction;
    float constant;
    float linear;
    float quadratic;
    float cutOff;
    float outerCutOff;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform int numLights;
uniform Light lights[256];
uniform Material material;
uniform vec3 viewPosition;
uniform sampler2D textureUnitID;
uniform int useTexture;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

void main() {
    vec3 norm = normalize(Normal);
    vec3 result = vec3(0.0);
    
    vec3 surfaceColor = material.diffuse;
    if (useTexture == 1) {
        surfaceColor = texture(textureUnitID, TexCoord).rgb;
    }

    for (int i = 0; i < numLights; i++) {
        Light light = lights[i];
        vec3 lightDir;

        if (light.type == 0) { // Ambient
            result += light.color * material.ambient * surfaceColor;
        }
        else if (light.type == 1) { // Point
            lightDir = normalize(light.position - FragPos);
            float diff = max(dot(norm, lightDir), 0.0);

            float distance = length(light.position - FragPos);
            float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

            result += diff * light.color * surfaceColor * attenuation;
        }
        else if (light.type == 2) { // Directional
            lightDir = normalize(-light.direction);
            float diff = max(dot(norm, lightDir), 0.0);
            result += diff * light.color * surfaceColor;
        }
        else if (light.type == 3) { // Spot
            lightDir = normalize(light.position - FragPos);
            float theta = dot(lightDir, normalize(-light.direction));
            float epsilon = light.cutOff - light.outerCutOff;
            float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
            float diff = max(dot(norm, lightDir), 0.0);

            float distance = length(light.position - FragPos);
            float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

            result += diff * light.color * surfaceColor * attenuation * intensity;
        }
    }

    FragColor = vec4(result, 1.0);
}