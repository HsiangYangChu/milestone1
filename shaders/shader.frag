#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;
layout(binding = 2) uniform UniformLightAttr{
    vec3 lightPos;
    vec3 viewPos;
    vec3 lightColor;
} lightAttr;

layout(location = 0) in vec4 fragColor;
// layout(location = 1) in vec2 fragTexCoord;
layout(location = 1) in vec3 fragNormal;
layout(location = 2) in vec3 fragPos;

layout(location = 0) out vec4 outColor;

void main() {
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightAttr.lightColor;
      
    // diffuse
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(lightAttr.lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightAttr.lightColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(lightAttr.viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightAttr.lightColor;
        
    vec3 result = (ambient + diffuse + specular) * fragColor.rgb;
    outColor = vec4(result, fragColor.a);
    // outColor = vec4(fragColor.a);

    // norm = (norm + vec3(1.0f, 1.0f, 1.0f))*0.5;
    // outColor = vec4(norm, 1.0);
    
    // outColor = texture(texSampler, fragTexCoord);
    // outColor = vec4(fragColor, 1.0f);
    // outColor = vec4(lightAttr.lightPos, 1.0f);
}
