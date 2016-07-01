#include "Aabb.h"


bool Aabb::Collides(const Aabb& box) const {
	if (m_min_x > box.m_max_x || m_max_x < box.m_min_x
		|| m_min_y > box.m_max_y || m_max_y < box.m_min_y) {
		return false;
	}
	return true;
}

bool Aabb::IsOver(const Aabb & box) const {
	bool b = Collides(box);
	return b
		&& m_min_y < box.m_max_y
		&& box.m_max_y < m_max_y;
}

bool Aabb::IsUnder(const Aabb & box) const {
	return box.IsOver(*this);
}

bool Aabb::IsOnLeftOf(const Aabb & box) const {
	return Collides(box)
		&& m_min_x < box.m_min_x
		&& box.m_min_x < m_max_x;
}

bool Aabb::IsOnRightOf(const Aabb & box) const {
	return box.IsOnLeftOf(*this);
}