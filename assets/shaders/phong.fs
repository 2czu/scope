#version 330 core

out vec4 FragColor;

flat in vec3 faceColor;
uniform vec3 lightColor;
in vec2 TexCoord;
in vec3 Norm;
in vec3 FragPos;
in vec3 localNorm;
in vec3 localPos;

uniform vec3 viewPos;

uniform float texOpacity;

struct Light {
    vec3 position;  
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
    float alpha;
    int illum;
}; 
  
uniform Material material;
uniform Light light;

uniform sampler2D ourTexture;


vec4 triplanarTexture(sampler2D tex, vec3 pos, vec3 normal, float scale)
{
    vec3 w = abs(normal);
    w /= (w.x + w.y + w.z);

    vec2 uvX = pos.yz * scale;
    vec2 uvY = pos.xz * scale;
    vec2 uvZ = pos.xy * scale;

    vec4 tx = texture(tex, uvX);
    vec4 ty = texture(tex, uvY);
    vec4 tz = texture(tex, uvZ);

    return tx * w.x + ty * w.y + tz * w.z;
}


vec3 pointLight(Light light, vec3 norm, vec3 fragPos, vec3 viewDir, vec4 texColor)
{
    vec3 actualTexColor = texOpacity * texColor.rgb;

    vec3 lightDir = normalize(light.position - FragPos);

    vec3 ambient = (((1 - texOpacity) * material.ambient) + actualTexColor) * light.ambient;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * ((((1 - texOpacity) * material.diffuse) + actualTexColor) * light.diffuse);

    float shininess = max(material.shininess, 2.0);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = light.specular * ((((1 - texOpacity) * material.specular) + actualTexColor) * spec);

    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + (light.linear * distance) +
        (light.quadratic * pow(distance, 2.0)));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    switch (material.illum)
    {
        case 0:
            return (diffuse);
        case 1:
            return (diffuse + ambient);
        default:
            break;
    }
    return (diffuse + ambient + specular);
}

void main()
{
    vec3 norm = normalize(Norm);
    vec3 viewDir  = normalize(viewPos - FragPos);

    vec4 texColor = triplanarTexture(ourTexture, localPos, localNorm, 1.0);
    
    vec3 result = pointLight(light, norm, FragPos, viewDir, texColor);

    result *= faceColor;

    FragColor = vec4(result, material.alpha * texColor.a);
}
