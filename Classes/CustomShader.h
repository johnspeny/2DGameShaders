#pragma once

#include "cocos2d.h"
#include "renderer/backend/Device.h"

class CustomShader
{
private:
	static std::string defaultVertex;
	int currentTextureSlot;
	std::map<std::string, int> textureToSlot;

public:
	CustomShader(const std::string& vertexShader, const std::string& fragShader);
	~CustomShader();
	
	cocos2d::backend::Program* program;
	cocos2d::backend::ProgramState* programState;


	static CustomShader* createWithFragmentShader(const std::string& fragShader);
	static CustomShader* createWithVertexnFragment(const std::string& vertexShader, const std::string& fragShader);

	/*template <typename T>
	void setUniform(std::string uniform, T value);*/

	template<typename T>
	inline void setUniform(std::string uniform, T value)
	{
		auto uniformLocation = programState->getUniformLocation(uniform);
		programState->setUniform(uniformLocation, &value, sizeof(value));
	}

	void setUniform(std::string uniform, cocos2d::Texture2D* value);
		
};



class CustomShaderManager
{
public:
	CustomShaderManager();
	~CustomShaderManager();

	static CustomShaderManager* getInstance();
	friend CustomShader;

	void updateShaderTime();

private:
	std::vector<CustomShader*> shaders;


};




