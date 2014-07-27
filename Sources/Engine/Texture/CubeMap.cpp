#include "CubeMap.h"

CubeMap::CubeMap(const std::string& file, int width, int height, int mipmap):
	_fileName(file),
	_width(width),
	_height(height),
	_mipmap(mipmap)
{
	_init();
}

CubeMap::~CubeMap()
{

}

GLuint CubeMap::id() const
{
	return _id;
}

void CubeMap::bind(int textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _id);
}

void CubeMap::unbind()
{	
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeMap::_init()
{
	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _id);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0); 
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 0);
	
	//glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA32F, delta, delta, 0, GL_BGRA, GL_UNSIGNED_BYTE, XP.bits());
	//glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA32F, delta, delta, 0, GL_BGRA, GL_UNSIGNED_BYTE, XN.bits());
	//glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA32F, delta, delta, 0, GL_BGRA, GL_UNSIGNED_BYTE, YN.bits());
	//glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA32F, delta, delta, 0, GL_BGRA, GL_UNSIGNED_BYTE, YP.bits());
	//glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA32F, delta, delta, 0, GL_BGRA, GL_UNSIGNED_BYTE, ZN.bits());
	//glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA32F, delta, delta, 0, GL_BGRA, GL_UNSIGNED_BYTE, ZP.bits());

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);	

	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}
