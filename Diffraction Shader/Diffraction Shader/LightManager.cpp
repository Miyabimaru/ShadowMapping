#include "LightManager.h"



LightManager::LightManager()
{
	for (int i = 0; i < POINT_LIGHTS_COUNT; i++)
	{
		_pointLights[i] = nullptr;
	}
}


LightManager::~LightManager()
{
	for (int i = 0; i < POINT_LIGHTS_COUNT; i++)
	{
		if (_pointLights[i] != nullptr)
			delete _pointLights[i];
		_pointLights[i] = nullptr;
	}
}

void LightManager::Initialise(IShader * shader)
{
	for (int i = 0; i < POINT_LIGHTS_COUNT; i++)
	{
		if (_pointLights[i] == nullptr)
			break;
		_pointLights[i]->Initialise(shader);
	}
}

void LightManager::Draw(IShader * shader, glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
	for (int i = 0; i < POINT_LIGHTS_COUNT; i++)
	{
		if (_pointLights[i] == nullptr)
			break;
		_pointLights[i]->Draw(shader, model, view, projection);
	}
}

int LightManager::getPointLightsCount()
{
	for (int i = 0; i < POINT_LIGHTS_COUNT; i++)
		if (_pointLights[i] == nullptr)
			return i;
	return POINT_LIGHTS_COUNT;
}

void LightManager::addPointLight(glm::vec4 p, glm::vec3 la, glm::vec3 ld, glm::vec3 ls)
{
	GLuint light_id = getPointLightsCount();
	if (light_id < POINT_LIGHTS_COUNT)
		_pointLights[light_id] = new PointLight(p, la, ld, ls, light_id);
}
