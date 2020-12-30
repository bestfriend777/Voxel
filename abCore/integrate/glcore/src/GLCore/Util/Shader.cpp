#include "glpch.h"
#include "Shader.h"

#include <fstream>

namespace GLUtils {

	static std::string ReadFileAsString(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize((size_t)in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			LOG("Could not open file '{0}'");
		}

		return result;
	}

	Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
		m_RendererID = ObjFromGLSLTextFiles(vertexShaderPath, fragmentShaderPath);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	GLuint Shader::CompileShader(GLenum type, const std::string& source)
	{
		GLuint shader = glCreateShader(type);

		const GLchar* sourceCStr = source.c_str();
		glShaderSource(shader, 1, &sourceCStr, 0);

		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(shader);

			LOG("{0}");
			// HZ_CORE_ASSERT(false, "Shader compilation failure!");
		}

		return shader;
	}

	int Shader::GetUniformLocation(const std::string& name)
	{
		if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
			return m_UniformLocationCache[name];

		int uniformLocation = glGetUniformLocation(m_RendererID, name.c_str());
		if (uniformLocation == -1)
			std::cout << "Warning uniform " << name << " doesn't exist!" << std::endl;

		m_UniformLocationCache[name] = uniformLocation;

		return uniformLocation;
	}

	Shader* Shader::FromGLSLTextFiles(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
		Shader* shader = new Shader();
		shader->LoadFromGLSLTextFiles(vertexShaderPath, fragmentShaderPath);
		return shader;
	}

	void Shader::SetUniform1i(const std::string& name, int v0)
	{
		glUniform1i(GetUniformLocation(name), v0);
	}

	void Shader::SetUniform1iv(const std::string& name, int count, int* source)
	{
		glUniform1iv(GetUniformLocation(name), count, source);
	}

	void Shader::SetUniform1f(const std::string& name, float v0)
	{
		glUniform1f(GetUniformLocation(name), v0);
	}

	void Shader::SetUniform2f(const std::string& name, float v0, float v1)
	{
		glUniform2f(GetUniformLocation(name), v0, v1);
	}

	void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
	{
		glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
	}

	void Shader::SetUniform2fv(const std::string& name, const glm::vec2& vector)
	{
		glUniform2fv(GetUniformLocation(name), 1, &vector.x);
	}

	void Shader::SetUniform3fv(const std::string& name, const glm::vec3& vector)
	{
		glUniform3fv(GetUniformLocation(name), 1, &vector.x);
	}

	void Shader::SetUniform4fv(const std::string& name, const glm::vec4& vector)
	{
		glUniform4fv(GetUniformLocation(name), 1, &vector.x);
	}

	void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
	{
		// Raw reference to matrix 
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);

		// glm::value_ptr lets you drop the weird syntax for a matrix reference
		//glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
	}
	
	void Shader::LoadFromGLSLTextFiles(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
		std::string vertexSource = ReadFileAsString(vertexShaderPath);
		std::string fragmentSource = ReadFileAsString(fragmentShaderPath);

		GLuint program = glCreateProgram();
		int glShaderIDIndex = 0;
			
		GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
		glAttachShader(program, vertexShader);
		GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			LOG("{0}");
			// HZ_CORE_ASSERT(false, "Shader link failure!");
		}
		
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		m_RendererID = program;
	}

	GLuint Shader::ObjFromGLSLTextFiles(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	{
		std::string vertexSource = ReadFileAsString(vertexShaderPath);
		std::string fragmentSource = ReadFileAsString(fragmentShaderPath);

		GLuint program = glCreateProgram();
		int glShaderIDIndex = 0;

		GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
		glAttachShader(program, vertexShader);
		GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			LOG("{0}");
			// HZ_CORE_ASSERT(false, "Shader link failure!");
		}

		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return program;
	}

}