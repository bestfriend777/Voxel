#pragma once

#include <string>

#include <glad/glad.h>
#include <GLCore.h>

namespace GLUtils {

	class Shader
	{
	public:
		Shader() = default;
		Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		~Shader();

		GLuint GetRendererID() { return m_RendererID; }
		static Shader* FromGLSLTextFiles(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);


		// Set uniforms
		void SetUniform1i(const std::string& name, int v0);
		void SetUniform1iv(const std::string& name, int count, int* source);
		void SetUniform1f(const std::string& name, float v0);
		void SetUniform2f(const std::string& name, float v0, float v1);
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniform2fv(const std::string& name, const glm::vec2& vector);
		void SetUniform3fv(const std::string& name, const glm::vec3& vector);
		void SetUniform4fv(const std::string& name, const glm::vec4& vector);
		void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	private:

		void LoadFromGLSLTextFiles(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		GLuint ObjFromGLSLTextFiles(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		GLuint CompileShader(GLenum type, const std::string& source);
		int GetUniformLocation(const std::string& name);

	private:
		GLuint m_RendererID;
		std::unordered_map<std::string, int> m_UniformLocationCache;
	};

}