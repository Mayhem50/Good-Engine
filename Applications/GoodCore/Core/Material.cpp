#include "Material.h"

#include <glm/gtc/type_ptr.hpp>
using namespace Good;

const GLchar* Material::UNIFORM_BLOCK_NAMES = 
{
	"MatrerialDataBlock"
};

Material::Material(ShaderProgramPtr vertexShader, ShaderProgramPtr fragmentShader, ShaderProgramPtr geometryShader, ShaderProgramPtr tessControlShader, ShaderProgramPtr tessEvalShader) :
_vertexShader(vertexShader),
_fragmentShader(fragmentShader),
_geometryShader(geometryShader),
_tessControlShader(tessControlShader),
_tessEvalShader(tessEvalShader)
{
	_data.diffuseColor = glm::vec4(1.0, 0.0, 0.0, 0.0);
	_data.specularColor = glm::vec4(1.0);
	_data.emissiveColor = glm::vec4(0.0);

	_data.metalic = 200;
	_data.roughness = 0.0;
	_data.opacity = 1.0;
	_data.refraction = 1.0;

	_alphaMap = 0;
	_normalMap = 0;

	glGenBuffers(1, &_dataUniformBlockID);
	glBindBuffer(GL_UNIFORM_BUFFER, _dataUniformBlockID);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(Data), NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Material::use()
{
	if (_vertexShader)
		_vertexShader->use();

	if (_fragmentShader)
		_fragmentShader->use();

	if (_geometryShader)
		_geometryShader->use();

	if (_tessControlShader && _tessEvalShader)
	{
		_tessControlShader->use();
		_tessEvalShader->use();
	}

	_updateUniforms();
}

ShaderProgramPtr Material::vertexShader() const
{
	return _vertexShader;
}

ShaderProgramPtr Material::fragmentShader() const
{
	return _fragmentShader;
}

void Material::_updateUniforms()
{
	glBindBufferBase(GL_UNIFORM_BUFFER, 10, _dataUniformBlockID);
	Data *materialData = (Data*)glMapBufferRange(GL_UNIFORM_BUFFER, 0, sizeof(Data), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
	*materialData = _data;
	glUnmapBuffer(GL_UNIFORM_BUFFER);
}