#pragma once
#include<string>
#include<unordered_map>
//hashmap or hashtable
struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};
class Shader
{
private:
	std::unordered_map<std::string, int> m_UniformLocationCache;
	std::string m_filepath;
	unsigned int m_RendererID;
public:
	Shader(const std::string& filepath);
	~Shader();
	void Bind() const;
	void UnBind() const;
	//set uniforms
	void SetUniform4f(const std::string& name,float v0, float v1, float v3, float v4);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform1i(const std::string& name, int value);
private:
	
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	ShaderProgramSource ParseShader(const std::string filepath);
	int GetUniformLocation(const std :: string & name);
};
