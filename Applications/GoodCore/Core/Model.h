#pragma once

#include "GoodFoundation.h"
#include "Vertex.h"

#include <vector>

namespace Good
{
	class GOOD_DLL Model
	{
	public:
		Model(const std::vector<VertexPtr>& list);
		void setVerticesList(const std::vector<VertexPtr>& list);
		std::vector<VertexPtr> vertices() const;

	private:
		std::vector<VertexPtr> _verticesList;
	};

	typedef std::shared_ptr<Model> ModelPtr;
}