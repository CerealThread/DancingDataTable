#version 330 core		
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 instancePos;
layout (location = 2) in vec2 offsetInstancePos;	
layout (location = 3) in float length;


uniform vec3 color;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out float gradientOut;

out vec3 fColor;

void main()							
{
	float x = pos.y - model[1][3];
	float gradient = (pow(x + 0.2, 2));
	gradientOut = gradient;
	gl_Position = projection * view * model * vec4(pos.x + instancePos.x + (offsetInstancePos.x * .7) * gradient, (pos.y * length) + instancePos.y, pos.z + instancePos.z + (offsetInstancePos.y * .7) * gradient, 1.0);

	fColor = color;
};
