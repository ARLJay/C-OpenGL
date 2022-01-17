#include <stdio.h>
#include <stdlib.h>
#include <shader.h>
#include <glad/glad.h>
#include <string.h>

static char* readFile(const char* path)
{
	
	char *buffer = 0;
	
	FILE *f = fopen(path, "r");
	
	if(f)
	{
		fseek(f, 0, SEEK_END); //Make offset length of file
		long length = ftell(f); //Get current offset (length of file)
		fseek(f, 0, SEEK_SET);  //Offset = beginning of set

		buffer = malloc(length);
		memset(buffer, 0, length);

		if(buffer)
		{
			fread(buffer, 1, length-1, f); //Read file into buffer
		} 

		fclose(f);

		return buffer;
	}
}

static GLuint CompileShader(GLenum type, const char* source)
{
	GLuint shader = glCreateShader(type);

	glShaderSource(shader, 1, &source, 0);

	glCompileShader(shader);

	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE)
	{
		printf("Failed to compile: \n\n%s\n\n", source);
	}

	return shader;
}

unsigned int CreateShader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	char* vertexShader = readFile(vertexShaderPath);
	char* fragmentShader = readFile(fragmentShaderPath);

	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);

	GLint program_linked;
	glGetProgramiv(program, GL_LINK_STATUS, &program_linked);
	if(program_linked != GL_TRUE)
	{
		printf("Failed to link program");
	}

	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}
