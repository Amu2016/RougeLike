#pragma once
#ifndef _Path_H_
#define _Path_H_

#include<list>
#include"stdafx.h"

class Path {
public:
	Path() {}

	void addWayPoint(Vec2 point) { m_WayPoints.push_back(point); }

	Vec2 currentWayPoint() { return *curWayPoint; }

	bool setNextWayPoint() {
		if (++curWayPoint == m_WayPoints.end()) {
			return true;
		}
		return false;
	}

	void setCurrWayPoint(){ curWayPoint = m_WayPoints.begin(); }

	void set(std::list<Vec2> list){ m_WayPoints = list; curWayPoint = m_WayPoints.begin(); }
	void set(const Path* path) { m_WayPoints = path->getPath(); curWayPoint = m_WayPoints.begin(); }

	void clear() { m_WayPoints.clear(); }

	bool Finished() { return !(curWayPoint != m_WayPoints.end()); }

	std::list<Vec2> getPath()const { return m_WayPoints; }

private:
	std::list<Vec2> m_WayPoints;
	std::list<Vec2>::iterator curWayPoint;
};

#endif // !_Path_H_
