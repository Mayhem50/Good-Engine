#pragma once

#include "GL/glew.h"

#include <string>
#include <memory>

class CubeMap
{
public:
	CubeMap(const std::string& file = "../HDR/default.jpg", int width = 512, int height = 512, int mipmap = 0);
	~CubeMap();

	GLuint id() const;
	void bind(int textureUnit = 0);
	void unbind();

private:
	void _init();

	GLuint _id;

	std::string _fileName;
	int _width;
	int _height;
	int _mipmap;
};

typedef std::shared_ptr<CubeMap> CubeMapPtr;
