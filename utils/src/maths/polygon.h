/*****************************************************************\
           __
          / /
		 / /                     __  __
		/ /______    _______    / / / / ________   __       __
	   / ______  \  /_____  \  / / / / / _____  | / /      / /
	  / /      | / _______| / / / / / / /____/ / / /      / /
	 / /      / / / _____  / / / / / / _______/ / /      / /
	/ /      / / / /____/ / / / / / / |______  / |______/ /
   /_/      /_/ |________/ / / / /  \_______/  \_______  /
                          /_/ /_/                     / /
			                                         / /
		       High Level Game Framework            /_/

  ---------------------------------------------------------------

  Copyright (c) 2007-2011 - Rodrigo Braz Monteiro.
  This file is subject to the terms of halley_license.txt.

\*****************************************************************/


#pragma once

#include <vector>
#include "vector2d.h"
#include "aabb.h"

namespace Halley {

	typedef Vector2f Vertex;
	typedef std::vector<Vertex> VertexList;

	class Polygon {
	public:
		Polygon();
		Polygon(const VertexList& vertices, Vertex origin=Vertex());

		static Polygon makePolygon(Vector2f origin, float w, float h);

		bool isPointInside(const Vector2f &point) const;
		bool overlaps(const Polygon &param,Vector2f *translation=NULL,Vector2f *collisionPoint=NULL) const;

		void setVertices(const VertexList& vertices);
		void setOrigin(const Vertex& _origin) { origin = _origin; }
		const VertexList& getVertices() const { return vertices; }
		const Vertex& getOrigin() const { return origin; }
		void rotate(Angle<float> angle);
		void rotateAndScale(Angle<float> angle, Vector2f scale);
		bool isClockwise() const;
		float getRadius() const;

	private:
		float outerRadius;
		VertexList vertices;
		Vertex origin;
		AABB aabb;

		void project(const Vector2f &axis,float &min,float &max) const;
		void unproject(const Vector2f &axis,const float point,std::vector<Vector2f> &ver) const;
		void realize();
	};
}
