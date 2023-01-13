#version 330 core

in float gradientOut;
in vec3 fColor;

out vec4 fragColor;

void main() 
{
	float gradient = gradientOut * 2;

	fragColor = vec4(vec3(fColor.x * (gradient + 0.1), fColor.y * (gradient + 0.1), fColor.z), 1.0f);
}
