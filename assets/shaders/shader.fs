#version 330 core

out vec4 FragColor;

flat in vec3 ourColor;
uniform vec3 lightColor;
in vec2 TexCoord;
in vec3 Norm;
in vec3 FragPos;

uniform vec3 inLightPos;
uniform vec3 viewPos;

uniform vec3 mtlAmbient;
uniform vec3 mtlDiffuse;
uniform vec3 mtlSpecular;
uniform float mtlShininess;

uniform sampler2D ourTexture;

void main()
{
    vec3 norm = normalize(Norm);
    vec3 lightDir = normalize(inLightPos - FragPos);
    vec3 viewDir  = normalize(viewPos - FragPos);

    vec3 ambient = mtlAmbient * lightColor;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * (lightColor * mtlDiffuse);

    float shininess = max(mtlShininess, 2.0);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = lightColor * mtlSpecular * spec;

    vec3 result = ambient + diffuse + specular;
    result *= ourColor;

    FragColor = vec4(result, 1.0);
}
