#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>


#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>

using namespace std;

Shader::Shader(const char* vertexPath, const char* fragmentPath )
{
	ifstream vertextFile;
	ifstream fragmentFile;
	stringstream vertexSStream;
	stringstream fragmnetSStream;

	vertextFile.open(vertexPath);
	fragmentFile.open(fragmentPath);
	vertextFile.exceptions(ifstream::failbit || ifstream::badbit);
	fragmentFile.exceptions(ifstream::failbit || ifstream::badbit);

	try
	{
		if (!vertextFile.is_open() || !fragmentFile.is_open())
		{

			throw exception("open file error");
		}
	
		vertexSStream << vertextFile.rdbuf();
		fragmnetSStream << fragmentFile.rdbuf();

		vertexString = vertexSStream.str();
		fragmentString = fragmnetSStream.str();

		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, NULL);
		glCompileShader(vertex);

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		glDeleteShader(vertex);
		glDeleteShader(fragment);
		
	}
	catch (const std::exception&  ex)
	{
		cout << ex.what();
	}
}


void Shader::use()
{
	glUseProgram(ID);
}