#version 460 core

layout (location = 0) in vec4 Position;

uniform mat4 Projection;
uniform mat4 View;

void main()
{
	gl_Position = Projection* View * Position;
}
