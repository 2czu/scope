#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNorm;
layout (location = 3) in vec2 aTexCoord;

flat out vec3 faceColor;
out vec3 Norm;
out vec3 FragPos;
out vec3 localNorm;
out vec3 localPos;
out vec2 TexCoord;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(Position, 1.0);

	FragPos = vec3(model * vec4(Position, 1.0));
	localPos = Position;

	faceColor = aColor;
	TexCoord = aTexCoord;

	Norm = mat3(transpose(inverse(model))) * aNorm;  
	localNorm = aNorm;
}