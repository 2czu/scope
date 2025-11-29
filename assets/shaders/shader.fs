#version 330 core

out vec4 FragColor;

flat in vec3 ourColor;
uniform vec3 lightColor;
in vec2 TexCoord;
in vec3 Norm;
in vec3 FragPos;

uniform vec3 inLightPos;

uniform sampler2D ourTexture;

void main()
{
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(Norm);
	vec3 lightDir = normalize(inLightPos - FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * ourColor;

	FragColor = vec4(result, 1.0);
}