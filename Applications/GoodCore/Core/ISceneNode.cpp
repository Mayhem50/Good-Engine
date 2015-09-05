#include "ISceneNode.h"

#include <utility>
#include <random>

#include <glm/gtc/matrix_transform.hpp>

using namespace Good;

ISceneNode::ISceneNode(const std::string& name, const ISceneNodePtr& parent):
_name(name), _parent(parent), _inherit(true)
{
	if (_name.empty())
		_name = NameTools::nameGenerator();

	_scale = glm::vec3(1.0);
	_position = glm::vec3(0.0);
	_orientation = glm::normalize(_orientation);
}

bool ISceneNode::addChild(const ISceneNodePtr& child)
{
	std::pair<std::string, ISceneNodePtr> pair(child->getName(), child);
	std::pair<ISceneNodeList::iterator, bool> ret = _childs.insert(pair);

	return ret.second;
}

bool ISceneNode::removeChild(const ISceneNodePtr& child)
{
	if(_childs.erase(child->getName()) == 1)
		return true;
	else
		return false;
}

bool ISceneNode::removeAllChilds()
{
	std::map<std::string, ISceneNodePtr>::iterator it = _childs.begin();
	bool ret = true;

	for(; it != _childs.end(); ++it)
	{
		it->second->removeAllChilds();
		ret &= (bool)_childs.erase(it->first);
	}

	return ret;
}

unsigned int ISceneNode::childsCount() const
{
	return _childs.size();
}

ISceneNodePtr ISceneNode::getChild(const std::string& name)
{
	ISceneNodeList::iterator it = _childs.find(name);

	if(it != _childs.end())
		return it->second;
	else
		return nullptr;
}

ISceneNodePtr ISceneNode::getParent() const
{
	return _parent;
}

void ISceneNode::translate(const glm::vec3& direction, TRANSFORM_RELATIVE relativeTo)
{
	switch (relativeTo)
	{
	case Good::LOCAL:
		_position = _orientation * direction;
		break;
	case Good::PARENT:
		_position += direction;
		break;
	case Good::WORLD:
		if (_parent)
		{
			_position += (glm::inverse(_parent->derivedOrientation()) * direction) / _parent->derivedScale();
		}
		else
			_position += direction;
		break;
	default:
		break;
	}
}

void ISceneNode::translate(double x, double y, double z, TRANSFORM_RELATIVE relativeTo)
{
	glm::vec3 move(x, y, z);
	translate(move, relativeTo);
}

void ISceneNode::translate(const glm::mat3& axes, const glm::vec3& direction, TRANSFORM_RELATIVE relativeTo)
{
	glm::vec3 move = axes * direction;
	translate(move, relativeTo);
}

void ISceneNode::translate(const glm::mat3& axes, double x, double y, double z, TRANSFORM_RELATIVE relativeTo)
{

}

void ISceneNode::roll(double angle, TRANSFORM_RELATIVE relativeTo)
{
	glm::quat quaternion = glm::angleAxis((float)angle, glm::vec3(0.0, 0.0, 1.0));
	rotate(quaternion, relativeTo);
}

void ISceneNode::pitch(double angle, TRANSFORM_RELATIVE relativeTo)
{
	glm::quat quaternion = glm::angleAxis((float)angle, glm::vec3(1.0, 0.0, 0.0));
	rotate(quaternion, relativeTo);
}

void ISceneNode::yaw(double angle, TRANSFORM_RELATIVE relativeTo)
{
	glm::quat quaternion = glm::angleAxis((float)angle, glm::vec3(0.0, 1.0, 0.0));
	rotate(quaternion, relativeTo);
}

void ISceneNode::rotate(const glm::vec3& axis, double angle, TRANSFORM_RELATIVE relativeTo)
{
	glm::quat quaternion = glm::angleAxis((float)angle, axis);
	rotate(quaternion, relativeTo);
}

void ISceneNode::rotate(const glm::quat& quaternion, TRANSFORM_RELATIVE relativeTo)
{
	glm::quat qnorm = quaternion;
	glm::normalize(qnorm);

	switch (relativeTo)
	{
	case Good::LOCAL:
		_orientation = _orientation * qnorm;
		break;
	case Good::PARENT:
		_orientation = qnorm * _orientation;
		break;
	case Good::WORLD:
		_orientation = _orientation * glm::inverse(derivedOrientation()) * qnorm * derivedOrientation();
		break;
	default:
		break;
	}
}

void ISceneNode::setPosition(const glm::vec3& position)
{
	_position = position;
}

void ISceneNode::setPosition(double x, double y, double z)
{
	setPosition(glm::vec3(x, y, z));
}

glm::vec3 ISceneNode::position() const
{
	return _position;
}

void ISceneNode::setScale(const glm::vec3& scale)
{
	_scale = scale;
}

void ISceneNode::setScale(double x, double y, double z)
{
	setScale(glm::vec3(x, y, z));
}

glm::vec3 ISceneNode::scale() const
{
	return _scale;
}

void ISceneNode::setOrientation(const glm::quat& quaternion)
{
	_orientation = quaternion;
}

void ISceneNode::setOrientation(double w, double x, double y, double z)
{
	setOrientation(glm::quat(w, x, y, z));
}

glm::quat ISceneNode::orientation() const
{
	return _orientation;
}

glm::mat4 ISceneNode::localMatrix() const
{
	glm::mat4 orientationMatrix = glm::mat4_cast(_orientation);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0), _scale);
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0), _position);

	return translationMatrix * orientationMatrix * scaleMatrix;
}

glm::vec3 ISceneNode::derivedPosition()
{
	updateFromParent();
	return _derivedPosition;
}

glm::vec3 ISceneNode::derivedScale()
{
	updateFromParent();
	return _derivedScale;
}

glm::quat ISceneNode::derivedOrientation()
{
	updateFromParent();
	return _derivedOrientation;
}

void ISceneNode::updateFromParent()
{
	if (_parent)
	{
		const glm::quat parentOrientation = _parent->derivedOrientation();
		if (_inherit)
		{
			_derivedOrientation = parentOrientation * _orientation;
		}
		else
		{
			_derivedOrientation = _orientation;
		}

		const glm::vec3 parentScale = _parent->derivedScale();
		if (_inherit)
		{
			_derivedScale = parentScale * _scale;
		}
		else
		{
			_derivedScale = _scale;
		}

		_derivedPosition = parentOrientation * parentScale * _position;
		_derivedPosition += _parent->derivedPosition();
	}
	else
	{
		_derivedOrientation = _orientation;
		_derivedPosition = _position;
		_derivedScale = _scale;
	}
}

std::string ISceneNode::getName()
{
	return _name;
}

std::string NameTools::nameGenerator()
{
	std::random_device generator;
	std::uniform_int_distribution<int> sizeRand(10, 20);

	int nameLenght = sizeRand(generator);
	char* name = new char[nameLenght];

	memset(name, 0, nameLenght);

	for (int idx = 0; idx < nameLenght - 1; ++idx)
	{
		std::uniform_int_distribution<int> asciiPart(1, 3);

		int part = asciiPart(generator);
		int begin = 0;
		int end = 0;

		switch (part)
		{
		default:
		case 1:
			begin = 48;
			end = 57;
			break;
		case 2:
			begin = 65;
			end = 90;
			break;
		case 3:
			begin = 97;
			end = 122;
			break;
		}

		std::uniform_int_distribution<int> letterChoose(begin, end);
		name[idx] = letterChoose(generator);
	}

	name[nameLenght] = '\0';

	return std::string(name);
}