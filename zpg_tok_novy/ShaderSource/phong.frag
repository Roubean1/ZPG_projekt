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
    vec3 viewDir = normalize(viewPosition - FragPos);
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
        else {
            if (light.type == 1) { // Point
                lightDir = normalize(light.position - FragPos);
            }
            else if (light.type == 2) { // Directional
                lightDir = normalize(-light.direction);
            }
            else if (light.type == 3) { // Spot
                lightDir = normalize(light.position - FragPos);
            }

            float diff = max(dot(norm, lightDir), 0.0);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

            // Attenuation
            float distance = 1.0;
            float attenuation = 1.0;
            if (light.type == 1 || light.type == 3) {
                distance = length(light.position - FragPos);
                attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
            }

            // Spot intensity
            float intensity = 1.0;
            if (light.type == 3) {
                float theta = dot(lightDir, normalize(-light.direction));
                float epsilon = light.cutOff - light.outerCutOff;
                intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
            }

            vec3 ambient = light.color * material.ambient * surfaceColor;
            vec3 diffuse = diff * light.color * surfaceColor;
            vec3 specular = spec * light.color * material.specular;

            result += (ambient + diffuse + specular) * attenuation * intensity;
        }
    }

    FragColor = vec4(result, 1.0);
}