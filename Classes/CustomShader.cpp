#include "CustomShader.h"


std::string CustomShader::defaultVertex = R"(
attribute vec4 a_position;
    attribute vec2 a_texCoord;
    attribute vec4 a_color;

    uniform mat4 u_MVPMatrix;

    #ifdef GL_ES
    varying lowp vec4 cc_FragColor;
    varying mediump vec2 cc_FragTexCoord1;
    #else
    varying vec4 cc_FragColor;
    varying vec2 cc_FragTexCoord1;
    #endif

    void main()
    {
        gl_Position = u_MVPMatrix * a_position;
        cc_FragColor = a_color;
        cc_FragTexCoord1 = a_texCoord;
    }
)";


CustomShader::CustomShader(const std::string& vertexShader, const std::string& fragShader)
{
	// add vertex shader and frag shader in program
	program = cocos2d::backend::Device::getInstance()->newProgram(vertexShader, fragShader);
	programState = new cocos2d::backend::ProgramState(program);

	// add this created shader to the vector container
	CustomShaderManager::getInstance()->shaders.push_back(this);
}

CustomShader::~CustomShader()
{
	//cleanup
	delete programState;
	delete program;

	auto& vec = CustomShaderManager::getInstance()->shaders;
	vec.erase(std::remove(vec.begin(), vec.end(), this), vec.end());
}

CustomShader* CustomShader::createWithFragmentShader(const std::string& fragShader)
{
	auto fragPath = cocos2d::FileUtils::getInstance()->getStringFromFile(fragShader);

	return new CustomShader(defaultVertex, fragPath);
}

CustomShader* CustomShader::createWithVertexnFragment(const std::string& vertexShader, const std::string& fragShader)
{
	//custom vertex shader
	auto vertSource = cocos2d::FileUtils::getInstance()->getStringFromFile(vertexShader);

	//custom fragment shader
	auto fragSourceRaw = cocos2d::FileUtils::getInstance()->getStringFromFile(fragShader);

	return new CustomShader(vertSource, fragSourceRaw);
}

void CustomShader::setUniform(std::string uniform, cocos2d::Texture2D* value)
{
    //determine texture slot
    int slot = currentTextureSlot;
    if (textureToSlot.count(uniform) > 0)
    {
        //texture already has a slot
        slot = textureToSlot[uniform];
    }
    else
    {
        //new texture
        textureToSlot[uniform] = slot;
        currentTextureSlot++;
    }

    auto uniformLocation = programState->getUniformLocation(uniform);
    programState->setTexture(uniformLocation, slot, value->getBackendTexture());
}

CustomShaderManager::CustomShaderManager()
{
}

CustomShaderManager::~CustomShaderManager()
{
}

CustomShaderManager* CustomShaderManager::getInstance()
{
	auto instance = new CustomShaderManager();
	return instance;
}

void CustomShaderManager::updateShaderTime()
{
    for (auto& shader : shaders)
    {
        // update uniform value of shader 
    }
}
