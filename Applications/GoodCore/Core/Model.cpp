#include "Model.h"

using namespace Good;

Model::Model(const std::vector<VertexPtr>& list):
_verticesList(list)
{

}

void Model::setVerticesList(const std::vector<VertexPtr>& list)
{
	_verticesList = list;
}

std::vector<VertexPtr> Model::vertices() const
{
	return _verticesList;
}